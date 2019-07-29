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
#pragma once
#include <sql_server_connection.hpp>
#if defined(_SQL_EVENTS)
#include <sql_tableevent.hpp>
#endif
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
	class _SQLDYNAMICLINK database;
	class _SQLDYNAMICLINK field;
	class _SQLDYNAMICLINK table_impl : public server_connection,
		public std::map<std::string_view, std::shared_ptr<field>>,
		public ADORecordset
	{
	protected:
		bool m_is_canceling{ false };
		//
	public:
		using pointer = std::shared_ptr<table_impl>;
		using record_map = std::map<key_type, mapped_type>;
		//
	public:
		table_impl();
		explicit table_impl(database const & db);
		explicit table_impl(Recordset20 const & record_set);
		virtual ~table_impl();
		virtual bool const open(std::string_view const & table_name,
										CommandTypeEnum cmd_type = adCmdText,
										CursorTypeEnum cursor_type = adOpenDynamic,
										LockTypeEnum lock_type = adLockOptimistic);
		//process
		virtual bool const is_eof() = 0;
		virtual bool const is_bof() = 0;
		virtual bool const go(long const lrecno = 0) = 0;
		virtual long const record_count() = 0;
		virtual long const get_record_number() = 0;
		virtual long const get_last_record() = 0;
		virtual bool const is_top() = 0;
		virtual bool const is_bottom() = 0;

		//move
		virtual bool const next_record() = 0;
		virtual bool const previous_record() = 0;
		virtual bool const skip(long lrecno = 0);

		//query manager
		bool close() override;
		//name
		virtual std::shared_ptr<field> operator[](std::string_view const & field_name);
		virtual std::shared_ptr<field> operator[](std::uint32_t const & index);
		//inline
		virtual std::shared_ptr<field> get_field_by_name(std::string_view const & field_name);
		virtual std::shared_ptr<field> get_field_by_index(std::uint32_t const & field_index);
		//fields
		virtual record_map &  get_fields_map(std::initializer_list<std::string_view> const ignored_fields = {}) = 0;
		//logical result
		virtual bool const is_actived();
		//
	protected:
		virtual std::shared_ptr<std::string_view> format_com_error(_com_error e);
		//
	protected:
		long m_last_record_number{ -1L };
	};
};
//-----------------------------------------------------------------------------------------------//
