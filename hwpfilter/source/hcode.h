/*************************************************************************
 *
 *  $RCSfile: hcode.h,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: dvo $ $Date: 2003-10-15 14:35:27 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2001 by Mizi Research Inc.
 *  Copyright 2003 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Mizi Research Inc.
 *
 *  Copyright: 2001 by Mizi Research Inc.
 *  Copyright: 2003 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

/* $Id: hcode.h,v 1.1 2003-10-15 14:35:27 dvo Exp $ */

#ifndef _HCODE_H_
#define _HCODE_H_

#include "hwplib.h"

/**
 * Codetype of Korean
 * KSSM - Johap, KS - Wansung
 */
enum { KSSM, KS, UNICODE };
/**
 *   Transfer combination-code for internal using of hwp to ascii
 */
DLLEXPORT int hcharconv(hchar ch, hchar *dest, int codeType) ;

DLLEXPORT int   kssm_hangul_to_ucs2(hchar ch, hchar *dest) ;
DLLEXPORT hchar ksc5601_han_to_ucs2 (hchar);
DLLEXPORT hchar ksc5601_sym_to_ucs2 (hchar);
DLLEXPORT hchar* hstr2ucsstr(hchar* hstr, hchar* ubuf);
/**
 * ���Ľ�Ʈ���� �ϼ�����Ʈ������ ��ȯ�Ѵ�.
 */
DLLEXPORT int hstr2ksstr(hchar* hstr, char* buf);

/**
 * �ѱ��� ������ �� �ִ� char����Ʈ���� ���Ľ�Ʈ������ ��ȯ�Ѵ�.
 */
DLLEXPORT hchar *kstr2hstr( uchar *src, hchar *dest );

/**
 * hwp�� ��θ� unix���·� �ٲ۴�.
 */
DLLEXPORT char *urltounix(const char *src, char *buf );

/**
 * hwp�� ��θ� windows���·� �ٲ۴�.
 */
#ifdef _WIN32
DLLEXPORT char *urltowin(const char *src, char *buf );
#endif
/**
 *  Transfer interger to string following format
 */
DLLEXPORT char* Int2Str(int value, const char *format, char *buf);

/**
 * color�ε��� ���� �������� �����Ͽ� ��Ÿ���ǽ��� color�� ��ȯ
 */
DLLEXPORT char *hcolor2str(uchar color, uchar shade, char *buf, bool bIsChar = false);

DLLEXPORT char *base64_encode_string( const uchar *buf, unsigned int len );
DLLEXPORT double calcAngle(int x1, int y1, int x2, int y2);


#endif                                            /* _HCODE_H_ */
