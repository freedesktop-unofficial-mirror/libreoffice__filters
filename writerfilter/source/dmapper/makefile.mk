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
PRJ=..$/..
PRJNAME=writerfilter
TARGET=dmapper
GEN_HID=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings ----------------------------------

.INCLUDE : settings.mk
.INCLUDE :  $(PRJ)$/inc$/writerfilter.mk

# --- Files -------------------------------------

SLOFILES=           $(SLO)$/BorderHandler.obj \
                    $(SLO)$/TblStylePrHandler.obj \
                    $(SLO)$/GraphicHelpers.obj \
                    $(SLO)$/TablePropertiesHandler.obj \
                    $(SLO)$/CellColorHandler.obj \
                    $(SLO)$/CellMarginHandler.obj \
                    $(SLO)$/SectionColumnHandler.obj \
                    $(SLO)$/ConversionHelper.obj \
                    $(SLO)$/DomainMapper.obj \
                    $(SLO)$/DomainMapper_Impl.obj \
                    $(SLO)$/DomainMapperTableHandler.obj \
                    $(SLO)$/DomainMapperTableManager.obj \
                    $(SLO)$/FontTable.obj   \
                    $(SLO)$/GraphicImport.obj  \
                    $(SLO)$/LFOTable.obj    \
                    $(SLO)$/ListTable.obj  \
                    $(SLO)$/MeasureHandler.obj \
                    $(SLO)$/PropertyMap.obj  \
                    $(SLO)$/PropertyIds.obj  \
                    $(SLO)$/StyleSheetTable.obj \
                    $(SLO)$/TDefTableHandler.obj \
                    $(SLO)$/ThemeTable.obj \
                    $(SLO)$/SettingsTable.obj \
                    $(SLO)$/ModelEventListener.obj\
                    $(SLO)$/OLEHandler.obj \
                    $(SLO)$/PageBordersHandler.obj 

# --- Targets ----------------------------------

.INCLUDE : target.mk



