#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: hjs $ $Date: 2004-06-28 16:39:57 $
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

PRJ=..

PRJNAME=hwpfilter
TARGET=hwp

USE_DEFFILE=TRUE
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Files --------------------------------------------------------

.IF "$(SYSTEM_ZLIB)" == "YES"
CFLAGS+=-DSYSTEM_ZLIB
.ENDIF
SLOFILES =	\
        $(SLO)$/attributes.obj \
        $(SLO)$/cspline.obj \
        $(SLO)$/fontmap.obj \
        $(SLO)$/formula.obj \
        $(SLO)$/grammar.obj \
        $(SLO)$/hbox.obj \
        $(SLO)$/hcode.obj \
        $(SLO)$/hfont.obj \
        $(SLO)$/hgzip.obj \
        $(SLO)$/himgutil.obj \
        $(SLO)$/hinfo.obj \
        $(SLO)$/hiodev.obj \
        $(SLO)$/hpara.obj \
        $(SLO)$/hstream.obj \
        $(SLO)$/hstyle.obj \
        $(SLO)$/htags.obj \
        $(SLO)$/hutil.obj \
        $(SLO)$/hwpeq.obj \
        $(SLO)$/hwpfile.obj \
        $(SLO)$/hwpread.obj \
        $(SLO)$/hwpreader.obj \
        $(SLO)$/lexer.obj \
        $(SLO)$/mzstring.obj \
        $(SLO)$/solver.obj

# --- Shared-Library -----------------------------------------------

SHL1TARGET= $(TARGET)
#SHL1IMPLIB= ihwp

SHL1STDLIBS= \
        $(CPPULIB)		\
        $(CPPUHELPERLIB)\
        $(SALLIB)		\
        $(ZLIB3RDLIB)

.IF "$(GUI)"=="WNT"
SHL1STDLIBS+= \
        ole32.lib uuid.lib
.ENDIF			# "$(GUI)"=="WNT"		


SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
SHL1LIBS=   $(SLB)$/$(TARGET).lib
SHL1VERSIONMAP = hwp.map

DEF1NAME=$(SHL1TARGET)

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
