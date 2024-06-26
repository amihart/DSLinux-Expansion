/* lkmain.c */

/*
 * (C) Copyright 1989-1995
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 *
 * 31-Oct-97 JLH:
 *           - add jflag and jfp to control NoICE output file genration
 *  3-Nov-97 JLH: 
 *           - use a_type == 0 as "virgin area" flag: set == 1 if -b
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aslink.h"

#ifdef WIN32T
#include <time.h>

void Timer(int action, char * message)
{
	static double start, end, total=0.0;
    static const double secs_per_tick = 1.0 / CLOCKS_PER_SEC;

    if(action==0) start=clock()*secs_per_tick;
    else if(action==1)
    {
    	end=clock() * secs_per_tick;
		printf("%s \t%f seconds.\n", message, (end-start));
		total+=end-start;
    }
    else
    {
		printf("Total time: \t%f seconds.\n", total);
		total=0.0;
    }
}
#endif

/* yuck - but including unistd.h causes problems on Cygwin by redefining
 * Addr_T.
 */
extern int unlink(const char *);

/*)Module	lkmain.c
 *
 *	The module lkmain.c contains the functions which
 *	(1) input the linker options, parameters, and specifications
 *	(2) perform a two pass link
 *	(3) produce the appropriate linked data output and/or
 *	    link map file and/or relocated listing files.
 *
 *	lkmain.c contains the following functions:
 *		FILE *	afile(fn,ft,wf)
 *		VOID	bassav()
 *		VOID	gblsav()
  *		VOID	link_main()
 *		VOID	lkexit()
 *		VOID	main(argc,argv)
 *		VOID	map()
 *		int	parse()
 *		VOID	setbas()
 *		VOID	setgbl()
 *		VOID	usage()
 *
 *	lkmain.c contains the following local variables:
 *		char *	usetext[]	array of pointers to the
 *					command option tect lines
 *
 */

/*JCF: 	Creates some of the default areas so they are allocated in the right order.*/
void Areas51 (void)
{
	char * rel[]={
		"XH",
		"H 7 areas 0 global symbols",
		"A _CODE size 0 flags 0",		/*Each .rel has one, so...*/
		"A REG_BANK_0 size 0 flags 4",	/*Register banks are overlayable*/
		"A REG_BANK_1 size 0 flags 4",
		"A REG_BANK_2 size 0 flags 4",
		"A REG_BANK_3 size 0 flags 4",
		"A BSEG size 0 flags 80",		/*BSEG must be just before BITS*/
		"A BSEG_BYTES size 0 flags 0",	/*Size will be obtained from BSEG in lnkarea()*/
		""
	};
	int j;

	for (j=0; rel[j][0]!=0; j++)
	{
		ip=rel[j];
		link_main();
	}
	
	/*Set the start address of the default areas:*/
	for(ap=areap; ap; ap=ap->a_ap)
	{
		/**/ if (!strcmp(ap->a_id, "REG_BANK_0")) { ap->a_addr=0x00; ap->a_type=1; }
		else if (!strcmp(ap->a_id, "REG_BANK_1")) { ap->a_addr=0x08; ap->a_type=1; }
		else if (!strcmp(ap->a_id, "REG_BANK_2")) { ap->a_addr=0x10; ap->a_type=1; }
		else if (!strcmp(ap->a_id, "REG_BANK_3")) { ap->a_addr=0x18; ap->a_type=1; }
		else if (!strcmp(ap->a_id, "BSEG_BYTES")) { ap->a_addr=0x20; ap->a_type=1; }
	}
}

