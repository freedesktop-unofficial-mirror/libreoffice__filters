/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include <asiancfg.hxx>
#include <bf_svtools/svarray.hxx>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <tools/debug.hxx>
namespace binfilter {

//-----------------------------------------------------------------------------
using namespace utl;
using namespace rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;

#define C2U(cChar) OUString::createFromAscii(cChar)
/*N*/ const sal_Char sStartEndCharacters[] = "StartEndCharacters";
/*N*/ const sal_Char sStartCharacters[] = "StartCharacters";
/*N*/ const sal_Char sEndCharacters[] = "EndCharacters";

//-----------------------------------------------------------------------------
/*N*/ struct SvxForbiddenStruct_Impl
/*N*/ {
/*N*/ 	Locale 		aLocale;
/*N*/ 	OUString	sStartChars;
/*N*/ 	OUString	sEndChars;
/*N*/ };
//-----------------------------------------------------------------------------
/*N*/ typedef SvxForbiddenStruct_Impl* SvxForbiddenStruct_ImplPtr;
/*N*/ SV_DECL_PTRARR_DEL(SvxForbiddenStructArr, SvxForbiddenStruct_ImplPtr, 2, 2)
/*N*/ SV_IMPL_PTRARR(SvxForbiddenStructArr, SvxForbiddenStruct_ImplPtr);
//-----------------------------------------------------------------------------
/*N*/ struct SvxAsianConfig_Impl
/*N*/ {
/*N*/ 	sal_Bool 	bKerningWesternTextOnly;
/*N*/ 	sal_Int16	nCharDistanceCompression;
/*N*/ 
/*N*/ 	SvxForbiddenStructArr	aForbiddenArr;
/*N*/ 
/*N*/ 	SvxAsianConfig_Impl() :
/*N*/ 		bKerningWesternTextOnly(sal_True),
/*N*/ 		nCharDistanceCompression(0) {}
/*N*/ };
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ Sequence<OUString> lcl_GetPropertyNames()
/*N*/ {
/*N*/ 	Sequence<OUString> aNames(2);
/*N*/ 	OUString* pNames = aNames.getArray();
/*N*/ 	pNames[0] = C2U("IsKerningWesternTextOnly");
/*N*/ 	pNames[1] = C2U("CompressCharacterDistance");
/*N*/ 	return aNames;;
/*N*/ }
// ---------------------------------------------------------------------------
/*N*/ SvxAsianConfig::SvxAsianConfig(sal_Bool bEnableNotify) :
/*N*/ 	::utl::ConfigItem(C2U("Office.Common/AsianLayout")),
/*N*/ 	pImpl(new SvxAsianConfig_Impl)
/*N*/ {
/*N*/ 	if(bEnableNotify)
/*N*/ 		EnableNotification(lcl_GetPropertyNames());
/*N*/ 	Load();
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SvxAsianConfig::~SvxAsianConfig()
/*N*/ {
/*N*/ 	delete pImpl;
/*N*/ }
/* -----------------------------17.01.01 09:57--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SvxAsianConfig::Load()
/*N*/ {
/*N*/ 	Sequence<Any> aValues = GetProperties(lcl_GetPropertyNames());
/*N*/ 	const Any* pValues = aValues.getConstArray();
/*N*/ 	if(pValues[0].hasValue())
/*N*/ 		pImpl->bKerningWesternTextOnly = *(sal_Bool*) pValues[0].getValue();
/*N*/ 	pValues[1] >>= pImpl->nCharDistanceCompression;
/*N*/ 
/*N*/ 	pImpl->aForbiddenArr.DeleteAndDestroy(0, pImpl->aForbiddenArr.Count());
/*N*/ 	OUString sPropPrefix(C2U(sStartEndCharacters));
/*N*/ 	Sequence<OUString> aNodes = GetNodeNames(sPropPrefix);
/*N*/ 
/*N*/ 	Sequence<OUString> aPropNames(aNodes.getLength() * 2);
/*N*/ 	OUString* pNames = aPropNames.getArray();
/*N*/ 	sal_Int32 nName = 0;
/*N*/ 	sPropPrefix += C2U("/");
/*N*/ 	sal_Int32 nNode;
/*N*/ 	const OUString* pNodes = aNodes.getConstArray();
/*N*/ 	for(nNode = 0; nNode < aNodes.getLength(); nNode++)
/*N*/ 	{
/*?*/ 		OUString sStart(sPropPrefix);
/*?*/ 		sStart += pNodes[nNode];
/*?*/ 		sStart += C2U("/");
/*?*/ 		pNames[nName] = sStart; 	pNames[nName++] += C2U("StartCharacters");
/*?*/ 		pNames[nName] = sStart; 	pNames[nName++] += C2U("EndCharacters");
/*N*/ 	}
/*N*/ 	Sequence<Any> aNodeValues = GetProperties(aPropNames);
/*N*/ 	const Any* pNodeValues = aNodeValues.getConstArray();
/*N*/ 	nName = 0;
/*N*/ 	for(nNode = 0; nNode < aNodes.getLength(); nNode++)
/*N*/ 	{
/*?*/ 		SvxForbiddenStruct_ImplPtr pInsert = new SvxForbiddenStruct_Impl;
/*?*/ 		pInsert->aLocale.Language = pNodes[nNode].copy(0, 2);
/*?*/ 		DBG_ASSERT(pInsert->aLocale.Language.getLength(), "illegal language");
/*?*/ 		pInsert->aLocale.Country = pNodes[nNode].copy(3, 2);
/*?*/ 
/*?*/ 		pNodeValues[nName++] >>= pInsert->sStartChars;
/*?*/ 		pNodeValues[nName++] >>= pInsert->sEndChars;
/*?*/ 		pImpl->aForbiddenArr.Insert(pInsert, pImpl->aForbiddenArr.Count());
/*N*/ 	}
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_Bool 	SvxAsianConfig::IsKerningWesternTextOnly() const
/*N*/ {
/*N*/ 	return pImpl->bKerningWesternTextOnly;
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_Int16	SvxAsianConfig::GetCharDistanceCompression() const
/*N*/ {
/*N*/ 	return pImpl->nCharDistanceCompression;
/*N*/ }
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ uno::Sequence<lang::Locale> SvxAsianConfig::GetStartEndCharLocales()
/*N*/ {
/*N*/ 	Sequence<Locale> aRet(pImpl->aForbiddenArr.Count());
/*N*/ 	Locale* pRet = aRet.getArray();
/*N*/ 	for(sal_uInt16 i = 0; i < pImpl->aForbiddenArr.Count(); i++)
/*N*/ 	{
/*?*/ 		pRet[i] = pImpl->aForbiddenArr[i]->aLocale;
/*N*/ 	}
/*N*/ 	return aRet;
/*N*/ }

void SvxAsianConfig::Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& /*rPropertyNames*/ ) {}
void SvxAsianConfig::Commit() {}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
