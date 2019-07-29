/*
*
*  libsqlserver c++17 Version 1.1
*
*
*  Created by Wilson.Souza
*  Copyright (C) 2012, 2018, WR DevInfo, All Rights Reserved.
*
*  Description: access ms sqlserver by ado
*  Last update: 7/2019
*
*  Dependence: msado15.dll, sqlncli.lib
*/
#include <sql_server_connection_impl.hpp>
namespace sql::server
{
	//-----------------------------------------------------------------------------------------------//
	//
	// initialize variables of control
	//
	bool connection_impl::m_complus_ok = false;
	std::size_t connection_impl::m_id = 0;
	connection_impl::internal_stacker_map m_internal_stacker{};
	//-----------------------------------------------------------------------------------------------//
	connection_impl::connection_impl() noexcept
	{
		this->initialize_complus();
		this->m_connection_id = ++connection_impl::m_id;
		m_internal_stacker.emplace(this->m_connection_id, *this);
	}
	//-----------------------------------------------------------------------------------------------//
	connection_impl::~connection_impl()
	{
		auto p = m_internal_stacker.find(this->m_connection_id);
		//
		if (p != m_internal_stacker.end())
		{
			m_internal_stacker.erase(p->first);
		}
		//queue is empty
		if (m_internal_stacker.size() == 0)
		{
			uninitialize_complus();
		}
	}
	//-----------------------------------------------------------------------------------------------//
	bool connection_impl::close()
	{
		m_db_data_access->m_connected = (m_db_data_access->m_connected ?
													!(this->Close() == S_OK) :
													m_db_data_access->m_connected);
		return m_db_data_access->m_connected;
	}
	//-----------------------------------------------------------------------------------------------//
	bool connection_impl::is_connected() const
	{
		return m_db_data_access->m_connected;
	}
	//-----------------------------------------------------------------------------------------------//
	bool const connection_impl::initialize_complus()
	{
		if (!connection_impl::m_complus_ok)
		{
			connection_impl::m_complus_ok = ::CoInitialize(NULL) == S_OK;
		}
		return connection_impl::m_complus_ok;
	}
	//-----------------------------------------------------------------------------------------------//
	bool const connection_impl::uninitialize_complus()
	{
		if (connection_impl::m_complus_ok)
		{
			::CoUninitialize();
			connection_impl::m_complus_ok = false;
		}
		return connection_impl::m_complus_ok;
	}
}//-----------------------------------------------------------------------------------------------//