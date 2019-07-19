/*
*
*  libsql_x86_pplx c++14 Version 1.0
*
*
*  Created by Wilson.Souza
*  Copyright (C) 2012, 2018, WR DevInfo, All Rights Reserved.
*
*  Description: access ms sqlserver by ado
*  Last update:
*
*  Dependence: msado15.dll, sqlncli.lib
*/
#pragma once
#include <sql_server_connection.hpp>
#include <sql_table.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   namespace catalog
   {
      static std::aul::string<wchar_t> const CatalogName = T( "CATALOG_NAME" );
      static std::aul::string<wchar_t> const TableName = T( "TABLE_NAME" );
   }
   //-----------------------------------------------------------------------------------------------//
   class _SQLDYNAMICLINK database :  
      virtual public server_connection,  
      virtual public _ConnectionPtr,
      public concurrency::task_group
   {
   public:
      using pointer = std::shared_ptr<database>;
   protected:
      DWORD m_dwConnectionEvent;
      IConnectionPointContainer *m_pConnPointC;
      IConnectionPoint *m_pConnPoint;
      IUnknown *m_unknown;
      bool m_is_canceling{ false };
   public:
      database( );
      explicit database( sql::server_connection const & sql_handle );
      explicit database( _ConnectionPtr const & db );
      virtual ~database( );

      virtual bool const __fastcall disconnect( );
      virtual bool const __fastcall set_active_connection( bool enable = false );
      virtual bool const __fastcall is_connected( );
      virtual bool const __fastcall begin_transaction( );
      virtual bool const __fastcall commit_transaction( );
      virtual bool const __fastcall rollback( );
      //
      virtual void const __fastcall set_initial_catalog( std::wstring const & strinitialcatalog );
      virtual std::unicode_string::pointer __fastcall get_initial_catalog( );
      //
      virtual bool const __fastcall is_catalog( std::wstring const & strcatalogname );
      virtual bool const __fastcall is_table( std::wstring const & tablename );
      //
      virtual bool const __fastcall create_database( std::wstring const & strcatalogname );
      virtual bool const __fastcall create_table( std::wstring const & strtablename, std::wstring const & fields );
      //list
      virtual sql::table::pointer __fastcall get_catalogs( );
      virtual sql::table::pointer __fastcall get_tables( );
      virtual sql::table::pointer __fastcall open_schema( SchemaEnum se );
      //
   #if defined(_SQL_EVENTS)
      //Start events
      virtual void const   __fastcall SetConnectionPtrEventsClass( );
      virtual void const   __fastcall FinalizeConnectionPtrEventsClass( );
   #endif
      //
      virtual sql::table::pointer __fastcall execute( std::wstring const & strcmd, ExecuteOptionEnum mode = adExecuteRecord );
      virtual bool const __fastcall execute_non_query( std::wstring const & strcmd );
      /**/
      virtual bool drop_database( std::wstring const & szcatalogname );
      virtual bool drop_table( std::wstring const & sztablename );
   protected:
      virtual std::ansi_string::pointer __stdcall format_com_error( _com_error e );
      std::exception const __stdcall throw_com_error( _com_error e );
   };
};
//-----------------------------------------------------------------------------------------------//