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

#ifndef wTaskBarH
#define wTaskBarH

#pragma link "Shlwapi.lib"

#include <Shobjidl.h>
#include <propvarutil.h>

#include "sFields.h"
#include "wGeneral.h"

class PACKAGE wTaskBar {
	/*Variables*/private:
	sSField _categorys   ;
	sSField _linkCategory;
	sSField _linkTitle   ;
	sSField _linkPath    ;
	sSField _linkParams  ;
	sSField _linkIcon    ;
	sIField _linkIndex   ;
	sIField _linkType    ;
	//###########################################################################


	/*Creacion*/public:
	wTaskBar();
	//###########################################################################


	/*Metodos - icon*/public:
	static void SetIcon( HICON hicon, String description = "" );
	static void DelIcon(                                      );

	/*Metodos - progreso*/public:
	static void SetProgress( seTypeProg type, int vmax, int vmin, int vprogress );
	static void DelProgress(                                                    );

	/*Metodos - jumpList*/public:
	void AddLink( String category, String title, String path, String params, String iconPath, int iconIndex, seTypeLink type = tlShellLink );

		   bool CreateJump( String applicationID = "", bool viewFrequent = false, bool viewRecent = false );
	static bool DeleteJump( String applicationID = ""                                                     );
	//###########################################################################


	/*Funciones*/private:
	bool CreateCategory( ICustomDestinationList *jumplist, String title );
	bool CreateLink    ( IObjectCollection *list, int index             );
	//###########################################################################
 };

#endif
