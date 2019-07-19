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
#include <sql_defs.hpp>
#include <sql_interface.hpp>
#include <sql_query.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
static bool s_initialized = false;
static std::shared_ptr<sql::query> s_db = nullptr;
//-----------------------------------------------------------------------------------------------//
_SQLDYNAMICLINK bool const complus::initialize( unsigned long value )
{
   if( !s_initialized )
   {
      if( ( s_initialized = SUCCEEDED( ::CoInitializeEx( NULL, value ) ) ) == false )
      {
         throw std::exception
         {
            std::string( "Cann´t possible initialize complus manager!" ).c_str( )
         };
      }
   }
   return s_initialized;
}
//-----------------------------------------------------------------------------------------------//
_SQLDYNAMICLINK const void complus::uninitialize( )
{
   if( s_initialized )
   {
      if( s_db )
      {
         s_db.reset( );
      }
      /**/
      ::CoUninitialize( );
      s_initialized = false;
   }
}
//-----------------------------------------------------------------------------------------------//
_SQLDYNAMICLINK bool const complus::is_started( )
{
   return s_initialized;
}
//-----------------------------------------------------------------------------------------------//
_SQLDYNAMICLINK std::shared_ptr<sql::query> complus::get_db( )
{
   if( s_db == nullptr )
   {
      s_db = allocator<sql::query>( );
   }
   return s_db;
}
//-----------------------------------------------------------------------------------------------//