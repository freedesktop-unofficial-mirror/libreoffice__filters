/*************************************************************************
 *
 *  $RCSfile: scriptcont.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:52 $
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



#ifndef _SFX_SCRIPTCONT_HXX
#define _SFX_SCRIPTCONT_HXX

#include <namecont.hxx>
#ifndef _BASMGR_HXX
#include <basmgr.hxx>
#endif


//============================================================================

class BasicManager;

class SfxScriptLibraryContainer : public SfxLibraryContainer_Impl, public OldBasicPassword
{
    ::rtl::OUString maScriptLanguage;
    BasicManager* mpBasMgr;

    // Methods to distinguish between deffirent library types
    virtual SfxLibrary_Impl* SAL_CALL implCreateLibrary( void );
    virtual SfxLibrary_Impl* SAL_CALL implCreateLibraryLink
        ( const ::rtl::OUString& aLibInfoFileURL, 
          const ::rtl::OUString& StorageURL, sal_Bool ReadOnly );
    virtual ::com::sun::star::uno::Any SAL_CALL createEmptyLibraryElement( void );
    virtual sal_Bool SAL_CALL isLibraryElementValid( ::com::sun::star::uno::Any aElement );
    virtual void SAL_CALL writeLibraryElement
    ( 
        ::com::sun::star::uno::Any aElement,
        const ::rtl::OUString& aElementName, 
        ::com::sun::star::uno::Reference< ::com::sun::star::io::XOutputStream > xOutput 
    )
        throw(::com::sun::star::uno::Exception);
    virtual ::com::sun::star::uno::Any SAL_CALL importLibraryElement
        ( const ::rtl::OUString& aFile, SotStorageStreamRef xElementStream );
    virtual void SAL_CALL importFromOldStorage( const ::rtl::OUString& aFile );

    virtual SfxLibraryContainer_Impl* createInstanceImpl( void ){DBG_ASSERT(0, "STRIP");return NULL;}//STRIP001 virtual SfxLibraryContainer_Impl* createInstanceImpl( void );


    // Password encryption
    virtual sal_Bool implStorePasswordLibrary( SfxLibrary_Impl* pLib, const ::rtl::OUString& aName, 
        SotStorageRef xStorage );
    virtual sal_Bool implLoadPasswordLibrary( SfxLibrary_Impl* pLib, const ::rtl::OUString& Name,
        sal_Bool bVerifyPasswordOnly=false ) 
            throw(::com::sun::star::lang::WrappedTargetException, 
                  ::com::sun::star::uno::RuntimeException);

    // OldBasicPassword interface
    virtual void setLibraryPassword( const String& rLibraryName, const String& rPassword );
    virtual String getLibraryPassword( const String& rLibraryName );
    virtual void clearLibraryPassword( const String& rLibraryName );
    virtual sal_Bool hasLibraryPassword( const String& rLibraryName );
    
    sal_Bool init( const ::rtl::OUString& aInitialisationParam,
                   const ::rtl::OUString& aScriptLanguage,
                   BasicManager* pBasMgr=NULL, SotStorage* pStor=NULL );

public:
    SfxScriptLibraryContainer( void );
    SfxScriptLibraryContainer( const ::rtl::OUString& aScriptLanguage, 
        BasicManager* pBasMgr, SotStorage* pStor=NULL );

    // TODO: Methods of new XLibraryStorage interface?
    virtual void SAL_CALL storeLibraries( sal_Bool bComplete );
    virtual void SAL_CALL storeLibrariesToStorage( SotStorageRef xStorage );

    // Methods XInitialization
    virtual void SAL_CALL initialize( const ::com::sun::star::uno::Sequence< 
        ::com::sun::star::uno::Any >& aArguments ) 
            throw (::com::sun::star::uno::Exception, 
                   ::com::sun::star::uno::RuntimeException);

    // Methods XLibraryContainerPassword
    virtual sal_Bool SAL_CALL isLibraryPasswordProtected( const ::rtl::OUString& Name ) 
        throw (::com::sun::star::container::NoSuchElementException, 
               ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isLibraryPasswordVerified( const ::rtl::OUString& Name ) 
        throw (::com::sun::star::lang::IllegalArgumentException, 
               ::com::sun::star::container::NoSuchElementException, 
               ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL verifyLibraryPassword( const ::rtl::OUString& Name, const ::rtl::OUString& Password ) 
        throw (::com::sun::star::lang::IllegalArgumentException, 
               ::com::sun::star::container::NoSuchElementException, 
               ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL changeLibraryPassword( const ::rtl::OUString& Name, 
        const ::rtl::OUString& OldPassword, const ::rtl::OUString& NewPassword ) 
        throw (::com::sun::star::lang::IllegalArgumentException, 
               ::com::sun::star::container::NoSuchElementException, 
               ::com::sun::star::uno::RuntimeException);

    // Service
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > impl_getStaticSupportedServiceNames();
    static ::rtl::OUString impl_getStaticImplementationName();
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL impl_createInstance
        ( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager ) 
            throw( ::com::sun::star::uno::Exception );
    static ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory > impl_createFactory
        ( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager );

};

// class to represent application container service
class SfxApplicationScriptLibraryContainer
{
public:
    // Service
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > impl_getStaticSupportedServiceNames();
    static ::rtl::OUString impl_getStaticImplementationName();
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL impl_createInstance
        ( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager ) 
            throw( ::com::sun::star::uno::Exception );
    static ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory > impl_createFactory
        ( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager );

};


//============================================================================

class SfxScriptLibrary : public SfxLibrary_Impl
{
    friend SfxScriptLibraryContainer;

    sal_Bool mbLoadedSource;
    sal_Bool mbLoadedBinary;

public:
    SfxScriptLibrary
    (
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF,
        ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSFI
    );

    SfxScriptLibrary
    (
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF,
        ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSFI,
        const ::rtl::OUString& aLibInfoFileURL, const ::rtl::OUString& aStorageURL, sal_Bool ReadOnly
    );
};

#endif

