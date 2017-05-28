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

#ifndef wStreamH
#define wStreamH

#include <classes.hpp>
#include "wGeneral.h"

class PACKAGE wStream {
	/*Definiciones*/
	#define wStream_start \
		_size    = 0;                     \
		_buffer  = (BYTE*)GetMemory( 0 ); \
		ROT      = true;                  \
		Position = 0;
	//###########################################################################


	/*Variables*/private:
	unsigned long  _size  ;
	BYTE          *_buffer;

	/*Variables*/public:
	bool     ROT     ;
	unsigned Position;
	//###########################################################################


	/*Creacion*/public:
	__fastcall  wStream(             );
	__fastcall  wStream( String file );
	__fastcall ~wStream(             );
	//###########################################################################


	/*Propiedades*/public:
	__property unsigned long  Size   = { read = _size   };
	__property BYTE          *Buffer = { read = _buffer };
	//###########################################################################


	/*Metodos*/public:
	void __fastcall I16    ( __int16       value );
	void __fastcall I64    ( __int64       value );
	void __fastcall Int    ( int           value );
	void __fastcall Flo    ( float         value );
	void __fastcall Dou    ( double        value );
	void __fastcall Str    ( String        value );
	void __fastcall Sun    ( UnicodeString value );
	void __fastcall OnlyStr( String        value );

	__int16       __fastcall I16    (                        );
	__int64       __fastcall I64    (                        );
	int           __fastcall Int    (                        );
	float         __fastcall Flo    (                        );
	double        __fastcall Dou    (                        );
	String        __fastcall Str    (                        );
	UnicodeString __fastcall Sun    (                        );
	String        __fastcall OnlyStr( unsigned long size = 0 );

	void __fastcall Save ( String file                         );
	void __fastcall Load ( String file                         );
	void __fastcall Copy ( wStream *stream, unsigned long size );
	void __fastcall Clear(                                     );
	//###########################################################################
 };

#endif
