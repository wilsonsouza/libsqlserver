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
#include <sql_table.hpp>
#include <sql_error.hpp>
#include <sql_database.hpp>
//-----------------------------------------------------------------------------------------------//
#pragma comment(lib, "libaulstring.lib")
//-----------------------------------------------------------------------------------------------//
sql::database::database( )
{
   auto success = CreateInstance( __uuidof( _ADOConnection ) );
#if defined(_SQL_EVENTS)   //
   if( success == S_OK )
   {
      SetConnectionPtrEventsClass( );
   }
   /**/
#endif
}
//-----------------------------------------------------------------------------------------------//
database::database( sql::connectinfo const & sqlcon ) :connectinfo( sqlcon )
{
   auto success = CreateInstance( __uuidof( _Connection ) );
#if defined(_SQL_EVENTS)   //
   if( success == S_OK )
   {
      SetConnectionPtrEventsClass( );
   }
   /**/
#endif
}
//-----------------------------------------------------------------------------------------------//
database::database( _ConnectionPtr const & db ) :connectinfo( )
{
   CreateInstance( __uuidof( _Connection ) );
   _ConnectionPtr::operator=( db );
#if defined(_SQL_EVENTS)   //
   SetConnectionPtrEventsClass( );
   /**/
#endif
}
//-----------------------------------------------------------------------------------------------//
database::~database( )
{
   auto wait_ms = std::chrono::duration<double, std::milli>( 0x64 );
#if defined(_PPLX)
   cancel( );
#else
   m_is_canceling = true;
#endif
   /* wait 100 milliseconds to disconnect */
   std::this_thread::sleep_for( wait_ms );
#if defined(_SQL_EVENTS)   //
   FinalizeConnectionPtrEventsClass( );
#endif
   disconnect( );
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::disconnect( )
{
   try
   {
      long lState;
      /**/
      if( GetInterfacePtr( )->get_State( &lState ) == S_OK )
      {
         if( lState == adStateOpen )
         {
            if( GetInterfacePtr( )->Close( ) == S_OK )
            {
               return true;
            }
         }
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::set_active_connection( bool benable )
{
   try
   {
      if( benable )
      {
         bstr_t bConnectionString = get_connection_string( )->data( );
         auto db = GetInterfacePtr( );

         /* detected if already connected with db */
         if( is_connected( ) )
         {
            return true;
         }
         /* set parameters */
         db->put_CursorLocation( adUseClient );
         db->put_IsolationLevel( adXactUnspecified );
         /**/
         auto success = S_FALSE;
         auto dns = get_map( config::DNS );
         auto u = std::unicode_string::copy_alloc( get_map( config::User_ID )->second );
         auto p = std::unicode_string::copy_alloc( get_map( config::Password )->second );
         /**/
         if( dns != end( ) )
         {
            auto d = std::unicode_string::copy_alloc( dns->second );
            /* rebuild */
            clear( );
            /**/
            emplace( config::DNS, d->reference() );
            emplace( config::User_ID, u->reference() );
            emplace( config::Password, p->reference() );
            /* open connection with sql server */
            success = db->Open( d->data( ), u->data( ), p->data( ), adConnectUnspecified );
         }
         else
         {
            success = db->Open( bConnectionString, "", "", adConnectUnspecified );
         }
         /**/
         if( success != S_OK )
         {
            throw std::exception( this->format_com_error( _com_error( success ) )->c_str( ) );
         }
      }
      else
      {
         this->disconnect( );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   catch( std::exception & e )
   {
      throw e;
   }
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::is_connected( )
{
   try
   {
      if( GetInterfacePtr( )->State == adStateOpen )
      {
         return true;
      }
   }
   catch( _com_error & e )
   {
      throw this->throw_com_error( e );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::begin_transaction( )
{
   try
   {
      if( GetInterfacePtr( )->BeginTrans( ) == S_OK )
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
bool const __fastcall database::commit_transaction( )
{
   try
   {
      if( GetInterfacePtr( )->CommitTrans( ) == S_OK )
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
bool const __fastcall database::rollback( )
{
   try
   {
      if( GetInterfacePtr( )->RollbackTrans( ) == S_OK )
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
sql::table::pointer __fastcall database::execute( std::wstring const & szCmd, ExecuteOptionEnum eMode )
{
   try
   {
      VARIANT vRecordsAffected = VARIANT( );
      auto pDataSet = GetInterfacePtr( )->Execute( szCmd.data( ), &vRecordsAffected, eMode );
      /**/
      if( eMode == adExecuteRecord )
      {
         return allocator<table, _RecordsetPtr>( pDataSet );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::execute_non_query( std::wstring const & szCmd )
{
   try
   {
      run_and_wait( [ & ]
      {
         _bstr_t bszCmd = szCmd.c_str( );
         GetInterfacePtr( )->Execute( bszCmd, nullptr, adExecuteNoRecords );
      } );
      return true;
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
sql::table::pointer __fastcall database::get_catalogs( )
{
   try
   {
      auto & r = GetInterfacePtr( )->OpenSchema( adSchemaCatalogs );

      if( r != nullptr )
      {
         return allocator<table, _RecordsetPtr>( r );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
sql::table::pointer __fastcall database::get_tables( )
{
   try
   {
      auto & r = GetInterfacePtr( )->OpenSchema( adSchemaTables );
      /**/
      if( r != nullptr )
      {
         return allocator<table, _RecordsetPtr>( r );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
sql::table::pointer __fastcall database::open_schema( SchemaEnum se )
{
   try
   {
      auto & r = GetInterfacePtr( )->OpenSchema( se );
      /**/
      if( r != nullptr )
      {
         return allocator<table, _RecordsetPtr>( r );
      }
   }
   catch( _com_error & e )
   {
      throw std::exception( format_com_error( e )->c_str( ) );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::is_catalog( std::wstring const & szCatalogName )
{
   try
   {
      bool bExists = false;
      /**/
      run_and_wait( [ & ]
      {
         auto p = open_schema( adSchemaCatalogs );

         if( p != nullptr )
         {
            while( !p->eof( ) && !is_canceling( ) && !bExists )
            {
               auto f = p->get_field( sql::catalog::CatalogName );

               if( f != nullptr )
               {
                  if( f->name( )->compare( szCatalogName ) == 0 )
                  {
                     bExists = !bExists;
                     return;
                  }
               }
               /**/
               p->next( );
            }
         }
      } );
      return bExists;
   }
   catch( std::exception & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::is_table( std::wstring const & szTableName )
{
   try
   {
      bool bSuccess = false;
      /* call by pplx */
      run_and_wait( [ & ]
      {
         auto queue = get_tables( );
         /**/
         if( queue != nullptr )
         {
            while( !queue->eof( ) && !is_canceling( ) )
            {
               auto f = queue->get_field( sql::catalog::TableName );
               /**/
               if( f != nullptr )
               {
                  if( f->name( )->compare( szTableName ) == 0 )
                  {
                     bSuccess = !bSuccess;
                     return;
                  }
               }
               /**/
               queue->next( );
            }
         }
      } );
      /* catch result */
      return bSuccess;
   }
   catch( _com_error const & e )
   {
      throw std::exception( format_com_error( const_cast< _com_error & >( e ) )->c_str( ) );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::create_database( std::wstring const & strCatalogName )
{
   try
   {
      if( execute_non_query( std::T( "create database " ) + strCatalogName ) )
      {
         GetInterfacePtr( )->put_DefaultDatabase( bstr_t( strCatalogName.c_str( ) ) );
         return true;
      }
   }
   catch( std::exception & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall database::create_table( std::wstring const & szTableName,
                                              std::wstring const & szFields )
{
   try
   {
      return execute_non_query( std::T( "create table dbo." ) +
                                szTableName +
                                std::T( "(" ) +
                                szFields + std::T( ")" ) );
   }
   catch( std::exception & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
void const database::set_initial_catalog( std::wstring const & szInitialCatalog )
{
   auto db = GetInterfacePtr( );
   /**/
   db->put_DefaultDatabase( bstr_t( szInitialCatalog.c_str( ) ) );
   emplace( config::Initial_Catalog, szInitialCatalog );
}
//-----------------------------------------------------------------------------------------------//
std::unicode_string::pointer __fastcall database::get_initial_catalog( )
{
   auto catalog = get_map( config::Initial_Catalog );
   /**/
   if( catalog != end( ) )
   {
      return std::unicode_string::copy_alloc( catalog->second );
   }
   return std::unicode_string::alloc( );
}
//-----------------------------------------------------------------------------------------------//
#if defined(_SQL_EVENTS)
void const   __fastcall database::SetConnectionPtrEventsClass( )
{
#if 0
   /* check client window handle to notified */
   m_hSuccess = m_conn->QueryInterface( __uuidof( IConnectionPointContainer ),
                                        reinterpret_cast< void ** >( &m_pConnPointC ) );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_conn->QueryInterface() failed!" );
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint( __uuidof( ConnectionEvents ), &m_pConnPoint );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPointC->FindConnectionPoint() failed!" );
   /**/
   m_hSuccess = m_pConnPoint->QueryInterface( __uuidof( IUnknown ), reinterpret_cast< void ** >( &m_pUnknown ) );
   /**/
   m_hSuccess = m_pConnPoint->Advise( m_pUnknown, static_cast< LPDWORD >( &m_dwConnectionEvent ) );
   /**/
   if( FAILED( m_hSuccess ) )
   {
      throw std::exception( "called m_pConnPoint->Advise() failed!" );
   }
   /**/
   m_pConnPoint->Release( );
#endif
}
//-----------------------------------------------------------------------------------------------//
void const   __fastcall database::FinalizeConnectionPtrEventsClass( )
{
#if 0
   m_hSuccess = m_conn->QueryInterface( __uuidof( IConnectionPointContainer ),
                                        reinterpret_cast< void ** >( &m_pConnPointC ) );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_conn->QueryInterface() failed!" );
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint( __uuidof( ConnectionEvents ), &m_pConnPoint );
   m_pConnPointC->Release( );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPointC->FindConnectionPoint() failed!" );
   /**/
   m_hSuccess = m_pConnPoint->Unadvise( m_dwConnectionEvent );
   m_pConnPoint->Release( );
   /**/
   if( FAILED( m_hSuccess ) )
      throw std::exception( "called m_pConnPoint->Unadivse() failed!" );
#endif
}
#endif
//-----------------------------------------------------------------------------------------------//
bool database::drop_database( std::wstring const & szCatalogName )
{
   try
   {
      //select other catalog to erase the current
      set_initial_catalog( std::T( "master" ) );
      //active connection
      set_active_connection( true );
      //check if catalog
      if( is_catalog( szCatalogName ) )
      {
         return execute_non_query( std::T( "drop database " ) + szCatalogName );
      }
      //isn´t rollback
      set_initial_catalog( szCatalogName );
      set_active_connection( true );
   }
   catch( std::exception const & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool database::drop_table( std::wstring const & szTableName )
{
   try
   {
      if( is_table( szTableName ) )
      {
         return execute_non_query( std::T( "drop table " ) + szTableName );
      }
   }
   catch( std::exception const & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
std::ansi_string::pointer __stdcall database::format_com_error( _com_error e )
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
std::exception const __stdcall database::throw_com_error( _com_error e )
{
   return std::exception( format_com_error( e )->data( ) );
}
//-----------------------------------------------------------------------------------------------//

