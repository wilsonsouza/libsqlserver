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
#include <sql_field.hpp>
#include <sql_connectinfo.hpp>
#if defined(_SQL_EVENTS)
#include <sql_tableevent.hpp>
#endif
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK database;
   class _SQLDYNAMICLINK table : virtual public connectinfo,
      virtual public std::multimap<std::unicode_string, field::pointer>,
      virtual public _RecordsetPtr,
      public concurrency::task_group
   {
   protected:
      bool m_is_canceling = false;
   public:
      using pointer = std::shared_ptr<sql::table>;
      using pointer_const = pointer const;
      using multimap_type = std::multimap<key_type, mapped_type>;
   public:
      table( );
      explicit table( sql::database const & db );
      explicit table( _RecordsetPtr const & db );
      virtual ~table( );
      virtual bool const   __fastcall open( std::wstring const & tablename,
                                            CommandTypeEnum ctCommandType = adCmdText,
                                            CursorTypeEnum ctCursorType = adOpenDynamic,
                                            LockTypeEnum ltLockType = adLockOptimistic );
      //process
      virtual bool const   __fastcall eof( );
      virtual bool const   __fastcall bof( );
      virtual bool const   __fastcall go( long const lrecno = 0 );
      virtual long const   __fastcall reccount( );
      virtual long const   __fastcall recno( );
      virtual long const   __fastcall lastrec( );
      virtual bool const   __fastcall top( );
      virtual bool const   __fastcall bottom( );

      //move
      virtual bool const   __fastcall next( );
      virtual bool const   __fastcall previous( );
      virtual bool const   __fastcall skip( long lrecno = 0 );

      //query manager
      virtual void const   __fastcall close( );

   #if defined(_SQL_EVENTS)
      //Start events
      virtual void const   __fastcall SetRecordsetPtrEventsClass( );
      virtual void const   __fastcall FinalizeRecordsetPtrEventsClass( );
   #endif
      //name
      virtual field::pointer __fastcall operator[]( std::wstring const & strname );
      virtual field::pointer __fastcall operator[]( std::unicode_string::pointer const & pname );
      virtual field::pointer __fastcall operator[]( unsigned int uindex );
      //inlie
      virtual field::pointer __stdcall get_field( std::wstring const & szname );
      virtual field::pointer __stdcall get_field( std::unicode_string::pointer const & pname );
      virtual field::pointer __stdcall get_field( unsigned int ufieldindex );
      //fields
      virtual table::multimap_type & __fastcall get_fieldlist( std::initializer_list<std::wstring> const ignored_fields = {} );
      //logical result
      virtual bool const   __fastcall is_actived( );

   protected:
      virtual std::ansi_string::pointer __stdcall format_com_error( _com_error e );

   protected:
      long m_lrecno = -1L;
      DWORD m_dwRecordEvent;
      IConnectionPointContainer *m_pConnPointC;
      IConnectionPoint *m_pConnPoint;
      IUnknown *m_unknown;
   #if defined(_SQL_EVENTS)
      std::shared_ptr<sql::tableevent> m_pTableEvent;
   #endif
      _RecordsetPtr m_db;
   };
};
//-----------------------------------------------------------------------------------------------//
