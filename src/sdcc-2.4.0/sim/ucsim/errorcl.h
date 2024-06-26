/*
 * Simulator of microcontrollers (errorcl.h)
 *
 * Copyright (C) 2001,01 Drotos Daniel, Talker Bt.
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

#ifndef ERRORCL_HEADER
#define ERRORCL_HEADER

// prj
#include "pobjcl.h"
#include "stypes.h"

// cmd.src
//#include "newcmdcl.h"


class cl_commander; //forward

class cl_error: public cl_base
{
public:
  bool inst;	// Occured during instruction execution
  t_addr PC;	// Address of the instruction
public:
  cl_error(void);
  virtual ~cl_error(void);

  virtual void print(class cl_commander *c);
};


#endif

/* End of sim.src/errorcl.h */