/*)Function	VOID	main(argc,argv)
 *
 *		int	argc		number of command line arguments + 1
 *		char *	argv[]		array of pointers to the command line
 *					arguments
 *
 *	The function main() evaluates the command line arguments to
 *	determine if the linker parameters are to input through 'stdin'
 *	or read from a command file.  The functiond getline() and parse()
 *	are to input and evaluate the linker parameters.  The linking process
 *	proceeds by making the first pass through each .rel file in the order
 *	presented to the linker.  At the end of the first pass the setbase(),
 *	lnkarea(), setgbl(), and symdef() functions are called to evaluate
 *	the base address terms, link all areas, define global variables,
 *	and look for undefined symbols.  Following these routines a linker
 *	map file may be produced and the linker output files may be opened.
 *	The second pass through the .rel files will output the linked data
 *	in one of the four supported formats.
 *
 *	local variables:
 *		char *	p		pointer to an argument string
 *		int	c		character from argument string
 *		int	i		loop counter
 *
 *	global variables:
 *						text line in ib[]
 *		lfile	*cfp		The pointer *cfp points to the
 *						current lfile structure
 *		char	ctype[]		array of character types, one per
 *						ASCII character
 *		lfile	*filep			The pointer *filep points to the
 *						beginning of a linked list of
 *						lfile structures.
 *		head	*hp		Pointer to the current
 *						head structure
 *		char	ib[NINPUT]	.rel file text line
 *		char	*ip		pointer into the .rel file
 *		lfile	*linkp		pointer to first lfile structure
 *						containing an input .rel file
 *						specification
 *		int	lkerr		error flag
 *		int	mflag		Map output flag
 *		int	oflag		Output file type flag
 *		FILE	*ofp		Output file handle
 *						for word formats
 *		FILE	*ofph		Output file handle
 *						for high byte format
 *		FILE	*ofpl		Output file handle
 *						for low byte format
 *		int	pass		linker pass number
 *		int	pflag		print linker command file flag
 *		int	radix		current number conversion radix
 *		FILE	*sfp		The file handle sfp points to the
 *						currently open file
 *		lfile	*startp		asmlnk startup file structure
 *		FILE *	stdin		c_library
 *		FILE *	stdout		c_library
 *
 *	functions called:
 *		FILE *	afile()		lkmain.c
 *		int	fclose()	c_library
 *		int	fprintf()	c_library
 *		int	getline()	lklex.c
 *		VOID	library()	lklibr.c
 *		VOID	link_main()	lkmain.c
 *		VOID	lkexit()	lkmain.c
 *		VOID	lnkarea()	lkarea.c
 *		VOID	map()		lkmain.c
 *		VOID	new()		lksym.c
 *		int	parse()		lkmain.c
 *		VOID	reloc()		lkreloc.c
 *		VOID	search()	lklibr.c
 *		VOID	setbas()	lkmain.c
 *		VOID	setgbl()	lkmain.c
 *		VOID	symdef()	lksym.c
 *		VOID	usage()		lkmain.c
 *
 *	side effects:
 *		Completion of main() completes the linking process
 *		and may produce a map file (.map) and/or a linked
 *		data files (.ihx or .s19) and/or one or more
 *		relocated listing files (.rst).
 */

int
main(argc, argv)
char *argv[];
{
	register char *p;
	register int c, i;

#ifdef WIN32T
    Timer(0, "");
#endif

	startp = (struct lfile *) new (sizeof (struct lfile));

	pflag = 1;
	for (i=1; i<argc; ++i) {
		p = argv[i];
		if (*p == '-') {
			while (ctype[c = *(++p)] & LETTER) {
				switch(c) {

				case 'c':
				case 'C':
					startp->f_type = F_STD;
					break;

				case 'f':
				case 'F':
					startp->f_type = F_LNK;
					break;
	
				case 'n':
				case 'N':
					pflag = 0;
					break;

				case 'p':
				case 'P':
					pflag = 1;
					break;

				default:
					usage();
				}
			}
		} else {
			if (startp->f_type == F_LNK) {
				startp->f_idp = p;
			}
		}
	}
       if (startp->f_type == 0)
		usage();
	if (startp->f_type == F_LNK && startp->f_idp == NULL)
		usage();

	cfp = NULL;
	sfp = NULL;
	filep = startp;
	while (1) {
		ip = ib;
		if (getline() == 0)
			break;
		if (pflag && sfp != stdin)
			fprintf(stdout, "%s\n", ip);
               if (*ip == '\0' || parse())
			break;
	}

	if (sfp) {
	    fclose(sfp);
	    sfp = NULL;
	}

	if (linkp == NULL)
		usage();

	syminit();
	
	if (dflag){
	    //dfp = afile("temp", "cdb", 1);
		SaveLinkedFilePath(linkp->f_idp); //Must be the first one... 
		dfp = afile(linkp->f_idp,"cdb",1); //JCF: Nov 30, 2002
	    if (dfp == NULL) 
		lkexit(1);
	}

	for (pass=0; pass<2; ++pass) {
		cfp = NULL;
		sfp = NULL;
		filep = linkp;
		hp = NULL;
		radix = 10;
		
		Areas51(); /*JCF: Create the default 8051 areas in the right order*/

		while (getline()) {
			ip = ib;

                        /* pass any "magic comments" to NoICE output */
                        if ((ip[0] == ';') && (ip[1] == '!') && jfp) {
                        	fprintf( jfp, "%s\n", &ip[2] );
                        }
			link_main();
		}
		if (pass == 0) {
			/*
			 * Search libraries for global symbols
			 */
			search();
			/*
			 * Set area base addresses.
			 */
			setbas();
			/*
			 * Link all area addresses.
			 */
			lnkarea();
			/*
			 * Process global definitions.
			 */
			setgbl();
			/*
			 * Check for undefined globals.
			 */
			symdef(stderr);

			/* Open NoICE output file if requested */
			if (jflag) {
				jfp = afile(linkp->f_idp, "NOI", 1);
				if (jfp == NULL) {
					lkexit(1);
				}
			}

			/*
			 * Output Link Map if requested,
			 * or if NoICE output requested (since NoICE
                         * file is generated in part by map() processing)
			 */
			if (mflag || jflag)
				map();

			if (sflag) /*JCF: memory usage summary output*/
				if(summary(areap))lkexit(1);

			if (iram_size)
				iramcheck();

			/*
			 * Open output file
			 */
			if (oflag == 1) {
				ofp = afile(linkp->f_idp, "ihx", 1);
				if (ofp == NULL) {
					lkexit(1);
				}
				/* include NoICE command to load hex file */
        	                if (jfp) fprintf( jfp, "LOAD %s.IHX\n", linkp->f_idp );

			} else
			if (oflag == 2) {
				ofp = afile(linkp->f_idp, "S19", 1);
				if (ofp == NULL) {
					lkexit(1);
				}
				/* include NoICE command to load hex file */
        	                if (jfp) fprintf( jfp, "LOAD %s.S19\n", linkp->f_idp );
			}
		} else {
			/*
			 * Link in library files
			 */
			library();
			reloc('E');
		}
	}
	//JCF:
	CreateAOMF51();

#ifdef WIN32T
    Timer(1, "Linker execution time");
#endif

	lkexit(lkerr);
	return 0;
}

