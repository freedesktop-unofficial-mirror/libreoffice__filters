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
# $Revision: 1.3 $
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

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=numbers
LIBTARGET=NO

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

EXCEPTIONSFILES= \
        $(SLO)$/svt_numuno.obj \
        $(SLO)$/svt_numfmuno.obj \
        $(SLO)$/svt_supservs.obj

SLOFILES =  \
        $(EXCEPTIONSFILES) \
        $(SLO)$/svt_zforfind.obj	\
        $(SLO)$/svt_zforlist.obj \
        $(SLO)$/svt_zformat.obj 	\
        $(SLO)$/svt_zforscan.obj \
        $(SLO)$/svt_numhead.obj

LIB1TARGET=	$(SLB)$/$(TARGET).uno.lib
LIB1OBJFILES=	\
        $(SLO)$/svt_numfmuno.obj \
        $(SLO)$/svt_supservs.obj

LIB2TARGET=	$(SLB)$/$(TARGET).lib
LIB2OBJFILES=	\
        $(SLO)$/svt_zforfind.obj	\
        $(SLO)$/svt_zforlist.obj \
        $(SLO)$/svt_zformat.obj 	\
        $(SLO)$/svt_zforscan.obj \
        $(SLO)$/svt_numuno.obj \
        $(SLO)$/svt_numhead.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

