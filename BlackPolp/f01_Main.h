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

#ifndef f01_MainH
#define f01_MainH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>

#include "def.h"
#include "c01_Base.h"
#include "c02_Menu.h"
#include "c03_Colors.h"
#include "c04_Edit.h"
#include "c05_Pallet.h"
#include "p01_Edit.h"
#include "p02_Pallets.h"
#include "p03_Info.h"
#include "p04_Image.h"
#include "p05_Schemes.h"
#include "p06_Tones.h"
#include "p07_Net.h"

class Tf01Main : public TForm {__published:/**/
	/*Variables*/private:
	bool _dragColor;
	bool _dragPalle;
	bool _dragImage;
	bool _dragFiles;

	String _file;

	/*Variables - Controles*/private:
	TLayout       *_lback  ;
	TRectangle    *_rback  ;
	TShadowEffect *_eshadow;
	TCircle       *_cresize;

	cMenu   *_cmenu;
	cColors *_ccolors;
	cEdit   *_cedit;

	TLayout  *_lpanels;
	cBase    *_panel;
	pEdit    *_pedit;
	pPallets *_ppallets;
	pInfo    *_pinfo;
	pImage   *_pimage;
	pSchemes *_pschemes;
	pTones   *_ptones;
	pNet     *_padobe;
	pNet     *_plover;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreatePanel( TLayout *parent, cBase *panel );

	void CreateThis  ();
	void CreateMenu  ();
	void CreateColors();
	void CreateEdit  ();
	void CreatePanels();

	/*Creacion*/public:
	__fastcall Tf01Main( TComponent *owner );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall showw_this( TObject *sender                                                          );
	void __fastcall resiz_this( TObject *sender                                                          );
	void __fastcall chaco_this( TObject *sender, geColorType type, double color, TPoint position         );
	void __fastcall dinit_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	void __fastcall dover_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	void __fastcall ddrop_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );

	void __fastcall starc_cmenu( TObject *sender, geColorType type, double color, TPoint position );
	void __fastcall chanc_cmenu( TObject *sender, geColorType type, double color, TPoint position );
	void __fastcall finac_cmenu( TObject *sender, geColorType type, double color, TPoint position );
	void __fastcall panel_cmenu( TObject *sender                                                  );
	void __fastcall files_cmenu( TObject *sender                                                  );

	void __fastcall dblcl_rback  ( TObject *sender                                                           );
	void __fastcall moudw_rback  ( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall moudw_cresize( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall anifi_panels( fAnim *sender );
	void __fastcall frain_panels( fAnim *sender );
	void __fastcall fraou_panels( fAnim *sender );
	//###########################################################################


	/*Funciones*/private:
	void ShowPanel( cBase *panel );

	void SaveFile  ( String file );
	void SaveFileBP( wStream *st );
	void OpenFile  ( String file );
	void OpenFileAS( wStream *st );
	void OpenFileBP( wStream *st );
	//###########################################################################
 };

extern PACKAGE Tf01Main *f01Main;
#endif
