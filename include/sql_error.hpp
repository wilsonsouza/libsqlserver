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

namespace sql
{
   class _SQLDYNAMICLINK sql_error;
   using sql_error_pointer = std::shared_ptr<sql_error>;
   class _SQLDYNAMICLINK sql_error : public sql_interface
   {
   public:
      sql_error( ) = default;
      virtual ~sql_error( ) = default;
      explicit sql_error( _bstr_t const bsd, HRESULT h ) noexcept;
      explicit sql_error( sql_error_pointer const & in ) noexcept;
   protected:
      std::wstring  m_description = std::wstring( );
      HRESULT m_number = -1;
      unsigned int m_id = 0;
   };
};