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
#include <sql_server_field_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
   class _SQLDYNAMICLINK date;
   class _SQLDYNAMICLINK field : public field_impl
   {
   public:
      using pointer = std::shared_ptr<field>;
      using pointer_const = pointer const;
   public:
      field( );
      explicit field( FieldPtr const & ptr );
      virtual ~field( );

      //methods get
      /*get_string(), get_long(), get_unsigned_int()
      get_bool(), get_date(), get_double(), get_value(), get_type(),
      get_size(), get_name(), get_binary_object(),
      get_char(),
      set_value
      */
      virtual std::unicode_string::pointer  const  to_string( );
      virtual long         const  to_long( );
      virtual unsigned int const  to_unsigned_int( );
      virtual int          const  to_int( );
      virtual bool         const  to_bool( );
      virtual date         const  to_date( );
      virtual double       const  to_double( );
      virtual _variant_t   const  value( ) const;
      virtual sql_type     const  type( );
      virtual long         const  size( );
      virtual std::unicode_string::pointer  const  name( );
      virtual std::unicode_string::pointer const  to_blob( );
      virtual std::unicode_string::pointer const  to_char( );

      //methods set
      virtual void         const  set_value( _variant_t const vtvalue );
   };
};