/*
*
*  libsqlserver c++17 Version 1.1
*
*
*  Created by Wilson.Souza
*  Copyright (C) 2012, 2018, WR DevInfo, All Rights Reserved.
*
*  Description: access ms sqlserver by ado
*  Last update: 7/2019
*
*  Dependence: msado15.dll, sqlncli.lib
*/
#pragma once
#include <sql_server_connection.hpp>
#include <sql_server_table.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
   namespace catalog
   {
      static std::string_view const CatalogName = T( "CATALOG_NAME" );
      static std::string_view const TableName = T( "TABLE_NAME" );
   }
   //-----------------------------------------------------------------------------------------------//
   class _SQLDYNAMICLINK database :  
      virtual public server_connection,  
      virtual public _Connection,
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

      virtual bool const  disconnect( );
      virtual bool const  set_active_connection( bool enable = false );
      virtual bool const  is_connected( );
      virtual bool const  begin_transaction( );
      virtual bool const  commit_transaction( );
      virtual bool const  rollback( );
      //
      virtual void const  set_initial_catalog( std::wstring const & strinitialcatalog );
      virtual std::unicode_string::pointer  get_initial_catalog( );
      //
      virtual bool const  is_catalog( std::wstring const & strcatalogname );
      virtual bool const  is_table( std::wstring const & tablename );
      //
      virtual bool const  create_database( std::wstring const & strcatalogname );
      virtual bool const  create_table( std::wstring const & strtablename, std::wstring const & fields );
      //list
      virtual sql::table::pointer  get_catalogs( );
      virtual sql::table::pointer  get_tables( );
      virtual sql::table::pointer  open_schema( SchemaEnum se );
      //
   #if defined(_SQL_EVENTS)
      //Start events
      virtual void const    SetConnectionPtrEventsClass( );
      virtual void const    FinalizeConnectionPtrEventsClass( );
   #endif
      //
      virtual sql::table::pointer  execute( std::wstring const & strcmd, ExecuteOptionEnum mode = adExecuteRecord );
      virtual bool const  execute_non_query( std::wstring const & strcmd );
      /**/
      virtual bool drop_database( std::wstring const & szcatalogname );
      virtual bool drop_table( std::wstring const & sztablename );
   protected:
      virtual std::ansi_string::pointer __stdcall format_com_error( _com_error e );
      std::exception const __stdcall throw_com_error( _com_error e );
   };
};
//-----------------------------------------------------------------------------------------------//