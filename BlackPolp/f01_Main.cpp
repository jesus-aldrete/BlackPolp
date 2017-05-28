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

#include <fmx.h>
#pragma hdrstop
#include "f01_Main.h"
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource "_BlackPolp.res"

Tf01Main *f01Main;

//Otros #####################################################################
/*Definiciones*/
#define widthForm  315
#define heightForm 350
//###########################################################################


// class Tf01Main : public TForm ############################################
/*Creacion - private*/
void Tf01Main::CreatePanel( TLayout *parent, cBase *panel ) {
	panel->Parent  = parent;
	panel->Align   = AL::Contents;
	panel->Color   = colorHigh;
	panel->Visible = false;
 };

void Tf01Main::CreateThis  () {
	this->Width    = widthForm;
	this->Height   = heightForm;
	this->OnResize = resiz_this;

	_lback         = new TLayout( this );
	_lback->Parent = this;
	_lback->Align  = AL::Contents;
	MarG( _lback, 10 );

	_rback              = new TRectangle( this );
	_rback->Parent      = _lback;
	_rback->Align       = AL::Contents;
	_rback->StrK        = BK::None;
	_rback->FilC        = colorBlack;
	_rback->OnMouseDown = moudw_rback;
	_rback->OnDblClick  = dblcl_rback;

	_eshadow            = new TShadowEffect( this );
	_eshadow->Parent    = _rback;
	_eshadow->Direction = 0.001;
	_eshadow->Distance  = 0.001;
	_eshadow->Opacity   = 1;
	_eshadow->Softness  = 0.2;

	_cresize              = new TCircle( this );
	_cresize->Parent      = this;
	_cresize->Width       = 10;
	_cresize->Height      = 10;
	_cresize->FilC        = colorHigh;
	_cresize->StrC        = colorBlack;
	_cresize->PosY        = this->Height - _cresize->Height - 5;
	_cresize->PosX        = this->Width  - _cresize->Width  - 5;
	_cresize->Cursor      = crSizeNWSE;
	_cresize->OnMouseDown = moudw_cresize;
 };
void Tf01Main::CreateMenu  () {
	_cmenu               = new cMenu( this );
	_cmenu->Parent       = _lback;
	_cmenu->Align        = AL::MostLeft;
	_cmenu->Width        = 30;
	_cmenu->Color        = colorHigh;
	_cmenu->onStartColor = starc_cmenu;
	_cmenu->onChangColor = chanc_cmenu;
	_cmenu->onFinalColor = finac_cmenu;
	_cmenu->onClickPanel = panel_cmenu;
	_cmenu->onClickFiles = files_cmenu;
 };
void Tf01Main::CreateColors() {
	_ccolors               = new cColors( this );
	_ccolors->Parent       = _lback;
	_ccolors->Align        = AL::Client;
	_ccolors->Color        = colorHigh;
	_ccolors->onFinalColor = chaco_this;
 };
void Tf01Main::CreateEdit  () {
	_cedit               = new cEdit( this );
	_cedit->Parent       = _lback;
	_cedit->Height       = 70;
	_cedit->PosX         = _cmenu->Width;
	_cedit->Color        = colorHigh;
	_cedit->onChangColor = chaco_this;
 };
void Tf01Main::CreatePanels() {
	_lpanels          = new TLayout( this );
	_lpanels->Parent  = _lback;
	_lpanels->Height  = 100;
	_lpanels->PosX    = _cmenu->Width;

	_pedit    = new pEdit   ( this          ); CreatePanel( _lpanels, _pedit    ); _pedit->onChangColor = chaco_this; _pedit->onFinalColor = chaco_this;
	_ppallets = new pPallets( this          ); CreatePanel( _lpanels, _ppallets );
	_pinfo    = new pInfo   ( this          ); CreatePanel( _lpanels, _pinfo    );
	_pimage   = new pImage  ( this          ); CreatePanel( _lpanels, _pimage   );
	_pschemes = new pSchemes( this          ); CreatePanel( _lpanels, _pschemes );
	_ptones   = new pTones  ( this          ); CreatePanel( _lpanels, _ptones   );
	_padobe   = new pNet    ( this, "adobe" ); CreatePanel( _lpanels, _padobe   );
	_plover   = new pNet    ( this, "lover" ); CreatePanel( _lpanels, _plover   );
 };

