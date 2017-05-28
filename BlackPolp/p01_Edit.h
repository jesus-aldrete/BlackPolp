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

#ifndef p01_EditH
#define p01_EditH

#include "def.h"
#include "c01_base.h"

class pEdit : public cBase {
	/*Variables - controles*/private:
	TRectangle *_rback;

	TLayout    *_lhue;
	TRectangle *_rhue;
	TRectangle *_phue;

	TLayout    *_lsat;
	TRectangle *_rsat;
	TRectangle *_psat;

	TLayout    *_llum;
	TRectangle *_rlum;
	TRectangle *_plum;

	TLayout    *_lalp;
	TRectangle *_ralp;
	TRectangle *_palp;
	TRectangle *_talp;
	//###########################################################################


	/*Creacion - controles*/public:
	void CreateSample( TLayout **parent, TRectangle **rcolor, TRectangle **pcolor, String title );

	void CreateThis();
	void CreateHue ();
	void CreateSat ();
	void CreateLum ();
	void CreateAlp ();

	/*Creacion*/public:
	__fastcall pEdit( TComponent *owner );
	//###########################################################################


	/*Eventos - Muestras*/private:
	void __fastcall moudw_samplb( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall moudw_sample( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall mouwh_sample( TObject *sender, TShiftState shift, int wheelDelta, bool &handled         );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();

	/*Funciones*/private:
	void ChangeControls( unsigned color );
	//###########################################################################
 };

#endif