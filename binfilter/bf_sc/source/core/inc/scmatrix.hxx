/*************************************************************************
 *
 *  $RCSfile: scmatrix.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:21 $
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

#ifndef SC_MATRIX_HXX
#define SC_MATRIX_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
class SvStream;
namespace binfilter {

#define SC_MATVAL_STRING	0x01
#define SC_MATVAL_EMPTY		0x03	// EMPTY is empty string plus flag

union MatValue
{
    double fVal;
    String* pS;

    /// Only valid if ScMatrix methods indicate so!
    const String& GetString() const		{ return pS ? *pS : EMPTY_STRING; }
};

/** Matrix representation of double values and strings.

    @ATTENTION: optimized for speed and double values.

     Matrix elements are not initialized after construction.

     All methods using an ULONG nIndex parameter and all Is... methods don't
    check the range for validity! However, the Put... and Get... methods using
    USHORT nCol/nRow parameters do check the range. <p>

    GetString( ULONG nIndex ) does not check if there really is a string, do
    this with IsString() first. GetString( USHORT nC, USHORT nR ) does check
    it and returns and empty string if there is no string. Both GetDouble()
    methods don't check for a string, do this with IsNumeric() or IsString()
    or IsValue() first. <p>

     PutDouble() does not reset an eventual string! Use
    PutDoubleAndResetString() if that is wanted. Also the FillDouble...()
    methods don't reset strings. As a consequence memory leaks may occur if
    used wrong.
 */
class ScMatrix
{
    USHORT nAnzCol;
    USHORT nAnzRow;
    MatValue* pMat;
    BYTE* bIsString;

    void ResetIsString();
    void DeleteIsString();
    void CreateMatrix(USHORT nC, USHORT nR);

    // pStr may be NULL, bFlag MUST NOT be 0
    void PutStringEntry( const String* pStr, BYTE bFlag, ULONG nIndex );

public:

    /// The maximum number of elements a matrix may have at runtime
    inline static ULONG GetElementsMax()
    {
        const size_t nMemMax = (((size_t)(~0))-64) / sizeof(MatValue);
        const ULONG nArbitraryLimit = 0x80000;	// 512k elements ~= 4MB memory
        return nMemMax < nArbitraryLimit ? nMemMax : nArbitraryLimit;
    }

    ScMatrix(USHORT nC, USHORT nR)				{ CreateMatrix(nC, nR); }
    ~ScMatrix();
    ScMatrix* Clone() const;
    BOOL HasMat() const							{ return pMat != NULL; }

    ScMatrix(SvStream& rStream);
    void Store(SvStream& rStream) const;

    void GetDimensions(USHORT& rC, USHORT& rR) const { rC = nAnzCol; rR = nAnzRow; };
    ULONG GetElementCount() const       { return (ULONG) nAnzCol * nAnzRow; }
    void PutDouble(double fVal, USHORT nC, USHORT nR);
    void PutDouble(double fVal, ULONG nIndex) 	 	 { pMat[nIndex].fVal = fVal; }
//STRIP001 	void PutDoubleAndResetString( double fVal, USHORT nC, USHORT nR );
//STRIP001 	void PutDoubleAndResetString( double fVal, ULONG nIndex );
    void PutString(const String& rStr, USHORT nC, USHORT nR);
    void PutString(const String& rStr, ULONG nIndex);
    void PutEmpty(USHORT nC, USHORT nR);
    void PutEmpty(ULONG nIndex);
    void FillDouble( double fVal, USHORT nC1, USHORT nR1, USHORT nC2, USHORT nR2 );
    void FillDoubleLowerLeft( double fVal, USHORT nC2 );	// lower left triangle
    /// @return 0.0 if empty
    double GetDouble(USHORT nC, USHORT nR) const;
    /// @return 0.0 if empty
    double GetDouble(ULONG nIndex) const		{ return pMat[nIndex].fVal; }
    const String& GetString(USHORT nC, USHORT nR) const;
    const String& GetString(ULONG nIndex) const
        { return pMat[nIndex].GetString(); }

    /// @ATTENTION: If bString the MatValue->pS may still be NULL to indicate
    /// an empty string!
    const MatValue* Get(USHORT nC, USHORT nR, BOOL& bString) const;

    /// @return <TRUE/> if string or empty
    BOOL IsString( ULONG nIndex ) const
        { return bIsString && bIsString[nIndex]; }
    /// @return <TRUE/> if string or empty
    BOOL IsString( USHORT nC, USHORT nR ) const
        { return bIsString && bIsString[ (ULONG) nC * nAnzRow + nR ]; }
    BOOL IsEmpty( ULONG nIndex ) const
        { return bIsString && bIsString[nIndex] == SC_MATVAL_EMPTY; }
    BOOL IsEmpty( USHORT nC, USHORT nR ) const
        { return bIsString && bIsString[ (ULONG) nC * nAnzRow + nR ] == SC_MATVAL_EMPTY; }
    BOOL IsValue( ULONG nIndex ) const
        { return !bIsString || !bIsString[nIndex]; }
    BOOL IsValue( USHORT nC, USHORT nR ) const
        { return !bIsString || !bIsString[ (ULONG) nC * nAnzRow + nR ]; }
    BOOL IsValueOrEmpty( ULONG nIndex ) const
        { return !bIsString || !bIsString[nIndex] || bIsString[nIndex] == SC_MATVAL_EMPTY; }
    BOOL IsValueOrEmpty( USHORT nC, USHORT nR ) const
        { return !bIsString || !bIsString[ (ULONG) nC * nAnzRow + nR ]
            || bIsString[ (ULONG) nC * nAnzRow + nR ] == SC_MATVAL_EMPTY; }

    /// @return <TRUE/> if entire matrix is numeric and no strings are contained
    BOOL IsNumeric() const							 { return bIsString == NULL; }

    void MatTrans(ScMatrix& mRes) const;
    void MatCopy (ScMatrix& mRes) const;
    /// Copy upper left of this matrix to mRes matrix.
    /// This matrix dimensions must be greater than mRes matrix dimensions.
//STRIP001 	void MatCopyUpperLeft(ScMatrix& mRes) const;

    // Convert ScInterpreter::CompareMat values (-1,0,1) to boolean values
    void CompareEqual();
    void CompareNotEqual();
    void CompareLess();
    void CompareGreater();
    void CompareLessEqual();
    void CompareGreaterEqual();

    BOOL And();		// logical AND of all matrix values
    BOOL Or();		// logical OR of all matrix values

    // All other matrix functions  MatMult, MInv, ...  are in ScInterpreter
    // to be numerically safe.
};


// Old values as used up to SO52.
// The overall elements count had to be <= SC_MAX_MAT_DIM * SC_MAX_MAT_DIM.
// Don't use except maybe for file format compatibility.
// In any other case use ScMatrix::GetElementsMax() instead.
#ifdef WIN
#define SC_OLD_MAX_MAT_DIM			  64
#else
#define SC_OLD_MAX_MAT_DIM			 128
#endif
#define SC_OLD_MAX_MAT_ELEMENTS		((SC_OLD_MAX_MAT_DIM) * (SC_OLD_MAX_MAT_DIM))


} //namespace binfilter
#endif