/*Creacion - public*/
__fastcall Tf01Main::Tf01Main( TComponent *owner ) : TForm(owner) {
	_panel       = null;
	_file        = "";
	this->OnShow = showw_this;
 };
//###########################################################################


/*Eventos - private*/
void __fastcall Tf01Main::showw_this( TObject *sender                                                          ) {
	GetHandle( GetActiveWindow() );

	/*Inicio*/
	CreateThis  ();
	CreateMenu  ();
	CreateColors();
	CreateEdit  ();
	CreatePanels();

	this->Top  = ( Screen->WorkAreaHeight - this->Height ) / 2;
	this->Left = ( Screen->WorkAreaWidth  - this->Width  ) / 2;

	new wDragDrop( GetHandle(), dinit_this, dover_this, ddrop_this, (sfDrag)null );

	_cedit->BringToFront();
	this->resiz_this( this );

	/*Parametros*/
	if ( ParamCount() ) {
		if ( ExtractFileExt( ParamStr( 1 ) ).LowerCase() == ".ase" )
			OpenFile( ParamStr( 1 ) );
	}
 };
void __fastcall Tf01Main::resiz_this( TObject *sender                                                          ) {
	_cresize->PosY = this->Height - _cresize->Height - 5;
	_cresize->PosX = this->Width  - _cresize->Width  - 5;

	if ( _cedit ) {
		if ( _cedit->Tag == 0 )
			_cedit->PosY = ( _rback->Height - _cedit->Height ) / 2;
			// _cedit->PosY = 50;

		_cedit->Width = _rback->Width - _cmenu->Width;

		if ( _lpanels ) {
			_lpanels->PosY   = _cedit->PosY + _cedit->Height - 1;
			_lpanels->Height = _rback->Height - _lpanels->PosY;
			_lpanels->Width  = _cedit->Width;
		}
	}

	if ( _pedit && _pedit->Visible )
		_pedit->Color = _ccolors->Color;
 };
void __fastcall Tf01Main::chaco_this( TObject *sender, geColorType type, double color, TPoint position         ) {
	#define chaColt(x,y) \
		_cmenu   ->x = y;\
		_ccolors ->x = y;\
		_cedit   ->x = y;\
		if ( _pedit   ->Visible ) _pedit   ->x = y;\
		if ( _ppallets->Visible ) _ppallets->x = y;\
		if ( _pinfo   ->Visible ) _pinfo   ->x = y;\
		if ( _pimage  ->Visible ) _pimage  ->x = y;\
		if ( _pschemes->Visible ) _pschemes->x = y;\
		if ( _ptones  ->Visible ) _ptones  ->x = y;\
		if ( _padobe  ->Visible ) _padobe  ->x = y;\
		if ( _plover  ->Visible ) _plover  ->x = y;

	if      ( type == ctRGB ) color = ACOL( 255, RRGB( (unsigned)color ), GRGB( (unsigned)color ), BRGB( (unsigned)color ) );
	else if ( type == ctBGR ) color = ACOL( 255, BRGB( (unsigned)color ), GRGB( (unsigned)color ), RRGB( (unsigned)color ) );

	if      ( type == ctRGBA || type == ctRGB || type == ctBGR ) { chaColt( Color, color ); }
	else if ( type == ctRed                                    ) { chaColt( Red  , color ); }
	else if ( type == ctGreen                                  ) { chaColt( Green, color ); }
	else if ( type == ctBlue                                   ) { chaColt( Blue , color ); }
	else if ( type == ctAlpha                                  ) { chaColt( Alpha, color ); }
	else if ( type == ctHue                                    ) { chaColt( Hue  , color ); }
	else if ( type == ctSat                                    ) { chaColt( Sat  , color ); }
	else if ( type == ctLum                                    ) { chaColt( Lum  , color ); }
	else if ( type == ctAlp                                    ) { chaColt( Alp  , color ); }

	_cresize->FilC = _cmenu->PreserveColor;
 };
