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

#ifndef wRegistryH
#define wRegistryH

#include "wGeneral.h"
#include "Winreg.h"

class PACKAGE wRegistry {
	/*Definiciones*/
	#define wRegistry_start \
		ViewErrors  = false;             \
		HKey        = HKEY_CURRENT_USER; \
		Pass        = KEY_ALL_ACCESS;    \
		Transaction = null;
	//###########################################################################


	/*Variables*/public:
	bool           ViewErrors ;
	HKEY           HKey       ;
	unsigned long  Pass       ;
	String         Key        ;
	void          *Transaction;
	//###########################################################################


	/*Creacion*/public:
	wRegistry(                                                                         );
	wRegistry( HKEY hkey, String key,                     bool create, bool viewErrors );
	wRegistry( HKEY hkey, String key, unsigned long pass, bool create, bool viewErrors );
	//###########################################################################


	/*Metodos*/public:
	bool OpenKey  (                        bool create );
	bool OpenKey  (            String key, bool create );
	bool OpenKey  ( HKEY hkey, String key, bool create );
	void CloseKey (                                    );
	bool RenameKey(            String key, String name );
	bool DeleteKey(            String key              );
	bool DeleteKey( HKEY hkey, String key              );
	bool DeleteVal(            String key              );
	bool DeleteVal( HKEY hkey, String key              );

	int    Int( String name );
	String Str( String name );
	double Dou( String name );

	bool Int( String name, int    value );
	bool Str( String name, String value );
	bool Dou( String name, double value );

	int    DefInt( String name, int    def = 0  );
	String DefStr( String name, String def = "" );
	double DefDou( String name, double def = 0  );
	//###########################################################################
 };

#endif