/*)Function	VOID	lkexit(i)
 *
 *			int	i	exit code
 *
 *	The function lkexit() explicitly closes all open
 *	files and then terminates the program.
 *
 *	local variables:
 *		none
 *
 *	global variables:
 *		FILE *	mfp		file handle for .map
 *		FILE *	ofp		file handle for .ihx/.s19
 *		FILE *	rfp		file hanlde for .rst
 *		FILE *	sfp		file handle for .rel
 *		FILE *	tfp		file handle for .lst
 *
 *	functions called:
 *		int	fclose()	c_library
 *		VOID	exit()		c_library
 *
 *	side effects:
 *		All files closed. Program terminates.
 */

VOID
lkexit(i)
int i;
{
	if (mfp != NULL) fclose(mfp);
	if (jfp != NULL) fclose(jfp);
	if (ofp != NULL) fclose(ofp);
	if (rfp != NULL) fclose(rfp);
	if (sfp != NULL) fclose(sfp);
	if (tfp != NULL) fclose(tfp);
	if (dfp != NULL) fclose(dfp);
	/*if (dfp != NULL)
	    FILE *xfp = afile(linkp->f_idp,"cdb",1);
	    dfp = freopen("temp.cdb","r",dfp);
	    copyfile(xfp,dfp);
	    fclose(xfp);
	    fclose(dfp);
	    unlink("temp.cdb");
	}*/
	exit(i);
}

/*)Function	link_main()
 *
 *	The function link_main() evaluates the directives for each line of
 *	text read from the .rel file(s).  The valid directives processed
 *	are:
 *		X, D, Q, H, M, A, S, T, R, and P.
 *
 *	local variables:
 *		int	c		first non blank character of a line
 *
 *	global variables:
 *		head	*headp		The pointer to the first
 *						head structure of a linked list
 *		head	*hp		Pointer to the current
 *						head structure
 *		int	pass		linker pass number
 *		int	radix		current number conversion radix
 *
 *	functions called:
 *		char	endline()	lklex.c
 *		VOID	module()	lkhead.c
 *		VOID	newarea()	lkarea.c
 *		VOID	newhead()	lkhead.c
 *		sym *	newsym()	lksym.c
 *		VOID	reloc()		lkreloc.c
 *
 *	side effects:
 *		Head, area, and symbol structures are created and
 *		the radix is set as the .rel file(s) are read.
 */

