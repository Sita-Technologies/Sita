/**
 * This file is part of Sita Team Decompiler.
 *
 * Sita Team Decompiler is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 *
 * Sita Team Decompiler is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sita Team Decompiler. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef SAL_DATATYPES_HPP_
#define SAL_DATATYPES_HPP_

enum datatype {
	ANY,
	VARIABLE_DATE, // reference to variable name
	VARIABLE_HANDLE, // reference to variable name
	VARIABLE_NUMBER, // reference to variable name
	VARIABLE_STRING, // reference to variable name
	VARIABLE_POINTER, // reference to variable name
	VARIABLE_ADDRESS, // reference to variable name
	VARIABLE_BINARY,
	DLGITEM, // reference to DLGITEM
	// built-in types
	_BINARY,
	_BOOLEAN, // internal, this datatype is identical to NUMBER
	DATE_TIME,
	FILE_HANDLE,
	LONG_STRING,
	FUNCTIONAL_CLASS_OBJECT,
	NUMBER,
	SESSION_HANDLE,
	SQL_HANDLE,
	STRING,
	WINDOW_HANDLE,
	RECEIVE_BINARY,
	RECEIVE_BOOLEAN,
	RECEIVE_DATE_TIME,
	RECEIVE_FILE_HANDLE,
	RECEIVE_NUMBER,
	RECEIVE_SESSION_HANDLE,
	RECEIVE_SQL_HANDLE,
	RECEIVE_STRING,
	RECEIVE_WINDOW_HANDLE,
	STRUCTPOINTER,
	// external types
	HBINARY,
	_BOOL,
	_LPBOOL,
	DATETIME,
	LPDATETIME,
	__HFILE,
	_LPHFILE,
	_LONG,
	_LPLONG,
	HSESSIONHANDLE,
	LPHSESSIONHANDLE,
	HSQLHANDLE,
	LPHSQLHANDLE,
	_LPHANDLE,
	HSTRING,
	TEMPLATE,
	_HWND,
	_LPHWND,
	HUDV,
	_LPWSTR,
	_LPSTR,
	LPHSTRING,
	_LPVOID,
	LPASCSTR,
	_CHAR,
	_BYTE,
	_DOUBLE,
	_FLOAT,
	_WORD,
	_INT,
	_SHORT,
	INTFUNCLASS, // reference to method of internal class
	ITEM_REFERENCE,
	SCOPE_REFERENCE,
	_DWORD,
	_HANDLE,
	_LPBYTE,
	_LPCHAR,
	_LPDOUBLE,
	_LPWORD,
	_LPDWORD,
	_LPFLOAT,
	_LPINT,
	LPNUMBER,
	_WCHAR,
	UDV
};

#endif /* SAL_DATATYPES_HPP_ */
