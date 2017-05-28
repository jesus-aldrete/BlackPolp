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
#include "c02_Menu.h"
#pragma package(smart_init)

// class cMenu : public cBase //#############################################
/*Creacion - controles - private*/
void cMenu::CreateButton( TLayout *parent, TLayout **button, TNotifyEvent onclick, String id, String data ) {
	(*button)               = new TLayout( this );
	(*button)->Parent       = parent;
	(*button)->PosY         = parent->Height + 1000;
	(*button)->Align        = AL::Top;
	(*button)->Height       = 18;
	(*button)->HitTest      = true;
	(*button)->TagString    = id;
	(*button)->OnClick      = onclick;
	(*button)->TagFloat     = dzCMenu;
	(*button)->OnMouseEnter = mouen_this;
	(*button)->OnMouseLeave = moule_this;

	TRectangle *
	rec          = new TRectangle( this );
	rec->Parent  = (*button);
	rec->Align   = AL::Contents;
	rec->StrK    = BK::None;
	rec->FilC    = colorBlack;
	rec->HitTest = false;

	TPath *
	pat             = new TPath( this );
	pat->Parent     = (*button);
	pat->Align      = AL::Center;
	pat->Height     = 13;
	pat->Width      = 13;
	pat->StrK       = BK::None;
	pat->FilC       = colorGray3;
	pat->HitTest    = false;
	pat->Data->Data = data;

	pat      ->TagObject = rec;
	(*button)->TagObject = pat;
 };

void cMenu::CreateThis  () {
	this->CanFocus = true;
 };
void cMenu::CreateSystem() {
	_system         = new TLayout( this );
	_system->Parent = this;
	_system->Align  = AL::Top;
	_system->MarT   = 5;

	CreateButton( _system, &_lclose   , click_lclose   , "_lclose"   , "M15,2.1 12.9,0 7.5,5.4 2.1,0 0,2.1 5.4,7.5 0,12.9 2.1,15 7.5,9.6 12.9,15 15,12.9 9.6,7.5z M0,0 M15,15" );
	CreateButton( _system, &_lminimize, click_lminimize, "_lminimize", "M0,6.3 15,6.3 15,8.8 0,8.8z M0,0 M15,15" );
	CreateButton( _system, &_lpin     , click_lpin     , "_lpin"     , "M9,8.9 9,3.1 6,3.1 6,8.9 0,8.9 0,11.9 15,11.9 15,8.9z M0,0 M15,15" );

	_system->Height = 18 * 3;
 };
