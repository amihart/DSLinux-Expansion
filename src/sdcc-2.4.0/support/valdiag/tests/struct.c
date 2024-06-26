
#ifdef TEST1
struct tag {
  int good1;
  register int bad;	/* ERROR */
  int good2;
} badstruct;		/* IGNORE */
#endif

#ifdef TEST2
struct tag {
  int good1;
  int bad;
  int bad;	/* ERROR */
  int good2;
} badstruct;
#endif


#ifdef TEST3
struct tag {
  int good1;
  int bad:255;	/* ERROR */
  int good2;
} badstruct;
#endif

#ifdef TEST4
struct tag {
  int good1;
  int good2;
} goodstruct1;

struct tag goodstruct2;
#endif

#ifdef TEST5a
struct tag {
  int good1;
  int good2;
} goodstruct1;

union tag badunion;	/* ERROR */
#endif

#ifdef TEST5b
union tag {
  int good1;
  int good2;
} goodunion1;

struct tag badstruct;	/* ERROR */
#endif


#ifdef TEST6
struct linklist {
  struct linklist *prev;
  struct linklist *next;
  int x;
} ll;
#endif

#ifdef TEST7a
union tag {
  struct tag *next;	/* ERROR */
  int x;
} ll;
#endif

#ifdef TEST7b
struct tag {
  union tag *next;	/* ERROR */
  int x;
} ll;
#endif
