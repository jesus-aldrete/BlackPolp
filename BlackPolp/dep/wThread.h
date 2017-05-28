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

#ifndef wThreadH
#define wThreadH

#include <windows.h>
#include <classes.hpp>

#include "wGeneral.h"

class PACKAGE wThread {
	/*Definiciones*/
	#define wThread_start \
		_handle = GetHandle();                                                     \
		_hpause = false;                                                           \
		HMutex  = null;                                                            \
		HThread = null;                                                            \
		HSemapo = null;                                                            \
		Cancel  = false;                                                           \
		HTimer  = null;                                                            \
		HMutex  = null;                                                            \
		HThread = null;                                                            \
		for ( int i = 0; i < 10; i++ ) { Str[i] = ""; Num[i] = 0 ; i64[i] = 0 ; }  \
		onThread = null;                                                           \
		onFinal  = null;                                                           \
		onSync   = null;
	//###########################################################################


	/*Variables*/private:
	HWND _handle;
	bool _hpause;

	/*Variables*/public:
	void    *HMutex ;
	void    *HThread;
	void    *HSemapo;
	UINT     HTimer ;
	String   HID    ;
	bool     Cancel ;
	String   Error  ;
	String   Str[10];
	double   Num[10];
	__int64  i64[10];

	/*Variables - Eventos*/public:
	sfThread onThread;
	sfThread onFinal ;
	sfThread onSync  ;
	//###########################################################################


	/*Creacion*/public:
	wThread(                                     );
	wThread( sfThread onthread                   );
	wThread( sfThread onthread, sfThread onfinal );
	//###########################################################################


	/*Metodos*/public:
	void Play(                 );
	void Paus( bool pause      );
	void Stop(                 );
	void Sync( sfThread onsync );
	//###########################################################################
 };

#endif