void cMenu::CreatePanels() {
	_panels         = new TLayout( this );
	_panels->Parent = this;
	_panels->Align  = AL::VertCenter;

	CreateButton( _panels, &_lgout    , null       , "_lgout"    , "M15,0 7,0 7,5.2 0,12.2 2.8,15 9.8,8 15,8z M0,0 M15,15" );
	CreateButton( _panels, &_lpEdit   , click_panel, "_lpEdit"   , "M15,5.8 11.9,5.8 11.9,2.8 8.5,2.8 8.5,5.8 0,5.8 0,9.2 8.5,9.2 8.5,12.2 11.9,12.2 11.9,9.2 15,9.2z M0,0 M15,15" );
	CreateButton( _panels, &_lpPallets, click_panel, "_lpPallets", "M7.5,1.8c-4.1,0-7.5,2.6-7.5,5.7c0,0.4-0.3,0.7,0.2,1.2s1.6-0.9,1.6-0.9 c0.8-0.6,2.2-0.1,2.9,0.7l0,0c0.6,0.8,0.8,2.3,0,2.9c0,0-1.5,0.5-0.9,1.1c0.6,0.5,2.4,0.8,3.8,0.8c4.1,0,7.5-2.6,7.5-5.7 S11.7,1.8,7.5,1.8z M8.4,2.5c0.6,0,1.1,0.5,1.1,1.1S9,4.6,8.4,4.6S7.4,4.1,7.4,3.5S7.8,2.5,8.4,2.5z M4.4,3.5c0-0.6,0.5-1.1,1.1-1.1 s1.1,0.5,1.1,1.1S6,4.6,5.4,4.6S4.4,4.1,4.4,3.5z M8,12c-1,0-1.9-0.5-1.9-1.1C6.2,10.4,7,9.9,8,9.9c1,0,1.9,0.5,1.9,1.1 C9.9,11.5,9.1,12,8,12z M10.3,4.6c0-0.6,0.5-1.1,1.1-1.1s1.1,0.5,1.1,1.1c0,0.6-0.5,1.1-1.1,1.1S10.3,5.1,10.3,4.6z M13,8.3 c-0.6,0-1.1-0.5-1.1-1.1s0.5-1.1,1.1-1.1s1.1,0.5,1.1,1.1S13.6,8.3,13,8.3z M0,0 M15,15" );
	CreateButton( _panels, &_lpInfo   , click_panel, "_lpInfo"   , "M7.5,0C3.4,0,0,3.4,0,7.5S3.4,15,7.5,15S15,11.6,15,7.5S11.6,0,7.5,0z M7.5,14.2 c-3.7,0-6.7-3-6.7-6.7s3-6.7,6.7-6.7s6.7,3,6.7,6.7S11.2,14.2,7.5,14.2z M9,3.2c0,0.5-0.6,1-1.5,1C6.6,4.1,6,3.7,6,3.2c0-0.6,0.6-1,1.5-1C8.4,2.2,9,2.6,9,3.2z M6.3,12.8l0.3-7.4h1.7l0.4,7.4H6.3z M0,0 M15,15" );
	CreateButton( _panels, &_lpImage  , click_panel, "_lpImage"  , "M0,0 M15,15 M1.1,14 14.8,14 9.3,6.6 6.6,11.2 3.8,8.5 0.2,14 z M2.1,2.7A2.1,2 0 0,0 2.1,6.7A2.1,2 0 0,0 2.1,2.7z" );
	CreateButton( _panels, &_lpSchemes, click_panel, "_lpSchemes", "M0,0 4.4,0 4.4,4.4 0,4.4z M5.3,0 9.7,0 9.7,4.4 5.3,4.4z M10.6,0 15,0 15,4.4 10.6,4.4z M0,5.3 4.4,5.3 4.4,9.7 0,9.7z M5.3,5.3 9.7,5.3 9.7,9.7 5.3,9.7z M10.6,5.3 15,5.3 15,9.7 10.6,9.7z M0,10.6 4.4,10.6 4.4,15 0,15z M5.3,10.6 9.7,10.6 9.7,15 5.3,15z M10.6,10.6 15,10.6 15,15 10.6,15z M0,0 M15,15" );
	CreateButton( _panels, &_lpTones  , click_panel, "_lpTones"  , "M0.1,0 4.5,0 4.5,4.4 0.1,4.4z M5.8,0.4 9.4,0.4 9.4,4 5.8,4z M11.6,0.9 14.2,0.9 14.2,3.5 11.6,3.5z M0.1,5.3 4.5,5.3 4.5,9.7 0.1,9.7z M5.8,5.7 9.4,5.7 9.4,9.3 5.8,9.3z M11.6,6.2 14.2,6.2 14.2,8.8 11.6,8.8z M0.1,10.6 4.5,10.6 4.5,15 0.1,15z M5.8,11 9.4,11 9.4,14.6 5.8,14.6z M11.6,11.5 14.2,11.5 14.2,14.1 11.6,14.1z M0,0 M15,15" );
	CreateButton( _panels, &_lpAdobe  , click_panel, "_lpAdobe"  , "M9,5.6L7.7,6.8C7.8,7,7.9,7.2,7.9,7.4c0,0.3-0.1,0.5-0.2,0.7l1.2,1.2c0.4-0.5,0.7-1.2,0.7-2 C9.6,6.7,9.3,6.1,9,5.6z M6.3,9C5.5,9,4.8,8.3,4.8,7.4c0-0.9,0.7-1.5,1.5-1.5c0.3,0,0.5,0.1,0.7,0.2l1.2-1.2 c-0.5-0.4-1.2-0.7-2-0.7c-1.8,0-3.2,1.4-3.2,3.2c0,1.8,1.4,3.2,3.2,3.2c0.7,0,1.4-0.2,1.9-0.6L7,8.8C6.8,8.9,6.6,9,6.3,9z M11.6,10.5C11.6,10.5,11.6,10.5,11.6,10.5l-0.7-0.7c0.4-0.7,0.6-1.6,0.6-2.4 c0-0.9-0.2-1.7-0.6-2.4l0.6-0.6c0,0,0.1,0,0.1,0c1.2,0,2.2-1,2.2-2.2c0-1.2-1-2.2-2.2-2.2S9.4,1,9.4,2.2c0,0,0,0.1,0,0.1L8.8,2.9 C8.1,2.5,7.2,2.3,6.3,2.3c-2.9,0-5.2,2.3-5.2,5.2c0,2.9,2.3,5.2,5.2,5.2c0.8,0,1.6-0.2,2.4-0.6l0,0l0.7,0.7c0,0,0,0,0,0 c0,1.2,1,2.2,2.2,2.2c1.2,0,2.2-1,2.2-2.2C13.8,11.5,12.8,10.5,11.6,10.5z M9.6,4.9c0.5,0.7,0.9,1.6,0.9,2.5c0,1-0.3,1.9-0.9,2.6 l1.6,1.6c0.1-0.1,0.3-0.1,0.5-0.1c0.7,0,1.2,0.5,1.2,1.2c0,0.7-0.5,1.2-1.2,1.2c-0.7,0-1.2-0.5-1.2-1.2c0-0.2,0-0.3,0.1-0.4 l-1.6-1.6c-0.7,0.5-1.6,0.9-2.5,0.9c-2.3,0-4.2-1.9-4.2-4.2c0-2.3,1.9-4.2,4.2-4.2c1,0,1.9,0.3,2.6,0.9l1.5-1.5 c-0.1-0.1-0.1-0.3-0.1-0.4c0-0.7,0.5-1.2,1.2-1.2s1.2,0.5,1.2,1.2c0,0.7-0.5,1.2-1.2,1.2c-0.2,0-0.3,0-0.4-0.1L9.6,4.9z M0,0 M15,15 M0,0 M15,15" );
	CreateButton( _panels, &_lpLover  , click_panel, "_lpLover"  , "M10.9,3.3c0-1.4-1.3-2.6-2.8-2.6c-1.2,0-2.2,0.7-2.6,1.7C5,1.4,4,0.7,2.8,0.7 C1.3,0.7,0,1.9,0,3.3c0,0,0,0.1,0,0.2c0,2.2,3.8,3.2,5.4,6.2c1.6-3,5.4-4,5.4-6.2C10.9,3.5,10.9,3.3,10.9,3.3z M15,9.7c0-1-0.9-1.9-2-1.9c-0.9,0-1.6,0.5-1.9,1.2c-0.3-0.7-1-1.2-1.9-1.2 c-1.1,0-2,0.8-2,1.9c0,0,0,0.1,0,0.1c0,1.6,2.8,2.3,3.9,4.5c1.2-2.1,3.9-2.8,3.9-4.5C15,9.8,15,9.7,15,9.7z M0,0 M15,15" );

	_lgout->OnMouseDown = moudw_lgout;

	_panels->Height = 18 * 9;
 };