void __fastcall Tf01Main::dinit_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	_dragColor = IsColor ( texts[0] );
	_dragPalle = IsPallet( texts[0] );
	_dragImage = IsImages( files    ) > -1;
	_dragFiles = IsFiles ( files    ) > -1;
	accept     = _dragPalle || _dragColor || _dragImage || _dragFiles;
 };
void __fastcall Tf01Main::dover_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	if ( !_dragColor && !_dragPalle && !_dragImage && !_dragFiles ) {
		accept = false;
		return;
	}

	if ( _dragFiles || _dragImage ) effects = DROPEFFECT_COPY;
	if ( _dragFiles               ) { accept = true; return; }

	IControl   *con = ObjectAtPoint( TPoint( point.x, point.y ) );
	TFmxObject *obj = con ? con->GetObjectW() : NULL;

	accept = obj && obj->TagFloat > dzNone;

	if ( accept ) {
		if ( obj->TagFloat == dzCPalletColor ) {
			TRectangle *rec = (TRectangle*)obj;
			cPallet    *pal = (cPallet   *)rec->TagObject;

			accept = pal->Palette->Colors.Size < numberColors;
		}
		else if ( _dragImage ) accept = obj->TagFloat == dzCImage  || obj->TagFloat == dzCMenu;
		else if ( _dragPalle ) accept = obj->TagFloat == dzCMenu   || obj->TagFloat == dzCPallet || obj->TagFloat == dzCPallets;
		else if ( _dragColor ) accept = obj->TagFloat != dzCPallet && obj->TagFloat != dzCImage;
	}
 };
void __fastcall Tf01Main::ddrop_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	accept = true;

	if ( !_dragColor && !_dragPalle && !_dragImage && !_dragFiles ) {
		accept = false;
		return;
	}

	if ( _dragFiles ) {
		int ind = IsFiles( files );

		OpenFile( files[ind] );
		return;
	}

	IControl   *con = ObjectAtPoint( TPoint( point.x, point.y ) );
	TFmxObject *obj = con ? con->GetObjectW() : NULL;

	if ( obj ) {
		if      ( obj->TagFloat == dzCColors ) _ccolors->Drop( texts, files, point, effects, accept );
		else if ( obj->TagFloat == dzCImage  ) _pimage ->Drop( texts, files, point, effects, accept );
		else if (
			obj->TagFloat == dzCMenu        ||
			obj->TagFloat == dzCPallet      ||
			obj->TagFloat == dzCPallets     ||
			obj->TagFloat == dzCPalletColor
		) {
			if ( _dragImage ) _pimage  ->Drop( texts, files, point, effects, accept );
			else              _ppallets->Drop( texts, files, point, effects, accept );
		}
	}
 };

void __fastcall Tf01Main::starc_cmenu( TObject *sender, geColorType type, double color, TPoint position ) {
	AnimO( (TShape*)_cmenu  , 0.3, 0, sfExponentialOut );
	AnimO(          _rback  , 0.3, 0, sfExponentialOut );
	AnimO( (TShape*)_panel  , 0.3, 0, sfExponentialOut );
	AnimO(          _cresize, 0.3, 0, sfExponentialOut );
 };
void __fastcall Tf01Main::chanc_cmenu( TObject *sender, geColorType type, double color, TPoint position ) {
	 _ccolors->Color = color   ;
	 _cedit  ->Color = color   ;
	 _ccolors->Glass = position;
 };
void __fastcall Tf01Main::finac_cmenu( TObject *sender, geColorType type, double color, TPoint position ) {
	 chaco_this( sender, type, color, position );

	 _ccolors->Glass = TPoint(snan,0);

	 AnimO( _panel  , 0.3, 1, sfExponentialOut );
	 AnimO( _cmenu  , 0.3, 1, sfExponentialOut );
	 AnimO( _rback  , 0.3, 1, sfExponentialOut );
	 AnimO( _cresize, 0.3, 1, sfExponentialOut );
 };
