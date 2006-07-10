#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: obo $ $Date: 2006-07-10 18:48:22 $
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
TARGET=sc_ui

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
INC+= -I$(PRJ)$/inc$/bf_sc
#IMGLST_SRS=$(SRS)$/sc_ui.srs
#BMP_IN=$(BFPRJ)$/res/imglst/apptbx
# --- Update-Version -----------------------------------------------

RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES = \
    sc_sc.src		 \
    sc_pseudo.src	 \
    sc_menue.src	 \
    sc_popup.src	 \
    sc_toolbox.src	 \
    sc_scstring.src \
    sc_attrdlg.src  \
    sc_sortdlg.src  \
    sc_filter.src	 \
    sc_namedlg.src  \
    sc_dbnamdlg.src \
    sc_subtdlg.src  \
    sc_miscdlgs.src \
    sc_autofmt.src  \
    sc_solvrdlg.src \
    sc_tabopdlg.src \
    sc_hdrcont.src  \
    sc_globstr.src  \
    sc_optdlg.src   \
    sc_scerrors.src \
    sc_textdlgs.src \
    sc_chartdlg.src \
    sc_scfuncs.src	 \
    sc_crnrdlg.src	 \
    sc_condfrmt.src \
    sc_opredlin.src \
    sc_simpref.src

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

$(SRS)$/sc_ui.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

