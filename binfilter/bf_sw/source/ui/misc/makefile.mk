#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-09 06:13:53 $
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
TARGET=sw_misc

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :	$(PRJ)$/inc$/swpre.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
#.INCLUDE :	$(PRJ)$/inc$/sw.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

CXXFILES = \
        sw_bookmark.cxx \
        sw_docfnote.cxx \
        sw_glosbib.cxx \
        sw_glosdoc.cxx \
        sw_glossary.cxx \
        sw_glshell.cxx \
        sw_hdftctrl.cxx \
        sw_insfnote.cxx \
        sw_insrule.cxx \
        sw_linenum.cxx \
        sw_num.cxx \
        sw_numberingtypelistbox.cxx \
        sw_outline.cxx \
        sw_pgfnote.cxx \
        sw_pggrid.cxx \
        sw_redlndlg.cxx \
        sw_srtdlg.cxx

SRS1NAME=$(TARGET)
SRC1FILES=\
    sw_bookmark.src \
    sw_docfnote.src \
    sw_glossary.src \
    sw_glosbib.src \
    sw_insfnote.src \
    sw_insrule.src \
    sw_linenum.src \
    sw_num.src \
    sw_numberingtypelistbox.src \
    sw_outline.src \
    sw_pgfnote.src \
    sw_pggrid.src \
    sw_redlndlg.src \
    sw_srtdlg.src

SLOFILES =	\
        $(SLO)$/sw_bookmark.obj \
        $(SLO)$/sw_docfnote.obj \
        $(SLO)$/sw_glosbib.obj \
        $(SLO)$/sw_glosdoc.obj \
        $(SLO)$/sw_glossary.obj \
        $(SLO)$/sw_glshell.obj \
        $(SLO)$/sw_hdftctrl.obj \
        $(SLO)$/sw_insfnote.obj \
        $(SLO)$/sw_insrule.obj \
        $(SLO)$/sw_linenum.obj \
        $(SLO)$/sw_num.obj \
        $(SLO)$/sw_numberingtypelistbox.obj \
        $(SLO)$/sw_outline.obj \
        $(SLO)$/sw_pgfnote.obj \
        $(SLO)$/sw_pggrid.obj \
        $(SLO)$/sw_redlndlg.obj \
        $(SLO)$/sw_srtdlg.obj

EXCEPTIONSFILES = \
        $(SLO)$/sw_glossary.obj \
        $(SLO)$/sw_numberingtypelistbox.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :	target.mk

