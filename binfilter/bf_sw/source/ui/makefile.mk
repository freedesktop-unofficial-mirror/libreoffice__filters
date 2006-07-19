#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 14:59:16 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=sw_ui

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(GUI)" != "WNT"
.IF "$(GUI)" != "MAC"
.IF "$(COM)" != "BLC"
.IF "$(COM)" != "WTC"
LIBFLAGS=/NOI /NOE /PAGE:256
.ENDIF
.ENDIF
.ENDIF
.ENDIF

# --- Files --------------------------------------------------------

# andere Label als Verzeichnisnamen fuer VC++/NT

#SUBLIBS1= \
#		$(SLB)$/app.lib      \
#		$(SLB)$/cctrl.lib    \
#		$(SLB)$/chrdlg.lib   \
#		$(SLB)$/config.lib   \
#		$(SLB)$/dbui.lib     \
#		$(SLB)$/dialog.lib   \
#		$(SLB)$/dochdl.lib   \
#		$(SLB)$/docvw.lib    \
#        $(SLB)$/envelp.lib   \
#		$(SLB)$/fldui.lib    \
#		$(SLB)$/fmtui.lib    \
#		$(SLB)$/frmdlg.lib   \
#		$(SLB)$/globdoc.lib

SUBLIBS1= \
        $(SLB)$/sw_app.lib      \
        $(SLB)$/sw_config.lib   \
        $(SLB)$/sw_dbui.lib     \
        $(SLB)$/sw_dialog.lib   \
        $(SLB)$/sw_dochdl.lib   \
        $(SLB)$/sw_docvw.lib    \
        $(SLB)$/sw_envelp.lib   \
        $(SLB)$/sw_fldui.lib    \
        $(SLB)$/sw_globdoc.lib
        
#SUBLIBS2= \
#		$(SLB)$/index.lib    \
#		$(SLB)$/lingu.lib    \
#		$(SLB)$/misc.lib     \
#		$(SLB)$/ribbar.lib   \
#		$(SLB)$/shells.lib   \
#		$(SLB)$/table.lib    \
#		$(SLB)$/unoidl.lib   \
#		$(SLB)$/utlui.lib    \
#		$(SLB)$/web.lib   \
#		$(SLB)$/wizard.lib   \
#		$(SLB)$/uiview.lib   \
#		$(SLB)$/wrtsh.lib

SUBLIBS2= \
        $(SLB)$/sw_index.lib    \
        $(SLB)$/sw_misc.lib     \
        $(SLB)$/sw_ribbar.lib   \
        $(SLB)$/sw_shells.lib   \
        $(SLB)$/sw_table.lib    \
        $(SLB)$/sw_unoidl.lib   \
        $(SLB)$/sw_utlui.lib    \
        $(SLB)$/sw_web.lib   \
        $(SLB)$/sw_uiview.lib   \
        $(SLB)$/sw_wrtsh.lib
# -----------------------------------------------------------

################################################################

LIB1TARGET=$(SLB)$/sw_ui1.lib
LIB1FILES= \
        $(SUBLIBS1)

LIB2TARGET=$(SLB)$/sw_ui2.lib
LIB2FILES= \
        $(SUBLIBS2)

.INCLUDE :  target.mk

################################################################

kill:
    @+$(RM) $(SLB)$/ui.lst
    @+$(RM) $(SLB)$/ui.lib


