/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: scerrors.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:26:25 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _SCERRORS_HXX
#define _SCERRORS_HXX

// auto strip #ifndef _ERRCODE_HXX //autogen
// auto strip #include <tools/errcode.hxx>
// auto strip #endif

// ERRCODE_CLASS_READ - file related, displays "Read-Error" in MsgBox
#define SCERR_IMPORT_CONNECT        (   1 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_OPEN           (   2 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_UNKNOWN        (   3 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_IMPORT_OUTOFMEM       (   4 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_IMPORT_UNKNOWN_WK     (   5 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_FORMAT         (   6 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_NI             (   7 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_IMPORT_UNKNOWN_BIFF   (   8 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_IMPORT_NI_BIFF        (   9 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_IMPORT_FILEPASSWD     (  10 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_IMPORT_INTERNAL       (  11 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_8K_LIMIT       (  12 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
//STRIP001 #define SCWARN_IMPORT_OPEN_FM3      (  13 | ERRCODE_CLASS_READ | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
//STRIP001 #define SCWARN_IMPORT_WRONG_FM3     (  14 | ERRCODE_CLASS_READ | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_INFOLOST      (  15 | ERRCODE_CLASS_READ | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCERR_IMPORT_FILE_ROWCOL    (  16 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCERR_IMPORT_FORMAT_ROWCOL  (  17 | ERRCODE_CLASS_READ | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_FILE_ROWCOL   (  18 | ERRCODE_CLASS_READ | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

// ERRCODE_CLASS_WRITE - file related, displays "Write-Error" in MsgBox
//STRIP001 #define SCERR_EXPORT_CONNECT        (   1 | ERRCODE_CLASS_WRITE | ERRCODE_AREA_SC )
//STRIP001 #define SCERR_EXPORT_DATA           (   2 | ERRCODE_CLASS_WRITE | ERRCODE_AREA_SC )

// ERRCODE_CLASS_IMPORT - does not display "Read-Error" in MsgBox
#define SCWARN_IMPORT_RANGE_OVERFLOW (  1 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_ROW_OVERFLOW (  2 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_COLUMN_OVERFLOW (  3 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_IMPORT_SHEET_OVERFLOW (  4 | ERRCODE_CLASS_IMPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

// ERRCODE_CLASS_EXPORT - does not display "Write-Error" in MsgBox
//STRIP001 #define SCWARN_EXPORT_NONCONVERTIBLE_CHARS  (   1 | ERRCODE_CLASS_EXPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
//STRIP001 #define SCWARN_EXPORT_ASCII         (   2 | ERRCODE_CLASS_EXPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
#define SCWARN_EXPORT_MAXROW        (   3 | ERRCODE_CLASS_EXPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )
//STRIP001 #define SCWARN_EXPORT_DATALOST      (   4 | ERRCODE_CLASS_EXPORT | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

// ERRCODE_CLASS_GENERAL
#define SCWARN_CORE_HARD_RECALC     (   1 | ERRCODE_CLASS_GENERAL | ERRCODE_WARNING_MASK | ERRCODE_AREA_SC )

#endif

