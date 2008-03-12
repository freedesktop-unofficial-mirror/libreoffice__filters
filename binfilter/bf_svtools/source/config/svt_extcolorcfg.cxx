/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_extcolorcfg.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:30:06 $
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

#include "extcolorcfg.hxx"

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
#ifndef UNOTOOLS_CONFIGPATHES_HXX_INCLUDED
#include <unotools/configpathes.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx> //Any2Bool
#endif
#ifndef _SFXSMPLHINT_HXX
#include <bf_svtools/smplhint.hxx>
#endif
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

 /* #100822# ----
#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif
 ------------- */
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_EVENT_HXX
#include <vcl/event.hxx>
#endif
#ifndef INCLUDED_RTL_INSTANCE_HXX
#include <rtl/instance.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif


//-----------------------------------------------------------------------------
using namespace utl;
using namespace rtl;
using namespace com::sun::star;

namespace binfilter
{

#define C2U(cChar) OUString::createFromAscii(cChar)
sal_Int32            nExtendedColorRefCount_Impl = 0;
namespace 
{
    struct ColorMutex_Impl 
        : public rtl::Static< ::osl::Mutex, ColorMutex_Impl > {}; 
}

ExtendedColorConfig_Impl*    ExtendedColorConfig::m_pImpl = NULL;

/* -----------------------------16.01.01 15:36--------------------------------
 ---------------------------------------------------------------------------*/
class ExtendedColorConfig_Impl : public utl::ConfigItem, public SfxBroadcaster
{
    DECLARE_STL_USTRINGACCESS_MAP( ::rtl::OUString, TDisplayNames);
    DECLARE_STL_USTRINGACCESS_MAP(ExtendedColorConfigValue,TConfigValues);
    typedef ::std::vector<TConfigValues::iterator> TMapPos;
    typedef ::std::pair< TConfigValues, TMapPos > TComponentMapping;
    DECLARE_STL_USTRINGACCESS_MAP(TComponentMapping,TComponents);
    TComponents			m_aConfigValues;
    TDisplayNames		m_aComponentDisplayNames;
    ::std::vector<TComponents::iterator> m_aConfigValuesPos;	

    sal_Bool            m_bEditMode;
    rtl::OUString       m_sLoadedScheme;
    sal_Bool			m_bIsBroadcastEnabled;
    static sal_Bool     m_bLockBroadcast;
    static sal_Bool     m_bBroadcastWhenUnlocked;

    uno::Sequence< ::rtl::OUString> GetPropertyNames(const rtl::OUString& rScheme);
    void FillComponentColors(uno::Sequence < ::rtl::OUString >& _rComponents,const TDisplayNames& _rDisplayNames);
public:
    ExtendedColorConfig_Impl(sal_Bool bEditMode = sal_False);
    virtual ~ExtendedColorConfig_Impl();

    void                            Load(const rtl::OUString& rScheme);
    void                            CommitCurrentSchemeName();
    //changes the name of the current scheme but doesn't load it!
    void                            SetCurrentSchemeName(const rtl::OUString& rSchemeName) {m_sLoadedScheme = rSchemeName;}
    sal_Bool						ExistsScheme(const ::rtl::OUString& _sSchemeName);
    virtual void                    Commit();
    virtual void                    Notify( const uno::Sequence<rtl::OUString>& aPropertyNames);

    sal_Int32						GetComponentCount() const;
    ::rtl::OUString					GetComponentName(sal_uInt32 _nPos) const;
    ::rtl::OUString					GetComponentDisplayName(const ::rtl::OUString& _sComponentName) const;
    sal_Int32						GetComponentColorCount(const ::rtl::OUString& _sName) const;
    ExtendedColorConfigValue		GetComponentColorConfigValue(const ::rtl::OUString& _sName,sal_uInt32 _nPos) const;

    ExtendedColorConfigValue GetColorConfigValue(const ::rtl::OUString& _sComponentName,const ::rtl::OUString& _sName)
    {
        TComponents::iterator aFind = m_aConfigValues.find(_sComponentName);
        if ( aFind != m_aConfigValues.end() )
        {
            TConfigValues::iterator aFind2 = aFind->second.first.find(_sName);
            if ( aFind != m_aConfigValues.end() )
                return aFind2->second;
        }
        OSL_ENSURE(0,"Could find the required config!");
        return ExtendedColorConfigValue();
    }
    void                            SetColorConfigValue(const ::rtl::OUString& _sName,
                                                            const ExtendedColorConfigValue& rValue );

