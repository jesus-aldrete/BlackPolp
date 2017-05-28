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

#ifndef p07_NetH
#define p07_NetH

#include "def.h"
#include "p02_pallets.h"

class pNet : public pPallets {
	/*Variables*/private:
	bool _adobe;

	wThread *_thread;
	fLoader *_loader;

	/*Variables - controles*/private:
	TLayout *_ledit;

	TLayout *_lnpp;
	TText   *_tnpp;
	fLine   *_fnpp;

	TLayout    *_lbuttons;
	TRectangle *_rselect ;
	TText      *_tnew;
	TText      *_ttop;
	TText      *_tpop;
	TText      *_trec;
	TText      *_tcla;
	TText      *_tran;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateButton( TText **butext, TLayout *parent, float width, String title, String id );

	void CreateThis   ();
	void CreateNPP    ();
	void CreateButtons();

	/*Creacion*/public:
	__fastcall pNet( TComponent *owner, String type );
	//###########################################################################


	/*Hilos*/
	void __fastcall thini_net( wThread *thread );
	void __fastcall thfin_net( wThread *thread );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall click_button( TObject *sender );
	void __fastcall showl_loader( TObject *sender );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();

	void QueryNet( String url      );
	void GetAdobe( wThread *thread );
	void GetLover( wThread *thread );
	//###########################################################################
 };

#endif