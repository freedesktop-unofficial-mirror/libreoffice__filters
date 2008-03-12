#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.14 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 07:31:49 $
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
