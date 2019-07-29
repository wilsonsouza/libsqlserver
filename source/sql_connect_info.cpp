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
#include <sql_connectinfo.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
connectinfo::connectinfo( )
{
}
//-----------------------------------------------------------------------------------------------//
connectinfo::connectinfo( sql::connectinfo::pointer const & ptr )
{
   assign( ptr->begin( ), ptr->end( ) );
}
//-----------------------------------------------------------------------------------------------//
connectinfo::connectinfo( sql::connectinfo const & in )
{
   assign( in.begin( ), in.end( ) );
}
//-----------------------------------------------------------------------------------------------//
connectinfo::connectinfo( std::wstring const & user_id,
                          std::wstring const & password,
                          std::wstring const & initial_catalog,
                          std::wstring const & data_source )
{
   emplace( config::User_ID, user_id );
   emplace( config::Password, password );
   emplace( config::Initial_Catalog, initial_catalog );
   emplace( config::Data_Source, data_source );
   emplace( config::Initial_File_Name, std::T( "" ) );
   emplace( config::Server_SPN, std::T( "" ) );
}
//-----------------------------------------------------------------------------------------------//
std::unicode_string::pointer connectinfo::get_connection_string( )
{
   auto & out = std::unicode_string::alloc( );
   /**/
   std::for_each( begin( ), end( ), [ & ] ( value_type const & p )
   {
      out->append( std::wstring( p.first + std::T( "='" ) + p.second + std::T( "';" ) ) );
   } );
   return out;
}
//-----------------------------------------------------------------------------------------------//
void connectinfo::set_connection( std::shared_ptr<sql::connectinfo> const & conn )
{
   assign( conn->begin( ), conn->end( ) );
}
//-----------------------------------------------------------------------------------------------//
void connectinfo::set_connectinfo( std::vector<sql::connectinfo::value_type> const & ptr )
{
   this->assign( ptr.begin( ), ptr.end( ) );
}
//-----------------------------------------------------------------------------------------------//
sql::connectinfo::pointer connectinfo::get_connection( )
{
   return std::make_shared<connectinfo>( *this );
}
//-----------------------------------------------------------------------------------------------//
bool connectinfo::operator == ( sql::connectinfo const & in ) const
{
   return std::equal( begin( ), end( ), in.begin( ) );
}
//-----------------------------------------------------------------------------------------------//
void connectinfo::emplace( std::wstring const & fieldname, std::wstring const & value )
{
   auto updated = false;
   /**/
   for( auto & found : std::vector<value_type>( *this ) )
   {
      if( found.first.compare( fieldname ) == 0 )
      {
         found.second = value;
         updated = !updated;
         break;
      }
   }
   /**/
   if( !updated )
   {
      push_back( value_type( fieldname, value ) );
   }
}
//-----------------------------------------------------------------------------------------------//
void connectinfo::emplace( std::wstring const & fieldname, std::string const & value )
{
   emplace( fieldname, std::T( value ) );
}
//-----------------------------------------------------------------------------------------------//
void connectinfo::emplace( std::string const & fieldname, std::string const & value )
{
   emplace( std::T( fieldname ), std::T( value ) );
}
//-----------------------------------------------------------------------------------------------//
void connectinfo::emplace( std::string const & fieldname, std::wstring const & value )
{
   emplace( std::T( fieldname ), value );
}
//-----------------------------------------------------------------------------------------------//
std::vector<sql::connectinfo::value_type>::iterator connectinfo::get_map( std::wstring const & key )
{
   return std::find_if( begin( ), end( ), [ & ] ( value_type const & data )
   {
      return data.first.compare( key ) == 0;
   } );
}
//-----------------------------------------------------------------------------------------------//
std::vector<std::pair<std::wstring, std::wstring>>::iterator connectinfo::get_map( std::string const & key )
{
   return get_map( std::T( key ) );
}
//-----------------------------------------------------------------------------------------------//
