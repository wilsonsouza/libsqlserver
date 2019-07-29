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
#pragma  once
#include <sql_server_defs.hpp>
#include <map>
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
   class connection_impl: public Connection15, public concurrency::task_group
   {
   public:
      struct database_access_data
      {
         using pointer = std::shared_ptr<connection_impl::database_access_data>;
         //
         std::string_view m_dns{};
         std::string_view m_user{};
         std::string_view m_password{};
         std::string_view m_database_name{};
         bool m_connected{ false };
         //
			database_access_data() = default;
         database_access_data(connection_impl::database_access_data const & in) = delete;
      };
      //
      using internal_stacker_map = std::multimap<std::size_t, connection_impl const &>;
		//
   protected:
		connection_impl::database_access_data::pointer m_db_data_access{ nullptr };
		std::size_t m_connection_id{ 0 };
		//
   public:
		static bool m_complus_ok;
		static std::size_t m_id;
		static connection_impl::internal_stacker_map m_internal_stacker;
		//
   public:
      explicit connection_impl( ) noexcept;
      virtual ~connection_impl( ) noexcept;
      virtual bool open(connection_impl::database_access_data::pointer const & db_data) = 0;
      virtual bool close( );
      bool is_connected( ) const;
      //
   private:
      bool const initialize_complus( );
      bool const uninitialize_complus( );
   };
}
//-----------------------------------------------------------------------------------------------//