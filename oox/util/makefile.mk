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

PRJNAME=oox
TARGET=oox
USE_DEFFILE=TRUE
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Allgemein ----------------------------------------------------

LIB1TARGET= $(SLB)$/$(TARGET).lib
LIB1FILES=	\
    $(SLB)$/token.lib\
    $(SLB)$/helper.lib\
    $(SLB)$/core.lib\
    $(SLB)$/ppt.lib\
    $(SLB)$/xls.lib\
    $(SLB)$/vml.lib\
    $(SLB)$/drawingml.lib\
    $(SLB)$/diagram.lib\
    $(SLB)$/chart.lib\
    $(SLB)$/table.lib\
    $(SLB)$/shape.lib\
    $(SLB)$/dump.lib

# --- Shared-Library -----------------------------------------------

SHL1TARGET= $(TARGET)$(DLLPOSTFIX)
SHL1IMPLIB= i$(SHL1TARGET)
SHL1USE_EXPORTS=name

SHL1STDLIBS= \
        $(VOSLIB)		\
        $(CPPULIB)		\
        $(CPPUHELPERLIB)\
        $(COMPHELPERLIB)\
        $(RTLLIB)		\
        $(SALLIB)		\
        $(BASEGFXLIB)	\
        $(SAXLIB)

SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
SHL1LIBS=   $(LIB1TARGET)
DEF1NAME    =$(SHL1TARGET)
DEFLIB1NAME =$(TARGET)

# --- Targets ----------------------------------------------------------

.INCLUDE :  target.mk
