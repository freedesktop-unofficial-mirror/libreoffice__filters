/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: nfversi.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:20:25 $
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

#ifndef NF_NFVERSI_HXX
#define NF_NFVERSI_HXX

//		file ID's

#define SV_NUMBERFORMATTER_VERSION_SYSTORE		0x0004
#define SV_NUMBERFORMATTER_VERSION_KEYWORDS		0x0005
#define SV_NUMBERFORMATTER_VERSION_NEWSTANDARD	0x0006
#define SV_NUMBERFORMATTER_VERSION_NF_TIME_HH_MMSS00	0x0007
#define SV_NUMBERFORMATTER_VERSION_NF_DATE_WW	0x0008
#define SV_NUMBERFORMATTER_VERSION_NEW_CURR		0x0009
#define SV_NUMBERFORMATTER_VERSION_YEAR2000		0x000a
#define SV_NUMBERFORMATTER_VERSION_TWODIGITYEAR	0x000b
#define SV_NUMBERFORMATTER_VERSION_NF_DATETIME_SYS_DDMMYYYY_HHMMSS	0x000c
#define SV_NUMBERFORMATTER_VERSION_CALENDAR		0x000d
#define SV_NUMBERFORMATTER_VERSION_ADDITIONAL_I18N_FORMATS	0x000e

#define SV_NUMBERFORMATTER_VERSION				0x000e

// 1 bis 18.01.96
// 2 ab  19.01.96, TT.MM.JJJJ dazu
// 3 ab  13.02.96 (nicht emergency) #.##0,00 CCC dazu
// 4 ab  30.07.97 364i speichern, was SYSTEM wirklich war (vorhandenes
//					Dummy-Feld wird benutzt, keine File-Format Aenderung)
// 5 ab  07.08.97 nicht-deutsch ist nicht immer englisch
//					aeltere nicht-deutsche benutzerdefinierte Formate onLoad
//					konvertieren
// 6 ab  17.10.97 neu: Keyword NNN fuer langen Wochentag ohne Separator,
//					wird in aelteren Versionen nicht ausgewertet!
//					Neue Standard Datumformate, DIN etc.
// 7 ab  25.05.98 StandardFormat [HH]:MM:SS,00 (NF_TIME_HH_MMSS00) fuer
//					automatische Eingabe-Erkennung von 100stel Sekunden mit Stunden
// 8 ab  19.06.98 StandardFormat WW (NF_DATE_WW) fuer Kalenderwoche
// 9 ab  17.12.98 neue Waehrungsformate [$DM-xxx]
// A ab  25.01.99 Year2000 speichern/laden
// B ab  12.02.99 Year2000 ist allgemeines TwoDigitYearStart
// C     ??.??.?? date/time format of system variables
// D     23.11.00 new calendar
// E     19.01.01 additional formats provided by i18n

#endif

