/*************************************************************************
 *
 *  $RCSfile: sc_cellform.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:13:42 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <bf_sfx2/objsh.hxx>
// auto strip #include <svtools/smplhint.hxx>
#include <svtools/zforlist.hxx>

#include "cellform.hxx"
#include "cell.hxx"
// auto strip #include "compiler.hxx"
#include "document.hxx"
#include "bf_sc.hrc"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

// Err527 Workaround
const ScFormulaCell* pLastFormulaTreeTop = 0;

// -----------------------------------------------------------------------

/*N*/ void ScCellFormat::GetString( ScBaseCell* pCell, ULONG nFormat, String& rString,
/*N*/ 							  Color** ppColor, SvNumberFormatter& rFormatter,
/*N*/ 							  BOOL bNullVals,
/*N*/ 							  BOOL bFormula,
/*N*/ 							  ScForceTextFmt eForceTextFmt )
/*N*/ {
/*N*/ 	*ppColor = NULL;
/*N*/ 	if (&rFormatter==NULL)
/*N*/ 	{
/*N*/ 		rString.Erase();
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	CellType eType = pCell->GetCellType();
/*N*/ 	switch(eType)
/*N*/ 	{
/*N*/ 		case CELLTYPE_STRING:
/*N*/ 			{
/*N*/ 				String aCellString;
/*N*/ 				((ScStringCell*)pCell)->GetString( aCellString );
/*N*/ 				rFormatter.GetOutputString( aCellString, nFormat, rString, ppColor );
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		case CELLTYPE_EDIT:
/*N*/ 			{
/*N*/ 				String aCellString;
/*N*/ 				((ScEditCell*)pCell)->GetString( aCellString );
/*N*/ 				rFormatter.GetOutputString( aCellString, nFormat, rString, ppColor );
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		case CELLTYPE_VALUE:
/*N*/ 			{
/*N*/ 				double nValue = ((ScValueCell*)pCell)->GetValue();
/*N*/ 				if ( !bNullVals && nValue == 0.0 )
/*N*/ 					rString.Erase();
/*N*/ 				else
/*N*/ 				{
/*N*/ 					if( eForceTextFmt == ftCheck )
/*N*/ 					{
/*N*/ 						if( nFormat && rFormatter.IsTextFormat( nFormat ) )
/*N*/ 							eForceTextFmt = ftForce;
/*N*/ 					}
/*N*/ 					if( eForceTextFmt == ftForce )
/*N*/ 					{
/*?*/ 						String aTemp;
/*?*/ 						rFormatter.GetOutputString( nValue, 0, aTemp, ppColor );
/*?*/ 						rFormatter.GetOutputString( aTemp, nFormat, rString, ppColor );
/*N*/ 					}
/*N*/ 					else
/*N*/ 						rFormatter.GetOutputString( nValue, nFormat, rString, ppColor );
/*N*/ 				}
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		case CELLTYPE_FORMULA:
/*N*/ 			{
/*N*/ 				ScFormulaCell*	pFCell = (ScFormulaCell*)pCell;
/*N*/ 				if ( bFormula )
/*?*/ 					pFCell->GetFormula( rString );
/*N*/ 				else
/*N*/ 				{
/*N*/ 					// #62160# Ein via Interpreter gestartetes Makro, das hart
/*N*/ 					// auf Formelzellen zugreift, bekommt einen CellText, auch
/*N*/ 					// wenn dadurch ein weiterer Interpreter gestartet wird,
/*N*/ 					// aber nicht wenn diese Zelle gerade interpretiert wird.
/*N*/ 					// IdleCalc startet generell keine weiteren Interpreter,
/*N*/ 					// um keine Err522 (zirkulaer) zu bekommen.
/*N*/ 					if ( pFCell->GetDocument()->IsInInterpreter() &&
/*N*/ 							(!pFCell->GetDocument()->GetMacroInterpretLevel()
/*N*/ 							|| pFCell->IsRunning()) )
/*N*/ 					{
/*?*/ 						rString.AssignAscii( RTL_CONSTASCII_STRINGPARAM("...") );
/*N*/ 					}
/*N*/ 					else
/*N*/ 					{
/*N*/ 						USHORT nErrCode = pFCell->GetErrCode();
/*N*/ 						if ( nErrCode == errInterpOverflow )
/*N*/ 						{	// maxrecursion ausbuegeln, Err527 Workaround
/*?*/ 							DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pDoc = pFCell->GetDocument();
//STRIP001 /*?*/ 							// z.B. nach Import von Fremdformaten FormulaTree
//STRIP001 /*?*/ 							// aufbauen
//STRIP001 /*?*/ 							if ( !pDoc->IsInFormulaTree( pFCell ) )
//STRIP001 /*?*/ 								pFCell->SetDirty();
//STRIP001 /*?*/ 							if ( pDoc->GetAutoCalc()
//STRIP001 /*?*/ 							  && !pDoc->GetHardRecalcState()
//STRIP001 /*?*/ 							  && pLastFormulaTreeTop != pDoc->GetFormulaTree() )
//STRIP001 /*?*/ 							{
//STRIP001 /*?*/ 								pLastFormulaTreeTop = pDoc->GetFormulaTree();
//STRIP001 /*?*/ 								// ohne ProgressBar falls fehlendes Repaint:
//STRIP001 /*?*/ 								// pDoc->CalcFormulaTree( FALSE, TRUE );
//STRIP001 /*?*/ 								//! austesten
//STRIP001 /*?*/ 								pDoc->CalcFormulaTree( FALSE, FALSE );
//STRIP001 /*?*/ 								nErrCode = pFCell->GetErrCode();
//STRIP001 /*?*/ 								if ( nErrCode != errInterpOverflow )
//STRIP001 /*?*/ 								{	// von hinten durch die Brust ins Auge ...
//STRIP001 /*?*/ 									pDoc->GetDocumentShell()->Broadcast( SfxSimpleHint( FID_DATACHANGED ) );
//STRIP001 /*?*/ 									pDoc->ResetChanged( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB) );
//STRIP001 /*?*/ 								}
//STRIP001 /*?*/ 							}
/*N*/ 						}
/*N*/ 
/*N*/ 						// erst nach dem Interpretieren (GetErrCode) das Zahlformat holen:
/*N*/ 						if ( (nFormat % SV_COUNTRY_LANGUAGE_OFFSET) == 0 )
/*N*/ 							nFormat = pFCell->GetStandardFormat( rFormatter,
/*N*/ 								nFormat );
/*N*/ 
/*N*/ 						if (nErrCode != 0)
/*N*/ 							rString = ScGlobal::GetErrorString(nErrCode);
/*N*/ 						else if ( pFCell->IsValue() )
/*N*/ 						{
/*N*/ 							double fValue = pFCell->GetValue();
/*N*/ 							if ( !bNullVals && fValue == 0.0 )
/*?*/ 								rString.Erase();
/*N*/ 							else
/*N*/ 								rFormatter.GetOutputString( fValue, nFormat, rString, ppColor );
/*N*/ 						}
/*N*/ 						else
/*N*/ 						{
/*N*/ 							String aCellString;
/*N*/ 							pFCell->GetString( aCellString );
/*N*/ 							rFormatter.GetOutputString( aCellString, nFormat, rString, ppColor );
/*N*/ 						}
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		default:
/*N*/ 			rString.Erase();
/*N*/ 			break;
/*N*/ 	}
/*N*/ }

/*N*/ void ScCellFormat::GetInputString( ScBaseCell* pCell, ULONG nFormat, String& rString,
/*N*/ 									  SvNumberFormatter& rFormatter )
/*N*/ {
/*N*/ 	if (&rFormatter==NULL)
/*N*/ 	{
/*N*/ 		rString.Erase();
/*N*/ 		return;
/*N*/ 	}
/*N*/ 
/*N*/ 	CellType eType = pCell->GetCellType();
/*N*/ 	switch(eType)
/*N*/ 	{
/*N*/ 		case CELLTYPE_STRING:
/*N*/ 			{
/*N*/ 				((ScStringCell*)pCell)->GetString( rString );
/*N*/ 			}
/*N*/ 			break;
/*?*/ 		case CELLTYPE_EDIT:
/*?*/ 			{
/*?*/ 				((ScEditCell*)pCell)->GetString( rString );
/*?*/ 			}
/*?*/ 			break;
/*?*/ 		case CELLTYPE_VALUE:
/*?*/ 			{
/*?*/ 				double nValue = ((ScValueCell*)pCell)->GetValue();
/*?*/ 				rFormatter.GetInputLineString( nValue, nFormat, rString );
/*?*/ 			}
/*?*/ 			break;
/*N*/ 		case CELLTYPE_FORMULA:
/*N*/ 			{
/*N*/ 				if (((ScFormulaCell*)pCell)->IsValue())
/*N*/ 				{
/*?*/ 					double nValue = ((ScFormulaCell*)pCell)->GetValue();
/*?*/ 					rFormatter.GetInputLineString( nValue, nFormat, rString );
/*N*/ 				}
/*N*/ 				else
/*N*/ 				{
/*N*/ 					((ScFormulaCell*)pCell)->GetString( rString );
/*N*/ 				}
/*N*/ 
/*N*/ 				USHORT nErrCode = ((ScFormulaCell*)pCell)->GetErrCode();
/*N*/ 				if (nErrCode != 0)
/*N*/ 				{
/*?*/ 					rString.Erase();
/*N*/ 				}
/*N*/ 			}
/*N*/ 			break;
/*?*/ 		default:
/*?*/ 			rString.Erase();
/*?*/ 			break;
/*N*/ 	}
/*N*/ }



}
