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
#include <sql_server_connection.hpp>
#include <variant>
#include <exception>
//-----------------------------------------------------------------------------------------------//
sql::server_connection::server_connection( )
{
   this->m_data = data::pointer( new data() );
}
//-----------------------------------------------------------------------------------------------//
sql::server_connection::~server_connection( )
{
   this->close( );
}
//-----------------------------------------------------------------------------------------------//
bool sql::server_connection::open( sql::connection_impl::data const & user_data_info )
{
   try
   {

   }
   catch( std::exception const & e )
   {
      this->m_data->m_connected = false;
   }
   return this->m_data->m_connected;
}
//-----------------------------------------------------------------------------------------------//
void sql_connection::close( )
{
   if( this->m_odbc_handler != NULL )
   {
      SQLDisconnect( this->m_odbc_handler );
      SQLFreeConnect( this->m_odbc_handler );
      this->m_odbc_handler = NULL;
      this->m_sql_user_data_copy->m_connected = false;
   }
   if( this->m_odbc_environment != NULL )
   {
      SQLFreeEnv( this->m_odbc_environment );
      this->m_odbc_environment = NULL;
   }
}
//-----------------------------------------------------------------------------------------------//
bool sql_connection::open( std::string const & connection_file )
{

}
//-----------------------------------------------------------------------------------------------//
bool sql_connection::isconnected( ) const
{
   return this->m_sql_user_data_copy->m_connected;
}
//-----------------------------------------------------------------------------------------------//
bool const sql_connection::initialize_complus( )
{
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const sql_connection::uninitialize_complus( )
{
   return true;
}
//-----------------------------------------------------------------------------------------------//