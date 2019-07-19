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
#pragma once
#include <sql_database.hpp>
#include <sql_table.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK query : public sql::database
   {
   public:
      using pointer = std::shared_ptr<sql::query>;
      using pointer_const = pointer const;
   public:
      query( ) = default;
      explicit query( sql::database const & db );
      virtual ~query( ) = default;
      sql::table::pointer __fastcall exec( std::unicode_string::pointer const & sql_cmd );
      sql::table::pointer __fastcall exec( std::unicode_string const & sql_cmd );
      sql::query::pointer __fastcall clone( );
   };
};
//-----------------------------------------------------------------------------------------------//