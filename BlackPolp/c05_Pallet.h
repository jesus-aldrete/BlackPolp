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

#ifndef c05_PalletH
#define c05_PalletH

#include "def.h"
#include "c01_base.h"

class cPalette { public: String Title; sIField Colors; int Select; };

class cPallet : public cBase {
	/*Variables*/private:
	unsigned _colorSelect;
	bool     _dblclick;
	bool     _readOnly;

	/*Variables*/public:
	cPalette *Palette;

	/*Variables - controles*/private:
	TRectangle *_rback;
	TRectangle *_rclose;

	TLayout *_ltitle;
	fLine   *_ftitle;

	TLayout    *_lcolors;
	TRectangle *_rtransp;
	TRectangle *_rcolors[numberColors];

	TLayout    *_lselect;
	TRectangle *_rselect;

	TLayout *_linfo;
	TLayout *_lhex1; fLine *_fhex1;
	TLayout *_lhex2; fLine *_fhex2;
	TLayout *_lrgb1; fLine *_frgb1; TText *_trgb1;
	TLayout *_lrgb2; fLine *_frgb2; TText *_trgb2;
	TLayout *_lrgb3; fLine *_frgb3; TText *_trgb3;

	/*Variables - eventos*/public:
	gfEventSelect onClose;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateFHex( TLayout *parent, TLayout **lline, fLine **fline, float width  );
	void CreateFRGB( TLayout *parent, TLayout **lline, fLine **fline, String title );

	void CreateThis  ();
	void CreateTitle ();
	void CreateColors();
	void CreateSelect();
	void CreateInfo  ();

	/*Creacion*/public:
	__fastcall cPallet( TComponent *owner );
	//###########################################################################


	/*Propiedades*/private:
	void WReadOnly( bool readOnly );

	/*Propiedades*/public:
	__property bool ReadOnly = { read=_readOnly, write=WReadOnly };
	//###########################################################################


	/*Intervalos*/private:
	void __fastcall timer_stop( TObject *sender );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall resiz_this( TObject *sender                                                           );
	void __fastcall moudw_this( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall click_close( TObject *sender );
	void __fastcall mouen_close( TObject *sender );
	void __fastcall moule_close( TObject *sender );

	void __fastcall exitt_title( TObject *sender                                                           );
	void __fastcall keych_title( TObject *sender                                                           );
	void __fastcall moudw_title( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall moudw_color( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall exitt_info( TObject *sender                                                           );
	void __fastcall moudw_info( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();

	/*Metodos*/public:
	void   Render   ();
	String GetPallet();

	cPallet *Add   ( unsigned color            );
	cPallet *Insert( unsigned color, int index );
	cPallet *Delete( int      index            );
	//###########################################################################
 };

#endif