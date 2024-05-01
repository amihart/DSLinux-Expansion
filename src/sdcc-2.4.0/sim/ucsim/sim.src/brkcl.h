/*
 * Simulator of microcontrollers (sim.src/brkcl.h)
 *
 * Copyright (C) 1999,99 Drotos Daniel, Talker Bt.
 * 
 * To contact author send email to drdani@mazsola.iit.uni-miskolc.hu
 *
 */

/* This file is part of microcontroller simulator: ucsim.

UCSIM is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

UCSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with UCSIM; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA. */
/*@1@*/

#ifndef SIM_BRKCL_HEADER
#define SIM_BRKCL_HEADER

#include "ddconfig.h"

// prj
#include "pobjcl.h"
#include "stypes.h"

// sim
#include "memcl.h"


/*
 * Base object of breakpoints
 */

class cl_brk: public cl_base
{
protected:
  class cl_mem *mem;
public:
  int nr;
  t_addr addr;
  enum  brk_perm perm;  // permanency (FIX,DYNAMIC)
  int   hit;
  int   cnt;

  cl_brk(class cl_mem *imem, int inr, t_addr iaddr,
	 enum brk_perm iperm, int ihit);
  virtual ~cl_brk(void);

  virtual void activate(void);
  virtual void inactivate(void);
  virtual enum brk_type type(void)= 0;
  virtual enum brk_event get_event(void)= 0;
  virtual bool do_hit(void);
};


/*
 * FETCH type of breakpoints
 */

class cl_fetch_brk: public cl_brk
{
public:
  uchar code;

  cl_fetch_brk(class cl_mem *imem, int inr, t_addr iaddr,
	       enum brk_perm iperm, int ihit);

  virtual enum brk_type type(void);
  virtual enum brk_event get_event(void) { return(brkNONE); }
};


/*
 * Base of EVENT type of breakpoints
 */

class cl_ev_brk: public cl_brk
{
public:
  cl_ev_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit, enum brk_event ievent, const char *iid);
  cl_ev_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit, char op);
  enum brk_event event;
  const char *id;

  virtual enum brk_type type(void);
  virtual enum brk_event get_event(void) { return(event); }
  virtual bool match(struct event_rec *ev);
};


/* 
 * WRITE IRAM
 */

/*class cl_wi_brk: public cl_ev_brk
{
public:
  cl_wi_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/* 
 * READ IRAM
 */

/*class cl_ri_brk: public cl_ev_brk
{
public:
  cl_ri_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/* 
 * WRITE XRAM
 */

/*class cl_wx_brk: public cl_ev_brk
{
public:
  cl_wx_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/* 
 * READ XRAM
 */

/*class cl_rx_brk: public cl_ev_brk
{
public:
  cl_rx_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/* 
 * WRITE SFR
 */

/*class cl_ws_brk: public cl_ev_brk
{
public:
  cl_ws_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/* 
 * READ SFR
 */

/*class cl_rs_brk: public cl_ev_brk
{
public:
  cl_rs_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/* 
 * READ CODE
 */

/*class cl_rc_brk: public cl_ev_brk
{
public:
  cl_rc_brk(class cl_mem *imem, int inr, t_addr iaddr, enum brk_perm iperm,
	    int ihit);

  virtual bool match(struct event_rec *ev);
};*/


/*
 * Collection of breakpoint sorted by address
 */

class brk_coll: public cl_sorted_list
{
public:
  class cl_mem/*rom*/ *rom;
public:
  brk_coll(t_index alimit, t_index adelta, class cl_mem/*rom*/ *arom);
  virtual void *key_of(void *item);
  virtual int  compare(void *key1, void *key2);

  virtual bool there_is_event(enum brk_event ev);
  //virtual int make_new_nr(void);

  virtual void add_bp(class cl_brk *bp);
  virtual void del_bp(t_addr addr);
  virtual void del_bp(t_index idx, int /*dummy*/);
  virtual class cl_brk *get_bp(t_addr addr, int *idx);
  virtual class cl_brk *get_bp(int nr);
  virtual bool bp_at(t_addr addr);
};


#endif

/* End of brkcl.h */
