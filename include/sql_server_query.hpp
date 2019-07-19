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
*  Dependence: odbc32.lib
*/
#pragma once
#include <sql_server_connection.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class query: public ADORecordset
   {
   protected:
      sql::server_connection::server_connection_pointer m_connection;
      _RecordsetPtr m_record_ptr = NULL;
   public:
      explicit sql_query( std::shared_ptr<sql_connection> const & db_conn ) noexcept;
      virtual ~sql_query( );
      virtual bool execute( );
   };
}