void cMenu::CreateFiles () {
	_file         = new TLayout( this );
	_file->Parent = this;
	_file->Align  = AL::Bottom;
	_file->MarB   = 5;

	CreateButton( _file, &_lopen   , click_files, "_lopen"   , "M10.3,4.3C10.3,4.3,10.3,4.3,10.3,4.3c-0.3,0-0.6,0-0.8-0.3C9.2,3.8,9.2,3.4,9.2,3.2V0H1.9 C1.6,0,1.3,0.3,1.3,0.6v13.8c0,0.3,0.3,0.6,0.6,0.6h11.2c0.3,0,0.6-0.3,0.6-0.6v-10L10.3,4.3z M11.7,13.8c-1-1.3-4.6-2.7-4.6-2.7 c1,0,2.2-0.8,2.2-0.8c-3.8-6.4-6.7-0.1-6.8,0.2c0,0,0,0,0,0c0,0,0,0,0,0c4.5-10.2,8.3-1,8.3-1c0.7-0.3,1.8-0.9,1.8-0.9 C11.2,10.5,11.7,13.8,11.7,13.8z M9.8,0v3.2c0,0,0,0.3,0.1,0.4c0.1,0.1,0.4,0.1,0.4,0.1l3.4,0L9.8,0z M0,0 M15,15" );
	CreateButton( _file, &_lsave   , click_files, "_lsave"   , "M14.7,0.1H0.4C0.2,0.1,0,0.2,0,0.5v12.6l1.2,1.7h13.5c0.2,0,0.3-0.3,0.3-0.5V0.5 C15,0.2,14.9,0.1,14.7,0.1z M0.8,1.4H0.2V0.7h0.7V1.4z M11.6,14.7H3.5c-0.4,0-0.4,0-0.4-0.3V9.8c0-0.3,0.3-0.6,0.7-0.6h7.3 c0.4,0,0.7,0.3,0.7,0.6v4.6C11.9,14.7,12,14.7,11.6,14.7z M13.4,8.2H1.7V0.5h11.7V8.2z M14.9,1.2h-0.5V0.6h0.5V1.2z M12.7,7.8H2.3V1h10.4v0.6c0,0,0,0,0,0c0,0,0,0,0,0V7.8z M4.6,10.1c-0.3,0-0.7,0.1-0.7,0.3v3.3c0,0.2,0.1,0.3,0.4,0.3h4.3v-4H4.6z M0,0 M15,15" );
	CreateButton( _file, &_lsaveAs , click_files, "_lsaveAs" , "M14.7,0.1H0.4C0.2,0.1,0,0.2,0,0.5v12.6l1.2,1.7h13.5c0.2,0,0.3-0.3,0.3-0.5V0.5 C15,0.2,14.9,0.1,14.7,0.1z M0.8,1.4H0.2V0.7h0.7V1.4z M11.6,14.7H3.5c-0.4,0-0.4,0-0.4-0.3V9.8c0-0.3,0.3-0.6,0.7-0.6h7.3 c0.4,0,0.7,0.3,0.7,0.6v4.6C11.9,14.7,12,14.7,11.6,14.7z M13.4,8.2H1.7V0.5h11.7V8.2z M14.9,1.2h-0.5V0.6h0.5V1.2z M4.6,10.1c-0.3,0-0.7,0.1-0.7,0.3v3.3c0,0.2,0.1,0.3,0.4,0.3h4.3v-4H4.6z M2.4,1.8 7.5,6.9 12.6,1.8z M0,0 M15,15" );

	_file->Height = 18 * 3;
 };

