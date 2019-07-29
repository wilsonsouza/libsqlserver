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
*  Dependence: odbc32.lib
*/
#include <sql_server_connection.hpp>
#include <variant>
#include <exception>
namespace sql::server
{
	//-----------------------------------------------------------------------------------------------//
	server_connection::server_connection()
	{
		this->m_db_data_access = database_access_data::pointer{ new database_access_data{} };
	}
	//-----------------------------------------------------------------------------------------------//
	server_connection::~server_connection()
	{
		this->close();
	}
	//-----------------------------------------------------------------------------------------------//
	bool server_connection::open(connection_impl::database_access_data::pointer const & user_data_info)
	{
		try
		{
			this->m_db_data_access.swap(const_cast<database_access_data::pointer &>(user_data_info));
		}
		catch (std::exception const & e)
		{
			this->m_db_data_access->m_connected = false;
		}
		return this->m_db_data_access->m_connected;
	}
}
//-----------------------------------------------------------------------------------------------//