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
# $Revision: 1.5 $
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

PRJ	= ..$/.. 
PRJNAME = xmerge
#PACKAGE = com$/sun$/star$/documentconversion$/XSLTFilter
TARGET  = xmergesync 
ENABLE_EXCEPTIONS=TRUE
LIBTARGET=NO
.IF "$(POCKETPCSDK_HOME)" != ""
SOLARINC+=-I$(POCKETPCSDK_HOME)$/support$/ActiveSync$/inc
.ENDIF          # "$(POCKETPCSDK_HOME)" != ""

# --- Settings ----------------------------------------------------- 
.INCLUDE: settings.mk  

.IF 0
.IF "$(GUI)" == "WNT"
.IF "$(POCKETPCSDK_HOME)" != ""

RCFILES=XMergeSync.rc

SLOFILES= \
    $(SLO)$/XMergeFactory.obj \
    $(SLO)$/XMergeSync.obj \
    $(SLO)$/XMergeFilter.obj 
LIBNAME=$(TARGET)
SHL1TARGETDEPN=makefile.mk
SHL1OBJS=$(SLOFILES) $(RES)$/xmergesync.res
SHL1TARGET=$(LIBNAME)
SHL1IMPLIB=i$(LIBNAME)
SHL1DEF=XMergeSync.def
USE_DEFFILE=true

SHL1STDLIBS= uuid.lib Advapi32.lib

.ENDIF          # "$(POCKETPCSDK_HOME)" != ""
.ENDIF
.ENDIF


# --- Targets ------------------------------------------------------  
.INCLUDE :  target.mk 

ALLTAR :
    .IF "$(GUI)" == "WNT"
        $(COPY) BIN$/xmergesync.dll $(BIN)
    .ENDIF