VOID
link_main()
{
	register int c;

	if ((c=endline()) == 0) { return; }
	switch (c) {

    case 'O': /*For some important sdcc options*/
        if (pass == 0)
        {
            if(strlen(sdccopt)==0)
            {
                strcpy(sdccopt, &ip[1]);
                strcpy(sdccopt_module, curr_module);
            }
            else
            {
                if(strcmp(sdccopt, &ip[1])!=0)
                {
				    fprintf(stderr,
				    "?ASlink-Warning-Conflicting sdcc options:\n"
                    "   \"%s\" in module \"%s\" and\n"
                    "   \"%s\" in module \"%s\".\n",
                    sdccopt, sdccopt_module, &ip[1], curr_module);
				    lkerr++;
                }
            }
        }
		break;

	case 'X':
		radix = 16;
		break;

	case 'D':
		radix = 10;
		break;

	case 'Q':
		radix = 8;
		break;

	case 'H':
		if (pass == 0) {
			newhead();
		} else {
			if (hp == 0) {
				hp = headp;
			} else {
				hp = hp->h_hp;
			}
		}
		sdp.s_area = NULL;
		sdp.s_areax = NULL;
		sdp.s_addr = 0;
		break;

	case 'M':
		if (pass == 0)
        {
            strcpy(curr_module, &ip[1]);
			module();
        }
		break;

	case 'A':
		if (pass == 0)
			newarea();
		if (sdp.s_area == NULL) {
			sdp.s_area = areap;
			sdp.s_areax = areap->a_axp;
			sdp.s_addr = 0;
		}
		break;

	case 'S':
		if (pass == 0)
			newsym();
		break;

	case 'T':
	case 'R':
	case 'P':
		if (pass == 0)
			break;
		reloc(c);
		break;

	default:
		break;
	}
	if (c == 'X' || c == 'D' || c == 'Q') {
		if ((c = get()) == 'H') {
			hilo = 1;
		} else
		if (c == 'L') {
			hilo = 0;
		}
	}
}


/*)Function	VOID	map()
 *
 *	The function map() opens the output map file and calls the various
 *	routines to
 *	(1) output the variables in each area,
 *	(2) list the files processed with module names,
 *	(3) list the libraries file processed,
 *	(4) list base address definitions,
 *	(5) list global variable definitions, and
 *	(6) list any undefined variables.
 *
 *	local variables:
 *		int		i		counter
 *		head *	hdp		pointer to head structure
 *		lbfile *lbfh		pointer to library file structure
 *
 *	global variables:
 *		area	*ap		Pointer to the current
 *						area structure
 *		area	*areap		The pointer to the first
 *						area structure of a linked list
 *		base	*basep		The pointer to the first
 *						base structure
 *		base	*bsp		Pointer to the current
 *						base structure
 *		lfile	*filep			The pointer *filep points to the
 *						beginning of a linked list of
 *						lfile structures.
 *		globl	*globlp		The pointer to the first
 *						globl structure
 *		globl	*gsp		Pointer to the current
 *						globl structure
 *		head	*headp		The pointer to the first
 *						head structure of a linked list
 *		lbfile	*lbfhead	The pointer to the first
 *					lbfile structure of a linked list
 *		lfile	*linkp		pointer to first lfile structure
 *						containing an input REL file
 *						specification
 *		int	lop		current line number on page
 *		FILE	*mfp		Map output file handle
 *		int	page		current page number
 *
 *	functions called:
 *		FILE *	afile()		lkmain.c
 *		int	fprintf()	c_library
 *		VOID	lkexit()	lkmain.c
 *		VOID	lstarea()	lklist.c
 *		VOID	newpag()	lklist.c
 *		VOID	symdef()	lksym.c
 *
 *	side effects:
 *		The map file is created.
 */

