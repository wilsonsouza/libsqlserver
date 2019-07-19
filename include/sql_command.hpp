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
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK table;
   class _SQLDYNAMICLINK database;
   class _SQLDYNAMICLINK command :
      virtual public connectinfo,
      virtual public _CommandPtr
   {
   public:
      command( ) noexcept;
      explicit command( std::shared_ptr<sql::database> const & db );
      virtual ~command( ) = default;
      std::shared_ptr<sql::table> execute( std::wstring const & sqlcmd );
   };
   //-----------------------------------------------------------------------------------------------//
};