void __fastcall Tf01Main::panel_cmenu( TObject *sender                                                  ) {
	TLayout *lay = (TLayout*)sender;

	if      ( lay->TagString == "_lpEdit"    ) ShowPanel( _pedit    );
	else if ( lay->TagString == "_lpPallets" ) ShowPanel( _ppallets );
	else if ( lay->TagString == "_lpInfo"    ) ShowPanel( _pinfo    );
	else if ( lay->TagString == "_lpImage"   ) ShowPanel( _pimage   );
	else if ( lay->TagString == "_lpSchemes" ) ShowPanel( _pschemes );
	else if ( lay->TagString == "_lpTones"   ) ShowPanel( _ptones   );
	else if ( lay->TagString == "_lpAdobe"   ) ShowPanel( _padobe   );
	else if ( lay->TagString == "_lpLover"   ) ShowPanel( _plover   );
 };
void __fastcall Tf01Main::files_cmenu( TObject *sender                                                  ) {
	TLayout *lay = (TLayout*)sender;
	wDialog *dig = new wDialog;

	if ( lay->TagString == "_lopen" ) {
		dig->Filter = "*.ase|Adobe Swatch Exchange";
		dig->Index  = 1;

		if ( dig->RunOP() )
			OpenFile( dig->Path );
	}
	else if ( lay->TagString == "_lsave" ) {
		if ( _file == "" ) goto SALTO1;
		else               SaveFile( _file );
	}
	else if ( lay->TagString == "_lSaveAs" ) {
		/**/SALTO1:/**/
		dig->Filter = "*.ase|Adobe Swatch Exchange";
		dig->Index  = 1;

		if ( dig->RunSA() )
			SaveFile( dig->Path );
	}

	delete dig;
 };

void __fastcall Tf01Main::dblcl_rback  ( TObject *sender                                                           ) {
	_eshadow->Enabled = !_eshadow->Enabled;
 };
void __fastcall Tf01Main::moudw_rback  ( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	SendMessage( GetHandle(), WM_LBUTTONUP    , 0        , 0 );
	SendMessage( GetHandle(), WM_NCLBUTTONDOWN, HTCAPTION, 0 );
 };
void __fastcall Tf01Main::moudw_cresize( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	ChangeCursor( LoadCursor( null, IDC_SIZENWSE ) );

	varPom;
	float px1 = pom.x - fom.left - x, py1 = pom.y - fom.top  - y;
	float px2, py2;
	float wid = fom.Width(), hei = fom.Height();
	HWND  han = GetHandle();

	while ( whileDown ) {
		GetCursorPos( &pom );

		px2 = wid + ( pom.x - fom.left - x - px1 ); if ( px2 < widthForm  ) px2 = widthForm ;
		py2 = hei + ( pom.y - fom.top  - y - py1 ); if ( py2 < heightForm ) py2 = heightForm;

		SetWindowPos( han, null, 0, 0, px2, py2, SWP_NOOWNERZORDER | SWP_NOMOVE );

		Application->ProcessMessages();
	}

	RestoreCursor();
 };

void __fastcall Tf01Main::frain_panels( fAnim *sender ) {
	if ( sender->Percent >= sender->Max ) {
		sender->Final();

		_cedit  ->PosY    = 100;
		_lpanels->PosY    = _cedit->PosY + _cedit->Height - 1;
		_lpanels->Height  = _rback->Height - _lpanels->PosY;
		_panel  ->Opacity = 1;
	}
	else {
		double ini = ( _rback->Height - _cedit->Height ) / 2;

		_cedit  ->PosY    = sfSinusoidalOut( sender->Percent, ini, 100 - ini, sender->Max );
		_lpanels->PosY    = _cedit->PosY + _cedit->Height - 1;
		_lpanels->Height  = _rback->Height - _lpanels->PosY;
		_panel  ->Opacity = sfSinusoidalOut( sender->Percent, 0, 1, sender->Max );
	}
 };
