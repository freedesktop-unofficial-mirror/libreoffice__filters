/*************************************************************************
 *
 *  $RCSfile: fla.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2005-04-18 15:14:04 $
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
 *  Copyright 2000 by Sun Microsystems, Inc.
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
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

/*
This file include an implementation of FLA - a simple Funtional Language for Attributes. 
The language is LISP-like and has the following grammar:
FLA_Expression ::= '(' FLA_Operation FLA_Attribute+ ')'
FLA_Attribtute ::= FLA_Constant | FLA_Expression
FLA_Constant ::= '[' String ']'
The language currently supports the following operations:
"+"-Operation, e.g. (+[1][2]) = [3]
"-"-Operation, e.g. (-[3][2]) = [1]
"*"-Operation, e.g. (*[3][2]) = [6]
"/"-Operation, e.g. (-[6][2]) = [3]
"<"-Operation, e.g. (<[3][4]) = [t] resp. (<[4][3]) = []
"<="-Operation, e.g. (<=[3][4]) = [t] resp. (<=[4][3]) = []
">"-Operation, e.g. (>[3][4]) = [] resp. (>[4][3]) = [t]
">="-Operation, e.g. (>=[3][4]) = [] resp. (>=[4][3]) = [t]
Variable assignment, e.g. ($var1[4])
Variable access, e.g. (+($var1[4])($var1)($var1)) = [8]
Condition, e.g. (?[t][3][4])=[3] resp. (?[][3][4])=4
Priorized Choice, e.g. (|[4][5])=[4] resp. (|[][5])=[5]; i.e. result is the first occurrence of a non-[].
*/

#include "fla.hxx"
#include "sal/main.h"
#include <hash_map>


