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
#include <sql_server_defs.hpp>
namespace sql
{
   using T = std::string_view;
   //dbase
   static std::string_view SQL_DBASE = T("Driver={Microsoft dBASE Driver (*.dbf)};DriverID=277;"
                   "Dbq=c:\\DatabasePath;");
   //excel
   static std::string_view SQL_EXCEL = T("Driver={Microsoft Excel Driver (*.xls)};DriverId=790;"
    "Dbq=%1;DefaultDir=%2;");

   //text
   static std::string_view SQL_TEXT = T("Driver={Microsoft Text Driver (*.txt; *.csv)};"
        "Dbq=%1;Extensions=asc,csv,tab,txt;");
   //create schema.ini where information
   //Format=TabDelimited

   //visual foxpro
   static std::string_view SQL_VISUAL_FOXPRO = T("Driver={Microsoft Visual Foxpro Driver};UID=;"
    "SourceType=%1;SourceDB=%2;Exclusive=%3");

   //If you are working without a Database container, you must change the SourceType 
   //parameter by DBF as in the following connection std::string_view:

   static std::string_view SQL_VISUAL_FOXPRO_1 = T("Driver={Microsoft Visual Foxpro Driver};UID=;"
    "SourceType=DBF;SourceDB=%1;Exclusive=%2");

   //ODBC Driver for Access
   //Collapse | Copy Code
   static std::string_view SQL_ACCESS = T("Driver={Microsoft Access Driver (*.mdb)};"
           "Dbq=%1;Uid=;Pwd=;");

   //If you are using a Workgroup (System Database): you need to inform the SystemDB Path, the User Name and its password. For that, you have two solutions: inform the user and password in the connection std::string_view or in the moment of the Open operation. For example:

