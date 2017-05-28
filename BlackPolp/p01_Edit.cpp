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
#include "p01_Edit.h"
#pragma package(smart_init)



// class pEdit : public cBase //#############################################
/*Creacion - controles - public*/
void pEdit::CreateSample( TLayout **parent, TRectangle **rcolor, TRectangle **pcolor, String title ) {
	(*parent)               = new TLayout( this );
	(*parent)->Parent       = this;
	(*parent)->PosY         = this->Height + 1000;
	(*parent)->Align        = AL::Top;
	(*parent)->MarL         = 10;
	(*parent)->MarR         = 10;
	(*parent)->MarT         = 10;
	(*parent)->Height       = 25;
	(*parent)->HitTest      = true;
	(*parent)->OnMouseWheel = mouwh_sample;

	TText *
	tex               = new TText( this );
	tex->Parent       = (*parent);
	tex->Text         = title;
	tex->Align        = AL::Left;
	tex->Width        = 8;
	tex->Color        = colorWhite;
	tex->Font->Size   = fontSize;
	tex->Font->Family = fontFamily;

	(*rcolor)              = new TRectangle( this );
	(*rcolor)->Parent      = (*parent);
	(*rcolor)->Align       = AL::Client;
	(*rcolor)->MarT        = 8;
	(*rcolor)->MarB        = 8;
	(*rcolor)->MarL        = 10;
	(*rcolor)->MarR        = 10;
	(*rcolor)->StrK        = BK::None;
	(*rcolor)->OnMouseDown = moudw_samplb;

	(*pcolor)              = new TRectangle( this );
	(*pcolor)->Parent      = (*rcolor);
	(*pcolor)->Height      = (*parent)->Height;
	(*pcolor)->Width       = 8;
	(*pcolor)->PosY        = -( ( (*pcolor)->Height / 2 ) - ( (*rcolor)->Height / 2 ) );
	(*pcolor)->PosX        = -( (*pcolor)->Width / 2 );
	(*pcolor)->FilC        = colorBlack;
	(*pcolor)->StrC        = _preserveColor;
	(*pcolor)->OnMouseDown = moudw_sample;

	(*parent)->TagObject = (*rcolor);
	(*rcolor)->TagObject = (*pcolor);
	(*pcolor)->TagObject = tex;
 };

void pEdit::CreateThis() {
	_rback         = new TRectangle( this );
	_rback->Parent = this;
	_rback->Align  = AL::Contents;
	_rback->StrK   = BK::None;
	_rback->FilC   = colorBlack;
 };
void pEdit::CreateHue () {
	CreateSample( &_lhue, &_rhue, &_phue, "H" );

	_lhue->MarT = 5;

	TGradient *
	gra                   = new TGradient();
	gra->Style            = TGradientStyle::Linear;
	gra->Color1           = claRed;
	gra->StartPosition->Y = 0.5;
	gra->StopPosition ->X = 1;
	gra->StopPosition ->Y = 0.5;

	TGradientPoint *
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claRed    ; pun->Offset = 0.000;
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claYellow ; pun->Offset = 0.166;
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claLime   ; pun->Offset = 0.333;
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claAqua   ; pun->Offset = 0.500;
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claBlue   ; pun->Offset = 0.666;
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claFuchsia; pun->Offset = 0.833;
	pun = (TGradientPoint*)gra->Points->Add(); pun->Color = claFuchsia; pun->Offset = 0.833;

	_rhue->FilK = BK::Gradient;
	_rhue->Fill->Gradient->Assign( gra );

	delete gra;
 };
void pEdit::CreateSat () {
	CreateSample( &_lsat, &_rsat, &_psat, "S" );
 };
void pEdit::CreateLum () {
	CreateSample( &_llum, &_rlum, &_plum, "L" );
 };
void pEdit::CreateAlp () {
	CreateSample( &_lalp, &_ralp, &_palp, "A" );

	TResourceStream *
	res           = new TResourceStream( (int)HInstance, "TRANSPARENCIA", L"PNG" );
	res->Position = 0;

	_talp         = new TRectangle( this );
	_talp->Parent = _lalp;
	_talp->Align  = AL::Client;
	_talp->MarT   = ((TRectangle*)_lalp->TagObject)->MarT;
	_talp->MarB   = ((TRectangle*)_lalp->TagObject)->MarB;
	_talp->MarL   = 10;
	_talp->MarR   = 10;
	_talp->StrK   = BK::None;
	_talp->FilK   = BK::Bitmap;
	_talp->Fill->Bitmap->Bitmap->LoadFromStream( res );
	_talp->SendToBack();

	delete res;
 };

/*Creacion - public*/
__fastcall pEdit::pEdit( TComponent *owner ) : cBase( owner ) {
	CreateThis();
	CreateHue ();
	CreateSat ();
	CreateLum ();
	CreateAlp ();
 };
//###########################################################################


/*Eventos - Muestras - private*/
void __fastcall pEdit::moudw_samplb( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	TRectangle *re1 = (TRectangle*)sender;
	TRectangle *re2 = (TRectangle*)re1->TagObject;

	moudw_sample( re2, button, shift, re2->Width / 2, 0 );
 };
