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
#pragma once
//#import <msado15.dll> no_namespace rename("EOF", "EndOfFile")
#include <sqlncli.h>
#include <string_view>
#include <memory>
#include <Ole2.h>
#include <oledb.h>
#include <adoint.h>
#include <comutil.h>
#include <ppl.h>
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
      static std::string_view const Provider = std::string_view( "Provider" );
      static std::string_view const Password = std::string_view( "Password" );
      static std::string_view const Persist_Security_Info = std::string_view( "Persist Security Info" );
      static std::string_view const User_ID = std::string_view( "User ID" );
      static std::string_view const Initial_Catalog = std::string_view( "Initial Catalog" );
      static std::string_view const Data_Source = std::string_view( "Data Source" );
      static std::string_view const ConnectionTimeout = std::string_view( "ConnectionTimeout" );
      static std::string_view const CommentTimeout = std::string_view( "CommandTimeout" );
      static std::string_view const CursorLocation = std::string_view( "CursorLocation" );
      static std::string_view const IsolationLevel = std::string_view( "IsolationLevel" );
      //-----------------------------------------------------------------------------------------------//
      static std::string_view const True = std::string_view( "TRUE" );
      static std::string_view const False = std::string_view( "FALSE" );
   }
}