    const rtl::OUString&            GetLoadedScheme() const {return m_sLoadedScheme;}

    uno::Sequence< ::rtl::OUString> GetSchemeNames();

    sal_Bool                        AddScheme(const rtl::OUString& rNode);
    sal_Bool                        RemoveScheme(const rtl::OUString& rNode);
    void                            SetModified(){ConfigItem::SetModified();}
    void                            ClearModified(){ConfigItem::ClearModified();}
    void                            SettingsChanged();

    static void						DisableBroadcast();
    static void						EnableBroadcast();
    static sal_Bool					IsEnableBroadcast();

    static void                     LockBroadcast();
    static void                     UnlockBroadcast();

    // #100822#
    DECL_LINK( DataChangedEventListener, VclWindowEvent* );
};

/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
uno::Sequence< OUString> ExtendedColorConfig_Impl::GetPropertyNames(const rtl::OUString& rScheme)
{
    uno::Sequence< OUString> aNames(GetNodeNames(rScheme));
    ::rtl::OUString* pIter = aNames.getArray();
    ::rtl::OUString* pEnd	 = pIter + aNames.getLength();
    ::rtl::OUString sSep(RTL_CONSTASCII_USTRINGPARAM("/"));
    for(;pIter != pEnd;++pIter)
    {
        *pIter = rScheme + sSep + *pIter;
    }
    return aNames;
}
// -----------------------------------------------------------------------------
sal_Int32 ExtendedColorConfig_Impl::GetComponentCount() const
{
    return m_aConfigValues.size();
}
// -----------------------------------------------------------------------------
sal_Int32 ExtendedColorConfig_Impl::GetComponentColorCount(const ::rtl::OUString& _sName) const
{
    sal_Int32 nSize = 0;
    TComponents::const_iterator aFind = m_aConfigValues.find(_sName);
    if ( aFind != m_aConfigValues.end() )
    {
        nSize = aFind->second.first.size();
    }
    return nSize;
}
// -----------------------------------------------------------------------------
ExtendedColorConfigValue ExtendedColorConfig_Impl::GetComponentColorConfigValue(const ::rtl::OUString& _sName,sal_uInt32 _nPos) const
{
    TComponents::const_iterator aFind = m_aConfigValues.find(_sName);
    if ( aFind != m_aConfigValues.end() )
    {
        if ( _nPos < aFind->second.second.size() )
        {
            return aFind->second.second[_nPos]->second;
        }
    }
    return ExtendedColorConfigValue();
}
// -----------------------------------------------------------------------------
::rtl::OUString	ExtendedColorConfig_Impl::GetComponentDisplayName(const ::rtl::OUString& _sComponentName) const
{
    ::rtl::OUString sRet;
    TDisplayNames::const_iterator aFind = m_aComponentDisplayNames.find(_sComponentName);
    if ( aFind != m_aComponentDisplayNames.end() )
        sRet = aFind->second;
    return sRet;
}
// -----------------------------------------------------------------------------
::rtl::OUString ExtendedColorConfig_Impl::GetComponentName(sal_uInt32 _nPos) const
{
    ::rtl::OUString sRet;
    if ( _nPos < m_aConfigValuesPos.size() )
        sRet = m_aConfigValuesPos[_nPos]->first;
    return sRet;
}
// -----------------------------------------------------------------------------
/* -----------------------------22.03.2002 14:37------------------------------

 ---------------------------------------------------------------------------*/
sal_Bool ExtendedColorConfig_Impl::m_bLockBroadcast = sal_False;
sal_Bool ExtendedColorConfig_Impl::m_bBroadcastWhenUnlocked = sal_False;
ExtendedColorConfig_Impl::ExtendedColorConfig_Impl(sal_Bool bEditMode) :
    ConfigItem(C2U("Office.ExtendedColorScheme")),
    m_bEditMode(bEditMode),
    m_bIsBroadcastEnabled(sal_True)
{
    if(!m_bEditMode)
    {
        //try to register on the root node - if possible
        uno::Sequence < ::rtl::OUString > aNames(1);
        EnableNotification( aNames );
    }
    Load(::rtl::OUString());

    // #100822#
    ::Application::AddEventListener( LINK(this, ExtendedColorConfig_Impl, DataChangedEventListener) );

}
/* -----------------------------25.03.2002 12:28------------------------------

 ---------------------------------------------------------------------------*/
ExtendedColorConfig_Impl::~ExtendedColorConfig_Impl()
{
    // #100822#
    ::Application::RemoveEventListener( LINK(this, ExtendedColorConfig_Impl, DataChangedEventListener) );
}
// -----------------------------------------------------------------------------
void ExtendedColorConfig_Impl::DisableBroadcast()
{
    if ( ExtendedColorConfig::m_pImpl )
        ExtendedColorConfig::m_pImpl->m_bIsBroadcastEnabled = sal_False;
}
// -----------------------------------------------------------------------------
void ExtendedColorConfig_Impl::EnableBroadcast()
{
    if ( ExtendedColorConfig::m_pImpl )
        ExtendedColorConfig::m_pImpl->m_bIsBroadcastEnabled = sal_True;
}
// -----------------------------------------------------------------------------
sal_Bool ExtendedColorConfig_Impl::IsEnableBroadcast() 
{ 
    return ExtendedColorConfig::m_pImpl ? ExtendedColorConfig::m_pImpl->m_bIsBroadcastEnabled : sal_False;
}
/* -----------------------------22.03.2002 14:38------------------------------

 ---------------------------------------------------------------------------*/
void lcl_addString(uno::Sequence < ::rtl::OUString >& _rSeq,const ::rtl::OUString& _sAdd)
{
    ::rtl::OUString* pIter = _rSeq.getArray();
    ::rtl::OUString* pEnd  = pIter + _rSeq.getLength();
    for(;pIter != pEnd;++pIter)
        *pIter += _sAdd;
}
// -----------------------------------------------------------------------------
void ExtendedColorConfig_Impl::Load(const rtl::OUString& rScheme)
{
    m_aComponentDisplayNames.clear();
    m_aConfigValuesPos.clear();
    m_aConfigValues.clear();

    // fill display names
    TDisplayNames aDisplayNameMap;
    ::rtl::OUString sEntryNames(RTL_CONSTASCII_USTRINGPARAM("EntryNames"));
    uno::Sequence < ::rtl::OUString > aComponentNames = GetPropertyNames(sEntryNames);
    ::rtl::OUString sDisplayName(RTL_CONSTASCII_USTRINGPARAM("/DisplayName"));
    ::rtl::OUString* pIter = aComponentNames.getArray();
    ::rtl::OUString* pEnd  = pIter + aComponentNames.getLength();
    for(sal_Int32 i = 0;pIter != pEnd;++pIter,++i)
    {
        uno::Sequence < ::rtl::OUString > aComponentDisplayNames(1);
        aComponentDisplayNames[0] = *pIter;
        aComponentDisplayNames[0] += sDisplayName;
        uno::Sequence< uno::Any > aComponentDisplayNamesValue = GetProperties( aComponentDisplayNames );
        ::rtl::OUString sComponentDisplayName;
        if ( aComponentDisplayNamesValue.getLength() && (aComponentDisplayNamesValue[0] >>= sComponentDisplayName) )
        {
            sal_Int32 nIndex = 0;
            m_aComponentDisplayNames.insert(TDisplayNames::value_type(pIter->getToken(1,'/',nIndex),sComponentDisplayName));
        }

        *pIter += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/Entries"));
        uno::Sequence < ::rtl::OUString > aDisplayNames = GetPropertyNames(*pIter);
        lcl_addString(aDisplayNames,sDisplayName);

        uno::Sequence< uno::Any > aDisplayNamesValue = GetProperties( aDisplayNames );
        
        const ::rtl::OUString* pDispIter = aDisplayNames.getConstArray();
        const ::rtl::OUString* pDispEnd  = pDispIter + aDisplayNames.getLength();
        for(sal_Int32 j = 0;pDispIter != pDispEnd;++pDispIter,++j)
        {
            sal_Int32 nIndex = 0;
            pDispIter->getToken(0,'/',nIndex);
            ::rtl::OUString sName = pDispIter->copy(nIndex);
            sName = sName.copy(0,sName.lastIndexOf(sDisplayName));
            ::rtl::OUString sCurrentDisplayName;
            aDisplayNamesValue[j] >>= sCurrentDisplayName;
            aDisplayNameMap.insert(TDisplayNames::value_type(sName,sCurrentDisplayName));
        } 
    }

    // load color settings
    rtl::OUString sScheme(rScheme);
    
    if(!sScheme.getLength())
    {
        //detect current scheme name
        uno::Sequence < ::rtl::OUString > aCurrent(1);
        aCurrent.getArray()[0] = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ExtendedColorScheme/CurrentColorScheme"));
        uno::Sequence< uno::Any > aCurrentVal = GetProperties( aCurrent );
        aCurrentVal.getConstArray()[0] >>= sScheme;
    } // if(!sScheme.getLength())
    
    m_sLoadedScheme = sScheme;
    ::rtl::OUString sBase(RTL_CONSTASCII_USTRINGPARAM("ExtendedColorScheme/ColorSchemes/"));
    sBase += sScheme;

    sal_Bool bFound = ExistsScheme(sScheme);
    if ( bFound )
    {
        aComponentNames = GetPropertyNames(sBase);
        FillComponentColors(aComponentNames,aDisplayNameMap);
    } // if ( bFound )

    if ( !m_sLoadedScheme.getLength() )
        m_sLoadedScheme = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("default"));
    
