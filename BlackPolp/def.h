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

#ifndef defH
#define defH

#include <FMX.Layouts.hpp>
#include <sGeneral.h>
#include <wGeneral.h>
#include <fGeneral.h>
#include <wDragDrop.h>
#include <wThread.h>
#include <wDialog.h>
#include <wStream.h>
#include <fAnim.h>
#include <fLine.h>
#include <fLoader.h>
#include <IdHTTP.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdIOHandlerSocket.hpp>

/*Definiciones*/
#define colorBlack 0xFF353535
#define colorGray1 0xFF434343
#define colorGray2 0xFF555555
#define colorGray3 0xFF707071
#define colorWhite 0xFFB3B3B3
#define colorHigh  0xFFA868D0

#define defSat 0.525
#define defLum 0.611
#define defAlp 1.000

#define toleranceDrag 5
#define numberColors  15
#define heightPallet  75
#define widthLetter	  float wil;TBitmap*bmp=new TBitmap;bmp->Canvas->Font->Family=fontFamily;bmp->Canvas->Font->Size=fontSize;wil=bmp->Canvas->TextWidth("00")-bmp->Canvas->TextWidth("0");delete bmp;

/*Enumeraciones*/
enum geColorType{ ctNone, ctRGBA, ctRGB, ctBGR, ctRed, ctGreen, ctBlue, ctAlpha, ctHue, ctSat, ctLum, ctAlp };
enum geDragZone { dzNone, dzCPallet, dzCPalletColor, dzCMenu, dzCColors, dzCPallets, dzCImage };

/*Tipos*/
typedef void __fastcall (__closure *gfEventColor )( TObject *sender, geColorType type, double color, TPoint position );
typedef void __fastcall (__closure *gfEventSelect)( TObject *sender, int index                                       );

/*Funciones*/
void ChangeCursor ( HICON cursor ) {
	if ( !cursor ) return;

	extern HCURSOR gdragCursor ;
	extern HCURSOR genterCursor;

	gdragCursor = CopyIcon( cursor );

	SetSystemCursor( gdragCursor, OCR_NORMAL );
 };
void RestoreCursor(              ) {
	extern HCURSOR gdragCursor ;
	extern HCURSOR genterCursor;

	if ( genterCursor ) SetSystemCursor( genterCursor, OCR_NORMAL );
	else                SystemParametersInfo( SPI_SETCURSORS, 0, NULL, 0 );

	DestroyIcon( gdragCursor );

	gdragCursor = null;
 };

void ColorDrop( TFmxObject *source, String color, float x, float y, SHDRAGIMAGE *imagen = null ) {
	TRectangle *rec = null;

	if ( !imagen ) {
		rec         = new TRectangle( null );
		rec->Width  = 50;
		rec->Height = 50;
		rec->StrC   = colorBlack;
		rec->FilC   = color.Length() >= 8 ? sau( "0x" + color ) : sau( "0xFF" + color );
	}

	if ( source ) wDragDrop::DoDragText( DROPEFFECT_COPY, true, imagen ? imagen : BMPaDBM( rec->MakeScreenshot(), x, y ), 2, color, (String)(__int64)source );
	else          wDragDrop::DoDragText( DROPEFFECT_COPY, true, imagen ? imagen : BMPaDBM( rec->MakeScreenshot(), x, y ), 1, color );

	delete rec;
 };

bool IsColor ( String text   ) {
	bool result = false;

	if ( text.Length() == 6 || text.Length() == 8 ) {
		int      pos = 0;
		int      len = text.Length();
		wchar_t *cad = text.w_str();

		for ( ;pos<len; pos++ ) {
			if ( ( cad[pos]<48 || cad[pos]>57 ) && ( cad[pos]<97 || cad[pos]>102 ) && ( cad[pos]<65 || cad[pos]>70 ) )
				break;
		}

		result = pos == len ;
	}

	return result;
 };
bool IsPallet( String text   ) {
	int      num = 0;
	int      pos = 0;
	int      len = text.Length();
	wchar_t *str = text.w_str();

	for ( ;pos<len; pos++ ) {
		if ( str[pos]=='|' ) num++;
		if ( num >= 2      ) return true;
	}

	return false;
 };
int  IsImages( sSField files ) {
	if ( files.Size ) {
		String ext;

		for ( int i = 0; i < files.Size; i++ ) {
			ext = ExtractFileExt( files[i] ).LowerCase();

			if ( ext == ".jpg" || ext == ".png" || ext == ".jepg" || ext == ".gif" || ext == ".ico" || ext == ".bmp" )
				return i;
		}
	}

	return -1;
 };
int  IsFiles ( sSField files ) {
	if ( files.Size ) {
		for ( int i = 0; i < files.Size; i++ ) {
			if ( ExtractFileExt( files[i] ).LowerCase() == ".ase" )
				return i;
		}
	}

	return -1;
 };

#endif
