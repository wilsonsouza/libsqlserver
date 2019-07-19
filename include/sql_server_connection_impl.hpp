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
#pragma  once
#include <sql_server_defs.hpp>
#include <map>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class connection_impl: public _ConnectionPtr
   {
   public:
      struct data
      {
         using pointer = std::shared_ptr<sql::connection_impl::data>;
         //
         std::aul::string<wchar_t> m_dns{};
         std::aul::string<wchar_t> m_user{};
         std::aul::string<wchar_t> m_password{};
         std::aul::string<wchar_t> m_database_name{};
         bool m_connected{ false };
         //
         data() = default;
         data(sql::connection_impl::data const & in) = delete;
      };
      //
      using interanL_stacker = std::multimap<std::size_t, sql::connection_impl const &>;
      using connection = _Connection;
   protected:
      connection_impl::data::pointer m_data;
      std::size_t m_connection_id = 0;
   public:
      static bool m_complus_ok;
      static std::size_t m_id;
      static sql::connection_impl::interanL_stacker m_internal_stacker;
   public:
      explicit connection_impl( ) noexcept;
      ~connection_impl( ) noexcept;
      virtual bool open(sql::connection_impl::data::pointer const & data) = 0;
      virtual bool close( ) = 0;
      bool is_connected( ) const;
      //
   private:
      bool const initialize_complus( );
      bool const uninitialize_complus( );
   };
}
//-----------------------------------------------------------------------------------------------//