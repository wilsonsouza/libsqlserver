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
#include <sql_server_defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK date: public variant_t
   {
   public:
      date( ) = default;
      virtual ~date( ) = default;
      explicit date(_variant_t value): variant_t(value) noexcept
      {
      }
      virtual DATE const get_value()
      {
         return *this;
      }
   };
};