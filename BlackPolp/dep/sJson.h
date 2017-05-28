/*

Copyright 2017 Jesús E. Aldréte Hernández

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef sJsonH
#define sJsonH

#include <classes.hpp>
#include <sField.hpp>

#include "sDef.h"
#include "wStream.h"

class PACKAGE sJson {
	/*Definiciones*/
	#define sJson_start \
		_child   = new TList__1<__int64>; \
		_count   = new __int64;           \
		_temp    = null;                  \
		_json    = new String;            \
		_file    = new String;            \
		_value   = new String;            \
		_tag     = new String;            \
		_type    = new seValueType;       \
		(*_type) = vlNothing;
	//###########################################################################


	/*Variables*/protected:
	TList__1<__int64> *_child;
	__int64           *_count;
	sJson             *_temp;
	String            *_json;
	String            *_file;
	String            *_value;
	String            *_tag;
	seValueType       *_type;
	//###########################################################################


	/*Creacion*/public:
	sJson(                   );
	sJson( const String file );
	sJson( const sJson *json );
	sJson( const sJson &json );
   ~sJson(                   );
	//###########################################################################


	/*Propiedades*/protected:
	void WJson ( String      json  );
	void WValue( String      value );
	void WTag  ( String      tag   );
	void WType ( seValueType type  );
	void WStr  ( String      str   );
	void WBoo  ( bool        boo   );
	void WNum  ( double      num   );

	/*Propiedades*/protected:
	int         RLength();
	String      RJson  ();
	String      RValue ();
	String      RTag   ();
	seValueType RType  ();
	String      RStr   ();
	bool        RBoo   ();
	double      RNum   ();

	/*Propiedades*/public:
	__property int         Length = { read=RLength               };
	__property String      Json   = { read=RJson  , write=WJson  };
	__property String      Value  = { read=RValue , write=WValue };
	__property String      Tag    = { read=RTag   , write=WTag   };
	__property seValueType Type   = { read=RType  , write=WType  };
	__property String      Str    = { read=RStr   , write=WStr   };
	__property bool        Boo    = { read=RBoo   , write=WBoo   };
	__property double      Num    = { read=RNum   , write=WNum   };
	//###########################################################################


	/*Operadores*/public:
	sJson operator = ( sJson value );

	sJson operator += ( sJson  value              );
	sJson operator -= ( int    index              );
	sJson operator [] ( int    index              );
	sJson operator [] ( String tag                );
	sJson operator () ( int    index, sJson value );
	//###########################################################################


	/*Metodos*/public:
	void Parse( String file                           );
	void Clear(                                       );
	void Save ( String file = "", bool format = false );
	void Clone( sJson json                            );

	sJson Add( seValueType type, String tag, String value );
	//###########################################################################


	/*Funciones*/protected:
	String GetString( wchar_t *cad, int &pos, int len );

	sJson GetTemporary();

	void AddString( wchar_t *cad, int &pos, int len, String tag );
	void AddBool  ( wchar_t *cad, int &pos, int len, String tag );
	void AddNull  ( wchar_t *cad, int &pos, int len, String tag );
	void AddArray ( wchar_t *cad, int &pos, int len, String tag );
	void AddObject( wchar_t *cad, int &pos, int len, String tag );
	void AddNumber( wchar_t *cad, int &pos, int len, String tag );

	void ViewObject( wchar_t *cad, int &pos, int len );
	void ViewArray ( wchar_t *cad, int &pos, int len );

	String AJson( sJson json, bool format, bool isObject, String slevel, int ilevel );

	void Delete();
	//###########################################################################
 };

#endif
