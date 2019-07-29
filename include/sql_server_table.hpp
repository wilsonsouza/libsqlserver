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
#include <sql_server_field.hpp>
#include <sql_server_connection.hpp>
#if defined(_SQL_EVENTS)
#include <sql_tableevent.hpp>
#endif
//-----------------------------------------------------------------------------------------------//
namespace sql::server
{
   class _SQLDYNAMICLINK database;
   class _SQLDYNAMICLINK table : virtual public connection,
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
      virtual bool const    open( std::wstring const & tablename,
                                            CommandTypeEnum ctCommandType = adCmdText,
                                            CursorTypeEnum ctCursorType = adOpenDynamic,
                                            LockTypeEnum ltLockType = adLockOptimistic );
      //process
      virtual bool const    eof( );
      virtual bool const    bof( );
      virtual bool const    go( long const lrecno = 0 );
      virtual long const    reccount( );
      virtual long const    recno( );
      virtual long const    lastrec( );
      virtual bool const    top( );
      virtual bool const    bottom( );

      //move
      virtual bool const    next( );
      virtual bool const    previous( );
      virtual bool const    skip( long lrecno = 0 );

      //query manager
      virtual void const    close( );

   #if defined(_SQL_EVENTS)
      //Start events
      virtual void const    SetRecordsetPtrEventsClass( );
      virtual void const    FinalizeRecordsetPtrEventsClass( );
   #endif
      //name
      virtual field::pointer  operator[]( std::wstring const & strname );
      virtual field::pointer  operator[]( std::unicode_string::pointer const & pname );
      virtual field::pointer  operator[]( unsigned int uindex );
      //inlie
      virtual field::pointer __stdcall get_field( std::wstring const & szname );
      virtual field::pointer __stdcall get_field( std::unicode_string::pointer const & pname );
      virtual field::pointer __stdcall get_field( unsigned int ufieldindex );
      //fields
      virtual table::multimap_type &  get_fieldlist( std::initializer_list<std::wstring> const ignored_fields = {} );
      //logical result
      virtual bool const    is_actived( );

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
