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
#include "p06_Tones.h"
#pragma package(smart_init)

// class pTones : public pPallets //#########################################
/*Creacion - public*/
__fastcall pTones::pTones( TComponent *owner ) : pPallets(owner) {
	this->ReadOnly = true;
 };
//###########################################################################


/*Metodos - public*/
void pTones::ChangeColor() {
	pPallets::ChangeColor();

	String che = IntToHex( HSLaRGB( _hue, _sat, _lum, _alp ), 8 ) + ",";

	this->ReadOnly = false;

	this->Clear();

	this->Add(
		"Similares|3|" +
			IntToHex( HSLaRGB( _hue - 0.01, _sat, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue - 0.02, _sat, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue - 0.03, _sat, _lum, _alp ), 8 ) + "," +
			che +
			IntToHex( HSLaRGB( _hue + 0.01, _sat, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue + 0.02, _sat, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue + 0.03, _sat, _lum, _alp ), 8 ) + ","
	);

	this->Add(
		"Monocromáticos|3|" +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.15, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.10, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.05, _alp ), 8 ) + "," +
			che +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.05, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.10, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.15, _alp ), 8 ) + ","
	);

	this->Add(
		"Variación de Sombra|12|" +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.48, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.44, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.40, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.36, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.32, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.28, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.24, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.20, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.16, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.12, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.08, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum - 0.04, _alp ), 8 ) + "," +
			che
	);

	this->Add(
		"Variación de Color|12|" +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.48, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.44, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.40, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.36, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.32, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.28, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.24, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.20, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.16, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.12, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.08, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat, _lum + 0.04, _alp ), 8 ) + "," +
			che
	);

	this->Add(
		"Tonos de Color|12|" +
			IntToHex( HSLaRGB( _hue, _sat - 0.96, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.88, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.80, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.72, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.64, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.56, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.48, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.40, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.32, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.24, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.16, _lum, _alp ), 8 ) + "," +
			IntToHex( HSLaRGB( _hue, _sat - 0.08, _lum, _alp ), 8 ) + "," +
			che
	);

	this->ReadOnly = true;

	this->Render();
 };
//###########################################################################