void __fastcall Tf01Main::fraou_panels( fAnim *sender ) {
	if ( sender->Percent >= sender->Max ) {
		sender->Final();

		_panel->Visible = false;
		_panel          = null;

		_cedit  ->Tag    = 0;
		_cedit  ->PosY   = ( _rback->Height - _cedit->Height ) / 2;
		_lpanels->PosY   = _cedit->PosY + _cedit->Height - 1;
		_lpanels->Height = _rback->Height - _lpanels->PosY;
	}
	else {
		double fin = ( _rback->Height - _cedit->Height ) / 2;

		_cedit  ->PosY    = sfSinusoidalOut( sender->Percent, 100, fin - 100, sender->Max );
		_lpanels->PosY    = _cedit->PosY + _cedit->Height - 1;
		_lpanels->Height  = _rback->Height - _lpanels->PosY;
		_panel  ->Opacity = sfSinusoidalOut( sender->Percent, 1, -1, sender->Max );
	}
 };
void __fastcall Tf01Main::anifi_panels( fAnim *sender ) {
	sender->parent->Visible = false;
 };
//###########################################################################


/*Funciones - private*/
void Tf01Main::ShowPanel( cBase *panel ) {
	if ( _panel == null ) {
		_cedit  ->Tag     = 1;
		 panel  ->Opacity = 0;
		 panel  ->Visible = true;
		_panel            = panel;

		panel->ChangeHSLA( _ccolors->Hue, _ccolors->Sat, _ccolors->Lum, _ccolors->Alp );

		AnimC( 0.5, frain_panels );
	}
	else if ( _panel != panel ) {
		panel->Opacity = 1;
		panel->Visible = true;
		panel->SendToBack();

		panel->ChangeHSLA( _ccolors->Hue, _ccolors->Sat, _ccolors->Lum, _ccolors->Alp );

		fAnim::Opacity( (TShape*)_panel, (String)(int)_panel, 0.3, 0, sfCircularOut, anifi_panels );

		_panel = panel;
	}
	else if ( _panel == panel ) AnimC( 0.5, fraou_panels );
 };

void Tf01Main::SaveFile  ( String file ) {
	_file = file;

	unsigned cl ;
	sIField  pa = _ppallets->Palettes;
	wStream *st = new wStream;
	wStream *s1 = new wStream;

	//Encabezado
	cl = 0;                                                   //
	for ( int i = 0; i < pa.Size; i++ )                       //
		cl += ((cPalette*)pa[i].Value)->Colors.Size;          //->Numero Total de colore
															  //
	st->Int( 0x41534546           );                          //->Tipo de Archivo "ASEF"
	st->I16( 1                    );                          //->Vercion 1|
	st->I16( 0                    );                          //->Vercion 0|->1.0
	st->Int( cl + ( pa.Size * 2 ) );                          //->Numero de Bloques
															  //
															  //
	for ( int i = 0; i < pa.Size; i++ ) {                     //
		cPalette *pl = (cPalette*)pa[i].Value;                //
															  //
		//Bloque - grupo                                   	  //
		st->I16( 0xC001 );                                 	  //-> Inicio de Grupo (0xc001 -> Group start, 0xc002 -> Group end, 0x0001 -> Color entry, 0x0002 -> Data App)
															  //
															  //
		s1->Clear();                                       	  //-> INICIO DEL GRUPO
		s1->Sun( pl->Title );                                 //   Titulo
		s1->Position = 0;                                     //
		st->Int( s1->Size );                                  //   Tamaño del titulo
		st->Copy( s1, s1->Size );                             //   Copiado del titulo
															  //
															  //
		for ( int ii = 0; ii < pl->Colors.Size; ii++ ) {      //-> INICIO DE LOS COLORES
			st->I16( 0x00001 );                            	  //   inicio del color
			s1->Clear();            	                   	  //
			cl = pl->Colors[ ii ].Value;                      //   cargando color
			s1->Sun( RGBaHEX( cl ) );                      	  //   titulo de color
			s1->Int( 0x52474220 );                         	  //   indicacion de tipo de color RGB
			s1->Flo( float(RRGB( cl )) / 255.f );             //   guardando valor de RED
			s1->Flo( float(GRGB( cl )) / 255.f );             //   guardando valor de GREEN
			s1->Flo( float(BRGB( cl )) / 255.f );             //   guardando valor de BLUE
			s1->I16( 0 );                                     //
			s1->Position = 0;                                 //
			st->Int( s1->Size );                              //   copiado del color
			st->Copy( s1, s1->Size );                         //
		}                                                     //
                                                              //
                                                              //
		st->I16( 0xC002 );                                    //-> FIN DEL GRUPO
		st->Int( 0 );                                         //
	}                                                         //
															  //
	SaveFileBP( st );                                         //-> Bloque - BlackPolp
	st->Save( file );

	delete st;
	delete s1;
 };
