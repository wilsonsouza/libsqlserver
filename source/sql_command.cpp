/*
*
*  libsqlserver c++17 Version 1.1
*
*
*  Created by Wilson.Souza
*  Copyright (C) 2017, WR DevInfo, All Rights Reserved.

*
*  Description: access ms sqlserver by ado
*  Last update: 7/2019
*
*  Dependence: msado15.dll
*/
#include <sql_command.hpp>
#include <sql_table.hpp>
#include <sql_database.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
command::command( ) noexcept :connectinfo( )
{
   CreateInstance( __uuidof( _Command ) );
}
//-----------------------------------------------------------------------------------------------//
command::command( std::shared_ptr<sql::database> const & db ) : connectinfo( )
{
   auto p = dynamic_cast< _Connection * >( db->GetInterfacePtr( ) );
   CreateInstance( __uuidof( _Command ) );
   dynamic_cast< _CommandPtr & >( *this )->putref_ActiveConnection( p );
   set_connection( db );
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::table> command::execute( std::wstring const & sqlcmd )
{
   auto vrecordsaffected = _variant_t( );
   auto cmd = dynamic_cast< _CommandPtr & >( *this );
   auto rec = cmd->Execute( &vrecordsaffected, nullptr, adCmdText );
   /**/
   if( rec != nullptr )
   {
      if( rec->Requery( adCmdUnspecified ) != S_OK )
      {
         throw std::exception( "Failure to execute sql query!" );
      }
      return allocator<table, _RecordsetPtr>( rec );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
