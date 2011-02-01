#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
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
TARGET=sw_swg

NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF

# --- Files --------------------------------------------------------

SLOFILES =  \
        $(SLO)$/sw_rdcont.obj \
        $(SLO)$/sw_rdflds.obj \
        $(SLO)$/sw_rdfmts.obj \
        $(SLO)$/sw_rdhnt.obj \
        $(SLO)$/sw_rdmisc.obj \
        $(SLO)$/sw_rdnds.obj \
        $(SLO)$/sw_rdnum.obj \
        $(SLO)$/sw_rdpage.obj \
        $(SLO)$/sw_rdswg.obj \
        $(SLO)$/sw_rdtox.obj \
        $(SLO)$/sw_swgpar.obj \
        $(SLO)$/sw_swgstr.obj \
        $(SLO)$/sw_SwXMLSectionList.obj

EXCEPTIONSFILES = \
        $(SLO)$/sw_SwXMLSectionList.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
