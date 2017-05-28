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

#ifndef wDragDropH
#define wDragDropH

#include <Shlobj.h>
#include <Shobjidl.h>
#include <classes.hpp>

#include "sFields.h"
#include "wGeneral.h"

class PACKAGE wDragDrop {
	/*Variables*/private:
	HWND         _handle    ;
	IDropTarget *_dropTarget;
	//###########################################################################


	/*Creacion*/public:
	wDragDrop( HWND handle, sfDrag oninit, sfDrag onover, sfDrag ondrop, sfDrag onleave );
   ~wDragDrop(                                                                          );
	//###########################################################################


	/*Funciones*/private:
	static HANDLE  STRaHAN( const TCHAR *text, int size = -1                            );
	static void    STRaDAT( String text, IDataObject *dataobject                        );
	static HBITMAP STRaBMP( String text, SIZE &size                                     );
	static void    FILaBMP( SHDRAGIMAGE *image, IDataObject *pDataObject, sSField files );

	/*Funciones*/public:
	static DWORD DoDragText( DWORD effects, bool viewimage, SHDRAGIMAGE *image, int ntexts, ...             );
	static DWORD DoDragFile( DWORD effects, bool viewimage, SHDRAGIMAGE *image, String  files, String extra );
	static DWORD DoDragFile( DWORD effects, bool viewimage, SHDRAGIMAGE *image, sSField files, String extra );
	//###########################################################################
 };

#endif
