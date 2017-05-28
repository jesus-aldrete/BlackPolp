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

#ifndef fGeneralH
#define fGeneralH

#include <Shobjidl.h>
#include <FMX.Graphics.hpp>
#include <FMX.Platform.Win.hpp>

#include <sDef.h>

/*Imagen*/
extern "C++" __declspec( dllexport )TMemoryStream *__stdcall HBMaMEM( HBITMAP  bitmap                 );
extern "C++" __declspec( dllexport )HBITMAP        __stdcall BMPaHBM( TBitmap *bitmap                 );
extern "C++" __declspec( dllexport )SHDRAGIMAGE   *__stdcall BMPaDBM( TBitmap *bitmap, long x, long y );
//###########################################################################


/*General*/
extern "C++" __declspec( dllexport )HWND __stdcall GetApplicationHandle();
//###########################################################################

#endif

