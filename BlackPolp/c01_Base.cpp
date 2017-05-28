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
#include "c01_Base.h"
#pragma package(smart_init)

// class cMenu : public cBase //#############################################
/*Creacion - public*/
__fastcall cBase::cBase( TComponent *owner ) : TLayout(owner) {
	onStartColor = null;
	onChangColor = null;
	onFinalColor = null;
 };
//###########################################################################


/*Propiedades - Entradas - protected*/
void cBase::WColor( unsigned color ) {
	RGBaHSL( color, _hue, _sat, _lum, _alp );

	_color         = color;
	_red           = RRGB( color );
	_green         = GRGB( color );
	_blue          = BRGB( color );
	_alpha         = ARGB( color );
	_preserveColor = HSLaRGB( _hue, defSat, defLum, defAlp );

	ChangeColor();
 };
void cBase::WHue  ( double   hue   ) {
	if ( hue < 0 ) hue = 0;
	if ( hue > 1 ) hue = 1;

	_hue           = hue;
	_color         = HSLaRGB( _hue, _sat, _lum, _alp );
	_red           = RRGB( _color );
	_green         = GRGB( _color );
	_blue          = BRGB( _color );
	_preserveColor = HSLaRGB( _hue, defSat, defLum, defAlp );

	ChangeColor();
 };
void cBase::WSat  ( double   sat   ) {
	if ( sat < 0 ) sat = 0;
	if ( sat > 1 ) sat = 1;

	_sat   = sat;
	_color = HSLaRGB( _hue, _sat, _lum, _alp );
	_red   = RRGB( _color );
	_green = GRGB( _color );
	_blue  = BRGB( _color );

	ChangeColor();
 };
void cBase::WLum  ( double   lum   ) {
	if ( lum < 0 ) lum = 0;
	if ( lum > 1 ) lum = 1;

	_lum   = lum;
	_color = HSLaRGB( _hue, _sat, _lum, _alp );
	_red   = RRGB( _color );
	_green = GRGB( _color );
	_blue  = BRGB( _color );

	ChangeColor();
 };
void cBase::WAlp  ( double   alp   ) {
	if ( alp < 0 ) alp = 0;
	if ( alp > 1 ) alp = 1;

	_alp   = alp;
	_color = HSLaRGB( _hue, _sat, _lum, _alp );
	_alpha = alp * 255;

	ChangeColor();
 };
void cBase::WRed  ( int      red   ) {
	if ( red < 0   ) red = 0  ;
	if ( red > 255 ) red = 255;

	_red   = red;
	_color = ACOL( _alpha, _red, _green, _blue );

	RGBaHSL( _red, _green, _blue, _hue, _sat, _lum );

	_preserveColor = HSLaRGB( _hue, defSat, defLum, defAlp );

	ChangeColor();
 };
void cBase::WGreen( int      green ) {
	if ( green < 0   ) green = 0  ;
	if ( green > 255 ) green = 255;

	_green = green;
	_color = ACOL( _alpha, _red, _green, _blue );

	RGBaHSL( _red, _green, _blue, _hue, _sat, _lum );

	_preserveColor = HSLaRGB( _hue, defSat, defLum, defAlp );

	ChangeColor();
 };
void cBase::WBlue ( int      blue  ) {
	if ( blue < 0   ) blue = 0  ;
	if ( blue > 255 ) blue = 255;

	_blue  = blue;
	_color = ACOL( _alpha, _red, _green, _blue );

	RGBaHSL( _red, _green, _blue, _hue, _sat, _lum );

	_preserveColor = HSLaRGB( _hue, defSat, defLum, defAlp );

	ChangeColor();
 };
void cBase::WAlpha( int      alpha ) {
	if ( alpha < 0   ) alpha = 0  ;
	if ( alpha > 255 ) alpha = 255;

	_alpha = alpha;
	_color = ACOL( _alpha, _red, _green, _blue );
	_alp   = double(alpha) / 255.0;

	ChangeColor();
 };
//###########################################################################


/*Metodos - public*/
void cBase::Render     () {};
void cBase::ChangeColor() {};

void cBase::ChangeHSLA( double hue, double sat, double lum, double alp ) {
	if ( hue < 0 ) hue = 0;	if ( hue > 1 ) hue = 1;
	if ( sat < 0 ) sat = 0;	if ( sat > 1 ) sat = 1;
	if ( lum < 0 ) lum = 0;	if ( lum > 1 ) lum = 1;
	if ( alp < 0 ) alp = 0;	if ( alp > 1 ) alp = 1;

	_hue           = hue;
	_sat           = sat;
	_lum           = lum;
	_alp           = alp;
	_color         = HSLaRGB( _hue, _sat, _lum, _alp );
	_red           = RRGB( _color );
	_green         = GRGB( _color );
	_blue          = BRGB( _color );
	_preserveColor = HSLaRGB( _hue, defSat, defLum, defAlp );

	ChangeColor();
 };
//###########################################################################
