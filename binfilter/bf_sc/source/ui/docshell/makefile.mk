#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:12:57 $
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

PRJNAME=binfilter
TARGET=sc_docshell

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..\pch\sc_ui_pch

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

CXXFILES = \
        sc_docsh.cxx	\
        sc_docsh2.cxx	\
        sc_docsh3.cxx	\
        sc_docsh4.cxx 	\
        sc_docsh5.cxx	\
        sc_docsh6.cxx 	\
        sc_docsh7.cxx 	\
        sc_docsh8.cxx 	\
        sc_tablink.cxx 	\
        sc_arealink.cxx 	\
        sc_dbdocfun.cxx 	\
        sc_dbdocimp.cxx 	\
        sc_impex.cxx	\
        sc_docfunc.cxx	\
        sc_olinefun.cxx	\
        sc_servobj.cxx	\
        sc_tpstat.cxx	\
        sc_autostyl.cxx	\
        sc_pagedata.cxx \
        sc_hiranges.cxx \
        sc_pntlock.cxx \
        sc_sizedev.cxx \
        sc_editable.cxx


SLOFILES =  \
        $(SLO)$/sc_docsh.obj	\
        $(SLO)$/sc_docsh2.obj	\
        $(SLO)$/sc_docsh3.obj	\
        $(SLO)$/sc_docsh4.obj   	\
        $(SLO)$/sc_docsh5.obj   	\
        $(SLO)$/sc_docsh6.obj   	\
        $(SLO)$/sc_docsh7.obj   	\
        $(SLO)$/sc_docsh8.obj   	\
        $(SLO)$/sc_tablink.obj   	\
        $(SLO)$/sc_arealink.obj   	\
        $(SLO)$/sc_dbdocfun.obj 	\
        $(SLO)$/sc_dbdocimp.obj 	\
        $(SLO)$/sc_impex.obj	\
        $(SLO)$/sc_docfunc.obj	\
        $(SLO)$/sc_olinefun.obj	\
        $(SLO)$/sc_servobj.obj	\
        $(SLO)$/sc_tpstat.obj	\
        $(SLO)$/sc_autostyl.obj	\
        $(SLO)$/sc_pagedata.obj \
        $(SLO)$/sc_hiranges.obj \
        $(SLO)$/sc_pntlock.obj \
        $(SLO)$/sc_sizedev.obj \
        $(SLO)$/sc_editable.obj


EXCEPTIONSFILES= \
        $(SLO)$/sc_docsh8.obj \
        $(SLO)$/sc_dbdocimp.obj


SRS1NAME=$(TARGET)
SRC1FILES =  sc_tpstat.src

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

