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

#ifndef c03_ColorsH
#define c03_ColorsH

#include "def.h"
#include "c01_Base.h"

class cColors : public cBase {
	/*Variables - controles*/private:
	TRectangle *_rback;

	TRectangle *_rcolor;
	TRectangle *_rcomplement;

	TLayout    *_lglass;
	TRectangle *_rglass;
	TImage     *_iglass;
	TPoint      _pglass;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateThis  ();
	void CreateColors();
	void CreateGlass ();

	/*Creacion*/public:
	__fastcall cColors( TComponent *owner );
	//###########################################################################


	/*Propiedades - Entradas*/private:
	void WGlass( TPoint glass );

	/*Propiedades*/public:
	__property TPoint Glass = { read=_pglass, write=WGlass };
	//###########################################################################


	/*Eventos*/private:
	void __fastcall moudw_rcolor( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();

	/*Metodos*/public:
	void ActiveGlass( bool active );

	void Drop( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	//###########################################################################
 };

#endif