/*Creacion - public*/
__fastcall cMenu::cMenu( TComponent *owner ) : cBase(owner) {
	CreateThis  ();
	CreateSystem();
	CreatePanels();
	CreateFiles ();
 };
//###########################################################################


/*Intervalos - private*/
void __fastcall cMenu::highh_save  ( TObject *sender ) {
	_lsave->Tag = 0;

	moule_this( _lsave );
 };
void __fastcall cMenu::highh_saveAs( TObject *sender ) {
	_lsaveAs->Tag = 0;

	moule_this( _lsaveAs );
 };
//###########################################################################


/*Eventos - private*/
void __fastcall cMenu::mouen_this( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;
	TPath   *pat = (TPath  *)lay->TagObject;

	if ( lay->Tag != 1 )
		AnimFC( pat, 1, _preserveColor, sfExponentialOut );
 };
void __fastcall cMenu::moule_this( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;
	TPath   *pat = (TPath  *)lay->TagObject;

	if ( lay->Tag != 1 )
		AnimFC( pat, 1, colorGray3, sfExponentialOut );
 };

void __fastcall cMenu::click_lclose   ( TObject *sender ) {
	Application->Terminate();
 };
void __fastcall cMenu::click_lminimize( TObject *sender ) {
	((TPath*)_lminimize->TagObject)->FilC = colorGray3;

	ShowWindow( GetHandle(), SW_MINIMIZE );
 };
