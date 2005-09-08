/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_dbgloop.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:04:51 $
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

//#ifdef PRODUCT
//#error Wer fummelt denn an den makefiles rum?
//#endif

// auto strip #ifndef _STREAM_HXX //autogen
// auto strip #include <tools/stream.hxx>
// auto strip #endif
//#include "dbgloop.hxx"
//#include "errhdl.hxx"
namespace binfilter {

//DbgLoopStack DbgLoop::aDbgLoopStack;

/*************************************************************************
 *						class DbgLoopStack
 *************************************************************************/

///*N*/ DbgLoopStack::DbgLoopStack()
///*N*/ {
///*N*/ 	Reset();
///*N*/ }

///*N*/ void DbgLoopStack::Reset()
///*N*/ {
///*N*/ 	nPtr = 0;
///*N*/ 	pDbg = 0;
///*N*/ 	for( USHORT i = 0; i < DBG_MAX_STACK; ++i )
///*N*/ 		aCount[i] = 0;
///*N*/ }

/*************************************************************************
 *						 DbgLoopStack::Push()
 *************************************************************************/

///*N*/ void DbgLoopStack::Push( const void *pThis )
///*N*/ {
///*N*/ 	// Wir muessen irgendwie mitbekommen, wann die erste Stackposition
///*N*/ 	// resettet werden soll, z.B. wenn wir einen Nullpointer uebergeben
///*N*/ 	if( !nPtr && ( pDbg != pThis || !pThis ) )
///*N*/ 	{
///*N*/ 		aCount[1] = 0;
///*N*/ 		pDbg = pThis;
///*N*/ 	}
///*N*/ 
///*N*/ 	++nPtr;
///*N*/ 	if( DBG_MAX_STACK > nPtr )
///*N*/ 	{
///*N*/ 		// Wenn eine loop entdeckt wird, wird der counter wieder zurueckgesetzt.
///*N*/ 		ASSERT( DBG_MAX_LOOP > aCount[nPtr], "DbgLoopStack::Push: loop detected" );
///*N*/ 		if( DBG_MAX_LOOP > aCount[nPtr] )
///*N*/ 			++(aCount[nPtr]);
///*N*/ 		else
///*N*/ 			aCount[nPtr] = 0;
///*N*/ 	}
///*N*/ }

/*************************************************************************
 *						 DbgLoopStack::Pop()
 *************************************************************************/

///*N*/ void DbgLoopStack::Pop()
///*N*/ {
///*N*/ 	if( DBG_MAX_STACK > nPtr )
///*N*/ 	{
///*N*/ 		ASSERT( nPtr, "DbgLoopStack::Pop: can't pop the stack" );
///*N*/ 
///*N*/ 		ASSERT( aCount[nPtr], "DbgLoopStack::Pop: can't dec the count" );
///*N*/ 		if( DBG_MAX_STACK > nPtr + 1 )
///*N*/ 			aCount[nPtr + 1] = 0;
///*N*/ 	}
///*N*/ 	--nPtr;
///*N*/ }

/*************************************************************************
 *						 DbgLoopStack::Print()
 *************************************************************************/

//STRIP001 void DbgLoopStack::Print( SvStream &rOS ) const
//STRIP001 {
//STRIP001 	rOS << "POS: " << nPtr << '\n';
//STRIP001 	for( USHORT i = 0; i < DBG_MAX_STACK; ++i )
//STRIP001 		rOS << i << " ";
//STRIP001 	rOS << '\n';
//STRIP001 	for( i = 0; i < DBG_MAX_STACK; ++i )
//STRIP001 		rOS << aCount[i] << " ";
//STRIP001 	rOS << '\n';
//STRIP001 }

//#ifdef STAND_ALONE
// compile with: cl /AL /DSTAND_ALONE dbgloop.cxx

/*************************************************************************
 *							main()
 *************************************************************************/

//#include <stdlib.h>

///*N*/ void AssertFail( const char *pErr, const char *pFile, USHORT nLine )
///*N*/ {
///*N*/ 	cout << pErr << '\n';
/////*N*/ 	PrintLoopStack( cout );
///*N*/ 	exit(0);
///*N*/ }

//STRIP001 class Test
//STRIP001 {
//STRIP001 public:
//STRIP001 		void Run() const;
//STRIP001 };
//STRIP001 
//STRIP001 void Test::Run() const
//STRIP001 {
//STRIP001 	cout << "---" << '\n';
//STRIP001 	for( USHORT i = 0; i < 10; ++i )
//STRIP001 	{
//STRIP001 		cout << "i" << i;
//STRIP001 		DBG_LOOP;
//STRIP001 		PrintLoopStack( cout );
//STRIP001 		for( USHORT j = 0; j < 10; ++j )
//STRIP001 		{
//STRIP001 			cout << " j" << j;
//STRIP001 			DBG_LOOP;
//STRIP001 			PrintLoopStack( cout );
//STRIP001 		}
//STRIP001 		cout << '\n';
//STRIP001 	}
//STRIP001 	PrintLoopStack( cout );
//STRIP001 }
//STRIP001 
//STRIP001 int main()
//STRIP001 {
//STRIP001 	// unterschiedliche Instanzen waehlen wg. pDbg != pThis
//STRIP001 	Test aTest1;
//STRIP001 	aTest1.Run();
//STRIP001 	Test aTest2;
//STRIP001 	aTest2.Run();
//STRIP001 	return 0;
//STRIP001 }
//#endif


}
