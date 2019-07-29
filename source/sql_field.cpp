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
#include <sql_field.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
field::field( )
{
   CreateInstance( __uuidof( Field20 ) );
}
//-----------------------------------------------------------------------------------------------//
field::field( FieldPtr const & ptr )
{
   FieldPtr::operator=( ptr );
}
//-----------------------------------------------------------------------------------------------//
field::~field( )
{
   GetInterfacePtr( )->Release( );
}
//-----------------------------------------------------------------------------------------------//
std::unicode_string::pointer const  field::to_string( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_BSTR || v.vt == VT_LPSTR || v.vt == VT_LPWSTR )
   {
      return std::unicode_string::copy_alloc( v.operator bstr_t( ) );
   }
   /**/
   if ( v.vt != VT_NULL )
   {
      return std::unicode_string::copy_alloc( v.operator bstr_t( ) );
   }
   return std::unicode_string::alloc( );
}
//-----------------------------------------------------------------------------------------------//
long const  field::to_long( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_DECIMAL || v.vt == VT_INT || v.vt == VT_BOOL || v.vt == VT_UI4 )
   {
      return v.operator long( );
   }
   return 0L;
}
//-----------------------------------------------------------------------------------------------//
unsigned int const  field::to_unsigned_int( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_UINT || v.vt == VT_DECIMAL || v.vt == VT_UI1 || v.vt == VT_UI2 || v.vt == VT_UI4 )
   {
      return v.operator unsigned int( );
   }
   return 0;
}
//-----------------------------------------------------------------------------------------------//
int const  field::to_int( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_INT || v.vt == VT_I4 )
   {
      return v.operator int( );
   }
   return 0;
}
//-----------------------------------------------------------------------------------------------//
std::unicode_string::pointer const  field::to_char( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_BSTR )
   {
      return std::unicode_string::copy_alloc( v.operator _bstr_t( ) );
   }
   return std::unicode_string::alloc();
}
//-----------------------------------------------------------------------------------------------//
bool const  field::to_bool( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_BOOL )
   {
      return v.operator bool( );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
sql::date const  field::to_date( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_DATE )
   {
      return sql::date( v.operator bstr_t( ) );
   }
   return sql::date( );
}
//-----------------------------------------------------------------------------------------------//
std::unicode_string::pointer const  field::to_blob( )
{
   auto const v = value( );

   if ( v.vt == VT_BLOB || v.vt == VT_BLOB_OBJECT || v.vt == VT_BLOB_PROPSET )
   {
      return std::unicode_string::copy_alloc( v.operator _bstr_t( ) );
   }
   return std::unicode_string::alloc();
}
//-----------------------------------------------------------------------------------------------//
_variant_t const  field::value( ) const
{
   auto v = _variant_t( );
   /**/
   if ( GetInterfacePtr( )->get_Value( &v ) == S_OK )
   {
      if ( v.vt == VT_NULL )
      {
         return _variant_t( );
      }
      else
      {
         return v;
      }
   }
   return v;
}
//-----------------------------------------------------------------------------------------------//
void const  field::set_value( _variant_t const vtvalue )
{
   if ( vtvalue.vt != VT_NULL )
   {
      GetInterfacePtr( )->PutValue( _variant_t( vtvalue ) );
   }
}
//-----------------------------------------------------------------------------------------------//
sql::sql_type const  field::type( )
{
   auto ltype = sql_type::SQL_FIELD_UNKNOW_TYPE;
   auto nType = GetInterfacePtr( )->Type;
   /**/
   switch ( nType )
   {
      case adBigInt:
         ltype = sql_type::SQL_FIELD_INT64;
         break;
      case adBinary:
      case adBoolean:
         ltype = sql_type::SQL_FIELD_BOOL;
         break;
      case adChar:
      case adVarBinary:
      case adVarChar:
         ltype = sql_type::SQL_FIELD_STRING;
         break;
      case adDate:
      case adDBDate:
         ltype = sql_type::SQL_FIELD_DATE;
         break;
      case adDBTime:
      case adDBTimeStamp:
         ltype = sql_type( long( sql_type::SQL_FIELD_TIME ) | long( sql_type::SQL_FIELD_DATE ) );
         break;
      case adNumeric:
      case adDecimal:
         ltype = sql_type::SQL_FIELD_INT32;
         break;
      case adLongVarBinary:
      case adLongVarChar:
      case adLongVarWChar:
         ltype = sql_type::SQL_FIELD_WORDCHAR;
         break;
      case adCurrency:
         ltype = sql_type::SQL_FIELD_CURRENCY;
         break;
      case adWChar:
      case adVarWChar:
         ltype = sql_type::SQL_FIELD_WCHAR_T;
         break;
      case adSmallInt:
         ltype = sql_type::SQL_FIELD_INT16;
         break;
      case adUnsignedBigInt:
      case adUnsignedInt:
      case adUnsignedSmallInt:
      case adUnsignedTinyInt:
      case adInteger:
         ltype = sql_type::SQL_FIELD_DWORD;
         break;
   }
   return ltype;
}
//-----------------------------------------------------------------------------------------------//
long const  field::size( )
{
   long loffset = 0;
   /**/
   if ( GetInterfacePtr( )->get_DefinedSize( &loffset ) == S_OK )
   {
      return loffset;
   }
   return 0;
}
//-----------------------------------------------------------------------------------------------//
std::unicode_string::pointer const  field::name( )
{
   auto field = GetInterfacePtr( );
   auto fname = std::unicode_string::copy_alloc( field->Name );
   /**/
   if ( fname->length( ) > 0 )
   {
      return fname;
   }
   return std::unicode_string::alloc( );
}
//-----------------------------------------------------------------------------------------------//
double const  field::to_double( )
{
   auto const v = value( );
   /**/
   if ( v.vt == VT_I8 || v.vt == VT_UI8 || v.vt == VT_DECIMAL )
   {
      return v.operator double( );
   }
   return 0;
}
//-----------------------------------------------------------------------------------------------//