void __fastcall cMenu::click_lpin     ( TObject *sender ) {
	_lpin->Tag = _lpin->Tag == 1 ? 0 : 1;

	SetWindowPos( GetHandle(), _lpin->Tag == 1 ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
 };

void __fastcall cMenu::moudw_lgout( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	ChangeCursor( LoadCursor( HInstance, L"GOTERO" ) );

	TPoint   pos;
	unsigned col;

	if ( onStartColor ) onStartColor( this, ctNone, col, pos );

	while ( whileDown ) {
		GetCursorPos( &pos );

		col = GetPixel( GetDC( GetDesktopWindow() ), pos.x, pos.y );
		col = ACOL( 255, BRGB( col ), GRGB( col ), RRGB( col ) );

		if ( onChangColor ) onChangColor( this, ctRGBA, col, pos );

		Application->ProcessMessages();
	}

	if ( onFinalColor ) onFinalColor( this, ctRGBA, col, pos );

	RestoreCursor();
 };

void __fastcall cMenu::click_panel( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;
	int      tag = lay->Tag;

	_lpEdit   ->Tag = 0; ColorButton( _lpEdit   , false );
	_lpPallets->Tag = 0; ColorButton( _lpPallets, false );
	_lpInfo   ->Tag = 0; ColorButton( _lpInfo   , false );
	_lpImage  ->Tag = 0; ColorButton( _lpImage  , false );
	_lpSchemes->Tag = 0; ColorButton( _lpSchemes, false );
	_lpTones  ->Tag = 0; ColorButton( _lpTones  , false );
	_lpAdobe  ->Tag = 0; ColorButton( _lpAdobe  , false );
	_lpLover  ->Tag = 0; ColorButton( _lpLover  , false );

	lay->Tag = tag == 0 ? 1 : 0;

	ColorButton( lay, true );

	if ( onClickPanel ) onClickPanel( sender );
 };
void __fastcall cMenu::click_files( TObject *sender ) {
	((TLayout*)sender)->Tag = sender == _lsave || sender == _lsaveAs ? 1 : 0;

	if      ( sender == _lsave   ) SetTimeout( "cMenuBSave"  , 2, highh_save   );
	else if ( sender == _lsaveAs ) SetTimeout( "cMenuBSaveAs", 2, highh_saveAs );

	if ( onClickFiles ) onClickFiles( sender );
 };
//###########################################################################


/*Metodos - private*/
void cMenu::ChangeColor() {
	TPath      *pat;
	TRectangle *rec;

	if ( _lpin->Tag == 1 ) {
		pat       = (TPath*)_lpin->TagObject;
		pat->FilC = _preserveColor;
	}

	if ( _lpEdit   ->Tag == 1 ) { pat = (TPath*)_lpEdit   ->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpPallets->Tag == 1 ) { pat = (TPath*)_lpPallets->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpInfo   ->Tag == 1 ) { pat = (TPath*)_lpInfo   ->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpImage  ->Tag == 1 ) { pat = (TPath*)_lpImage  ->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpSchemes->Tag == 1 ) { pat = (TPath*)_lpSchemes->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpTones  ->Tag == 1 ) { pat = (TPath*)_lpTones  ->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpAdobe  ->Tag == 1 ) { pat = (TPath*)_lpAdobe  ->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }
	if ( _lpLover  ->Tag == 1 ) { pat = (TPath*)_lpLover  ->TagObject; rec = (TRectangle*)pat->TagObject; rec->FilC = _preserveColor; }

	if ( _lsave  ->Tag == 1 ) { pat = (TPath*)_lsave  ->TagObject; pat->FilC = _preserveColor; }
	if ( _lsaveAs->Tag == 1 ) { pat = (TPath*)_lsaveAs->TagObject; pat->FilC = _preserveColor; }
 };
//###########################################################################


/*Funciones - private*/
void cMenu::ColorButton( TLayout *layout, bool buttonBlack ) {
	TPath      *pat = (TPath     *)layout->TagObject;
	TRectangle *rec = (TRectangle*)pat   ->TagObject;

	if ( layout->Tag == 1 ) {
		AnimFC( pat, 0.5, colorBlack    , sfCircularOut );
		AnimFC( rec, 0.5, _preserveColor, sfCircularOut );
	}
	else {
		AnimFC( pat, 0.5, buttonBlack ? _preserveColor : colorGray3, sfCircularOut );
		AnimFC( rec, 0.5, colorBlack                               , sfCircularOut );
	}
 };
//###########################################################################