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
#include <sql_server_date.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
   class _SQLDYNAMICLINK date;
   class _SQLDYNAMICLINK field_impl : virtual public ADOField
   {
   public:
      using pointer = std::shared_ptr<field_impl>;
      using pointer_const = pointer const;
		//
   public:
      field_impl( );
      explicit field_impl( ADOField const & field_value );
      virtual ~field_impl( );

      //methods get
      virtual std::string_view  const  to_string( ) = 0;
      virtual long         const  to_long( ) = 0;
		//
		template<class result_value = std::uint16_t,
			std::enable_if<std::is_integral<result_value>::type>::type = 0> result_value to_int()
		{
			return reinterpret_cast<result_value>(this->_to_integral());
		}
		//
      virtual bool         const  to_bool( ) = 0;
      virtual date         const  to_date( ) = 0;
      virtual double       const  to_double( ) = 0;
      virtual _variant_t   const  get_value( ) const = 0;
      virtual std::uint64_t const  get_type( ) = 0;
      virtual long         const  get_size( ) = 0;
      virtual std::string_view const  get_name( ) = 0;
      virtual std::string_view const  to_blob( ) = 0;
      virtual std::string_view const  to_char( ) = 0;

      //methods set
      virtual void const set_value( _variant_t const value ) = 0;
		//
	private:
		_variant_t _to_integral();
		//
   };
};