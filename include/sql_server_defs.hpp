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
#import <msado15.dll> no_namespace rename("EOF", "EndOfFile")
#include <sqlncli.h>
#include <string>
#include <memory>
#include <Ole2.h>
#include <oledb.h>
#include <comutil.h>
#include <std_aulstring.hpp>
//-----------------------------------------------------------------------------------------------//
#if defined(_WINDLL)
#define _SQLDYNAMICLINK __desclpec(dllexport)
#else
#define _SQLDYNAMICLINK 
#endif
namespace sql
{
   namespace config
   {
      static std::aul::string<wchar_t> const Provider = std::aul::string<wchar_t>( "Provider" );
      static std::aul::string<wchar_t> const Password = std::aul::string<wchar_t>( "Password" );
      static std::aul::string<wchar_t> const Persist_Security_Info = std::aul::string<wchar_t>( "Persist Security Info" );
      static std::aul::string<wchar_t> const User_ID = std::aul::string<wchar_t>( "User ID" );
      static std::aul::string<wchar_t> const Initial_Catalog = std::aul::string<wchar_t>( "Initial Catalog" );
      static std::aul::string<wchar_t> const Data_Source = std::aul::string<wchar_t>( "Data Source" );
      static std::aul::string<wchar_t> const ConnectionTimeout = std::aul::string<wchar_t>( "ConnectionTimeout" );
      static std::aul::string<wchar_t> const CommentTimeout = std::aul::string<wchar_t>( "CommandTimeout" );
      static std::aul::string<wchar_t> const CursorLocation = std::aul::string<wchar_t>( "CursorLocation" );
      static std::aul::string<wchar_t> const IsolationLevel = std::aul::string<wchar_t>( "IsolationLevel" );
      //-----------------------------------------------------------------------------------------------//
      static std::aul::string<wchar_t> const True = std::aul::string<wchar_t>( "TRUE" );
      static std::aul::string<wchar_t> const False = std::aul::string<wchar_t>( "FALSE" );
   }
}