    //Collapse | Copy Code
   static std::string_view SQL_ACCESS_V1 = T("Driver={Microsoft Access Driver (*.mdb)};"
           "Dbq=%1;SystemDB=%2;Uid=%3;Pwd=%4");

//   static std::std::string_view strConnection = _T("Driver={Microsoft Access Driver (*.mdb)};"
//           "Dbq=C:\\VC Projects\\ADO\\Samples\\AdoTest\\dbTestSecurity.mdb;"
//           "SystemDB=C:\\Program Files\\Microsoft Office\\Office\\SYSTEM.mdw;");
//
//   //If you want to Open in Exclusive mode:
//
//   // Collapse | Copy Code
//   static std::std::string_view strConnection = _T("Driver={Microsoft Access Driver (*.mdb)};"
//           "Dbq=c:\\DatabasePath\dbaccess.mdb;Exclusive=1;");
//
////ODBC Driver for SQL Server
////
////For Standard security:
////
//// Collapse | Copy Code
//   static std::std::string_view strConnection = _T("Driver={SQL Server};Server=MyServerName;"
//           "Trusted_Connection=no;"
//           "Database=MyDatabaseName;Uid=MyUserName;Pwd=MyPassword;");
////For Trusted Connection security (Microsoft Windows NT integrated security):
////
//// Collapse | Copy Code
//   static std::std::string_view strConnection = _T("Driver={SQL Server};Server=MyServerName;"
//        "Database=myDatabaseName;Uid=;Pwd=;");
////Also, you can use the parameter Trusted_Connection that indicates that you are using the Microsoft Windows NT Authentication Mode to authorize user access to the SQL Server Database. For example:
////
//// Collapse | Copy Code
//static std::std::string_view strConnection = _T("Driver={SQL Server};Server=MyServerName;"
//    "Database=MyDatabaseName;Trusted_Connection=yes;");
////If the SQL Server is running in the same computer, you can replace the Name of the server by the word (local) like in the following sample:
////
//// Collapse | Copy Code
//static std::std::string_view strConnection = _T("Driver={SQL Server};Server=(local);"
//        "Database=MyDatabaseName;Uid=MyUserName;Pwd=MyPassword;");
////If you want to connect with a remote SQL Server, you must inform the address, the port, and the Network Library to use:
////
////The Address parameter must be an IP address and must include the port. The Network parameter can be one of the following:
////
////dbnmpntw Win32 Named Pipes
////dbmssocn Win32 Winsock TCP/IP
////dbmsspxn Win32 SPX/IPX
////dbmsvinn Win32 Banyan Vines
////dbmsrpcn Win32 Multi-Protocol (Windows RPC)
////For more information, see Q238949.
////
//// Collapse | Copy Code
//strConnection = _T("Driver={SQL Server};Server=130.120.110.001;"
//     "Address=130.120.110.001,1052;Network=dbmssocn;Database=MyDatabaseName;"
//     "Uid=myUserName;Pwd=myPassword;");
////ODBC Driver for Oracle
////
////For the current Oracle ODBC driver from Microsoft:
////
//// Collapse | Copy Code
//strConnect = _T("Driver={Microsoft ODBC for Oracle};Server=OracleServer.world;"
//        "Uid=MyUserName;Pwd=MyPassword;");
////For the older Oracle ODBC driver from Microsoft:
////
//// Collapse | Copy Code
//strConnect = _T("Driver={Microsoft ODBC Driver for Oracle};"
//     "ConnectString=OracleServer.world;Uid=myUserName;Pwd=myPassword;");
////ODBC Driver for MySQL
//
////If you want to connect to a local Database, you can use a connection std::string_view like the following:
////
//// Collapse | Copy Code
//strConnect = _T("Driver={MySQL ODBC 3.51 Driver};Server=localhost;"
//     "Database=MyDatabase;User=MyUserName;Password=MyPassword;Option=4;");
////If you want to connect with a remote Database, you need to specify the Name of the server or its IP in the Server parameter. If the Port is distinct to 3306 (default port), you must specify it.
////
//// Collapse | Copy Code
//strConnect = _T("Driver={mySQL ODBC 3.51 Driver};Server=MyRemoteHost;"
//     "Port=3306;Option=4;Database=MyDatabase;Uid=MyUserName;Pwd=MyPassword;");
//The parameter Option can be one or more of the following values:
//
//1 - The client can't handle that MyODBC returns the real width of a column.
//2 - The client can't handle that MySQL returns the true value of affected rows. If this flag is set then MySQL returns 'found rows' instead. One must have MySQL 3.21.14 or newer to get this to work.
//4 - Make a debug log in c:\myodbc.log. This is the same as putting MYSQL_DEBUG=d:t:O,c::\myodbc.log in AUTOEXEC.BAT.
//8 - Don't set any packet limit for results and parameters.
//16 - Don't prompt for questions even if driver would like to prompt.
//32 - Enable or disable the dynamic cursor support. This is not allowed in MyODBC 2.50.
//64 - Ignore use of Database Name in 'Database.Table.column'.
//128 - Force use of ODBC manager cursors (experimental).
//256 - Disable the use of extended fetch (experimental).
//512 - Pad CHAR Fields to full column length.
//1024 - SQLDescribeCol() will return fully qualified column Names.
//2048 - Use the compressed server/client protocol.
//4096 - Tell server to ignore space after function Name and before '(' (needed by PowerBuilder). This will make all function Names keywords!
//8192 - Connect with Named pipes to a MySQLd server running on NT.
//16384 - Change LONGLONG columns to INT columns (some applications can't handle LONGLONG).
//32768 - Return 'user' as Table_qualifier and Table_owner from SQLTables (experimental).
//65536 - Read parameters from the client and ODBC groups from my.cnf.
//131072 - Add some extra safety checks (should not be needed but...).
//If you want to have multiple options, you should add the above flags! For example: 16 + 1024 = 1030 and use Option= 1030;.
//
//For more information, Go to MyODBC Reference Manual.
//
//ODBC Driver for AS400
//
// Collapse | Copy Code
//strConnect = _T("Driver={Client Access ODBC Driver (32-bit)};System=myAS400;"
//      "Uid=myUserName;Pwd=myPassword;");
//ODBC Driver for SyBase
//
// Collapse | Copy Code
//strConnect = _T("Driver={Sybase System 10};Srvr=MyServerName;Uid=MyUserName;"
//       "Pwd=myPassword;");
//ODBC Driver for Sybase SQL AnyWhere
//
// Collapse | Copy Code
//strConnect = _T("ODBC;Driver=Sybase SQL Anywhere 5.0;"
//    "DefaultDir=C:\\DatabasePath\;Dbf=C:\\SqlAnyWhere50\\MyDatabase.db;"
//    "Uid=MyUserName;Pwd=MyPassword;Dsn=\"\";");
//DSN Connection
//ODBC DSN
//
// Collapse | Copy Code
//strConnect = _T("DSN=MyDSN;Uid=MyUserName;Pwd=MyPassword;");
//OLE DB Provider
//OLE DB Provider for SQL Server
//
//For Standard security:
//
// Collapse | Copy Code
//strConnect = _T("Provider=sqloledb;Data Source=MyServerName;"
//        "Initial Catalog=MyDatabaseName;"
//        "User Id=MyUserName;Password=MyPassword;");
//For Trusted Connection security (Microsoft Windows NT integrated security):
//
// Collapse | Copy Code
//strConnect = _T("Provider=sqloledb;Data Source=MyServerName;"
//        "Initial Catalog=MyDatabaseName;"
//        "Integrated Security=SSPI;");
//If you want to connect to a "Named Instance" (SQL Server 2000), you must to specify Data Source=Servere Name\Instance Name like in the following example:
//
// Collapse | Copy Code
//strConnect = _T("Provider=sqloledb;Data Source=MyServerName\MyInstanceName;"
//    "Initial Catalog=MyDatabaseName;User Id=MyUserName;Password=MyPassword;");
//If you want to connect with a SQL Server running on the same computer, you must specify the keyword (local) in the Data Source like in the following example:
//
// Collapse | Copy Code
//strConnect = _T("Provider=sqloledb;Data Source=(local);"
//        "Initial Catalog=myDatabaseName;"
//        "User ID=myUserName;Password=myPassword;");
//To connect to SQL Server running on a remote computer (via an IP address):
//
// Collapse | Copy Code
//strConnect = _T("Provider=sqloledb;Network Library=DBMSSOCN;"
//        "Data Source=130.120.110.001,1433;"
//        "Initial Catalog=MyDatabaseName;User ID=MyUserName;"
//        "Password=MyPassword;");
//OLE DB Provider for MySQL (By Todd Smith)
//
// Collapse | Copy Code
//strConnection = _T("Provider=MySQLProv;Data Source=test");
//Where test is the Name of MySQL Database. Also, you can replace the Name of the Database by the following connection std::string_view: server=localhost;DB=test.
//
//OLE DB Provider for AS400
//
// Collapse | Copy Code
//strConnect = _T("Provider=IBMDA400;Data source=myAS400;User Id=myUserName;"
//     "Password=myPassword;");
//For more information, see: Using the OLE DB Provider for AS/400 and VSAM.
//
//OLE DB Provider for Active Directory
//
// Collapse | Copy Code
//strConnect = _T("Provider=ADSDSOObject;User Id=myUserName;Password=myPassword;");
//For more information, see: Microsoft OLE DB Provider for Microsoft Active Directory Service.
//
//OLE DB Provider for DB2
//
//If you are using a TCP/IP connection:
//
// Collapse | Copy Code
//strConnect = _T("Provider=DB2OLEDB;Network Transport Library=TCPIP;"
//        "Network Address=130.120.110.001;"
//        "Initial Catalog=MyCatalog;Package Collection=MyPackageCollection;"
//        "Default Schema=MySchema;User ID=MyUserName;Password=MyPassword;");
//If you are using APPC connection:
//
// Collapse | Copy Code
//strConnect = _T("Provider=DB2OLEDB;APPC Local LU Alias=MyLocalLUAlias;"
//        "APPC Remote LU Alias=MyRemoteLUAlias;Initial Catalog=MyCatalog;"
//        "Package Collection=MyPackageCollection;Default Schema=MySchema;"
//        "User ID=MyUserName;Password=MyPassword;");
//For more information, see: Using the OLE DB Provider for DB2.
//
//OLE DB Provider for Microsoft Jet
//
//Connecting to an Access file using the JET OLE DB Provider:
//Using Standard security:
//
// Collapse | Copy Code
//strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0;"
//        "Data Source=C:\\DatabasePath\\MmDatabase.mdb;"
//        "User Id=admin;Password=;");
//If you are using a Workgroup (System Database):
//
// Collapse | Copy Code
//strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0;"
//        "Data Source=C:\\DataBasePath\\mydb.mdb;"
//        "Jet OLEDB:System Database=MySystem.mdw;");
//pRs.Open(strConnect, "MyUserName", "MyPassword");
//Connecting to an Excel Spreadsheet using the JET OLE DB Provider:
// Collapse | Copy Code
//strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0;"
//        "Data Source=C:\\DatabasePath\\DBSpreadSheet.xls;"
//        "Extended Properties=\"\"Excel 8.0;HDR=Yes;\"\";");
//Note: If "HDR=Yes", the provider will not include the first row of the selection into the recordset. If "HDR=No", the provider will include the first row of the cell range (or Named ranged) into the recordset.
//
//For more information, see: Q278973.
//
//Connecting to a Text file using the JET OLE DB Provider:
// Collapse | Copy Code
//strConnect = 
//        _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\DatabasePath\\;"
//        "Extended Properties=\"\"text;"
//        "HDR=Yes;FMT=Delimited;\"\";");
//Note: You must specify the fileName in the SQL statement... For example:
//
// Collapse | Copy Code
//CString strQuery = _T("Select Name, Address From Clients.txt");
//For more information, see: Q262537.
//
//Connecting to an Outlook 2000 personal mail box using the JET OLE DB Provider: (By J. Cardinal)
// Collapse | Copy Code
//strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0;Outlook 9.0;"
//      "MAPILEVEL=;DATABASE=C:\\Temp\\;")
//Replace c:\temp with any temporary folder. It will create a schema file in that folder when you Open it which shows all the Fields available. Blank MAPILEVEL indicates top level of folders).
//
//Connecting to an Exchange mail box through JET: (By J. Cardinal)
// Collapse | Copy Code
//strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0;Exchange 4.0;"
//      "MAPILEVEL=Mailbox - Pat Smith|;DATABASE=C:\\Temp\\;")
//You must replace c:\temp with any temporary folder.
//
//Replace Pat Smith with the Name of the mail box and you must keep vertical pipe character | to indicate top level of folders. Place sub folder after vertical pipe if accessing specific folder.
//
//Note: you can enter queries against the mail store just like a Database... For example:
//
// Collapse | Copy Code
//CString strQuery = _T("SQL "SELECT Contacts.* FROM Contacts;");
//For more information, see: The Jet 4.0 Exchange/Outlook IISAM.
//
//OLE DB Provider for ODBC Databases
//
//If you want to connect with a Microsoft Access Database:
//
// Collapse | Copy Code
//strConnect = _T("Provider=MSDASQL;Driver={Microsoft Access Driver (*.mdb)};"
//        "Dbq=c:\\DatabasePath\\MyDatabase.mdb;Uid=MyUserName;Pwd=MyPassword;");
//If you want to connect with a SQL Server Database:
//
// Collapse | Copy Code
//strConnect = _T("Provider=MSDASQL;Driver={SQL Server};Server=MyServerName;"
//        "Database=MyDatabaseName;Uid=MyUserName;Pwd=MyPassword;");
//If you want to use DSN:
//
// Collapse | Copy Code
//strConnect = _T("Provider=MSDASQL;PersistSecurityInfo=False;"
//        "Trusted_Connection=Yes;"
//        "Data Source=MyDSN;catalog=MyDatabase;");
//For more information, see: Microsoft OLE DB Provider for ODBC.
//
//OLE DB Provider for OLAP
//
//Microsoft® OLE DB for Online Analytical Processing (OLAP) is a set of objects and interfaces that extends the ability of OLE DB to provide access to multidimensional data stores.
//
// Collapse | Copy Code
//strConnect = _T("Provider=MSOLAP;Data Source=MyOLAPServerName;"
//     "Initial Catalog=MyOLAPDatabaseName;");
//Connection using HTTP:
//This feature enables a client application to connect to an Analysis server through Microsoft® Internet Information Services (IIS) by specifying a URL in the Data Source property in the client application's connection std::string_view. This connection method allows PivotTable® Service to tunnel through firewalls or proxy servers to the Analysis server. A special Active Server Pages (ASP) page, Msolap.asp, enables the connection through IIS. The directory in which this file resides must be included as part of the URL when connecting to the server (for example, http://www.myserver.com/myolap/).
//
//Using a URL
// Collapse | Copy Code
//strConnect = _T("Provider=MSOLAP;Data Source=http://MyOLAPServerName/;"
//     "Initial Catalog=MyOLAPDatabaseName;");
//Using SSL
// Collapse | Copy Code
//strConnect = _T("Provider=MSOLAP;Data Source=https://MyOLAPServerName/;"
//     "Initial Catalog=MyOLAPDatabaseName;");
//For more information, see: OLE DB for OLAP, Connecting Using HTTP.
//
//OLE DB Provider for Oracle
//
//OLE DB Provider for Oracle (from Microsoft)
//The Microsoft OLE DB Provider for Oracle allows ADO to access Oracle Databases.
//
// Collapse | Copy Code
//strConnect = _T("Provider=MSDAORA;Data Source=MyOracleDB;User Id=myUserName;"
//     "Password=myPassword;");
//For more information, see: Microsoft OLE DB Provider for Oracle.
//
//OLE DB Provider for Oracle (from Oracle).
//For Standard security:
//
// Collapse | Copy Code
//strConnect = _T("Provider=OraOLEDB.Oracle;Data Source=MyOracleDB;"
//        "User Id=myUserName;Password=myPassword;");
//For a Trusted connection:
//
//OS Authenticated connect setting user ID to "/":
// Collapse | Copy Code
//strConnect = _T("Provider=OraOLEDB.Oracle;Data Source=MyOracleDB;"
//   "User Id=/;Password=;");
//OS Authenticated connect using OSAuthent:
// Collapse | Copy Code
//strConnect = _T("Provider=OraOLEDB.Oracle;Data Source=MyOracleDB;OSAuthent=1;")
//Note: "Data Source=" must be set to the appropriate Net8 Name which is known to the naming method in use. For example, for Local Naming, it is the alias in the tnsNames.ora file; for Oracle Names, it is the Net8 Service Name.
//
//For more information, see: Oracle Provider for OLE DB Developer's Guide.
//
//OLE DB Provider for Visual FoxPro
//
// Collapse | Copy Code
//strConnect = _T("Provider=vfpoledb;"
//     "Data Source=C:\\DatabasePath\\MyDatabase.dbc;");
//For more information, see: Microsoft OLE DB Provider for Visual FoxPro.
//
//OLE DB Provider for Index Server (By Chris Maunder)
//
// Collapse | Copy Code
//strConnect = _T("provider=msidxs;Data Source=MyCatalog;");
//For more information, see: Microsoft OLE DB Provider for Microsoft Indexing Service.
//
//OLE DB Data Link Connections
//Data Link File - UDL
//
// Collapse | Copy Code
//strConnection = _T("File Name=c:\\DataBasePath\\DatabaseName.udl;");
//If you want to create a Data Link File, you can make a new empty text file, change its extension by .udl, then double click over the file, and the operating system calls for you the Data Link app.



};