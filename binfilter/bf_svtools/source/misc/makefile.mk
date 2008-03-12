#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 08:56:48 $
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
PRJNAME=binfilter
TARGET=misc

ENABLE_EXCEPTIONS := TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

SRS1NAME=ehdl
SRC1FILES=\
    ctrltool.src\
    errtxt.src

SLOFILES=\
    $(SLO)$/svt_asynclink.obj			\
    $(SLO)$/svt_ctrltool.obj			\
    $(SLO)$/svt_embedhlp.obj            \
    $(SLO)$/svt_imageresourceaccess.obj \
    $(SLO)$/svt_templatefoldercache.obj \
    $(SLO)$/svt_urihelper.obj           \
    $(SLO)$/svt_ehdl.obj                \
    $(SLO)$/svt_flbytes.obj             \
    $(SLO)$/svt_imap.obj                \
    $(SLO)$/svt_imap2.obj               \
    $(SLO)$/svt_imap3.obj               \
    $(SLO)$/svt_ownlist.obj             \
    $(SLO)$/svt_vcldata.obj             \
    $(SLO)$/svt_restrictedpaths.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