VOID
map()
{
	register int i;
	register struct head *hdp;
	register struct lbfile *lbfh;

	/*
	 * Open Map File
	 */
	mfp = afile(linkp->f_idp, "map", 1);
	if (mfp == NULL) {
		lkexit(1);
	}

	/*
	 * Output Map Area Lists
	 */
	page = 0;
	lop  = NLPP;
	ap = areap;
	while (ap) {
		lstarea(ap);
		ap = ap->a_ap;
	}
	/*
	 * List Linked Files
	 */
	newpag(mfp);
	fprintf(mfp, "\nFiles Linked	  [ module(s) ]\n\n");
	hdp = headp;
	filep = linkp;
	while (filep) {
		fprintf(mfp, "%-16s", filep->f_idp);
		i = 0;
		while ((hdp != NULL) && (hdp->h_lfile == filep)) {
			if (i % 5) {
			    fprintf(mfp, ", %8.8s", hdp->m_id);
			} else {
			    if (i) {
				fprintf(mfp, ",\n%20s%8.8s", "", hdp->m_id);
			    } else {
				fprintf(mfp, "	[ %8.8s", hdp->m_id);
			    }
			}
			hdp = hdp->h_hp;
			i++;
		}
		if (i)
			fprintf(mfp, " ]");
		fprintf(mfp, "\n");
		filep = filep->f_flp;
	}
	/*
	 * List Linked Libraries
	 */
	if (lbfhead != NULL) {
		fprintf(mfp,
	"\nLibraries Linked		       [   object  file   ]\n\n");
		for (lbfh=lbfhead; lbfh; lbfh=lbfh->next) {
			fprintf(mfp, "%-32s    [ %16.16s ]\n",
				lbfh->libspc, lbfh->relfil);
		}
		fprintf(mfp, "\n");
	}
	/*
	 * List Base Address Definitions
	 */
	if (basep) {
		newpag(mfp);
		fprintf(mfp, "\nUser Base Address Definitions\n\n");
		bsp = basep;
		while (bsp) {
			fprintf(mfp, "%s\n", bsp->b_strp);
			bsp = bsp->b_base;
		}
	}
	/*
	 * List Global Definitions
	 */
	if (globlp) {
		newpag(mfp);
		fprintf(mfp, "\nUser Global Definitions\n\n");
		gsp = globlp;
		while (gsp) {
			fprintf(mfp, "%s\n", gsp->g_strp);
			gsp = gsp->g_globl;
		}
	}
	fprintf(mfp, "\n\f");
	symdef(mfp);
}

/*)Function	int	parse()
 *
 *	The function parse() evaluates all command line or file input
 *	linker directives and updates the appropriate variables.
 *
 *	local variables:
 *		int	c		character value
 *		char	fid[]		file id string
 *
 *	global variables:
 *		char	ctype[]		array of character types, one per
 *						ASCII character
 *		lfile	*lfp		pointer to current lfile structure
 *						being processed by parse()
 *		lfile	*linkp		pointer to first lfile structure
 *						containing an input REL file
 *						specification
 *		int	mflag		Map output flag
 *		int	oflag		Output file type flag
 *		int	pflag		print linker command file flag
 *		FILE *	stderr		c_library
 *		int	uflag		Relocated listing flag
 *		int	xflag		Map file radix type flag
 *
 *	Functions called:
 *		VOID	addlib()	lklibr.c
 *		VOID	addpath()	lklibr.c
 *		VOID	bassav()	lkmain.c
 *		int	fprintf()	c_library
 *		VOID	gblsav()	lkmain.c
 *		VOID	getfid()	lklex.c
 *		char	getnb()		lklex.c
 *		VOID	lkexit()	lkmain.c
 *		char *	strcpy()	c_library
 *		int	strlen()	c_library
 *
 *	side effects:
 *		Various linker flags are updated and the linked
 *		structure lfile is created.
 */

int
parse()
{
	register int c;
	char fid[NINPUT];

	while ((c = getnb()) != 0) {
		if ( c == '-') {
			while (ctype[c=get()] & LETTER) {
				switch(c) {

				case 'i':
				case 'I':
					oflag = 1;
					break;

				case 's':
				case 'S':
					oflag = 2;
					break;

				case 'm':
				case 'M':
					++mflag;
					break;

				case 'y': /*JCF: memory usage summary output*/
				case 'Y':
					++sflag;
					break;

				case 'j':
				case 'J':
					jflag = 1;
					break;

				case 'u':
				case 'U':
					uflag = 1;
					break;
				case 'r':
				case 'R':
					rflag = 1;
					break;
				case 'x':
				case 'X':
					xflag = 0;
					break;

				case 'q':
				case 'Q':
					xflag = 1;
					break;

				case 'd':
				case 'D':
					xflag = 2;
					break;

				case 'e':
				case 'E':
					return(1);

				case 'n':
				case 'N':
					pflag = 0;
					break;

				case 'p':
				case 'P':
					pflag = 1;
					break;

				case 'b':
				case 'B':
					bassav();
					return(0);

				case 'g':
				case 'G':
					gblsav();
					return(0);

				case 'k':
				case 'K':
					addpath();
					return(0);

				case 'l':
				case 'L':
					addlib();
					return(0);

				case 'a':
				case 'A':
					iramsav();
					return(0);

				case 'v':
				case 'V':
					xramsav();
					return(0);

				case 'w':
				case 'W':
					codesav();
					return(0);

				case 'z':
                                case 'Z':
				        dflag = 1;					
					return(0);
				default:
					fprintf(stderr, "Invalid option\n");
					lkexit(1);
				}
			}
		} else
               if (ctype[c] & ILL) {
                       fprintf(stderr, "Invalid input");
                       lkexit(1);
               } else {
			if (linkp == NULL) {
				linkp = (struct lfile *)
					new (sizeof (struct lfile));
				lfp = linkp;
			} else {
				lfp->f_flp = (struct lfile *)
						new (sizeof (struct lfile));
				lfp = lfp->f_flp;
			}
			getfid(fid, c);
			lfp->f_idp = (char *) new (strlen(fid)+1);
			strcpy(lfp->f_idp, fid);
			lfp->f_type = F_REL;
		}
	}
	return(0);
}

