#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: rt $ $Date: 2005-09-09 10:42:42 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=bf_wrapper

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

LIBTARGET=NO
AUTOSEG=true
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(UPD)minor.mk
RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

# --- Files --------------------------------------------------------

SLOFILES =	$(SLO)$/bf_wrapper.obj

SHL1OBJS=   $(SLOFILES)
SHL1TARGET= $(TARGET)$(UPD)$(DLLPOSTFIX)

SHL1IMPLIB= ibf_wrp
SHL1STDLIBS=    \
                $(FWELIB)			\
                $(BASICLIB) 		\
                $(SO2LIB) 			\
                $(SJLIB) 			\
                $(TKLIB) 			\
                $(SVTOOLLIB) 		\
                $(SVLLIB) 			\
                $(BFOFALIB)			\
                $(ONELIB) 			\
                $(VCLLIB) 			\
                $(SOTLIB) 			\
                $(SALLIB)			\
                $(VOSLIB)			\
                $(TOOLSLIB)			\
                $(UNOLIB)			\
                $(CPPULIB)			\
                $(CPPUHELPERLIB)	\
                $(BFSCHLIB)         \
                $(BFSMLIB)          \
                $(BFSWLIB)          \
                $(BFSDLIB)          \
                $(BFSCLIB)          \
                $(BFSVXLIB)         \
                $(UNOTOOLSLIB)		\
                $(COMPHELPERLIB)	\
                $(LEGACYSMGRLIB)

.IF "$(GUI)" == "UNX"
SHL1STDLIBS+= \
            $(BFSFXLIB)
.ENDIF     
SHL1DEPN=       makefile.mk
SHL1DEF=        $(MISC)$/$(SHL1TARGET).def

DEF1NAME=       $(SHL1TARGET)
DEF1EXPORTFILE= exports.dxp

# --- Targets ------------------------------------------------------

.IF "$(depend)" != ""
SRCFILES=$(SRC1FILES)
.ENDIF

.INCLUDE :  target.mk

