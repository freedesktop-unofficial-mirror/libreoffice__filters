#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: rt $ $Date: 2005-09-08 21:35:57 $
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

PRJ     = ..$/..$/..$/..
TARGET  = FCFGMerge
PRJNAME = $(TARGET)
PACKAGE = com$/sun$/star$/filter$/config$/tools$/merge

# --- Settings -----------------------------------------------------

.INCLUDE: settings.mk

#----- compile .java files -----------------------------------------

OWNCOPY         =   \
                    $(MISC)$/$(TARGET)_copied.done

JARFILES        =   \
                    ridl.jar        \
                    unoil.jar       \
                    jurt.jar        \
                    juh.jar         \
                    jut.jar         \
                    java_uno.jar

CFGFILES        =   \
                    FCFGMerge.cfg

JAVACLASSFILES  =   \
                    $(CLASSDIR)$/$(PACKAGE)$/Merger.class     \
                    $(CLASSDIR)$/$(PACKAGE)$/FCFGMerge.class

CUSTOMMANIFESTFILE     =   \
                    Manifest.mf

MAXLINELENGTH   =   100000

#----- make a jar from compiled files ------------------------------

JARCLASSDIRS    =   \
                    com$/sun$/star$/filter$/config$/tools$/utils    \
                    com$/sun$/star$/filter$/config$/tools$/merge

JARTARGET       =   $(TARGET).jar

JARCOMPRESS     =   TRUE

# --- targets -----------------------------------------------------

.INCLUDE :  target.mk

.IF "$(SOLAR_JAVA)" != ""
ALLTAR : $(OWNCOPY)

.IF "$(JARTARGETN)" != ""
$(JARTARGETN) : $(OWNCOPY)
.ENDIF

$(OWNCOPY) : $(CFGFILES)
    +-$(MKDIR) $(CLASSDIR)$/$(PACKAGE)
    +$(COPY) $? $(CLASSDIR)$/$(PACKAGE) && $(TOUCH) $@

.ENDIF # "$(SOLAR_JAVA)" != ""
