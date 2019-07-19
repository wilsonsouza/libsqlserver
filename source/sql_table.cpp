/*
*
*  libsqlserver c++11 Version 1.0
*
*
*  Created by Wilson.Souza
*  Copyright (C) 2017, WR DevInfo, All Rights Reserved.
*  Copyright (C) 2017, Tecsidel do Brasil, All Rights Reserved.
*
*  Description: access ms sqlserver by ado
*  Last update:
*
*  Dependence: msado15.dll
*/
#include <sql_database.hpp>
#include <sql_table.hpp>
#include <sql_query.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
using namespace concurrency;
//-----------------------------------------------------------------------------------------------//
table::table( ) :connectinfo( )
{
   auto success = CreateInstance( __uuidof( Recordset ) );
   m_db = GetInterfacePtr( );
}
//-----------------------------------------------------------------------------------------------//
table::table( sql::database const & db ) : connectinfo( db )
{
   auto success = CreateInstance( __uuidof( Recordset ) );
   m_db = GetInterfacePtr( );
   m_db->putref_ActiveConnection( db.GetInterfacePtr( ) );
}
//-----------------------------------------------------------------------------------------------//
table::table( _RecordsetPtr const & db ) : connectinfo( )
{
   auto success = CreateInstance( __uuidof( Recordset ) );
   /* assign new recordset */
   _RecordsetPtr::operator=( db );
   m_db = GetInterfacePtr( );
   m_db->put_StayInSync( true );
   get_fieldlist( );
}
//-----------------------------------------------------------------------------------------------//
table::~table( )
{
   /* free list */
   multimap_type::clear( );
   /* cancel task if still running */
#if defined(_PPLX)
   cancel( );
#else
   m_is_canceling = true;
#endif
#if defined(_SQL_EVENTS)
   /* finalize event class */
   //FinalizeRecordsetPtrEventsClass();
#endif
   /**/
   if( m_db->State == adStateOpen )
   {
      m_db->Close( );
   }
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::open( std::wstring const & tablename,
                                   CommandTypeEnum cteCommandType,
                                   CursorTypeEnum ctCursorType,
                                   LockTypeEnum ltLockType )
{
   try
   {
      auto success = S_FALSE;
      /**/
      if( is_actived( ) )
      {
         close( );
      }
      /* call by pplx */
      {
         _variant_t sqlcmd = tablename.c_str( );
         _variant_t active_connection = get_connection_string( )->data( );
         /**/
         m_db->put_CursorLocation( CursorLocationEnum::adUseClient );
         m_db->put_StayInSync( true );
         /**/
         if( m_db->Open( sqlcmd, active_connection, ctCursorType, ltLockType, cteCommandType ) != S_OK )
         {
            auto s = std::format( MAX_PATH,
                                  "called table::open(%s) failed result %ld!",
                                  get_connection_string( )->to_ansi( )->data( ),
                                  success );
            throw std::exception( s->data( ) );
         }
      }
      //check command
      auto cmd_list = std::vector<std::wstring>{{std::T( "insert" ), std::T( "update" ), std::T( "delete" )}};
      auto sql_cmd = std::unicode_string( tablename ).lowercase( );
      /**/
      if( std::find_if( cmd_list.begin( ), cmd_list.end( ), [ & ] ( std::unicode_string const & data )
      {
         return sql_cmd.find( data, data.length( ) ) == 0;
      } ) != cmd_list.end( ) )
      {
         return false;
      }
      /**/
      get_fieldlist( );
      /**/
      if( !eof( ) )
      {
         top( );
         return true;
      }
      return true;
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   catch( std::exception & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::eof( )
{
   try
   {
      return bool( m_db->EndOfFile );
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::bof( )
{
   try
   {
      return bool( m_db->BOF );
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::go( long const lrecno )
{
   try
   {
      auto result = S_FALSE;
      /**/
      if( !eof( ) && !bof( ) )
      {
         if( ( result = m_db->Move( lrecno ) ) == S_OK )
         {
            m_lrecno = lrecno;
            return true;
         }
         /**/
         throw _com_error{result};
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall table::reccount( )
{
   try
   {
      long lcount = 0L;
      auto result = m_db->get_RecordCount( &lcount );
      /**/
      if( result == S_OK && lcount >= 0L )
      {
         return lcount;
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return 0L;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall table::recno( )
{
   return m_lrecno;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall table::lastrec( )
{
   try
   {
      return reccount( );
   }
   catch( std::exception & e )
   {
      throw e;
   }
   return 0L;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::top( )
{
   try
   {
      if( !bof( ) )
      {
         return bool( m_lrecno = m_db->MoveFirst( ) );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::bottom( )
{
   try
   {
      if( !eof( ) )
      {
         return bool( m_lrecno = m_db->MoveLast( ) );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::next( )
{
   try
   {
      if( !eof( ) && !bof( ) )
      {
         return bool( m_lrecno = m_db->MoveNext( ) );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::previous( )
{
   try
   {
      if( !eof( ) && !bof( ) )
      {
         return bool( m_lrecno = m_db->MovePrevious( ) );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::skip( long lrecno )
{
   return go( lrecno );
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall table::close( )
{
   try
   {
      multimap_type::clear( );
      m_db->Close( );
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
}
//-----------------------------------------------------------------------------------------------//
field::pointer __fastcall table::operator[]( std::wstring const & strname )
{
   return get_field( strname );
}
//-----------------------------------------------------------------------------------------------//
field::pointer __fastcall table::operator[]( std::unicode_string::pointer const & pname )
{
   return get_field( pname );
}
//-----------------------------------------------------------------------------------------------//
field::pointer __fastcall table::operator[]( unsigned int uIndex )
{
   auto fps = m_db->GetFields( );
   /**/
   if( long( uIndex ) >= fps->GetCount( ) )
   {
      throw std::exception
      {
         std::format( MAX_PATH, "Field index %d out range!", uIndex )->data( )
      };
   }
   /**/
   _variant_t index;
   index.vt = VT_I2;
   index.iVal = SHORT( uIndex );
   /**/
   return field::pointer( new field( fps->GetItem( index ) ) );
}
//-----------------------------------------------------------------------------------------------//
field::pointer __fastcall table::get_field( std::wstring const & strname )
{
   auto fps = m_db->GetFields( );
   auto offset = int( fps->Count );
   _variant_t vindex;
   bool ok = false;
   /**/
   vindex.vt = VT_I2;
   /**/
   for( int i = 0; i < offset && !ok; i++ )
   {
      vindex.iVal = i;
      /**/
      auto fp = fps->GetItem( vindex );
      ok = std::unicode_string( strname ).lowercase( ).compare( std::unicode_string( fp->Name ).lowercase( ) ) == 0;
   }
   /**/
   if( !ok )
   {
      throw std::exception
      {
         std::unicode_string( std::T( "Field " ) + strname + std::T( " not exists!" ) ).to_ansi( )->data( )
      };
   }
   /**/
   return field::pointer( new field( fps->GetItem( vindex ) ) );
}
//-----------------------------------------------------------------------------------------------//
field::pointer __stdcall table::get_field( std::unicode_string::pointer const & pname )
{
   return get_field( pname->data( ) );
}
//-----------------------------------------------------------------------------------------------//
field::pointer __fastcall table::get_field( unsigned int uIndex )
{
   return table::operator[]( uIndex );
}
//-----------------------------------------------------------------------------------------------//
table::multimap_type & __fastcall table::get_fieldlist( std::initializer_list<std::wstring> const ignored_list )
{
   /* call by pplx */
   run_and_wait( [ &, this ]
   {
      try
      {
         auto fps = m_db->GetFields( );
         auto offset = int( fps->Count );
         _variant_t vindex;
         auto fn_compare_ignored_list = [ & ] ( std::unicode_string & name )->bool const
         {
            for( auto && i : ignored_list )
            {
               if( name.lowercase( ).compare( std::unicode_string( i ).lowercase( ) ) == 0 )
               {
                  return true;
               }
            }
            return false;
         };
         /**/
         vindex.vt = VT_I2;
         multimap_type::clear( );
         /**/
         for( int i = 0; i < offset; i++ )
         {
            vindex.iVal = i;
            /**/
            auto fp = fps->GetItem( vindex );
            /**/
            if( !fn_compare_ignored_list( std::unicode_string( fp->Name ) ) )
            {
               multimap_type::emplace( fp->Name, field::pointer( new field( fp ) ) );
            }
         }
      }
      catch( _com_error & e )
      {
         throw std::exception( format_com_error( e )->c_str( ) );
      }
   } );
   return *this;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall table::is_actived( )
{
   try
   {
      if( m_db->State == adStateOpen )
      {
         return true;
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
#if defined(_SQL_EVENTS)
void const __fastcall table::SetRecordsetPtrEventsClass( )
{
   /* check client window handle to notified */
   m_hSuccess = _RecordsetPtr::operator->( )->QueryInterface( __uuidof( IConnectionPointContainer ),
                                                              reinterpret_cast< void ** >( &m_pConnPointC ) );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called _RecordsetPtr::operator->()->QueryInterface() failed!" );
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint( __uuidof( RecordsetEvents ), &m_pConnPoint );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPointC->FindConnectionPoint() failed!" );
   /**/
   m_pTableEvent = std::shared_ptr<TableEvent>( new TableEvent( this ) );
   m_hSuccess = m_pTableEvent->QueryInterface( __uuidof( IUnknown ), reinterpret_cast< void ** >( &m_pUnknown ) );
   /**/
   m_hSuccess = m_pConnPoint->Advise( m_pUnknown, static_cast< LPDWORD >( &m_dwRecordEvent ) );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPoint->Advise() failed!" );
   /**/
   m_pConnPoint->Release( );
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall table::FinalizeRecordsetPtrEventsClass( )
{
   /* event class not started */
   m_hSuccess = _RecordsetPtr::operator->( )->QueryInterface( __uuidof( IConnectionPointContainer ),
                                                              reinterpret_cast< void ** >( &m_pConnPointC ) );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called _RecordsetPtr::operator->()->QueryInterface() failed!" );
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint( __uuidof( RecordsetEvents ), &m_pConnPoint );
   m_pConnPointC->Release( );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPointC->FindConnectionPoint() failed!" );
   /**/
   m_hSuccess = m_pConnPoint->Unadvise( m_dwRecordEvent );
   m_pConnPoint->Release( );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPoint->Unadivse() failed!" );
}
#endif
//-----------------------------------------------------------------------------------------------//
std::ansi_string::pointer __stdcall table::format_com_error( _com_error e )
{
   auto s = std::ansi_string
   {
      "Description: " + std::string( e.Description( ) ) + "\n" +
      "Error      : " + std::to_string( e.Error( ) ) + "\n" +
      "Message    : " + std::string( LPSTR( e.ErrorMessage( ) ) ) + "\n" +
      "Source     : " + std::string( e.Source( ) ) + "\n" +
      "Code       : " + std::to_string( e.WCode( ) )
   };
   return s.clone( );
}
//-----------------------------------------------------------------------------------------------//
