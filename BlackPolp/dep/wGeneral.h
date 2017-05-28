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

#ifndef wGeneralH
#define wGeneralH

#include <windows.h>
#include <shlobj.h>
#include <Shobjidl.h>
#include <classes.hpp>
#include <IniFiles.hpp>

#include "sFields.h"
#include "sDef.h"
#include "wRegistry.h"

/*Funciones - FILES*/
extern "C++" __declspec(dllexport)DWORD     __stdcall GetFileSize( String file                                                          );
extern "C++" __declspec(dllexport)TDateTime __stdcall GetDateFile( String file                                                          );
extern "C++" __declspec(dllexport)void      __stdcall GetDateFile( String file, TDateTime &create, TDateTime &access, TDateTime &modify );

extern "C++" __declspec(dllexport)bool __stdcall CopyFiles   ( String source, String destiny );
extern "C++" __declspec(dllexport)bool __stdcall MoveFiles   ( String source, String destiny );
extern "C++" __declspec(dllexport)bool __stdcall RecycleFiles( String source                 );
extern "C++" __declspec(dllexport)bool __stdcall DeleteFiles ( String source                 );

extern "C++" __declspec(dllexport)String __stdcall ExtractExtension( String file );
extern "C++" __declspec(dllexport)String __stdcall ExtractName     ( String file );
extern "C++" __declspec(dllexport)String __stdcall ExtractPath     ( String file );
extern "C++" __declspec(dllexport)bool   __stdcall FileExist       ( String file );
extern "C++" __declspec(dllexport)bool   __stdcall PathExist       ( String path );

extern "C++" __declspec(dllexport)String __stdcall CompressString( float fSize, String fFamily, float width, String cadena );
//###########################################################################


/*Funciones - DIRECTORIOS*/
extern "C++" __declspec(dllexport)bool                     __stdcall CopyPath   ( String source, String destiny );
extern "C++" __declspec(dllexport)bool                     __stdcall MovePath   ( String source, String destiny );
extern "C++" __declspec(dllexport)bool                     __stdcall RecyclePath( String source                 );
extern "C++" __declspec(dllexport)bool                     __stdcall DeletaPath ( String source                 );
extern "C++" __declspec(dllexport)sSField                  __stdcall TravelPath ( String source                 );
extern "C++" __declspec(dllexport)FILE_NOTIFY_INFORMATION *__stdcall WatchPath  ( String source                 );
//###########################################################################


/*Funciones - PORTAPAPELES*/
extern "C++" __declspec(dllexport)void   __stdcall SetClipBoardString( AnsiString text );
extern "C++" __declspec(dllexport)String __stdcall GetClipBoardString(                 );
//###########################################################################


/*Funciones - BITMAP*/
extern "C++" __declspec(dllexport)void    __stdcall OverHBitmap( HBITMAP base, HBITMAP up, RECT rup, bool alphablend = true );
extern "C++" __declspec(dllexport)HBITMAP __stdcall GetIconFile( String file, SIZE size                                     );
extern "C++" __declspec(dllexport)HICON   __stdcall HBMPaHICON ( HBITMAP bitmap                                             );

extern "C++" __declspec(dllexport)TMemoryStream *__stdcall GetIconStream( String path, int index );
//###########################################################################


/*Funciones - APLICACION*/
extern "C++" __declspec(dllexport)String __stdcall Run  ( String exe, String parameters            );
extern "C++" __declspec(dllexport)bool   __stdcall RunAs( String exe, String parameters, bool wait );
//###########################################################################


/*Funciones - LINK*/
typedef struct {
	String Destiny      ;
	String Arguments    ;
	String PathIcon     ;
	int    IndexIcon    ;
	int    VisualMode   ;
	String WorkPath     ;
	String Description  ;
} TInfoLink, *PInfoLink;

extern "C++" __declspec(dllexport)void   __stdcall SolveLink   ( AnsiString path, PInfoLink info                                             );
extern "C++" __declspec(dllexport)bool   __stdcall CreateLink  ( String     path, AnsiString pathLink, String description, String parameters );
extern "C++" __declspec(dllexport)String __stdcall DestinyLink ( AnsiString path                                                             );
extern "C++" __declspec(dllexport)void   __stdcall PinToTaskBar( String     path, bool unpin                                                 );
//###########################################################################


/*Funciones - GENERALES*/
static String appPath;
static String appDirectory;
static String appExtension;
static String appName;
static String appTemporary;

extern "C++" __declspec(dllexport)HWND   __stdcall GetHandle      ( HWND handle = null );
extern "C++" __declspec(dllexport)HWND   __stdcall GetGlobalHandle( HWND handle = null );
extern "C++" __declspec(dllexport)String __stdcall GetAppPath     (                    );
extern "C++" __declspec(dllexport)String __stdcall GetAppDirectory(                    );
extern "C++" __declspec(dllexport)String __stdcall GetAppExtension(                    );
extern "C++" __declspec(dllexport)String __stdcall GetAppName     (                    );
extern "C++" __declspec(dllexport)String __stdcall GetTemporary   (                    );
extern "C++" __declspec(dllexport)String __stdcall GetPathIcon    ( String path        );
extern "C++" __declspec(dllexport)String __stdcall AccentABat     ( String text        );
extern "C++" __declspec(dllexport)String __stdcall BatAAccent     ( String text        );
extern "C++" __declspec(dllexport)void   __stdcall bcBringToFront ( HWND form          );

extern "C++" __declspec(dllexport)sSField __stdcall GetTagsGroup( String allString );

extern "C++" __declspec(dllexport)String __stdcall LastError();

extern "C++" __declspec(dllexport)void __stdcall SetTimeout  ( String id, float time, TNotifyEvent function, TObject *sender = null );
extern "C++" __declspec(dllexport)void __stdcall SetInterval ( String id, float time, TNotifyEvent function, TObject *sender = null );
extern "C++" __declspec(dllexport)void __stdcall StopInterval( String id                                                            );

extern "C++" __declspec(dllexport)bool __stdcall ChangeIconExe( wchar_t *pathIcon, wchar_t* exe, wchar_t* nameRes, bool deletePrevious );

extern "C++" __declspec(dllexport)int __stdcall ShowPopUp( float x, float y, int number, ... );
//###########################################################################

#endif