    if ( !sScheme.equalsAscii("default") )
    {
        ::rtl::OUString sBaseDefault(RTL_CONSTASCII_USTRINGPARAM("ExtendedColorScheme/ColorSchemes/default"));
        aComponentNames = GetPropertyNames(sBaseDefault);
        FillComponentColors(aComponentNames,aDisplayNameMap);
    } // if ( !sScheme.equalsAscii("default") )
    if ( !bFound && sScheme.getLength() )
    {
        AddScheme(sScheme);
        CommitCurrentSchemeName();
    }
}
// -----------------------------------------------------------------------------
void ExtendedColorConfig_Impl::FillComponentColors(uno::Sequence < ::rtl::OUString >& _rComponents,const TDisplayNames& _rDisplayNames)
{
    const ::rtl::OUString sColorEntries(RTL_CONSTASCII_USTRINGPARAM("/Entries"));
    ::rtl::OUString* pIter = _rComponents.getArray();
    ::rtl::OUString* pEnd  = pIter + _rComponents.getLength();
    for(;pIter != pEnd;++pIter)
    {
        ::rtl::OUString sComponentName = pIter->copy(pIter->lastIndexOf('/')+1);
        if ( m_aConfigValues.find(sComponentName) == m_aConfigValues.end() )
        {
            ::rtl::OUString sEntry = *pIter;
            sEntry += sColorEntries;

            uno::Sequence < ::rtl::OUString > aColorNames = GetPropertyNames(sEntry);
            uno::Sequence < ::rtl::OUString > aDefaultColorNames = aColorNames;

            const ::rtl::OUString sColor(RTL_CONSTASCII_USTRINGPARAM("/Color"));
            const ::rtl::OUString sDefaultColor(RTL_CONSTASCII_USTRINGPARAM("/DefaultColor"));
            lcl_addString(aColorNames,sColor);
            lcl_addString(aDefaultColorNames,sDefaultColor);
            uno::Sequence< uno::Any > aColors = GetProperties( aColorNames );
            const uno::Any* pColors = aColors.getConstArray();

            uno::Sequence< uno::Any > aDefaultColors = GetProperties( aDefaultColorNames );
            bool bDefaultColorFound = aDefaultColors.getLength() != 0;
            const uno::Any* pDefaultColors = aDefaultColors.getConstArray();

            ::rtl::OUString* pColorIter = aColorNames.getArray();
            ::rtl::OUString* pColorEnd  = pColorIter + aColorNames.getLength();
            
            m_aConfigValuesPos.push_back(m_aConfigValues.insert(TComponents::value_type(sComponentName,TComponentMapping(TConfigValues(),TMapPos()))).first);
            TConfigValues& aConfigValues = (*m_aConfigValuesPos.rbegin())->second.first;
            TMapPos& aConfigValuesPos = (*m_aConfigValuesPos.rbegin())->second.second;
            for(int i = 0; pColorIter != pColorEnd; ++pColorIter ,++i)
            {
                if ( aConfigValues.find(*pColorIter) == aConfigValues.end() )
                {
                    sal_Int32 nIndex = 0;
                    pColorIter->getToken(2,'/',nIndex);
                    ::rtl::OUString sName(pColorIter->copy(nIndex)),sDisplayName;
                    ::rtl::OUString sTemp = sName.copy(0,sName.lastIndexOf(sColor));
                    
                    TDisplayNames::const_iterator aFind = _rDisplayNames.find(sTemp);
                    nIndex = 0;
                    sName = sName.getToken(2,'/',nIndex);
                    OSL_ENSURE(aFind != _rDisplayNames.end(),"DisplayName is not in EntryNames config list!");
                    if ( aFind != _rDisplayNames.end() )
                        sDisplayName = aFind->second;
                    
                    OSL_ENSURE(pColors[i].hasValue(),"Color config entry has NIL as color value set!");
                    OSL_ENSURE(pDefaultColors[i].hasValue(),"Color config entry has NIL as color value set!");
                    sal_Int32 nColor = 0,nDefaultColor = 0;
                    pColors[i] >>= nColor;
                    if ( bDefaultColorFound )
                        pDefaultColors[i] >>= nDefaultColor;
                    else
                        nDefaultColor = nColor;
                    ExtendedColorConfigValue aValue(sName,sDisplayName,nColor,nDefaultColor);
                    aConfigValuesPos.push_back(aConfigValues.insert(TConfigValues::value_type(sName,aValue)).first);
                }
            } // for(int i = 0; pColorIter != pColorEnd; ++pColorIter ,++i)
        }
    }
}
/* -----------------------------22.03.2002 14:38------------------------------

 ---------------------------------------------------------------------------*/
