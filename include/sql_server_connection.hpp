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
#pragma once
#include <sql_server_connection_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class server_connection : public sql::connection_impl
   {
   public:
      using pointer = std::shared_ptr<server_connection>;
   private:
      static bool m_is_coinitialized;
   public:
      server_connection() noexcept;
      ~server_connection();
      bool open(sql::connection_impl::data::pointer const & user_data_info) override;
      bool open(std::aul::string<wchar_t> const & connection_file_name);
      bool close() override;
      bool isconnected() const;

      static bool const initialize_complus();
      static bool const uninitialize_complus();
   private:
      server_connection(server_connection const &) = delete;
      void operator = (server_connection const &) = delete;
      void operator = (server_connection &) = delete;
   };
}