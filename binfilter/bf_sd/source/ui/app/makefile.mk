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

PROJECTPCH=sd
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sd_sd

PRJNAME=binfilter
TARGET=sd_app

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd

# --- Update-Version -----------------------------------------------

RSCUPDVER=$(RSCREVISION)SV$(UPD)$(UPDMINOR)

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =	\
        sd_strings.src

SLOFILES =	\
        $(SLO)$/sd_sdmod.obj		\
        $(SLO)$/sd_sddll.obj		\
        $(SLO)$/sd_sdresid.obj		\
        $(SLO)$/sd_optsitem.obj

DEPOBJFILES= \
        $(SLO)$/sd_sdlib.obj
        
.IF "$(GUI)" == "WNT"

NOOPTFILES=\
    $(SLO)$/sd_optsitem.obj

.ENDIF

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

$(INCCOM)$/sddll0.hxx: makefile.mk
    @echo $@
.IF "$(GUI)"=="UNX"
    echo \#define DLL_NAME \"libbf_sd$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE			# "$(GUI)"=="UNX"
.IF "$(USE_SHELL)"!="4nt"
    echo \#define DLL_NAME \"bf_sd$(DLLPOSTFIX).DLL\" >$@
.ELSE			# "$(USE_SHELL)"!="4nt"
    echo #define DLL_NAME "bf_sd$(DLLPOSTFIX).DLL" >$@
.ENDIF			#  "$(USE_SHELL)"!="4nt"
.ENDIF			# "$(GUI)"=="UNX"


ALLTAR : $(DEPOBJFILES)

$(SRS)$/sd_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

$(SLO)$/sd_sdlib.obj: $(INCCOM)$/sddll0.hxx
