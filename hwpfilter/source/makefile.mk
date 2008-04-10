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
# $Revision: 1.7 $
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

PRJ=..

PRJNAME=hwpfilter
TARGET=hwp

USE_DEFFILE=TRUE
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Files --------------------------------------------------------

.IF "$(SYSTEM_ZLIB)" == "YES"
CFLAGS+=-DSYSTEM_ZLIB
.ENDIF

SLOFILES =	\
        $(SLO)$/attributes.obj \
        $(SLO)$/cspline.obj \
        $(SLO)$/fontmap.obj \
        $(SLO)$/formula.obj \
        $(SLO)$/grammar.obj \
        $(SLO)$/hbox.obj \
        $(SLO)$/hcode.obj \
        $(SLO)$/hfont.obj \
        $(SLO)$/hgzip.obj \
        $(SLO)$/himgutil.obj \
        $(SLO)$/hinfo.obj \
        $(SLO)$/hiodev.obj \
        $(SLO)$/hpara.obj \
        $(SLO)$/hstream.obj \
        $(SLO)$/hstyle.obj \
        $(SLO)$/htags.obj \
        $(SLO)$/hutil.obj \
        $(SLO)$/hwpeq.obj \
        $(SLO)$/hwpfile.obj \
        $(SLO)$/hwpread.obj \
        $(SLO)$/hwpreader.obj \
        $(SLO)$/lexer.obj \
        $(SLO)$/mzstring.obj \
        $(SLO)$/solver.obj

# --- Shared-Library -----------------------------------------------

SHL1TARGET= $(TARGET)
#SHL1IMPLIB= ihwp

SHL1STDLIBS= \
        $(CPPULIB)		\
        $(CPPUHELPERLIB)\
        $(SALLIB)		\
        $(ZLIB3RDLIB)

.IF "$(GUI)"=="WNT"
SHL1STDLIBS+= \
        $(OLE32LIB) $(UUIDLIB)
.ENDIF			# "$(GUI)"=="WNT"		


SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
SHL1LIBS=   $(SLB)$/$(TARGET).lib
SHL1VERSIONMAP = hwp.map

DEF1NAME=$(SHL1TARGET)

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