void    ExtendedColorConfig_Impl::Notify( const uno::Sequence<OUString>& /*rPropertyNames*/)
{
    //loading via notification always uses the default setting
    Load(::rtl::OUString());

    vos::OGuard aVclGuard( Application::GetSolarMutex() );

    if(m_bLockBroadcast)
    {
        m_bBroadcastWhenUnlocked = sal_True;
    }
    else
        Broadcast(SfxSimpleHint(SFX_HINT_COLORS_CHANGED));
}
/* -----------------------------22.03.2002 14:38------------------------------

 ---------------------------------------------------------------------------*/
void ExtendedColorConfig_Impl::Commit()
{
    if ( !m_sLoadedScheme.getLength() )
        return;
    const ::rtl::OUString sColorEntries(RTL_CONSTASCII_USTRINGPARAM("Entries"));
    const ::rtl::OUString sColor(RTL_CONSTASCII_USTRINGPARAM("/Color"));
    const ::rtl::OUString sDefaultColor(RTL_CONSTASCII_USTRINGPARAM("/DefaultColor"));
    ::rtl::OUString sBase(RTL_CONSTASCII_USTRINGPARAM("ExtendedColorScheme/ColorSchemes/"));
    const ::rtl::OUString s_sSep(RTL_CONSTASCII_USTRINGPARAM("/"));
    sBase += m_sLoadedScheme;

    TComponents::iterator aIter = m_aConfigValues.begin();
    TComponents::iterator aEnd = m_aConfigValues.end();
    for( ;aIter != aEnd;++aIter )
    {
        ::rtl::OUString sEntry = aIter->first;
        sEntry += sColorEntries;

        if ( ConfigItem::AddNode(sBase, aIter->first) )
        {
            rtl::OUString sNode = sBase;
            sNode += s_sSep;
            sNode += aIter->first;
            //ConfigItem::AddNode(sNode, sColorEntries);
            sNode += s_sSep;
            sNode += sColorEntries;

            uno::Sequence < beans::PropertyValue > aPropValues(aIter->second.first.size());
            beans::PropertyValue* pPropValues = aPropValues.getArray();
            TConfigValues::iterator aConIter = aIter->second.first.begin();
            TConfigValues::iterator aConEnd  = aIter->second.first.end();
            for (; aConIter != aConEnd; ++aConIter,++pPropValues)
            {
                pPropValues->Name = sNode + s_sSep + aConIter->first;
                ConfigItem::AddNode(sNode, aConIter->first);
                pPropValues->Name += sColor;
                pPropValues->Value <<= aConIter->second.getColor();
                // the default color will never be changed
            }
            ::rtl::OUString s(RTL_CONSTASCII_USTRINGPARAM("ExtendedColorScheme/ColorSchemes"));
            SetSetProperties(s, aPropValues);
        }
    }    

    CommitCurrentSchemeName();
}
/* -----------------11.12.2002 10:42-----------------
 *
 * --------------------------------------------------*/