/*)Function	VOID	bassav()
 *
 *	The function bassav() creates a linked structure containing
 *	the base address strings input to the linker.
 *
 *	local variables:
 *		none
 *
 *	global variables:
 *		base	*basep		The pointer to the first
 *						base structure
 *		base	*bsp		Pointer to the current
 *						base structure
 *		char	*ip		pointer into the REL file
 *						text line in ib[]
 *
 *	 functions called:
 *		char	getnb()		lklex.c
 *		VOID *	new()		lksym.c
 *		int	strlen()	c_library
 *		char *	strcpy()	c_library
 *		VOID	unget()		lklex.c
 *
 *	side effects:
 *		The basep structure is created.
 */

VOID
bassav()
{
	if (basep == NULL) {
		basep = (struct base *)
			new (sizeof (struct base));
		bsp = basep;
	} else {
		bsp->b_base = (struct base *)
				new (sizeof (struct base));
		bsp = bsp->b_base;
	}
	unget(getnb());
	bsp->b_strp = (char *) new (strlen(ip)+1);
	strcpy(bsp->b_strp, ip);
}

/*)Function	VOID	setbas()
 *
 *	The function setbas() scans the base address lines in hte
 *	basep structure, evaluates the arguments, and sets beginning
 *	address of the specified areas.
 *
 *	local variables:
 *		int	v		expression value
 *		char	id[]		base id string
 *
 *	global variables:
 *		area	*ap		Pointer to the current
 *						area structure
 *		area	*areap		The pointer to the first
 *						area structure of a linked list
 *		base	*basep		The pointer to the first
 *						base structure
 *		base	*bsp		Pointer to the current
 *						base structure
 *		char	*ip		pointer into the REL file
 *						text line in ib[]
 *		int	lkerr		error flag
 *
 *	 functions called:
 *		Addr_T	expr()		lkeval.c
 *		int	fprintf()	c_library
 *		VOID	getid()		lklex.c
 *		char	getnb()		lklex.c
 *		int	symeq()		lksym.c
 *
 *	side effects:
 *		The base address of an area is set.
 */

VOID
setbas()
{
	register int v;
	char id[NCPS];

	bsp = basep;
	while (bsp) {
		ip = bsp->b_strp;
		getid(id, -1);
		if (getnb() == '=') {
			v = expr(0);
			for (ap = areap; ap != NULL; ap = ap->a_ap) {
				if (symeq(id, ap->a_id))
					break;
			}
			if (ap == NULL) {
				fprintf(stderr,
				"ASlink-Warning-No definition of area %s\n", id);
				lkerr++;
			} else {
				ap->a_addr = v;
                                ap->a_type = 1;	/* JLH: value set */
			}
		} else {
			fprintf(stderr, "ASlink-Warning-No '=' in base expression");
			lkerr++;
		}
		bsp = bsp->b_base;
	}
}

/*)Function	VOID	gblsav()
 *
 *	The function gblsav() creates a linked structure containing
 *	the global variable strings input to the linker.
 *
 *	local variable:
 *		none
 *
 *	global variables:
 *		globl	*globlp		The pointer to the first
 *						globl structure
 *		globl	*gsp		Pointer to the current
 *						globl structure
 *		char	*ip		pointer into the REL file
 *						text line in ib[]
 *		int	lkerr		error flag
 *
 *	functions called:
 *		char	getnb()		lklex.c
 *		VOID *	new()		lksym.c
 *		int	strlen()	c_library
 *		char *	strcpy()	c_library
 *		VOID	unget()		lklex.c
 *
 *	side effects:
 *		The globlp structure is created.
 */

VOID
gblsav()
{
	if (globlp == NULL) {
		globlp = (struct globl *)
			new (sizeof (struct globl));
		gsp = globlp;
	} else {
		gsp->g_globl = (struct globl *)
				new (sizeof (struct globl));
		gsp = gsp->g_globl;
	}
	unget(getnb());
	gsp->g_strp = (char *) new (strlen(ip)+1);
	strcpy(gsp->g_strp, ip);
}
	
