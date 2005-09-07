/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hcode.h,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:33:24 $
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

/* $Id: hcode.h,v 1.2 2005-09-07 16:33:24 rt Exp $ */

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
