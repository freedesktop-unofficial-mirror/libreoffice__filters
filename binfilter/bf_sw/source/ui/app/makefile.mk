#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: rt $ $Date: 2005-09-09 03:49:01 $
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

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_app

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

LIBTARGET=NO

# future: DEMO\...

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw
.INCLUDE :  $(UPD)minor.mk
RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

#IMGLST_SRS=$(SRS)$/app.srs
#BMP_IN=$(PRJ)$/win/imglst

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =\
        sw_acc.src     \
        sw_app.src     \
        sw_mn.src      \
        sw_mnport.src      \
        sw_error.src


#OBJFILES = \
#		$(OBJ)$/sw_swlib.obj   \
#		$(OBJ)$/sw_swcomlib.obj

SLOFILES = \
        $(SLO)$/sw_appenv.obj   \
        $(SLO)$/sw_apphdl.obj   \
        $(SLO)$/sw_applab.obj   \
        $(SLO)$/sw_appopt.obj   \
        $(SLO)$/sw_docsh.obj    \
        $(SLO)$/sw_docsh2.obj   \
        $(SLO)$/sw_docshdrw.obj \
        $(SLO)$/sw_docshini.obj \
        $(SLO)$/sw_docst.obj    \
        $(SLO)$/sw_docstyle.obj \
        $(SLO)$/sw_mainwn.obj   \
        $(SLO)$/sw_version.obj  \
        $(SLO)$/sw_swmodule.obj \
        $(SLO)$/sw_swmodul1.obj \
        $(SLO)$/sw_swdll.obj	 \
        $(SLO)$/sw_swwait.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_swmodule.obj \
        $(SLO)$/sw_swmodul1.obj \
        $(SLO)$/sw_docsh2.obj

LIB1TARGET= $(SLB)$/sw_app.lib

LIB1OBJFILES= \
        $(SLO)$/sw_appenv.obj   \
        $(SLO)$/sw_apphdl.obj   \
        $(SLO)$/sw_applab.obj   \
        $(SLO)$/sw_appopt.obj   \
        $(SLO)$/sw_docsh.obj    \
        $(SLO)$/sw_docsh2.obj   \
        $(SLO)$/sw_docshdrw.obj \
        $(SLO)$/sw_docshini.obj \
        $(SLO)$/sw_docst.obj    \
        $(SLO)$/sw_docstyle.obj \
        $(SLO)$/sw_mainwn.obj   \
        $(SLO)$/sw_swmodul1.obj \
        $(SLO)$/sw_version.obj	 \
        $(SLO)$/sw_swwait.obj

#LIB3TARGET=$(SLB)$/bf_yswlib.lib
#LIB3OBJFILES=

DEPOBJFILES= \
    $(SLO)$/sw_swlib.obj \
    $(SLO)$/sw_swcomlib.obj

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR : $(DEPOBJFILES)

$(SLO)$/sw_swdll.obj : $(INCCOM)$/swdll0.hxx
$(SLO)$/sw_swmodule.obj : $(INCCOM)$/swdll0.hxx

.IF "$(GUI)"=="UNX" || "$(USE_SHELL)"!="4nt"
$(INCCOM)$/swdll0.hxx: makefile.mk
    echo \#define DLL_NAME \"$(DLLPRE)bf_sw$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE			# "$(GUI)"=="UNX" || "$(USE_SHELL)"!="4nt"
$(INCCOM)$/swdll0.hxx: makefile.mk
    echo #define DLL_NAME "bf_sw$(UPD)$(DLLPOSTFIX).DLL" >$@
.ENDIF			# "$(GUI)"=="UNX" || "$(USE_SHELL)"!="4nt"


$(SRS)$/sw_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