void ExtendedColorConfig_Impl::CommitCurrentSchemeName()
{
    //save current scheme name
    uno::Sequence < ::rtl::OUString > aCurrent(1);
    aCurrent.getArray()[0] = C2U("ExtendedColorScheme/CurrentColorScheme");
    uno::Sequence< uno::Any > aCurrentVal(1);
    aCurrentVal.getArray()[0] <<= m_sLoadedScheme;
    PutProperties(aCurrent, aCurrentVal);
}
// -----------------------------------------------------------------------------
sal_Bool ExtendedColorConfig_Impl::ExistsScheme(const ::rtl::OUString& _sSchemeName)
{
    ::rtl::OUString sBase(RTL_CONSTASCII_USTRINGPARAM("ExtendedColorScheme/ColorSchemes"));
    
    uno::Sequence < ::rtl::OUString > aComponentNames = GetPropertyNames(sBase);
    sBase += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/")) + _sSchemeName;
    const ::rtl::OUString* pCompIter = aComponentNames.getConstArray();
    const ::rtl::OUString* pCompEnd	 = pCompIter + aComponentNames.getLength();
    for(;pCompIter != pCompEnd && *pCompIter != sBase;++pCompIter)
        ;
    return pCompIter != pCompEnd;
}
// -----------------------------------------------------------------------------
/* -----------------------------25.03.2002 12:19------------------------------

 ---------------------------------------------------------------------------*/
