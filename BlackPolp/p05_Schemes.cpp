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
#include "p05_Schemes.h"
#pragma package(smart_init)



// class pSchemes : public pPallets //#######################################
/*Creacion - public*/
__fastcall pSchemes::pSchemes( TComponent *owner ) : pPallets(owner) {
	this->ReadOnly = true;
 };
//###########################################################################


/*Metodos - private*/
void pSchemes::ChangeColor() {
	pPallets::ChangeColor();

	float
	th = _hue * 360.0;
	th+= th < 180.0 ? 180.0 : -180.0;
	th/= 360.0;

	String che = IntToHex( HSLaRGB( _hue, _sat, _lum, _alp ), 8 );

	this->ReadOnly = false;
	this->Clear();
	this->Add( "Complementarios|1|" + IntToHex( HSLaRGB( th         , _sat, _lum, _alp ), 8 ) + "," + che                                                                 );
	this->Add( "Análogos"     "|1|" + IntToHex( HSLaRGB( _hue - 0.08, _sat, _lum, _alp ), 8 ) + "," + che + "," + IntToHex( HSLaRGB( _hue + 0.08, _sat, _lum, _alp ), 8 ) );
	this->Add( "Divididos"    "|1|" + IntToHex( HSLaRGB( _hue - 0.42, _sat, _lum, _alp ), 8 ) + "," + che + "," + IntToHex( HSLaRGB( _hue + 0.42, _sat, _lum, _alp ), 8 ) );
	this->Add( "Triaticos"    "|1|" + IntToHex( HSLaRGB( _hue - 0.33, _sat, _lum, _alp ), 8 ) + "," + che + "," + IntToHex( HSLaRGB( _hue + 0.33, _sat, _lum, _alp ), 8 ) );
	this->Add( "Cuadraticos"  "|1|" + IntToHex( HSLaRGB( _hue - 0.17, _sat, _lum, _alp ), 8 ) + "," + che + "," + IntToHex( HSLaRGB( _hue + 0.33, _sat, _lum, _alp ), 8 ) + "," + IntToHex( HSLaRGB( _hue + 0.50, _sat, _lum, _alp ), 8 ) );
	this->ReadOnly = true;
	this->Render();
 };
//###########################################################################