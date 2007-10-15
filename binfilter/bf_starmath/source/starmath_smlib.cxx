/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: starmath_smlib.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-15 11:49:33 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_FCONTNR_HXX
#include <bf_sfx2/fcontnr.hxx>
#endif


#ifndef _DOCUMENT_HXX
#include "document.hxx"
#endif
#ifndef _STARMATH_HRC
#include "starmath.hrc"
#endif

#include "dllname.hxx"
namespace binfilter {

TYPEINIT1( SmModuleDummy, SfxModule );


/*************************************************************************
|*
|* ObjectFactory registrieren
|*
\************************************************************************/

extern "C" { static void SAL_CALL thisModule() {} }

SFX_IMPL_OBJECTFACTORY_LIB( SmDocShell,
                            SFXOBJECTSHELL_STD_NORMAL,
                            smath,
                               SvGlobalName(BF_SO3_SM_CLASSID), Sm,
                            String::CreateFromAscii(DLL_NAME) )
{
    SfxObjectFactory& rFactory = (SfxObjectFactory&)Factory();
    SfxFactoryFilterContainer *pFltContainer = rFactory.GetFilterContainer( FALSE );
    rFactory.GetFilterContainer()->SetDetectFilter( &SmDLL::DetectFilter );

   // FG: Sonst gibts keine Hilfe im Math  #38447#
   Factory().SetDocumentServiceName( String::CreateFromAscii("com.sun.star.formula.FormulaProperties") );
}


/*************************************************************************
|*
|* Ctor
|* the ctor is called at the beginning of SfxApplication-subclass::Main()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

SmDLL::SmDLL()
{
    (*(SmDLL**)GetAppData(BF_SHL_SM)) = this;
}

/*************************************************************************
|*
|* Dtor
|* the dtor is called at the end of SfxApplication-subclass::Main()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

SmDLL::~SmDLL()
{
    (*(SmDLL**)GetAppData(BF_SHL_SM)) = NULL;
}

/*************************************************************************
|*
|* LibInit
|* method is called before Application::Execute()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

void SmDLL::LibInit()
{
    SmDocShell::RegisterFactory(SDT_SMA_DOCFACTPRIO);
    SM_MOD() = new SmModuleDummy(NULL, TRUE, &SmDocShell::Factory());

}

/*************************************************************************
|*
|* LibExit
|* this method is called after Application::Execute()
|* do whatever you want, but no calls to Sd-DLL-code!
|*
\************************************************************************/

void SmDLL::LibExit()
{
    FreeLibSm();

    // destroy the dummy-module with Object-Factory-Pointer
    SfxModule *p = SM_MOD();
    delete p;
}

/************-*************************************************************
|*
|* Unterfenster oeffnen
|*
\************************************************************************/

SfxModule *SmModuleDummy::Load ()
{
    return LoadLibSm () ? SM_MOD() : 0;
}

/*************************************************************************
|*
|* Bestimme die GUID abh. von der Version
|*
\************************************************************************/

const SvGlobalName SmModuleDummy::GetID (USHORT nFileFormat)
{
    SvGlobalName aName;

    switch (nFileFormat)
    {
        case SOFFICE_FILEFORMAT_60:
        {
            aName = SvGlobalName(BF_SO3_SM_CLASSID_60);
        }
        break;

        case SOFFICE_FILEFORMAT_50:
        {
            aName = SvGlobalName(BF_SO3_SM_CLASSID_50);
        }
        break;

        case SOFFICE_FILEFORMAT_40:
        {
            aName = SvGlobalName(BF_SO3_SM_CLASSID_40);
        }
        break;

        case SOFFICE_FILEFORMAT_31:
        {
            aName = SvGlobalName(BF_SO3_SM_CLASSID_30);
        }
        break;

        default:
        {
            DBG_ASSERT(FALSE, "Unbekanntes Fileformat!");
        }
        break;
    }

    return aName;
}

/*************************************************************************
|*
|* Bestimme die Version aus der GUID
|*
\************************************************************************/

USHORT SmModuleDummy::HasID (const SvGlobalName &rName)
{
    static const USHORT aIdArr[] = { SOFFICE_FILEFORMAT_31,
                                     SOFFICE_FILEFORMAT_40,
                                     SOFFICE_FILEFORMAT_50,
                                     SOFFICE_FILEFORMAT_60,
                                     0 };

    const USHORT *pArr = aIdArr; for( ; *pArr; ++pArr )
        if( GetID( *pArr ) == rName )
            break;
    return *pArr;
}

ULONG SmDLL::DetectFilter( SfxMedium& rMedium, const SfxFilter** ppFilter,
                            SfxFilterFlags nMust, SfxFilterFlags nDont )
{
    ULONG nReturn = ERRCODE_ABORT;
    if( SVSTREAM_OK != rMedium.GetError() )
        nReturn = rMedium.GetError();
    else if ( rMedium.IsStorage() )
    {
        // Storage
        SvStorage* pStorage = rMedium.GetStorage();

        if( !pStorage )
            nReturn = ULONG_MAX;
        else
        {
            // Erkennung ueber contained streams (StarChart 3.0)
            static const sal_Char sStrmNm_0[] = "StarMathDocument";
            static const sal_Char sFltrNm_0[] = "StarMath 5.0";
            static const sal_Char sStrmNm_1[] = "Equation Native";
            static const sal_Char sFltrNm_1[] = "MathType 3.x";
            static const sal_Char sStrmNm_2[] = "content.xml";
            static const sal_Char sFltrNm_2[] = STAROFFICE_XML;
            static const sal_Char sStrmNm_3[] = "Content.xml";
            static const sal_Char sFltrNm_3[] = STAROFFICE_XML;

            const sal_uInt16 nCount = 4;
            const sal_Char *aStrmNms[nCount] =
                { sStrmNm_0, sStrmNm_1, sStrmNm_2, sStrmNm_3 };
            const sal_Char *aFltrNms[nCount] =
                { sFltrNm_0, sFltrNm_1, sFltrNm_2, sFltrNm_3 };

            String aStreamName;
            String sFilterName;
            if( *ppFilter )
            {
                for( sal_uInt16 i=0; i < nCount; i++ )
                {
                    if( (*ppFilter)->GetFilterName().EqualsAscii(aFltrNms[i]) )
                    {
                        aStreamName.AssignAscii( aStrmNms[i] );
                        if( pStorage->IsStream( aStreamName ) &&
                            ((*ppFilter)->GetFilterFlags() & nMust) == nMust &&
                            ((*ppFilter)->GetFilterFlags() & nDont) == 0 )
                            nReturn = ERRCODE_NONE;

                        break;	// The old XML filter (Content.xml) will be
                                // detected in the next loop.
                    }
                }
            }

            if( ERRCODE_NONE != nReturn )
            {
                for( sal_uInt16 i=0; i < nCount; i++ )
                {
                    aStreamName.AssignAscii( aStrmNms[i] );
                    if( pStorage->IsStream( aStreamName ))
                    {
                        sFilterName.AssignAscii( aFltrNms[i] );
                        const SfxFilter* pFilt = SFX_APP()->GetFilter(
                                    SmDocShell::Factory(), sFilterName );

                        if( pFilt &&
                            (pFilt->GetFilterFlags() & nMust) == nMust &&
                            (pFilt->GetFilterFlags() & nDont) == 0)
                        {
                            *ppFilter = pFilt;
                            nReturn = ERRCODE_NONE;
                        }

                        break; // There are no two filters with the same strm name
                    }
                }
            }
        }
    }
    else
    {
        //Test to see if this begins with xml and if so run it through
        //the MathML filter. There are all sorts of things wrong with
        //this approach, to be fixed at a better level than here
        SvStream *pStrm = rMedium.GetInStream();
        if (pStrm && !pStrm->GetError())
        {
            const int nSize = 5;
            sal_Char aBuffer[nSize+1];
            aBuffer[nSize] = 0;
            ULONG nBytesRead = pStrm->Read( aBuffer, nSize );
            pStrm->Seek( STREAM_SEEK_TO_BEGIN );
            if (nBytesRead == nSize)
            {
                if (0 == strncmp( "<?xml",aBuffer,nSize))
                {
                    static const sal_Char sFltrNm_2[] = MATHML_XML;

                    String sFltrNm;
                    sFltrNm.AssignAscii( sFltrNm_2 );
                    const SfxFilter* pFilt = SFX_APP()->GetFilter(
                                    SmDocShell::Factory(), sFltrNm );
                    *ppFilter = pFilt;

                    nReturn = ERRCODE_NONE;
                }
            }
        }
    }
    return nReturn;
}




}
