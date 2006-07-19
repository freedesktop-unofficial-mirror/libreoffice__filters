#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 14:59:05 $
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

PRJNAME=binfilter
TARGET=sw_xml

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
.IF "$(mydebug)" != ""
CDEFS=$(CDEFS) -Dmydebug
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
        sw_swxml.cxx      \
        sw_xmlimp.cxx      \
        sw_wrtxml.cxx      \
        sw_xmlexp.cxx      \
        sw_xmltext.cxx      \
        sw_xmltexte.cxx      \
        sw_xmltexti.cxx      \
        sw_xmltbli.cxx      \
        sw_xmltble.cxx      \
        sw_xmlfmt.cxx      \
        sw_xmlfmte.cxx      \
        sw_xmlmeta.cxx      \
        sw_xmlitemm.cxx	\
        sw_xmlitemi.cxx	\
        sw_xmliteme.cxx	\
        sw_xmlbrsh.cxx		\
        sw_xmlfonte.cxx	\
        sw_XMLRedlineImportHelper.cxx \
        sw_xmlitem.cxx	\
        sw_xmlithlp.cxx \
        sw_xmlitmpr.cxx	\
        sw_xmlimpit.cxx \
        sw_xmlexpit.cxx 

SLOFILES =  \
        $(SLO)$/sw_swxml.obj \
        $(SLO)$/sw_xmlimp.obj \
        $(SLO)$/sw_wrtxml.obj \
        $(SLO)$/sw_xmlexp.obj \
        $(SLO)$/sw_xmltext.obj \
        $(SLO)$/sw_xmltexte.obj \
        $(SLO)$/sw_xmltexti.obj \
        $(SLO)$/sw_xmltbli.obj \
        $(SLO)$/sw_xmltble.obj \
        $(SLO)$/sw_xmlfmt.obj \
        $(SLO)$/sw_xmlfmte.obj \
        $(SLO)$/sw_xmlmeta.obj \
        $(SLO)$/sw_xmlscript.obj \
        $(SLO)$/sw_xmlitemm.obj \
        $(SLO)$/sw_xmlitemi.obj \
        $(SLO)$/sw_xmliteme.obj \
        $(SLO)$/sw_xmlithlp.obj \
        $(SLO)$/sw_xmlbrsh.obj \
        $(SLO)$/sw_xmlfonte.obj \
        $(SLO)$/sw_XMLRedlineImportHelper.obj \
        $(SLO)$/sw_xmlitem.obj	\
        $(SLO)$/sw_xmlitmpr.obj	\
        $(SLO)$/sw_xmlimpit.obj \
        $(SLO)$/sw_xmlexpit.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_swxml.obj \
        $(SLO)$/sw_xmlimp.obj \
        $(SLO)$/sw_wrtxml.obj \
        $(SLO)$/sw_xmlexp.obj \
        $(SLO)$/sw_xmltext.obj \
        $(SLO)$/sw_xmltexti.obj \
        $(SLO)$/sw_xmltbli.obj \
        $(SLO)$/sw_xmltble.obj \
        $(SLO)$/sw_xmlfmt.obj \
        $(SLO)$/sw_xmlfmte.obj \
        $(SLO)$/sw_xmlmeta.obj \
        $(SLO)$/sw_xmlscript.obj \
        $(SLO)$/sw_xmlitemi.obj \
        $(SLO)$/sw_xmliteme.obj \
        $(SLO)$/sw_xmlithlp.obj \
        $(SLO)$/sw_xmlbrsh.obj \
        $(SLO)$/sw_xmlfonte.obj \
        $(SLO)$/sw_XMLRedlineImportHelper.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

