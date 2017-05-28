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

#ifndef c02_MenuH
#define c02_MenuH

#include "def.h"
#include "c01_Base.h"

class cMenu : public cBase {
	/*Variables - controles*/private:
	TLayout *_system   ;
	TLayout *_lclose   ;
	TLayout *_lminimize;
	TLayout *_lpin     ;

	TLayout *_panels   ;
	TLayout *_lgout    ;
	TLayout *_lpEdit   ;
	TLayout *_lpPallets;
	TLayout *_lpInfo   ;
	TLayout *_lpImage  ;
	TLayout *_lpSchemes;
	TLayout *_lpTones  ;
	TLayout *_lpAdobe  ;
	TLayout *_lpLover  ;

	TLayout *_file    ;
	TLayout *_lopen   ;
	TLayout *_lsave   ;
	TLayout *_lsaveAs ;
	TLayout *_lgarbage;

	/*Variables - Eventos*/public:
	TNotifyEvent onClickPanel;
	TNotifyEvent onClickFiles;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateButton( TLayout *parent, TLayout **button, TNotifyEvent onclick, String id, String data );

	void CreateThis  ();
	void CreateSystem();
	void CreatePanels();
	void CreateFiles ();

	/*Creacion*/public:
	__fastcall cMenu( TComponent *owner );
	//###########################################################################


	/*Intervalos*/private:
	void __fastcall highh_save  ( TObject *sender );
	void __fastcall highh_saveAs( TObject *sender );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall mouen_this( TObject *sender );
	void __fastcall moule_this( TObject *sender );

	void __fastcall click_lclose   ( TObject *sender );
	void __fastcall click_lminimize( TObject *sender );
	void __fastcall click_lpin     ( TObject *sender );

	void __fastcall moudw_lgout( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall click_panel( TObject *sender );
	void __fastcall click_files( TObject *sender );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();
	//###########################################################################


	/*Funciones*/private:
	void ColorButton( TLayout *layout, bool buttonBlack );
	//###########################################################################
 };

#endif
