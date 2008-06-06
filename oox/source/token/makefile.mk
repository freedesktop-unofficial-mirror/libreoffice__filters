#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2008 by Sun Microsystems, Inc.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# $RCSfile: makefile.mk,v $
#
# $Revision: 1.8 $
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

PRJ=..$/..

PRJNAME=oox
TARGET=token

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE: $(PRJ)$/util$/makefile.pmk

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/tokenmap.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

$(MISC)$/tokens.gperf $(INCCOM)$/tokenwords.inc $(INCCOM)$/tokens.hxx : 
    @@noop $(assign do_phony:=.PHONY)

$(MISC)$/do_tokens $(do_phony) : tokens.txt gentoken.pl $(MISC)$/tokens.gperf $(INCCOM)$/tokenwords.inc $(INCCOM)$/tokens.hxx
        $(PERL) gentoken.pl tokens.txt $(INCCOM)$/tokens.hxx $(INCCOM)$/tokenwords.inc $(MISC)$/tokens.gperf && $(TOUCH) $@

$(INCCOM)$/tokens.inc : $(MISC)$/tokens.gperf $(MISC)$/do_tokens
        gperf --compare-strncmp $(MISC)$/tokens.gperf | $(SED) -e "s/(char\*)0/(char\*)0, 0/g" | $(GREP) -v "^#line" >$(INCCOM)$/tokens.inc

$(SLO)$/tokenmap.obj : $(INCCOM)$/tokens.inc $(INCCOM)$/tokenwords.inc $(INCCOM)$/tokens.hxx $(MISC)$/do_tokens

