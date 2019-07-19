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
#pragma once
#include <sql_interface.hpp>
#include <sql_date.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK date;
   class _SQLDYNAMICLINK field : virtual public FieldPtr
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
      virtual std::unicode_string::pointer  const __fastcall to_string( );
      virtual long         const __fastcall to_long( );
      virtual unsigned int const __fastcall to_unsigned_int( );
      virtual int          const __fastcall to_int( );
      virtual bool         const __fastcall to_bool( );
      virtual date         const __fastcall to_date( );
      virtual double       const __fastcall to_double( );
      virtual _variant_t   const __fastcall value( ) const;
      virtual sql_type     const __fastcall type( );
      virtual long         const __fastcall size( );
      virtual std::unicode_string::pointer  const __fastcall name( );
      virtual std::unicode_string::pointer const __fastcall to_blob( );
      virtual std::unicode_string::pointer const __fastcall to_char( );

      //methods set
      virtual void         const __fastcall set_value( _variant_t const vtvalue );
   };
};