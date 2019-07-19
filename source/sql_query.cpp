/*
*
*  libsql_x86_pplx c++14 Version 1.0 full unicode
*
*
*  Created by Wilson.Souza
*  Copyright (C) 2012, 2018 WR DevInfo, All Rights Reserved.
*
*  Description: access ms sqlserver by ado
*  Last update:
*  8/14/2018
*  Dependence: msado15.dll
*/
#include <sql_query.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
query::query( sql::database const & db ) :
   database( const_cast< sql::database & >( db ).GetInterfacePtr( ) )
{
}
//-----------------------------------------------------------------------------------------------//
sql::table::pointer __fastcall query::query::exec( std::unicode_string::pointer const & sql_cmd )
{
   if( sql_cmd == nullptr )
   {
      throw std::exception( "variable sql_cmd is null!" );
   }
   return this->exec( sql_cmd->reference( ) );
}
//-----------------------------------------------------------------------------------------------//
sql::table::pointer __fastcall query::query::exec( std::unicode_string const & sql_cmd )
{
   auto tbl = allocator<table, database>( *this );
   /**/
   if( sql_cmd.empty( ) )
   {
      throw std::exception( "sql command is empty!" );
   }

   tbl->open( sql_cmd );
   /**/
   if( tbl->eof( ) )
   {
      throw std::exception( "204 - No records found to this request, or ocurred a internal error!" );
   }
   return tbl;
}
//-----------------------------------------------------------------------------------------------//
sql::query::pointer __fastcall sql::query::clone( )
{
   return allocator<query, database>( *this );
}
//-----------------------------------------------------------------------------------------------//