void ExtendedColorConfig_Impl::SetColorConfigValue(const ::rtl::OUString& _sName, const ExtendedColorConfigValue& rValue )
{
    TComponents::iterator aFind = m_aConfigValues.find(_sName);
    if ( aFind != m_aConfigValues.end() )
    {
        TConfigValues::iterator aFind2 = aFind->second.first.find(rValue.getName());
        if ( aFind2 != aFind->second.first.end() )
            aFind2->second = rValue;
        SetModified();
    }
}
/* -----------------------------25.03.2002 15:22------------------------------

 ---------------------------------------------------------------------------*/
uno::Sequence< ::rtl::OUString> ExtendedColorConfig_Impl::GetSchemeNames()
{
    return GetNodeNames(C2U("ExtendedColorScheme/ColorSchemes"));
}
/* -----------------------------09.04.2002 17:19------------------------------

 ---------------------------------------------------------------------------*/
sal_Bool ExtendedColorConfig_Impl::AddScheme(const rtl::OUString& rScheme)
{
    if(ConfigItem::AddNode(C2U("ExtendedColorScheme/ColorSchemes"), rScheme))
    {
        m_sLoadedScheme = rScheme;
        Commit();
        return sal_True;
    }
    return sal_False;
}
/* -----------------------------09.04.2002 17:19------------------------------

 ---------------------------------------------------------------------------*/
sal_Bool ExtendedColorConfig_Impl::RemoveScheme(const rtl::OUString& rScheme)
{
    uno::Sequence< rtl::OUString > aElements(1);
    aElements.getArray()[0] = rScheme;
    return ClearNodeElements(C2U("ExtendedColorScheme/ColorSchemes"), aElements);
}
/* -----------------------------2002/06/20 13:03------------------------------

 ---------------------------------------------------------------------------*/
void ExtendedColorConfig_Impl::SettingsChanged()
{
    vos::OGuard aVclGuard( Application::GetSolarMutex() );

    Broadcast( SfxSimpleHint( SFX_HINT_COLORS_CHANGED ) );
}
/* -----------------11.12.2002 09:21-----------------
 *
 * --------------------------------------------------*/
void ExtendedColorConfig_Impl::LockBroadcast()
{
    m_bLockBroadcast = sal_True;
}
/* -----------------11.12.2002 09:21-----------------
 *
 * --------------------------------------------------*/
void ExtendedColorConfig_Impl::UnlockBroadcast()
{
    if ( m_bBroadcastWhenUnlocked )
    {
        m_bBroadcastWhenUnlocked = ExtendedColorConfig::m_pImpl != NULL;
        if ( m_bBroadcastWhenUnlocked )
        {
            if ( ExtendedColorConfig::m_pImpl->IsEnableBroadcast() )
            {
                m_bBroadcastWhenUnlocked = sal_False;
                ExtendedColorConfig::m_pImpl->Broadcast(SfxSimpleHint(SFX_HINT_COLORS_CHANGED));
            }
        }
    }
    m_bLockBroadcast = sal_False;
}
/* -----------------------------2002/08/16 12:07 -----------------------------
   #100822#
 --------------------------------------------------------------------------- */
