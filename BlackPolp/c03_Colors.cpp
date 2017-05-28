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

#pragma hdrstop
#include "c03_Colors.h"
#pragma package(smart_init)

// class cColors : public cBase //###########################################
/*Creacion - controles - private*/
void cColors::CreateThis  () {
	TResourceStream *
	res           = new TResourceStream( (int)HInstance, "TRANSPARENCIA", L"PNG" );
	res->Position = 0;

	_rback         = new TRectangle( this );
	_rback->Parent = this;
	_rback->Align  = AL::Contents;
	_rback->StrK   = BK::None;
	_rback->FilK   = BK::Bitmap;
	_rback->Fill->Bitmap->Bitmap->LoadFromStream( res );

	delete res;
 };
void cColors::CreateColors() {
	/*Color*/
	_rcolor              = new TRectangle( this );
	_rcolor->Parent      = this;
	_rcolor->Align       = AL::Client;
	_rcolor->StrK        = BK::None;
	_rcolor->FilC        = colorBlack;
	_rcolor->TagFloat    = dzCColors;
	_rcolor->CanFocus    = true;
	_rcolor->OnMouseDown = moudw_rcolor;

	/*Complementario*/
	_rcomplement              = new TRectangle( this );
	_rcomplement->Parent      = this;
	_rcomplement->Align       = AL::Right;
	_rcomplement->StrK        = BK::None;
	_rcomplement->FilC        = colorBlack;
	_rcomplement->Width       = 30;
	_rcomplement->CanFocus    = true;
	_rcomplement->OnMouseDown = moudw_rcolor;
 };
void cColors::CreateGlass () {
	_lglass               = new TLayout( this );
	_lglass->Parent       = this;
	_lglass->Width        = 100;
	_lglass->Height       = 100;
	_lglass->Opacity      = 0;
	_lglass->ClipChildren = true;

	_iglass           = new TImage( this );
	_iglass->Parent   = _lglass;
	_iglass->Height   = 500;
	_iglass->Width    = 500;
	_iglass->MarT     = -6;
	_iglass->MarL     = -5;
	_iglass->Align    = AL::Center;
	_iglass->WrapMode = TImageWrapMode::Stretch;
	_iglass->HitTest  = false;

	_rglass          = new TRectangle( this );
	_rglass->Parent  = _lglass;
	_rglass->Height  = 5;
	_rglass->Width   = 5;
	_rglass->StrC    = claBlack;
	_rglass->FilC    = claRed;
	_rglass->Align   = AL::Center;
	_rglass->HitTest = true;
 };

/*Creacion - public*/
__fastcall cColors::cColors( TComponent *owner ) : cBase(owner) {
	CreateThis  ();
	CreateColors();
	CreateGlass ();
 };
//###########################################################################


/*Propiedades - Entradas - private*/
void cColors::WGlass( TPoint glass ) {
	_pglass = glass;

	if ( glass.x == snan ) ActiveGlass( false );
	else {
		ActiveGlass( true );

		int w = 100, h = 100, x = glass.x - 50, y = glass.y - 50;

		HDC   hScrDC;
		HDC   hMemDC;
		BYTE *lpBitmapBits = NULL;

		hScrDC = CreateDC( L"DISPLAY", NULL, NULL, NULL );
		hMemDC = CreateCompatibleDC( hScrDC );

		BITMAPINFO RGB24BitsBITMAPINFO;

		ZeroMemory( &RGB24BitsBITMAPINFO, sizeof( BITMAPINFO ) );

		RGB24BitsBITMAPINFO.bmiHeader.biSize     = sizeof( BITMAPINFOHEADER );
		RGB24BitsBITMAPINFO.bmiHeader.biWidth    = w;
		RGB24BitsBITMAPINFO.bmiHeader.biHeight   = h;
		RGB24BitsBITMAPINFO.bmiHeader.biPlanes   = 1;
		RGB24BitsBITMAPINFO.bmiHeader.biBitCount = 24;

		HBITMAP hBitmap    = CreateDIBSection( hMemDC, (BITMAPINFO*)&RGB24BitsBITMAPINFO,DIB_RGB_COLORS, (void**)&lpBitmapBits, NULL, 0 );
		HGDIOBJ hOldBitmap = SelectObject( hMemDC, hBitmap );

		BitBlt( hMemDC, 0, 0, w, h, hScrDC, x, y, SRCCOPY );

		BITMAPFILEHEADER bmBITMAPFILEHEADER;

		ZeroMemory( &bmBITMAPFILEHEADER, sizeof( BITMAPFILEHEADER ) );

		bmBITMAPFILEHEADER.bfType    = 0x4d42;
		bmBITMAPFILEHEADER.bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER );
		bmBITMAPFILEHEADER.bfSize    = bmBITMAPFILEHEADER.bfOffBits + ( ( w * h ) * 3 );

		TMemoryStream *ms = new TMemoryStream;

		ms->Write( &bmBITMAPFILEHEADER               , sizeof( BITMAPFILEHEADER ) );
		ms->Write( &( RGB24BitsBITMAPINFO.bmiHeader ), sizeof( BITMAPINFOHEADER ) );
		ms->Write( lpBitmapBits                      , 3 * w * h                  );

		ms->Position = 0;

		_iglass->Bitmap->LoadFromStream( ms );

		delete ms;

		DeleteObject( hMemDC );
		DeleteObject( hScrDC );

		DeleteObject( hBitmap );
		DeleteObject( hOldBitmap );
	}
 };
//###########################################################################


/*Eventos - private*/
void __fastcall cColors::moudw_rcolor( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	varPom;
	TRectangle *rec = (TRectangle*)sender;
	float       px1 = pom.x, py1 = pom.y;

	while ( whileDown ) {
		GetCursorPos( &pom );

		if (
			( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
			( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
		) {
			ColorDrop( null, IntToHex( (int)rec->FilC, 8 ),
				px1 - fom.left - rec->AbsoluteRect.left - x + 25,
				py1 - fom.top  - rec->AbsoluteRect.top  - y + 25
			);
			break;
		}
	}
 };
//###########################################################################


/*Metodos - private*/
void cColors::ChangeColor() {
	_rcolor->FilC = _color;

	/*Complementario*/
	double h = _hue;

	h  = h * 360.0;
	h += h < 180.0 ? 180.0 : -180.0;
	h  = h / 360.0;

	_rcomplement->FilC = HSLaRGB( h, _sat, _lum, _alp );
 };

/*Metodos - public*/
void cColors::ActiveGlass( bool active ) {
	if ( _lglass->Tag == 0 && active )  {
		_lglass->Tag = 1;

		AnimO( _lglass, 0.3, 1, sfExponentialOut );
	}
	else if ( _lglass->Tag == 1 && !active ) {
		_lglass->Tag = 0;

		AnimO( _lglass, 0.3, 0, sfExponentialOut );
	}
 };

void cColors::Drop( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	String sco = texts[0];

	if ( !IsColor( sco ) ) return;

	unsigned col = sau( ( sco.Length() <= 6 ? "0xFF" : "0x" ) + sco );

	if ( onFinalColor ) onFinalColor( this, sco.Length() <= 6 ? ctRGB : ctRGBA, col, TPoint(0,0) );
 };
//###########################################################################