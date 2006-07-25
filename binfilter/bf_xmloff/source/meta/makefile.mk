#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 09:15:17 $
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

PRJNAME=binfilter
TARGET=xmloff_meta

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/xmloff_xmlmetae.obj \
        $(SLO)$/xmloff_xmlmetai.obj \
        $(SLO)$/xmloff_MetaExportComponent.obj \
        $(SLO)$/xmloff_MetaImportComponent.obj

SVXLIGHTOBJFILES =	\
        $(OBJ)$/xmloff_xmlmetai.obj \
        $(OBJ)$/xmloff_MetaImportComponent.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

