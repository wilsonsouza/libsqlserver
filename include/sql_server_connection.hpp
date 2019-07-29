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
#pragma once
#include <sql_server_connection_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
   class server_connection : public connection_impl
   {
   public:
      using pointer = std::shared_ptr<server_connection>;
		//
   private:
      static bool m_is_coinitialized;
		//
   public:
      server_connection() noexcept;
      virtual ~server_connection();
      bool open(connection_impl::database_access_data::pointer const & user_data_info) override;
		//
   private:
      server_connection(server_connection const &) = delete;
      void operator = (server_connection const &) = delete;
      void operator = (server_connection &) = delete;
		//
   };
}