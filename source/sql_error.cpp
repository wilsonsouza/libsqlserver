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
#include <sql_interface.hpp>
#include <sql_error.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
sql_error::sql_error( _bstr_t const bsd, HRESULT hrn ) noexcept  : sql_interface( ),
m_description( ( bsd ) ),
m_number( hrn )
{
}
//-----------------------------------------------------------------------------------------------//
sql_error::sql_error( sql_error_pointer const & p ) noexcept : sql_interface( )
{
   m_description.assign( p->m_description.begin( ), p->m_description.end( ) );
   m_number = p->m_number;
}
//-----------------------------------------------------------------------------------------------//