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
# $Revision: 1.10 $
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

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_sw3io

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
    sw_sw3io.cxx		\
    sw_sw3attr.cxx 	\
    sw_sw3block.cxx	\
    sw_sw3doc.cxx		\
    sw_sw3field.cxx	\
    sw_sw3fmts.cxx 	\
    sw_sw3imp.cxx		\
    sw_sw3misc.cxx 	\
    sw_sw3nodes.cxx	\
    sw_sw3npool.cxx	\
    sw_sw3num.cxx		\
    sw_sw3page.cxx 	\
    sw_sw3redln.cxx 	\
    sw_sw3sectn.cxx	\
    sw_sw3style.cxx	\
    sw_sw3table.cxx	\
    sw_crypter.cxx

SLOFILES = \
    $(SLO)$/sw_sw3io.obj	\
    $(SLO)$/sw_sw3attr.obj	\
    $(SLO)$/sw_sw3block.obj \
    $(SLO)$/sw_sw3doc.obj	\
    $(SLO)$/sw_sw3field.obj \
    $(SLO)$/sw_sw3fmts.obj	\
    $(SLO)$/sw_sw3imp.obj	\
    $(SLO)$/sw_sw3misc.obj	\
    $(SLO)$/sw_sw3nodes.obj \
    $(SLO)$/sw_sw3npool.obj \
    $(SLO)$/sw_sw3num.obj	\
    $(SLO)$/sw_sw3page.obj	\
    $(SLO)$/sw_sw3redln.obj	\
    $(SLO)$/sw_sw3sectn.obj \
    $(SLO)$/sw_sw3style.obj \
    $(SLO)$/sw_sw3table.obj \
    $(SLO)$/sw_crypter.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

