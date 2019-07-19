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
#include <sql_server_connection_impl.hpp>
//-----------------------------------------------------------------------------------------------//
bool sql::connection_impl::m_complus_ok = false;
std::size_t sql::connection_impl::m_id = 0;
sql::connection_impl::interanL_stacker m_internal_stacker = sql::connection_impl::interanL_stacker{};
//-----------------------------------------------------------------------------------------------//
sql::connection_impl::connection_impl() noexcept
{ 
   this->initialize_complus( );
   this->m_connection_id = ++connection_impl::m_id;
   m_internal_stacker.emplace( this->m_connection_id, *this );
}
//-----------------------------------------------------------------------------------------------//
sql::connection_impl::~connection_impl( )
{
   auto p = m_internal_stacker.find(this->m_connection_id);
   //
   if( p != m_internal_stacker.end( ) )
   {
      m_internal_stacker.erase( p->first );
   }
   //queue is empty
   if( m_internal_stacker.size( ) == 0 )
   {
      uninitialize_complus( );
   }
}
//-----------------------------------------------------------------------------------------------//
bool sql::connection_impl::is_connected( ) const
{
   return m_data->m_connected;
}
//-----------------------------------------------------------------------------------------------//
bool const sql::connection_impl::initialize_complus( )
{
   if( !sql::connection_impl::m_complus_ok )
   {
      sql::connection_impl::m_complus_ok = ::CoInitialize( NULL ) == S_OK;
      return sql::connection_impl::m_complus_ok;
   }
   return sql::connection_impl::m_complus_ok;
}
//-----------------------------------------------------------------------------------------------//
bool const sql::connection_impl::uninitialize_complus( )
{
   if( sql::connection_impl::m_complus_ok )
   {
      ::CoUninitialize( );
      sql::connection_impl::m_complus_ok = false;
   }
   return sql::connection_impl::m_complus_ok;
}
//-----------------------------------------------------------------------------------------------//