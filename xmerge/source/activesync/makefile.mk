#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: ihi $ $Date: 2006-08-01 12:38:52 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
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
        +$(COPY) BIN$/xmergesync.dll $(BIN)
    .ENDIF