/*)Function	VOID	setgbl()
 *
 *	The function setgbl() scans the global variable lines in hte
 *	globlp structure, evaluates the arguments, and sets a variable
 *	to this value.
 *
 *	local variables:
 *		int	v		expression value
 *		char	id[]		base id string
 *		sym *	sp		pointer to a symbol structure
 *
 *	global variables:
 *		char	*ip		pointer into the REL file
 *						text line in ib[]
 *		globl	*globlp		The pointer to the first
 *						globl structure
 *		globl	*gsp		Pointer to the current
 *						globl structure
 *		FILE *	stderr		c_library
 *		int	lkerr		error flag
 *
 *	 functions called:
 *		Addr_T	expr()		lkeval.c
 *		int	fprintf()	c_library
 *		VOID	getid()		lklex.c
 *		char	getnb()		lklex.c
 *		sym *	lkpsym()	lksym.c
 *
 *	side effects:
 *		The value of a variable is set.
 */

VOID
setgbl()
{
	register int v;
	register struct sym *sp;
	char id[NCPS];

	gsp = globlp;
	while (gsp) {
		ip = gsp->g_strp;
		getid(id, -1);
		if (getnb() == '=') {
			v = expr(0);
			sp = lkpsym(id, 0);
			if (sp == NULL) {
				fprintf(stderr,
				"No definition of symbol %s\n", id);
				lkerr++;
			} else {
				if (sp->s_flag & S_DEF) {
					fprintf(stderr,
					"Redefinition of symbol %s\n", id);
					lkerr++;
					sp->s_axp = NULL;
				}
				sp->s_addr = v;
				sp->s_type |= S_DEF;
			}
		} else {
			fprintf(stderr, "No '=' in global expression");
			lkerr++;
		}
		gsp = gsp->g_globl;
	}
}

/*)Function	FILE *	afile(fn,, ft, wf)
 *
 *		char *	fn		file specification string
 *		char *	ft		file type string
 *		int	wf		read(0)/write(1) flag
 *
 *	The function afile() opens a file for reading or writing.
 *		(1)	If the file type specification string ft
 *			is not NULL then a file specification is
 *			constructed with the file path\name in fn
 *			and the extension in ft.
 *		(2)	If the file type specification string ft
 *			is NULL then the file specification is
 *			constructed from fn.  If fn does not have
 *			a file type then the default .rel file
 *			type is appended to the file specification.
 *
 *	afile() returns a file handle for the opened file or aborts
 *	the assembler on an open error.
 *
 *	local variables:
 *		char	fb[]		constructed file specification string
 *		FILE *	fp		filehandle for opened file
 *
 *	global variables:
 *		int	lkerr		error flag
 *
 *	functions called:
 *		FILE *	fopen()		c_library
 *		int	fprintf()	c_library
 *
 *	side effects:
 *		File is opened for read or write.
 */

FILE *
afile(fn, ft, wf)
char *fn;
char *ft;
{
	FILE *fp;
	char fb[PATH_MAX];
	char *omode = (wf ? (wf == 2 ? "a" : "w") : "r");
	int i;

	/*Look backward the name path and get rid of the extension, if any*/
	i=strlen(fn);
	for(; (fn[i]!='.')&&(fn[i]!='\\')&&(fn[i]!='/')&&(i>=0); i--);
	if( (fn[i]=='.') && strcmp(ft, "lnk") )
	{
		strncpy(fb, fn, i);
		fb[i]=0;
	}
	else
	{
		strcpy(fb, fn);
	}

	/*Add the extension*/
	strcat(fb, ".");
	strcat(fb, strlen(ft)?ft:"rel");
	
	fp = fopen(fb, omode);
	if (fp==NULL)
	{
	    if (strcmp(ft,"adb"))/*Do not complaint for optional adb files*/
		{
			fprintf(stderr, "%s: cannot %s.\n", fb, wf?"create":"open");
			lkerr++;
	    }
	}
	return (fp);
}

/*)Function	VOID	iramsav()
 *
 *	The function iramsav() stores the size of the chip's internal RAM.
 *	This is used after linking to check that variable assignment to this
 *	dataspace didn't overflow into adjoining segments.  Variables in the
 *	DSEG, OSEG, and ISEG are assigned to this dataspace.
 *
 *	local variables:
 *		none
 *
 *	global variables:
 *		char	*ip		pointer into the REL file
 *						text line in ib[]
 *		unsigned int		size of chip's internal
 *			iram_size		RAM segment
 *
 *	 functions called:
 *		char	getnb()		lklex.c
 *		VOID	unget()		lklex.c
 *		Addr_T	expr()		lkeval.c
 *
 *	side effects:
 *		The iram_size may be modified.
 */

