#!/usr/bin/perl
#########################################################################

 #*************************************************************************
 #
 #   OpenOffice.org - a multi-platform office productivity suite
 #
 #   $RCSfile: tappen.pl,v $
 #
 #   $Revision: 1.3 $
 #
 #   last change: $Author: ihi $ $Date: 2006-08-01 12:46:16 $
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