namespace FLA {


sal_Int32 Evaluator::evalFunc(const sal_Unicode*op, sal_Int32 opLen, sal_Int32 args, sal_Unicode* argv[10], sal_Unicode *result)
{
    if (opLen==1 && op[0]==L'+')
    {
        double res=0;
        for(sal_Int32 i=0;i<args;i++)
        {
            double v=rtl_ustr_toDouble(argv[i]);
            res+=v;
        }
        return rtl_ustr_valueOfDouble(result, res);
    }
    else if (opLen==1 && op[0]==L'-' && args>0)
    {
        double res=rtl_ustr_toDouble(argv[0]);
        for(sal_Int32 i=1;i<args;i++)
        {
            double v=rtl_ustr_toDouble(argv[i]);
            res-=v;
        }
        sal_Int32 _len= rtl_ustr_valueOfDouble(result, res);
        return _len;
    }
    else if (opLen==1 && op[0]==L'*')
    {
        double res=1;
        for(sal_Int32 i=0;i<args;i++)
        {
            double v=rtl_ustr_toDouble(argv[i]);
            res*=v;
        }
        return rtl_ustr_valueOfDouble(result, res);
    }
    else if (opLen==1 && op[0]==L'/' && args>0)
    {
        double res=rtl_ustr_toDouble(argv[0]);
        for(sal_Int32 i=1;i<args;i++)
        {
            double v=rtl_ustr_toDouble(argv[i]);
            res/=v;
        }
        return rtl_ustr_valueOfDouble(result, res);
    }
    else if (opLen==1 && op[0]==L'>' && args==2)
    {
        double p1=rtl_ustr_toDouble(argv[0]);
        double p2=rtl_ustr_toDouble(argv[1]);
        if (p1>p2)
        {
            result[0]=L't';
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    else if (opLen==1 && op[0]==L'<' && args==2)
    {
        double p1=rtl_ustr_toDouble(argv[0]);
        double p2=rtl_ustr_toDouble(argv[1]);
        if (p1<p2)
        {
            result[0]=L't';
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    else if (opLen==2 && op[0]==L'<' && op[1]==L'=' && args==2)
    {
        double p1=rtl_ustr_toDouble(argv[0]);
        double p2=rtl_ustr_toDouble(argv[1]);
        if (p1<=p2)
        {
            result[0]=L't';
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    else if (opLen==2 && op[0]==L'>' && op[1]==L'=' && args==2)
    {
        double p1=rtl_ustr_toDouble(argv[0]);
        double p2=rtl_ustr_toDouble(argv[1]);
        if (p1>=p2)
        {
            result[0]=L't';
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    else if (opLen>1 && op[0]==L'$' && args==0)
    {
        sal_Int32 reg=rtl_ustr_toInt32(op+1, 10);	
        int i=0; while(i<99 && environment[reg][i]!=L'\0') { result[i]=environment[reg][i]; i++; }
        result[i]=0;
        return i;
    }
    else if (opLen>1 && op[0]==L'$' && args==1)
    {
        sal_Int32 reg=rtl_ustr_toInt32(op+1, 10);	
        int i=0; while(i<99 && argv[0]!=NULL) { result[i]=argv[0][i]; environment[reg][i]=argv[0][i]; i++; }
        environment[reg][i]=0; result[i]=0;
        return i;
    }
    else if (opLen==1 && op[0]==L'?' && args==3)
    {
        sal_Unicode *source;
        if (argv[0][0]==L'\0')
        {
            source=argv[2];
        }
        else
        {
            source=argv[1];
        }
        int len=0; while (*source!=L'\0') result[len++]=*source++;
        result[len]=0;
        return len;
    }
    else if (opLen==1 && op[0]==L'|' && args>0)
    {
        sal_Unicode *source;
        int i=0; while (i<args && argv[i][0]==L'\0') i++;
        if (i<args)
        {
            source=argv[i];
            int len=0; while (*source!=L'\0') result[len++]=*source++;
            result[len]=0;
            return len;
        }
        else 
        {
            result[0]=0;
            return 0;
        }
    }
    else if (opLen==1 && op[0]==L'.' && args>0)
    {
        sal_Unicode *source;
        int len=0;
        for(sal_Int32 i=0;i<args;i++)
        {
            source=argv[i];
            while (*source!=L'\0') result[len++]=*source++;
        }
        result[len]=0;
        return len;
    }
    else if (opLen==8 && op[0]=='t' && op[1]=='w' && op[2]=='i' && op[3]=='p' && op[4]=='s' && op[5]=='2' && op[6]=='c' && op[7]=='m' && args==1)
    {
        double v=rtl_ustr_toDouble(argv[0]);
        return rtl_ustr_valueOfDouble(result, (v/567.0L));
    }
    else if (opLen==6 && op[0]=='s' && op[1]=='w' && op[2]=='i' && op[3]=='t' && op[4]=='c' && op[5]=='h' && args>2)
    {
        sal_Unicode *source;
        for(int i=1;i<args-1;i+=2)
        {
            if (rtl_ustr_compare(argv[0], argv[i])==0)
            {
                source=argv[i+1]; int len=0; while (*source!=L'\0') result[len++]=*source++;
                result[len]=0;
                return len;
            }
        }
        source=argv[args-1]; int len=0; while (*source!=L'\0') result[len++]=*source++;
        result[len]=0;
        return len;
//		double v=rtl_ustr_toDouble(argv[0]);
//		return rtl_ustr_valueOfDouble(result, (v/567.0L));
    }
    else
    {
        return 0;
    }
}


sal_Int32 Evaluator::evalExp(const sal_Unicode *expr, sal_Int32 exprLen, sal_Unicode *buf, sal_Int32 *bufLen)
{
    sal_Unicode ch;
    sal_Unicode* argv[10];
    sal_Int32 args=0;
    int offset=0; while(offset<exprLen && expr[offset]==' ') offset++;
    sal_Int32 startBuf=*bufLen;
    if(expr[offset]==L'(')
    {
        offset++;
        while(offset<exprLen && expr[offset]==' ') offset++;
        int op=offset;
        while(offset<exprLen && expr[offset]!=' ' && expr[offset]!='[' && expr[offset]!='('&& expr[offset]!=']' && expr[offset]!=')') offset++;
        int opLen=offset-op;
        bool done=false;
        while(offset<exprLen && !done)
        {
            switch(expr[offset])
            {
            case '(':
            case '[':
                argv[args++]=buf+*bufLen;
                offset+=evalExp(expr+offset, exprLen, buf, bufLen);
                buf[(*bufLen)++]=0;
                break;
            case ')':
                offset++;
                done=true;
                break;
            case ' ': /* skip */
                offset++;
                break;
            default: /* skip */
                offset++;
                break;
            };
        }
        if (done)
        {
            sal_Int32 len=evalFunc(expr+op, opLen, args, argv, buf+startBuf);
            *bufLen=startBuf+len;
        }

    }
    else if(expr[offset]==L'[')
    {
        offset++;
        argv[args++]=buf+*bufLen;
        while (offset<exprLen && (ch=expr[offset++])!=']')
        {
            buf[(*bufLen)++]=ch;
        }
        buf[(*bufLen)++]=0;
    }
    return offset;
}

const sal_Unicode *Evaluator::eval(const sal_Unicode *expr, sal_Int32 exprLen)
{

    sal_Int32 len=0;
    evalExp(expr, exprLen, _buf, &len);
    OSL_ASSERT(len<1024);
    return _buf;
}

};

/*
SAL_IMPLEMENT_MAIN_WITH_ARGS(argc, argv)
{
    FLA::Evaluator ev;
  for(int i=1;i<argc;i++)
    {
        rtl_uString *param=NULL;
        rtl_uString_newFromAscii(&param, argv[i]);
        ::rtl::OUString _param(param);
        const sal_Unicode *res=ev.eval(_param.getStr(), _param.getLength());
    }
    return 0;
}
*/
