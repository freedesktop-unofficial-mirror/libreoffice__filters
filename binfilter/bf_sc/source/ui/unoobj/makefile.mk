#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:19:03 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************
PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=bf_sc
TARGET=sc_unoobj

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..\pch\sc_ui_pch

ENABLE_EXCEPTIONS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------
CXXFILES = \
        sc_docuno.cxx \
        sc_servuno.cxx \
        sc_defltuno.cxx \
        sc_drdefuno.cxx \
        sc_cellsuno.cxx \
        sc_textuno.cxx \
        sc_notesuno.cxx \
        sc_cursuno.cxx \
        sc_srchuno.cxx \
        sc_fielduno.cxx \
        sc_miscuno.cxx \
        sc_optuno.cxx \
        sc_appluno.cxx \
        sc_funcuno.cxx \
        sc_nameuno.cxx \
        sc_viewuno.cxx \
        sc_dispuno.cxx \
        sc_datauno.cxx \
        sc_dapiuno.cxx \
        sc_chartuno.cxx \
        sc_shapeuno.cxx \
        sc_pageuno.cxx \
        sc_forbiuno.cxx \
        sc_styleuno.cxx \
        sc_afmtuno.cxx \
        sc_fmtuno.cxx \
        sc_linkuno.cxx \
        sc_targuno.cxx \
        sc_convuno.cxx \
        sc_editsrc.cxx \
        sc_unoguard.cxx \
        sc_confuno.cxx \
        sc_filtuno.cxx \
        sc_unodoc.cxx

SLOFILES =  \
        $(SLO)$/sc_docuno.obj \
        $(SLO)$/sc_servuno.obj \
        $(SLO)$/sc_defltuno.obj \
        $(SLO)$/sc_drdefuno.obj \
        $(SLO)$/sc_cellsuno.obj \
        $(SLO)$/sc_textuno.obj \
        $(SLO)$/sc_notesuno.obj \
        $(SLO)$/sc_cursuno.obj \
        $(SLO)$/sc_srchuno.obj \
        $(SLO)$/sc_fielduno.obj \
        $(SLO)$/sc_miscuno.obj \
        $(SLO)$/sc_optuno.obj \
        $(SLO)$/sc_appluno.obj \
        $(SLO)$/sc_funcuno.obj \
        $(SLO)$/sc_nameuno.obj \
        $(SLO)$/sc_viewuno.obj \
        $(SLO)$/sc_dispuno.obj \
        $(SLO)$/sc_datauno.obj \
        $(SLO)$/sc_dapiuno.obj \
        $(SLO)$/sc_chartuno.obj \
        $(SLO)$/sc_shapeuno.obj \
        $(SLO)$/sc_pageuno.obj \
        $(SLO)$/sc_forbiuno.obj \
        $(SLO)$/sc_styleuno.obj \
        $(SLO)$/sc_afmtuno.obj \
        $(SLO)$/sc_fmtuno.obj \
        $(SLO)$/sc_linkuno.obj \
        $(SLO)$/sc_targuno.obj \
        $(SLO)$/sc_convuno.obj \
        $(SLO)$/sc_editsrc.obj \
        $(SLO)$/sc_unoguard.obj \
        $(SLO)$/sc_confuno.obj \
        $(SLO)$/sc_filtuno.obj \
        $(SLO)$/sc_unodoc.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

