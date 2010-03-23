#!/usr/bin/perl
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

####################################################################
# File Name: template.pl
# Version  : 1.0
# Project  : XMerge
# Author   : Brian Cameron
# Date	   : 5th Sept. 2001
#
# Takes x and y from the command line and taps the screen there.
# Assumes pose is already running.
#
##########################################################################

if ($#ARGV != 1)
{
  print "\nUsage: $0 x y\n\n";
  exit -1;
}

use lib "$ENV{qa-dir}/lib";
use converterlib;

# Put commands to run between the open_connection() and
# close_connection() calls...
#
open_connection();

TapPen($ARGV[0], $ARGV[1]);

close_connection();