void Tf01Main::SaveFileBP( wStream *st ) {
	if ( !st ) return;

	sIField  paf = _ppallets->Palettes;
	wStream *mem = new wStream;

	mem->Int( _ccolors->Color );
	mem->Int( this->Width     );
	mem->Int( this->Height    );
	mem->Int( paf.Size        );

	for ( int i = 0; i < paf.Size; i++ ) {
		/*Giant Goldfish|0|FF69D2E7,FFA7DBD8,FFE0E4CC,FFF38630,FFFA6900,*/
		cPalette *pal = (cPalette*)paf[i].Value;
		String    cad = pal->Title + "|" + pal->Select + "|";

		for ( int ii = 0; ii < pal->Colors.Size; ii++ )
			cad+= IntToHex( (int)pal->Colors[ii].Value, 8 ) + ",";

		mem->Str( cad );
	}

	mem->Int( st->Position );

	mem->Position = 0;

	st->Copy( mem, mem->Size );

	delete mem;
 };
void Tf01Main::OpenFile  ( String file ) {
	if ( !FileExists( file ) ) return;

	wStream *st = new wStream( file );

	if ( st->Int() != 0x41534546 || st->I16() != 1 || st->I16() != 0 ) {
		delete st;
		return;
	}

	_file = file;

	_ppallets->Clear();

	st->Position = st->Size - 4;

	if ( st->Int() != 0 ) OpenFileBP( st );
	else                  OpenFileAS( st );

	_ppallets->Render();

	delete st;
 };
void Tf01Main::OpenFileAS( wStream *st ) {
	if ( !st ) return;

	__int16 n1;
	__int32 n2;
	sSField ft;
	sIField fc;

	for ( st->Position = 12; st->Position < st->Size; ) {
		n1 = st->I16();

		if ( n1 == (__int16)0xC001 ) {
			st->Position += 4;
			ft+= st->Sun();
			fc+= -1;
		}
		else if ( n1 == (__int16)0x0001 ) {
			st->Position += 4;
			st->Sun();

			if ( st->Int() == 0x52474220 ) {
				n2 = st->Int(); float c1 = (*(float*)&n2) * 255.f;
				n2 = st->Int(); float c2 = (*(float*)&n2) * 255.f;
				n2 = st->Int(); float c3 = (*(float*)&n2) * 255.f;

				fc+= ACOL( 255, c1, c2, c3 );

				st->Position+= 2;
			}
		}
	}

	_ppallets->Add( ft, fc );
 };
void Tf01Main::OpenFileBP( wStream *st ) {
	if ( !st ) return;

	st->Position = st->Size - 4;
	st->Position = st->Int();

	chaco_this( null, ctRGBA, st->Int(), TPoint(0,0) );

	this->Width  = st->Int();
	this->Height = st->Int();

	if ( this->Width  < 340 ) this->Width  = 340;
	if ( this->Height < 355 ) this->Height = 355;

	int siz = st->Int();

	for ( int x = 0; x < siz; x++ )
		_ppallets->Add( st->Str() );
 };
//###########################################################################