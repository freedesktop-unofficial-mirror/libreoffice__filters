#************************************************************************
#
#  OpenOffice.org - a multi-platform office productivity suite
#
#  $RCSfile: makefile.mk,v $
#
#  $Revision: 1.5 $
#
#  last change: $Author: os $ $Date: 2007-04-23 07:43:13 $
#
#  The Contents of this file are made available subject to
#  the terms of GNU Lesser General Public License Version 2.1.
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
# ***********************************************************************/

PRJ=..$/..
PRJNAME=writerfilter
TARGET=ooxml
#LIBTARGET=NO
#USE_DEFFILE=TRUE
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

#CFLAGS+=-DISOLATION_AWARE_ENABLED -DWIN32_LEAN_AND_MEAN -DXML_UNICODE -D_NTSDK -DUNICODE -D_UNICODE -D_WIN32_WINNT=0x0501
#CFLAGS+=-wd4710 -wd4711 -wd4514 -wd4619 -wd4217 -wd4820
CDEFS+=-DWRITERFILTER_DLLIMPLEMENTATION -DDEBUG_OOXML_ELEMENT


# --- Files --------------------------------------------------------

SLOFILES= \
    $(SLO)$/OOXMLresources.obj \
    $(SLO)$/OOXMLvalues.obj \
    $(SLO)$/TokenMapInit.obj \
    $(SLO)$/OOXMLPropertySetImpl.obj \
    $(SLO)$/OOXMLContext.obj \
    $(SLO)$/NamespaceMapper.obj \
    $(SLO)$/TokenMap.obj \
    $(SLO)$/OOXMLSaxHandler.obj \
    $(SLO)$/OOXMLDocumentImpl.obj \
    $(SLO)$/OOXMLStreamImpl.obj


SHL1TARGET=$(TARGET)

.IF "$(GUI)"=="UNX" || "$(GUI)"=="MAC"
RESOURCEMODELLIB=-lresourcemodel
.ELIF "$(GUI)"=="WNT"
RESOURCEMODELLIB=$(LB)$/iresourcemodel.lib
.ENDIF

SHL1STDLIBS=$(SALLIB)\
    $(CPPULIB)\
    $(CPPUHELPERLIB) \
    $(COMPHELPERLIB) \
    $(RESOURCEMODELLIB)
SHL1IMPLIB=i$(SHL1TARGET)
#SHL1USE_EXPORTS=name
SHL1USE_EXPORTS=ordinal

SHL1OBJS=$(SLOFILES)

SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)
DEFLIB1NAME=$(TARGET)

# --- Targets ------------------------------------------------------

.INCLUDE :	target.mk
