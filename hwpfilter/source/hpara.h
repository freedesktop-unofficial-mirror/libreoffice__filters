/*************************************************************************
 *
 *  $RCSfile: hpara.h,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: dvo $ $Date: 2003-10-15 14:36:22 $
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

/* $Id: hpara.h,v 1.1 2003-10-15 14:36:22 dvo Exp $ */

#ifndef _HWPPARA_H_
#define _HWPPARA_H_

#include <hwplib.h>
#include <hwpfile.h>
#include <hinfo.h>

class HBox;

/**
 * etc flag
 * 0 bit : Use page columns
 * 1 bit : Use page lows
 * 2 bit : Use section break
 * 3 bit : Block start
 * 4 bit : In Block
 * 5 bit : Block end
 * 6 bit : Preserve widow orphan
 * 7 bit : Reserved
 */
enum
{
    PA_USER_COLUMN    =   1,
    PA_USER_PAGE      =   2,                      /* p user_page definiton */
    PA_SECTION_BREAK  =   4,
    PA_BLOCK_BEGIN    =   8,
    PA_IN_BLOCK       =   16,
    PA_BLOCK_END      =   32,
    PA_WIDOW_ORPHAN   =   64
};

class HWPPara;
#define FIXED_SPACING_BIT (0x8000)

struct LineInfo
{
//�����ϴ� ������ ��ġ : ��Ʈ���� ���� ���̸� ������
/**
 * Starting character position
 */
    unsigned short    pos;
    hunit         space_width;
    hunit         height;
    hunit         pgy;                            /* internal */
    hunit         sx;                             /* internal */
    hunit         psx;                            /* internal */
    hunit         pex;                            /* internal */
// for formating
    hunit         height_sp;
    unsigned short    softbreak;                  // column, page, section

    bool  Read(HWPFile &hwpf, HWPPara *para);
};
/**
 * It represents the paragraph.
 * @short Paragraph
 */
class DLLEXPORT HWPPara
{
    private:
        HWPPara       *_next;

    public:
// paragraph information
/**
 * Zero is for the new paragraph style.
 */
        unsigned char     reuse_shape;            /* 0�̸� ����� */
        unsigned short    nch;
        unsigned short    nline;

// realking
        hunit         begin_ypos;
        unsigned char     scflag;

/**
 * If the value is 0, all character of paragraph have same style given cshape
 */
        unsigned char     contain_cshape;         /* 0�̸� ��� ���ڰ� ��ǥ ���� ��� */
        unsigned char     etcflag;
/**
 * Checks the special characters in the paragraph
 */
        unsigned long     ctrlflag;
        unsigned char     pstyno;
        CharShape     cshape;                     /* ���ڰ� ��� ���� ����϶�	*/
        ParaShape     pshape;                     /* reuse flag�� 0�̸�		*/
        int           pno;                        /* run-time only		*/

        LineInfo      *linfo;
        CharShape     *cshapep;
/**
 * Box object list
 */
        HBox          **hhstr;

        HWPPara(void);
        ~HWPPara(void);

        int   Read(HWPFile &hwpf, unsigned char flag = 0);
        int   Write(CTextOut &txtf);
        int   Write(CHTMLOut &html);

        void  SetNext(HWPPara *n) { _next = n; };

// layout�� ���� �Լ�
/**
 * Get line information of given line
 */
        LineInfo *GetLineInfo(int line);
/**
 * Returns the character sytle of paragraph.
 */
        CharShape *GetCharShape(int pos);
/**
 * Returns the sytle of paragraph.
 */
        ParaShape *GetParaShape(void);

/**
 * Returns previous paragraph.
 */
        HWPPara *Prev(void);
/**
 * Returns next paragraph.
 */
        HWPPara *Next(void);

        int HomePos(int line) const;
        int EndPos(int line) const;
        int LineLen(int line) const;

    private:
        HBox *readHBox(HWPFile &);
};

// inline functions

inline int HWPPara::HomePos(int line) const
{
    if( nline < line + 1 ) return nch;
    return linfo[line].pos;
}


inline int HWPPara::EndPos(int line) const
{
    if( nline <= line + 1 ) return nch;
    else return HomePos(line + 1);
}


inline int HWPPara::LineLen(int line) const
{
    return EndPos(line) - HomePos(line);
}
#endif                                            /* _HWPPARA_H_ */