VOID
iramsav()
{
  unget(getnb());
  if (ip && *ip)
    //iram_size = atoi(ip);
    iram_size = expr(0);	/* evaluate size expression */
  else
    iram_size = 128;		/* Default is 128 (0x80) bytes */
}

/*Similar to iramsav but for xram memory*/
VOID
xramsav()
{
  unget(getnb());
  if (ip && *ip)
    xram_size = expr(0);	/* evaluate size expression */
  else
	xram_size = rflag?0x1000000:0x10000;
}

/*Similar to iramsav but for code memory*/
VOID
codesav()
{
  unget(getnb());
  if (ip && *ip)
    code_size = expr(0);	/* evaluate size expression */
  else
	code_size = rflag?0x1000000:0x10000;
}


/*)Function	VOID	iramcheck()
 *
 *	The function iramcheck() is used at the end of linking to check that
 *	the internal RAM area wasn't overflowed by too many variable
 *	assignments.  Variables in the DSEG, ISEG, and OSEG are assigned to
 *	the chip's internal RAM.
 *
 *	local variables:
 *		none
 *
 *	global variables:
 *		unsigned int		size of chip's internal
 *			iram_size		RAM segment
 *		struct area		linked list of memory
 *			*areap			areas
 *
 *	 functions called:
 *
 *	side effects:
 */

VOID
iramcheck()
{
  register unsigned int last_addr;
  register struct area *ap;

  for (ap = areap; ap; ap=ap->a_ap) {
    if ((ap->a_size != 0) &&
        (!strcmp(ap->a_id, "DSEG") ||
         !strcmp(ap->a_id, "OSEG") ||
         !strcmp(ap->a_id, "ISEG")
        )
       )
    {
      last_addr = ap->a_addr + ap->a_size - 1;
      if (last_addr >= iram_size)
	fprintf(stderr,
		"\nWARNING! Segment %s extends past the end\n"
		"         of internal RAM.  Check map file.\n",
		ap->a_id);
    }
  }
}

char *usetxt[] = {
	"Startup:",
	"  -c	Command line input",
	"  -f	file[LNK] File input",
	"  -p	Prompt and echo of file[LNK] to stdout (default)",
	"  -n	No echo of file[LNK] to stdout",
/*	"Usage: [-Options] file [file ...]", */
	"Libraries:",
	"  -k	Library path specification, one per -k",
	"  -l	Library file specification, one per -l",
	"Relocation:",
	"  -b	area base address = expression",
	"  -g	global symbol = expression",
	"Map format:",
	"  -m	Map output generated as file[MAP]",
	"  -x	Hexadecimal (default),  -d  Decimal,  -q  Octal",
	"Output:",
	"  -i	Intel Hex as file[IHX]",
	"  -s	Motorola S19 as file[S19]",
	"  -j	Produce NoICE debug as file[NOI]",
	"  -z   Produce SDCdb debug as file[cdb]",
/*	"List:", */
	"  -u	Update listing file(s) with link data as file(s)[.RST]",
	"Miscellaneous:\n"
	"  -a	[iram-size] Check for internal RAM overflow",
	"  -v	[xram-size] Check for external RAM overflow",
	"  -w	[code-size] Check for code overflow",
	"End:",
	"  -e	or null line terminates input",
	0
};

/*)Function	VOID	usage()
 *
 *	The function usage() outputs to the stderr device the
 *	assembler name and version and a list of valid assembler options.
 *
 *	local variables:
 *		char **	dp		pointer to an array of
 *					text string pointers.
 *
 *	global variables:
 *		FILE *	stderr		c_library
 *
 *	functions called:
 *		int	fprintf()	c_library
 *
 *	side effects:
 *		none
 */

VOID
usage()
{
	register char	**dp;

	fprintf(stderr, "\nASxxxx Linker %s\n\n", VERSION);
	for (dp = usetxt; *dp; dp++)
		fprintf(stderr, "%s\n", *dp);
	lkexit(1);
}

/*)Function	VOID	copyfile()
 *		
 *		FILE    *dest           destination file
 *		FILE    *src            source file
 *
 *      function will copy source file to destination file
 *
 *
 *	functions called:
 *		int	fgetc() 	c_library
 *              int     fputc()         c_library
 *
 *	side effects:
 *		none
 */
VOID copyfile (dest,src)
FILE *src,*dest ;
{    
    int ch;
    while ((ch = fgetc(src)) != EOF) {

	fputc(ch,dest);
    }
}
