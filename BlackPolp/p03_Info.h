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

#ifndef p03_InfoH
#define p03_InfoH

#include "def.h"
#include "c01_base.h"

class pInfo : public cBase {
	/*Variables - controles*/private:
	TRectangle *_rback;

	TLayout *_lrgbp; TText *_trgbp; fLine *_frgbp;
	TLayout *_lcmyk; TText *_tcmyk; fLine *_fcmyk;
	TLayout *_lhsla; TText *_thsla; fLine *_fhsla;
	TLayout *_lhsva; TText *_thsva; fLine *_fhsva;
	TLayout *_llaba; TText *_tlaba; fLine *_flaba;
	TLayout *_lxyza; TText *_txyza; fLine *_fxyza;
	TLayout *_lxyya; TText *_txyya; fLine *_fxyya;
	TLayout *_lhlab; TText *_thlab; fLine *_fhlab;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateEdit( TLayout **lparent, TText **ttitle, fLine **fvalue, String title );

	void CreateThis ();
	void CreateLines();

	/*Creacion*/public:
	__fastcall pInfo( TComponent *owner );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();
	//###########################################################################
 };

#endif