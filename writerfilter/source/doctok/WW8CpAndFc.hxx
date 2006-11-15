/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: WW8CpAndFc.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hbrinkm $ $Date: 2006-11-15 16:31:22 $
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

#ifndef INCLUDED_WW8_CP_AND_FC_HXX
#define INCLUDED_WW8_CP_AND_FC_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
#ifndef INCLUDED_DOCUMENT_HXX
#include <doctok/WW8Document.hxx>
#endif
#include <set>
#include <hash_map>
#include <iostream>

namespace doctok 
{
using namespace ::std;

template <class T>
bool operator <= (const T & rA, const T & rB)
{
    return ! ( rB < rA );
}

/**
   A character position.

   This is a wrapper to make the type for WW8 character position (CP)
   distinct from WW8 file character positions (FC).
*/
struct Cp
{
    sal_uInt32 nCp; // the WW8 character position

    Cp() : nCp(0) {}

    Cp(sal_uInt32 nCp_) : nCp(nCp_) {}

    /**
       Returns the WW8 character position. 
       
       @return the WW8 character position
    */
    sal_uInt32 get() const { return nCp; }

    /**
       Sets the WW8 character position.

       @param nCp_    the WW8 character position to set
    */
    void set(sal_uInt32 nCp_) { nCp = nCp_; }

    /**       
       Calculate CP moved backward.       

       None of the involved CPs is changed.

       @param n     amount of movement

       @return CP moved @n steps backward
     */
    sal_uInt32 operator - (const Cp & rCp) const
    { return nCp - rCp.nCp; }

    /**       
       Calculate CP moved forward.       

       None of the involved CPs is changed.

       @param n     amount of movement

       @return CP moved @n steps forward
     */
    Cp operator + (sal_uInt32 n) const
    { return Cp(nCp + n); }

    /**
       Advance CP forward.

       @attention The CP is altered.

       @param n      amount of movement

       @return  CP moved @n steps forward
     */
    Cp & operator += (sal_uInt32 n)
    {
        nCp += n;

        return *this;
    }

    /**
       Return string representation of CP.
     */
    string toString() const;

    friend bool operator < (const Cp & rA, const Cp & rB);
    friend bool operator == (const Cp & rA, const Cp & rB);
    friend ostream & operator << (ostream & o, const Cp & rCp);
};

/**
   A file character position.

   This is a wrapper to make the type for WW8 character position (CP)
   distinct from WW8 file character positions (FC).

   \see{Cp}
*/
struct Fc
{
    sal_uInt32 mnFc; // the WW8 character position
    bool mbComplex;

    Fc() : mnFc(0), mbComplex(false) {}

    Fc(sal_uInt32 nFc, bool bComplex = true) 
    : mnFc(nFc), mbComplex(bComplex) 
    {}

    sal_uInt32 complexFactor() const { return mbComplex ? 1 : 2; }

    /**
       Returns the WW8 character position. 
       
       @return the WW8 character position
    */
    sal_uInt32 get() const { return mnFc; }

    /**
       Sets the WW8 file character position.

       @param nFc    the WW8 file character position to set
    */
    void set(sal_uInt32 nFc) { mnFc = nFc; }

    /**
       Set if the FC is complex.

       @param bComplex      true if FC is set to be complex
     */
    void setComplex(bool bComplex) { mbComplex = bComplex; }

    /**
       Return if FC is complex.

       @retval true   FC is complex
       @retval false  else
     */
    bool isComplex() const { return mbComplex; }

    /**
       Distance of FCs.

       None of the involved FCs is changed.

       @param  rFc      FC to calculate distance to

       @return Distance from @a rFc to this FC
     */
    sal_uInt32 operator - (const Fc & rFc) const
    { return (mnFc - rFc.mnFc) / complexFactor(); }

    /**
       Calculate FC moved backward.       

       None of the involved FCs is changed.

       @param n     amount of movement

       @return FC moved @n steps backward
     */
    Fc operator - (sal_uInt32 n) const
    { return Fc(mnFc - n * complexFactor(), mbComplex); }

    /**
       Calculate FC moved forward.       

       None of the involved FCs is changed.

       @param n     amount of movement

       @return FC moved @n steps Forward
     */
    Fc operator + (sal_uInt32 n) const
    { return Fc(mnFc + n * complexFactor(), mbComplex); }

    /**
       Return string representation of FC.
     */
    string toString() const;

    friend bool operator < (const Fc & rA, const Fc & rB);
    friend bool operator == (const Fc & rA, const Fc & rB);
    friend ostream & operator << (ostream & o, const Fc & rFc);
};

/**
   A character position and a corresponding file character position
   paired.   
 */
class CpAndFc
{
private:
    /**
       character position
    */
    Cp mCp;

    /**
       file character position
    */
    Fc mFc;

    /**
       property type
    */
    PropertyType mType;
        
public:
    CpAndFc() {}
    CpAndFc(const Cp & rCp, const Fc & rFc, PropertyType eType_);

    /**
       Return character position.
    */
    const Cp & getCp() const { return mCp; }

    /**
       Return file character position.
    */
    const Fc & getFc() const { return mFc; }

    /**
       Return property type.
    */
    PropertyType getType() const { return mType; }

    /**
       Return if FC is complex.
    
       @retval true    FC is complex
       @retval false   else
     */
    bool isComplex() const { return mFc.isComplex(); }

    /**
       Return the distance to other CpAndFc.

       @param  rCpAndFc    the other CpAndFc

       @return the distance from the CP in @a rCpAndFc to the CP in
       CpAndFc.
     */
    sal_uInt32 operator-(const CpAndFc & rCpAndFc) const
    { return mCp - rCpAndFc.mCp; }

    /**
       Return string representation of the CpAndFc.
    */
    string toString() const;

    friend bool operator < (const CpAndFc & rA, const CpAndFc & rB);
    friend bool operator == (const CpAndFc & rA, const CpAndFc & rB);
    friend ostream & operator << (ostream & o, const CpAndFc & rCpAndFc);
};

struct CpAndFcLess
{
    CpAndFcLess()
    {
    }

    bool operator()(const CpAndFc & rA, const CpAndFc & rB) const
    {
        return rA < rB;
    }

    bool operator()(const CpAndFc & rA, const Cp & rB) const
    {
        return rA.getCp() < rB;
    }

    bool operator()(const Cp & rA, const CpAndFc & rB) const
    {
        return rA < rB.getCp();
    }
};


typedef set<CpAndFc, CpAndFcLess> CpAndFcs;

ostream & operator << (ostream & o, const CpAndFcs & rCpAndFcs);

struct CpHash
{
    size_t operator()(const Cp & rCp) const
    {
        return rCp.get();
    }
};

struct FcHash
{
    size_t operator()(const Fc & rFc) const
    {
        return rFc.get();
    }
};

struct CpEq
{
    bool operator() (const Cp & rA, const Cp &rB) const
    {
        return rA == rB;
    }
};

struct CpAndFcHash
{
    size_t operator()(const CpAndFc & rCpAndFc) const
    {
        CpHash aHash;
        
        return aHash(rCpAndFc.getCp());
    }
};

typedef hash_map<Cp, Fc, CpHash, CpEq> Cp2FcHashMap_t;

} // namespace doctok

#endif // INCLUDED_WW8_CP_AND_FC_HXX