void __fastcall pEdit::moudw_sample( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	varPom;
	TRectangle *re1 = (TRectangle*)sender;
	TRectangle *re2 = (TRectangle*)re1->Parent;
	float       le1 = fom.left + re2->AbsoluteRect.left + x;
	float       po1 ;
	unsigned    col ;

	if ( onStartColor ) onStartColor( this, ctNone, col, pom );

	while ( whileDown ) {
		GetCursorPos( &pom );

		po1 = pom.x - le1;

		if ( po1 + ( re1->Width / 2 ) < 0          ) po1 =            - ( re1->Width / 2 );
		if ( po1 + ( re1->Width / 2 ) > re2->Width ) po1 = re2->Width - ( re1->Width / 2 );

		re1->PosX = po1;

		if      ( re1 == _phue ) { _hue = ( po1 + ( re1->Width / 2 ) ) / _rhue->Width; if ( onChangColor ) { onChangColor( this, ctHue, _hue, pom ); } }
		else if ( re1 == _psat ) { _sat = ( po1 + ( re1->Width / 2 ) ) / _rsat->Width; if ( onChangColor ) { onChangColor( this, ctSat, _sat, pom ); } }
		else if ( re1 == _plum ) { _lum = ( po1 + ( re1->Width / 2 ) ) / _rlum->Width; if ( onChangColor ) { onChangColor( this, ctLum, _lum, pom ); } }
		else if ( re1 == _palp ) { _alp = ( po1 + ( re1->Width / 2 ) ) / _ralp->Width; if ( onChangColor ) { onChangColor( this, ctAlp, _alp, pom ); } }

		Application->ProcessMessages();
	}

	if ( onFinalColor ) {
		if      ( re1 == _phue ) { onFinalColor( this, ctHue, _hue, pom ); }
		else if ( re1 == _psat ) { onFinalColor( this, ctSat, _sat, pom ); }
		else if ( re1 == _plum ) { onFinalColor( this, ctLum, _lum, pom ); }
		else if ( re1 == _palp ) { onFinalColor( this, ctAlp, _alp, pom ); }
	}
 };
void __fastcall pEdit::mouwh_sample( TObject *sender, TShiftState shift, int wheelDelta, bool &handled         ) {
	TRectangle *re1 = (TRectangle*)((TRectangle*)sender)->TagObject;
	TRectangle *re2 = (TRectangle*)re1->TagObject;
	double      can = ( re2->PosX + ( re2->Width / 2 ) ) / re1->Width;

	can += ( double(wheelDelta) / 10000.0 );

	if      ( re1 == _rhue ) { _hue = can; if ( onChangColor ) { onChangColor( this, ctHue, _hue, TPoint( snan, 0 ) ); } }
	else if ( re1 == _rsat ) { _sat = can; if ( onChangColor ) { onChangColor( this, ctSat, _sat, TPoint( snan, 0 ) ); } }
	else if ( re1 == _rlum ) { _lum = can; if ( onChangColor ) { onChangColor( this, ctLum, _lum, TPoint( snan, 0 ) ); } }
	else if ( re1 == _ralp ) { _alp = can; if ( onChangColor ) { onChangColor( this, ctAlp, _alp, TPoint( snan, 0 ) ); } }
 };
//###########################################################################


/*Metodos - private*/
void pEdit::ChangeColor() {
	if ( !_phue ) return;

	_phue->PosX = ( _hue * _rhue->Width ) - ( _phue->Width / 2 );
	_psat->PosX = ( _sat * _rsat->Width ) - ( _psat->Width / 2 );
	_plum->PosX = ( _lum * _rlum->Width ) - ( _plum->Width / 2 );
	_palp->PosX = ( _alp * _ralp->Width ) - ( _palp->Width / 2 );

	ChangeControls( _preserveColor );
 };
//###########################################################################


/*Funciones - private*/
void pEdit::ChangeControls( unsigned color ) {
	_phue->StrC = color;
	_psat->StrC = color;
	_plum->StrC = color;
	_palp->StrC = color;

	TGradient *
	/*SAT*/
	gra                   = new TGradient();
	gra->Style            = TGradientStyle::Linear;
	gra->Color1           = color;
	gra->StartPosition->Y = 0.5;
	gra->StopPosition->X  = 1;
	gra->StopPosition->Y  = 0.5;

	TGradientPoint *
	pun = ( TGradientPoint* )gra->Points->Add(); pun->Color = claWhite; pun->Offset = 0.000;

	_rsat->FilK = BK::Gradient;
	_rsat->Fill->Gradient->Assign( gra );

	delete gra;

	/*LUM*/
	gra                   = new TGradient();
	gra->Style            = TGradientStyle::Linear;
	gra->Color1           = color;
	gra->StartPosition->Y = 0.5;
	gra->StopPosition->X  = 1;
	gra->StopPosition->Y  = 0.5;

	pun = ( TGradientPoint* )gra->Points->Add(); pun->Color = claBlack; pun->Offset = 0.000;

	_rlum->FilK = BK::Gradient;
	_rlum->Fill->Gradient->Assign( gra );

	delete gra;


	/*ALP*/
	gra                   = new TGradient();
	gra->Style            = TGradientStyle::Linear;
	gra->Color1           = color;
	gra->StartPosition->Y = 0.5;
	gra->StopPosition->X  = 1;
	gra->StopPosition->Y  = 0.5;

	pun = ( TGradientPoint* )gra->Points->Add(); pun->Color = 0; pun->Offset = 0.000;

	_ralp->FilK = BK::Gradient;
	_ralp->Fill->Gradient->Assign( gra );

	delete gra;
 };
//###########################################################################