IMPL_LINK( ExtendedColorConfig_Impl, DataChangedEventListener, VclWindowEvent*, pEvent )
{
    if ( pEvent->GetId() == VCLEVENT_APPLICATION_DATACHANGED )
    {
        DataChangedEvent* pData = (DataChangedEvent*)(pEvent->GetData());
        if ( (pData->GetType() == DATACHANGED_SETTINGS) &&
             (pData->GetFlags() & SETTINGS_STYLE) )
        {
            SettingsChanged();
            return 1L;
        } else
            return 0L;
    } else
        return 0L;
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

ExtendedColorConfig::ExtendedColorConfig()
{
    ::osl::MutexGuard aGuard( ColorMutex_Impl::get() );
    if ( !m_pImpl )
        m_pImpl = new ExtendedColorConfig_Impl;
    ++nExtendedColorRefCount_Impl;
    StartListening( *m_pImpl);
}
/* -----------------------------16.01.01 15:36--------------------------------

 ---------------------------------------------------------------------------*/
ExtendedColorConfig::~ExtendedColorConfig()
{
    ::osl::MutexGuard aGuard( ColorMutex_Impl::get() );
    EndListening( *m_pImpl);
    if(!--nExtendedColorRefCount_Impl)
    {
        delete m_pImpl;
        m_pImpl = 0;
    }
}
/* -----------------------------11.04.2002 11:49------------------------------

 ---------------------------------------------------------------------------*/
ExtendedColorConfigValue ExtendedColorConfig::GetColorValue(const ::rtl::OUString& _sComponentName,const ::rtl::OUString& _sName)const
{
    return m_pImpl->GetColorConfigValue(_sComponentName,_sName);
}
// -----------------------------------------------------------------------------
sal_Int32 ExtendedColorConfig::GetComponentCount() const
{
    return m_pImpl->GetComponentCount();
}
// -----------------------------------------------------------------------------
sal_Int32 ExtendedColorConfig::GetComponentColorCount(const ::rtl::OUString& _sName) const
{
    return m_pImpl->GetComponentColorCount(_sName);
}
// -----------------------------------------------------------------------------
ExtendedColorConfigValue ExtendedColorConfig::GetComponentColorConfigValue(const ::rtl::OUString& _sName,sal_uInt32 _nPos) const
{
    return m_pImpl->GetComponentColorConfigValue(_sName,_nPos);
}
// -----------------------------------------------------------------------------
::rtl::OUString ExtendedColorConfig::GetComponentName(sal_uInt32 _nPos) const
{
    return m_pImpl->GetComponentName(_nPos);
}
// -----------------------------------------------------------------------------
::rtl::OUString ExtendedColorConfig::GetComponentDisplayName(const ::rtl::OUString& _sComponentName) const
{
    return m_pImpl->GetComponentDisplayName(_sComponentName);
}
// -----------------------------------------------------------------------------
/* -----------------------------12.04.2002 09:25------------------------------

 ---------------------------------------------------------------------------*/
void ExtendedColorConfig::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint )
{
    vos::OGuard aVclGuard( Application::GetSolarMutex() );

    Broadcast( rHint );
}
/* -----------------------------25.03.2002 12:01------------------------------

 ---------------------------------------------------------------------------*/
EditableExtendedColorConfig::EditableExtendedColorConfig() :
    m_pImpl(new ExtendedColorConfig_Impl),
    m_bModified(sal_False)
{
    m_pImpl->LockBroadcast();
}
/*-- 25.03.2002 12:03:08---------------------------------------------------

  -----------------------------------------------------------------------*/
EditableExtendedColorConfig::~EditableExtendedColorConfig()
{
    m_pImpl->UnlockBroadcast();
    if(m_bModified)
        m_pImpl->SetModified();
    if(m_pImpl->IsModified())
        m_pImpl->Commit();
    delete m_pImpl;
}

/*-- 25.03.2002 12:03:15---------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Sequence< ::rtl::OUString >  EditableExtendedColorConfig::GetSchemeNames() const
{
    return m_pImpl->GetSchemeNames();
}
/*-- 25.03.2002 12:03:16---------------------------------------------------

  -----------------------------------------------------------------------*/
