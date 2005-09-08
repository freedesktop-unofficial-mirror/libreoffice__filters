#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-08 05:28:45 $
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
TARGET=svx_engine3d

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SRS1NAME=svx_engine3d
SRC1FILES=\
        svx_string3d.src	\
        svx_float3d.src

SLOFILES= \
        $(SLO)$/svx_svx3ditems.obj	\
        $(SLO)$/svx_deflt3d.obj		\
        $(SLO)$/svx_class3d.obj		\
        $(SLO)$/svx_e3dundo.obj      \
        $(SLO)$/svx_volume3d.obj		\
        $(SLO)$/svx_viewpt3d.obj		\
        $(SLO)$/svx_camera3d.obj		\
        $(SLO)$/svx_poly3d.obj 		\
        $(SLO)$/svx_polygn3d.obj 		\
        $(SLO)$/svx_volmrk3d.obj 	\
        $(SLO)$/svx_objfac3d.obj 	\
        $(SLO)$/svx_obj3d.obj 		\
        $(SLO)$/svx_light3d.obj 		\
        $(SLO)$/svx_dlight3d.obj 	\
        $(SLO)$/svx_plight3d.obj 	\
        $(SLO)$/svx_pntobj3d.obj     \
        $(SLO)$/svx_polyob3d.obj		\
        $(SLO)$/svx_scene3d.obj		\
        $(SLO)$/svx_polysc3d.obj		\
        $(SLO)$/svx_cube3d.obj		\
        $(SLO)$/svx_sphere3d.obj		\
        $(SLO)$/svx_extrud3d.obj     \
        $(SLO)$/svx_lathe3d.obj		\
        $(SLO)$/svx_label3d.obj		\
        $(SLO)$/svx_dragmt3d.obj		\
        $(SLO)$/svx_view3d.obj		\
        $(SLO)$/svx_view3d1.obj       \
        $(SLO)$/svx_e3dcmpt.obj       \
        $(SLO)$/svx_float3d.obj

 SVXLIGHTOBJFILES= \
        $(OBJ)$/svx_svx3ditems.obj		\
        $(OBJ)$/svx_deflt3d.obj		\
        $(OBJ)$/svx_class3d.obj		\
        $(OBJ)$/svx_volume3d.obj		\
        $(OBJ)$/svx_viewpt3d.obj		\
        $(OBJ)$/svx_camera3d.obj		\
        $(OBJ)$/svx_poly3d.obj 		\
        $(OBJ)$/svx_polygn3d.obj 		\
        $(OBJ)$/svx_volmrk3d.obj 	\
        $(OBJ)$/svx_objfac3d.obj 	\
        $(OBJ)$/svx_obj3d.obj 		\
        $(OBJ)$/svx_light3d.obj 		\
        $(OBJ)$/svx_dlight3d.obj 	\
        $(OBJ)$/svx_plight3d.obj 	\
        $(OBJ)$/svx_pntobj3d.obj     \
        $(OBJ)$/svx_polyob3d.obj		\
        $(OBJ)$/svx_scene3d.obj		\
        $(OBJ)$/svx_polysc3d.obj		\
        $(OBJ)$/svx_cube3d.obj		\
        $(OBJ)$/svx_sphere3d.obj		\
        $(OBJ)$/svx_extrud3d.obj     \
        $(OBJ)$/svx_lathe3d.obj		\
        $(OBJ)$/svx_label3d.obj		\
        $(OBJ)$/svx_view3d.obj		\
        $(OBJ)$/svx_view3d1.obj       \
        $(OBJ)$/svx_e3dcmpt.obj


.IF "$(COM)"=="ICC"
NOOPTFILES=\
    $(SLO)$/svx_class3d.obj
.ENDIF

.INCLUDE :  target.mk

