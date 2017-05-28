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
#include "p03_Info.h"
#pragma package(smart_init)



// class pInfo : public cBase //#############################################
/*Creacion - controles - private*/
void pInfo::CreateEdit( TLayout **lparent, TText **ttitle, fLine **fvalue, String title ) {
	widthLetter;

	(*lparent)         = new TLayout( this );
	(*lparent)->Parent = this;
	(*lparent)->PosY   = this->Height + 1000;
	(*lparent)->Align  = AL::Top;
	(*lparent)->Height = 20;

	(*ttitle)               = new TText( this );
	(*ttitle)->Parent       = (*lparent);
	(*ttitle)->Align        = AL::Left;
	(*ttitle)->Font->Family = fontFamily;
	(*ttitle)->Font->Size   = fontSize;
	(*ttitle)->Text         = title;
	(*ttitle)->Width        = ( title.Length() * wil ) + 1;
	(*ttitle)->Color        = colorWhite;

	(*fvalue)           = new fLine( this );
	(*fvalue)->Parent   = (*lparent);
	(*fvalue)->Align    = AL::Client;
	(*fvalue)->Fill     = colorWhite;
	(*fvalue)->ReadOnly = true;
 };

void pInfo::CreateThis () {
	_rback         = new TRectangle( this );
	_rback->Parent = this;
	_rback->Align  = AL::Contents;
	_rback->StrK   = BK::None;
	_rback->FilC   = colorBlack;
 };
void pInfo::CreateLines() {
	CreateEdit( &_lrgbp, &_trgbp, &_frgbp, "RGBA%: " );
	CreateEdit( &_lcmyk, &_tcmyk, &_fcmyk, " CMYK: " );
	CreateEdit( &_lhsla, &_thsla, &_fhsla, "  HSL: " );
	CreateEdit( &_lhsva, &_thsva, &_fhsva, "  HSV: " );
	CreateEdit( &_lxyza, &_txyza, &_fxyza, "  XYZ: " );
	CreateEdit( &_lxyya, &_txyya, &_fxyya, "  xyY: " );
	CreateEdit( &_llaba, &_tlaba, &_flaba, "  LAB: " );
	CreateEdit( &_lhlab, &_thlab, &_fhlab, "H-LAB: " );
 };

/*Creacion - public*/
__fastcall pInfo::pInfo( TComponent *owner ) : cBase(owner) {
	CreateThis ();
	CreateLines();
 };
//###########################################################################


/*Metodos - private*/
void pInfo::ChangeColor() {
	_frgbp->Color = _preserveColor;
	_fcmyk->Color = _preserveColor;
	_fhsla->Color = _preserveColor;
	_fhsva->Color = _preserveColor;
	_flaba->Color = _preserveColor;
	_fxyza->Color = _preserveColor;
	_fxyya->Color = _preserveColor;
	_fhlab->Color = _preserveColor;

	_frgbp->Text =
		String( ( double(_red  ) * 100.0 ) / 255.0 ).SubString( 0, 5 ) + "%, " +
		String( ( double(_green) * 100.0 ) / 255.0 ).SubString( 0, 5 ) + "%, " +
		String( ( double(_blue ) * 100.0 ) / 255.0 ).SubString( 0, 5 ) + "%, " +
		String( ( double(_alpha) * 100.0 ) / 255.0 ).SubString( 0, 5 ) + "%"
	;

	/*CMYK*/
	double c, m, y, k;
	RGBaCMYK( _red, _green, _blue, c, m, y, k );
	_fcmyk->Text =
		String( sround( c * 100.0 ) ).SubString( 0, 5 ) + ", " +
		String( sround( m * 100.0 ) ).SubString( 0, 5 ) + ", " +
		String( sround( y * 100.0 ) ).SubString( 0, 5 ) + ", " +
		String( sround( k * 100.0 ) ).SubString( 0, 5 ) + ""
	;

	/*HSL*/
	_fhsla->Text =
		String(_hue * 360.0).SubString( 0, 5 ) + "°, " +
		String(_sat * 100.0).SubString( 0, 5 ) + ", " +
		String(_lum * 100.0).SubString( 0, 5 ) + ""
	;

	/*HSV*/
	double h, s, v;
	RGBaHSV( _red, _green, _blue, h, s, v );
	_fhsva->Text =
		String(h * 360.0).SubString( 0, 5 ) + "°, " +
		String(s * 100.0).SubString( 0, 5 ) + ", " +
		String(v * 100.0).SubString( 0, 5 ) + ""
	;

	/*LAB*/
	double l, a, b;
	RGBaLAB( _red, _green, _blue, l, a, b );
	_flaba->Text =
		String(l).SubString( 0, 5 ) + ", " +
		String(a).SubString( 0, 5 ) + ", " +
		String(b).SubString( 0, 5 ) + ""
	;

	/*XYZ*/
	double x1, y1, z1;
	RGBaXYZ( _red, _green, _blue, x1, y1, z1 );
	_fxyza->Text =
		String(x1).SubString( 0, 5 ) + ", " +
		String(y1).SubString( 0, 5 ) + ", " +
		String(z1).SubString( 0, 5 ) + ""
	;

	/*XYY*/
	double x2, y2, y3;
	y3 = y1;
	x2 = ( x1 + y1 + z1 ) ? x1 / ( x1 + y1 + z1 ) : 0;
	y2 = ( x1 + y1 + z1 ) ? y3 / ( x1 + y1 + z1 ) : 0;
	_fxyya->Text =
		String(x2).SubString( 0, 5 ) + ", " +
		String(y2).SubString( 0, 5 ) + ", " +
		String(y3).SubString( 0, 5 ) + ""
	;

	/*HLAB*/
	l = 10.0 * sqrt( y1 );
	a = 17.5 * ( l ? ( ( 1.02 * x1 ) - y1 ) / sqrt( y1 ) : 0 );
	b =  7.0 * ( l ? ( y1 - ( 0.847 * z1 ) ) / sqrt( y1 ) : 0 );
	_fhlab->Text =
		String(l).SubString( 0, 5 ) + ", " +
		String(a).SubString( 0, 5 ) + ", " +
		String(b).SubString( 0, 5 ) + ""
	;
 };
//###########################################################################