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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=sfx2_doc

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/timestamp.obj \
        $(SLO)$/sfx2_docfile.obj \
        $(SLO)$/sfx2_objuno.obj \
        $(SLO)$/sfx2_frmdescr.obj \
        $(SLO)$/sfx2_docinf.obj \
        $(SLO)$/sfx2_interno.obj \
        $(SLO)$/sfx2_objxtor.obj \
        $(SLO)$/sfx2_objmisc.obj \
        $(SLO)$/sfx2_objstor.obj \
        $(SLO)$/sfx2_objcont.obj \
        $(SLO)$/sfx2_objserv.obj \
        $(SLO)$/sfx2_objitem.obj \
        $(SLO)$/sfx2_docfac.obj \
        $(SLO)$/sfx2_docfilt.obj \
        $(SLO)$/sfx2_frameobj.obj \
        $(SLO)$/sfx2_sfxbasemodel.obj \
        $(SLO)$/sfx2_xmlversion.obj

EXCEPTIONSFILES=\
        $(SLO)$/sfx2_objuno.obj \
        $(SLO)$/sfx2_objcont.obj \
        $(SLO)$/sfx2_docfac.obj \
        $(SLO)$/sfx2_docfile.obj \
        $(SLO)$/sfx2_doctempl.obj \
        $(SLO)$/sfx2_doctemplates.obj \
        $(SLO)$/sfx2_sfxbasemodel.obj \
        $(SLO)$/sfx2_objxtor.obj \
        $(SLO)$/sfx2_objstor.obj \
        $(SLO)$/sfx2_xmlversion.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
