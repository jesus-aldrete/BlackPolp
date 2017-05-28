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

#ifndef wDialogH
#define wDialogH

#include <System.Classes.hpp>
#include <Shobjidl.h>

#include "sFields.h"
#include "wGeneral.h"

class PACKAGE wDialog {
	/*Variables*/public:
	int             Index     ;
	String          Path      ;
	String          Title     ;
	String          Filter    ;
	String          Folder    ;
	String          Extension ;
	String          AllFiles  ;
	String          AllFormats;
	seOptionsDialog Options   ;
	sSField         Paths     ;
	//###########################################################################


	/*Creacion*/public:
	wDialog();
	//###########################################################################


	/*Metodos*/public:
	bool RunDI();
	bool RunOP();
	bool RunSA();
	//###########################################################################


	/*Funciones*/private:
	HRESULT LoadPaths ( IFileOpenDialog *dialog, sSField paths, String &path );
	HRESULT LoadFilter( IFileDialog     *dialog, String  filter              );
	HRESULT LoadFolder( IFileDialog     *dialog, String  directory           );
	//###########################################################################
 };

#endif
