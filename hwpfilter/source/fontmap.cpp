/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fontmap.cpp,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 00:52:34 $
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

#include <stdio.h>
#ifdef SOLARIS
#include <strings.h>
#else
#include <string.h>
#endif

// #i42367# prevent MS compiler from using system locale for parsing
#ifdef _MSC_VER
#pragma setlocale("C")
#endif


struct FontEntry
{
    const char *familyname;
    int key;
     double ratio;
};
/**
 * ratio�� �ѱ� 70%, ���� 10% ���� 20%�� ������ �����Ǿ��ٴ� �����Ͽ� ��������.
 */
const struct FontEntry FontMapTab[] =
{
    {"����",0, 0.97},
    {"���",1, 0.97},
    {"����",1, 0.97},
    {"�ʱ�",0, 0.97},
    {"�ý���",1, 0.84},
    {"�ý��� ����",1, 0.84},
    {"�ý��� ����",1, 0.84},
    {"HY�ձ� ���",2, 0.97},
    {"���ѱ�",0, 0.97},
    {"���°���",0, 0.72},
    {"�߰�����",0, 0.72},
    {"��������",0, 0.72},
    {"������",0, 0.72},
    {"�߰���",0, 0.72},
    {"������",0, 0.72},
    {"�޸ո���",0, 0.97},
    {"�޸հ��",1, 0.97},
    {"���¾Ȼ��ü",0, 0.55},
    {"�߰��Ȼ��ü",0, 0.637},
    {"�����Ȼ��ü",0, 0.63},
    {"�޸հ��»�ü",0, 0.666},
    {"�޸��߰���ü",0, 0.685},
    {"�޸ձ�����ü",0, 0.727},
    {"�޸հ�����ü",0, 0.666},
    {"�޸��߰���ü",0, 0.685},
    {"�޸ձ�����ü",0, 0.727},
    {"�޸տ�ü",3, 0.97},
    {"�Ѿ�Ÿ���",0, 0.97},
    {"�Ѿ�߸���",1, 0.97},
    {"�Ѿ��߰��",1, 0.97},
    {"�Ѿ�߰��",1, 0.97},
    {"�Ѿ�׷���",0, 0.97},
    {"�Ѿ�ü�",3, 0.97},
    {"��ȭ����",0, 0.97},
    {"��ȭ��������",1, 0.97},
    {"��ȭ����",1, 0.97},
    {"��ȭ��������",0, 0.97},
    {"��ȭ����",0, 0.97},
    {"��ȭ�����긲",0, 0.97},
    {"���긲",0, 0.97},
    {"������",0, 0.827},
    {"������",0, 0.97},
    {"����",0, 0.97},
    {"����",0, 0.97},
    {"������",2, 0.97},
    {"����",3, 0.97},
    {"Ÿ����",0, 0.987},
    {"�� ����",1, 0.97},
    {"�� ������",0, 0.97},
    {"�� ���� ������",0, 0.97},
    {"�� ������T",0, 0.97},
    {"�� ���� ������T",0, 0.97},
    {"���� �ٿ����M",0, 0.97},
    {"���� ����M",0, 0.97},
    {"���� �ҽ�",1, 0.97},
    {"���� ��ȭ",1, 0.987},
    {"���� ưư",0, 0.97},
    {"���� ����",1, 0.97},
    {"���� �ѱ�",0, 0.97},
    {"���� ����",1, 0.97},
    {"���� �ʹ�",1, 0.97},
    {"�Ÿ� ������",0, 0.97},
    {"�Ÿ� �Ÿ���",0, 0.97},
    {"�Ÿ� �ŽŸ���",0, 0.97},
    {"�Ÿ� �߸���",0, 0.97},
    {"�Ÿ� �¸���",0, 0.97},
    {"�Ÿ� �߸���",0, 0.97},
    {"�Ÿ� �Ź�����",0, 0.97},
    {"�Ÿ� ������",0, 0.97},
    {"�Ÿ� �����",1, 0.97},
    {"�Ÿ� �߰��",1, 0.97},
    {"�Ÿ� �°��",1, 0.97},
    {"�Ÿ� �߰��",1, 0.97},
    {"�Ÿ� ������",2, 0.97},
    {"�Ÿ� �𳪷�",2, 0.97},
    {"�Ÿ� �ű׷���",2, 0.97},
    {"�Ÿ� �±׷���",2, 0.97},
    {"�Ÿ� �ü�",3, 0.97}
};

#define FONTCOUNT 4
#ifndef WIN32
#if defined(LINUX)
char* RepFontTab[] =
{
    "�鹬 ����",                                     /* 0 */
    "�鹬 ����",                                      /* 1 */
    "�鹬 ����",                                      /* 2 */
    "�鹬 ������"                                      /* 3 */
};
#else
const char* RepFontTab[] =
{
    "Batang",                                     /* 0 */
    "Dotum",                                      /* 1 */
    "Gulim",                                      /* 2 */
    "Gungso"                                      /* 3 */
};
#endif
#else
char* RepFontTab[] =
{
    "����",                                       /* 0 */
    "����",                                       /* 1 */
    "����",                                       /* 2 */
    "�ü�"                                        /* 3 */
};
#endif

int getRepFamilyName(const char* orig, char *buf, double &ratio)
{
    int i;
    int size = sizeof(FontMapTab)/sizeof(FontEntry);
    for( i = 0 ; i < size ; i++)
    {
        if( !strcmp(orig, FontMapTab[i].familyname) ){
                ratio = FontMapTab[i].ratio;
            return strlen( strcpy(buf,RepFontTab[FontMapTab[i].key]) );
          }
    }
     ratio = FontMapTab[0].ratio;
    return strlen( strcpy(buf, RepFontTab[0] ) );
}