void EditableExtendedColorConfig::DeleteScheme(const ::rtl::OUString& rScheme )
{
    m_pImpl->RemoveScheme(rScheme);
}
/*-- 25.03.2002 12:03:16---------------------------------------------------

  -----------------------------------------------------------------------*/
void EditableExtendedColorConfig::AddScheme(const ::rtl::OUString& rScheme )
{
    m_pImpl->AddScheme(rScheme);
}
/*-- 25.03.2002 12:03:16---------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Bool EditableExtendedColorConfig::LoadScheme(const ::rtl::OUString& rScheme )
{
    if(m_bModified)
        m_pImpl->SetModified();
    if(m_pImpl->IsModified())
        m_pImpl->Commit();
    m_bModified = sal_False;
    m_pImpl->Load(rScheme);
    //the name of the loaded scheme has to be committed separately
    m_pImpl->CommitCurrentSchemeName();
    return sal_True;
}
/*-- 25.03.2002 12:03:16---------------------------------------------------

  -----------------------------------------------------------------------*/
const ::rtl::OUString& EditableExtendedColorConfig::GetCurrentSchemeName()const
{
    return m_pImpl->GetLoadedScheme();
}
/* -----------------11.12.2002 10:56-----------------
 *  changes the name of the current scheme but doesn't load it!
 * --------------------------------------------------*/
void EditableExtendedColorConfig::SetCurrentSchemeName(const ::rtl::OUString& rScheme)
{
    m_pImpl->SetCurrentSchemeName(rScheme);
    m_pImpl->CommitCurrentSchemeName();
}
/*-- 25.03.2002 12:03:17---------------------------------------------------

  -----------------------------------------------------------------------*/
ExtendedColorConfigValue EditableExtendedColorConfig::GetColorValue(const ::rtl::OUString& _sComponentName,
    const ::rtl::OUString& _sName)const
{
    return m_pImpl->GetColorConfigValue(_sComponentName,_sName);
}
/*-- 25.03.2002 12:03:17---------------------------------------------------

  -----------------------------------------------------------------------*/
void EditableExtendedColorConfig::SetColorValue(
    const ::rtl::OUString& _sName, const ExtendedColorConfigValue& rValue)
{
    m_pImpl->SetColorConfigValue(_sName, rValue);
    m_pImpl->ClearModified();
    m_bModified = sal_True;
}
/* -----------------------------10.04.2002 13:22------------------------------

 ---------------------------------------------------------------------------*/
void EditableExtendedColorConfig::SetModified()
{
    m_bModified = sal_True;
}
/* -----------------15.10.2002 14:51-----------------
 *
 * --------------------------------------------------*/
void EditableExtendedColorConfig::Commit()
{
    if(m_bModified)
        m_pImpl->SetModified();
    if(m_pImpl->IsModified())
        m_pImpl->Commit();
    m_bModified = sal_False;
}
// -----------------------------------------------------------------------------
void EditableExtendedColorConfig::DisableBroadcast()
{
    m_pImpl->DisableBroadcast();
}
// -----------------------------------------------------------------------------
void EditableExtendedColorConfig::EnableBroadcast()
{
    m_pImpl->EnableBroadcast();
}
// -----------------------------------------------------------------------------
sal_Int32 EditableExtendedColorConfig::GetComponentCount() const
{
    return m_pImpl->GetComponentCount();
}
// -----------------------------------------------------------------------------
sal_Int32 EditableExtendedColorConfig::GetComponentColorCount(const ::rtl::OUString& _sName) const
{
    return m_pImpl->GetComponentColorCount(_sName);
}
// -----------------------------------------------------------------------------
ExtendedColorConfigValue EditableExtendedColorConfig::GetComponentColorConfigValue(const ::rtl::OUString& _sName,sal_uInt32 _nPos) const
{
    return m_pImpl->GetComponentColorConfigValue(_sName,_nPos);
}
// -----------------------------------------------------------------------------
::rtl::OUString EditableExtendedColorConfig::GetComponentName(sal_uInt32 _nPos) const
{
    return m_pImpl->GetComponentName(_nPos);
}
// -----------------------------------------------------------------------------
::rtl::OUString EditableExtendedColorConfig::GetComponentDisplayName(const ::rtl::OUString& _sComponentName) const
{
    return m_pImpl->GetComponentDisplayName(_sComponentName);
}
}

