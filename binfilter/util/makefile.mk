#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2004-12-16 10:41:45 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..

PRJNAME=binfilter
TARGET=bf_util

# --- Settings ----------------------------------

.INCLUDE :  	settings.mk

# --- Files -------------------------------------

.IF "$(GUI)"=="UNX"
LOCALLIBDIR=$(LB)
.ELSE          # "$(GUI)"=="UNX"
LOCALLIBDIR=$(BIN)
.ENDIF          # "$(GUI)"=="UNX"

RDBNAMES=		\
    bf_xo		\
    bf_sw		\
    bf_sc		\
    bf_sd		\
    bf_sm		\
    bf_sch		\
    bf_frm		\
    bf_lng		\
    bf_svx		\
    bf_wrapper

RDBLIBS=$(foreach,i,$(strip $(RDBNAMES)) $(LOCALLIBDIR)$/$(DLLPRE)$i$(UPD)$(DLLPOSTFIX)$(DLLPOST))
#RDBLIBS=$(foreach,i,$(strip $(RDBNAMES)) $(DLLPRE)$i$(UPD)$(DLLPOSTFIX)$(DLLPOST))

# --- Targets ----------------------------------

.INCLUDE : target.mk

ALLTAR : $(BIN)$/legacy_binfilters.rdb

$(BIN)$/legacy_binfilters.rdb : $(RDBLIBS)
    @+-$(RM) $@ >& $(NULLDEV)
    +cd $(LOCALLIBDIR) && $(REGCOMP) -register -r ..$/bin$/$(@:f) $(foreach,i,$(RDBLIBS:f) -c $i)

#$(BIN)$/legacy_binfilters.rdb .SETDIR=$(LOCALLIBDIR) : $(RDBLIBS)
#    @+-$(RM) $@ >& $(NULLDEV)
#    $(REGCOMP) -register -r ../$@ $(foreach,i,$(RDBLIBS) -c $(subst,$/,/ $i))

#$(BIN)$/legacy_binfilters.rdb : $(RDBLIBS)
#    @+-$(RM) $@ >& $(NULLDEV)
#    $(REGCOMP) -register -r $@ $(foreach,i,$(RDBLIBS) -c $(subst,$/,/ $i))
