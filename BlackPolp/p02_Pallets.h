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

#ifndef p02_PalletsH
#define p02_PalletsH

#include "def.h"
#include "c01_base.h"
#include "c05_pallet.h"

class pPallets : public cBase {
	/*Variables*/protected:
	float _position;
	float _heightView;
	float _numberView;

	bool _readOnly;

	/*Variables*/public:
	sIField Palettes;

	/*Variables - controls*/protected:
	TRectangle *_rback;
	TLayout    *_lback;

	TRectangle *_rdrop;
	TPath      *_pdrop;
	TText      *_tdrop;

	TLayout    *_lpallets;
	sIField     _ppallets;
	TRectangle *_rscroll;
	//###########################################################################


	/*Creacion - controls*/protected:
	void CreateThis   ();
	void CreateDrop   ();
	void CreatePallets();

	/*Creacion*/public:
	__fastcall pPallets( TComponent *owner );
	//###########################################################################


	/*Propiedades*/private:
	void WReadOnly( bool readOnly );

	/*Propiedades*/public:
    __property bool ReadOnly = { read=_readOnly, write=WReadOnly };
	//###########################################################################


	/*Intervalos*/protected:
	void __fastcall timer_scroll( TObject *sender );
	//###########################################################################


	/*Eventos*/protected:
	void __fastcall resiz_this( TObject *sender                                                   );
	void __fastcall mouwh_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled );

	void __fastcall click_close( TObject *sender, int index );
	//###########################################################################


	/*Metodos*/protected:
	void ChangeColor();

	/*Metodos*/public:
	pPallets *Add   ( unsigned color                 );
	pPallets *Add   ( String palette                 );
	pPallets *Add   ( sSField titles, sIField colors );
	pPallets *Insert( String palette, int index      );
	pPallets *Delete(                 int index      );
	pPallets *Clear (                                );

	void Drop      ( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	void DropColor ( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	void DropPallet( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );

	void Render();
	//###########################################################################


	/*Metodos*/protected:
	cPalette *GetPalette( String palette );
	//###########################################################################
 };

#endif