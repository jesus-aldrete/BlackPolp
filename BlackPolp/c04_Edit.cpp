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
#include "c04_Edit.h"
#pragma package(smart_init)



//Otros #####################################################################
/*Definiciones*/
#define playEdit _dblclick=true ;SetTimeout("cedit"+String((int)this),0.25,timer_edit);
#define stopEdit _dblclick=false;StopInterval("cedit"+String((int)this));
//###########################################################################




// class cEdit : public cBase //#############################################
/*Creacion - controles - private*/
void cEdit::CreateEdit( TLayout *lparent, TLayout **lbox, TText **ttitle, String title, fLine **fline, bool max ) {
	widthLetter;

	(*ttitle)               = new TText( this );
	(*ttitle)->Parent       = lparent;
	(*ttitle)->PosX         = lparent->Width + 1000;
	(*ttitle)->Align        = AL::Left;
	(*ttitle)->Text         = title;
	(*ttitle)->Color        = colorWhite;
	(*ttitle)->Width        = ( title.Length() * wil ) + 1;
	(*ttitle)->MarL         = 5;
	(*ttitle)->Font->Size   = fontSize;
	(*ttitle)->Font->Family = fontFamily;

	(*lbox)              = new TLayout( this );
	(*lbox)->Parent      = lparent;
	(*lbox)->PosX        = lparent->Width + 1000;
	(*lbox)->Align       = AL::Left;
	(*lbox)->Width       = ( ( max ? 8 : 6 ) * wil ) + 1;
	(*lbox)->HitTest     = true;
	(*lbox)->CanFocus    = true;
	(*lbox)->OnMouseDown = moudw_edit;

	(*fline)             = new fLine( this );
	(*fline)->Parent     = (*lbox);
	(*fline)->PosX       = lparent->Width + 1000;
	(*fline)->Align      = AL::Contents;
	(*fline)->Text       = "";
	(*fline)->Color      = colorWhite;
	(*fline)->HitTest    = false;
	(*fline)->onExit     = exitt_edit;
	(*fline)->onKeyEnter = keyen_this;

	(*lbox )->TagObject = (*fline);
	(*fline)->TagObject = (*lbox );
 };

void cEdit::CreateThis() {
	_rback           = new TRectangle( this );
	_rback->Parent   = this;
	_rback->Align    = AL::Contents;
	_rback->StrK     = BK::None;
	_rback->FilC     = colorBlack;
	_rback->CanFocus = true;
 };
void cEdit::CreateHEX () {
	_lhex         = new TLayout( this );
	_lhex->Parent = this;
	_lhex->PosY   = this->Height + 1000;
	_lhex->Align  = AL::Top;
	_lhex->Height = 20;
	_lhex->MarT   = 5;
	_lhex->MarL   = 5;
	_lhex->MarR   = 5;

	CreateEdit( _lhex, &_lf, &_tf, "F=", &_ff, true  );
	CreateEdit( _lhex, &_lw, &_tw, "W=", &_fw, false );
	CreateEdit( _lhex, &_lv, &_tv, "V=", &_fv, false );
	CreateEdit( _lhex, &_lu, &_tu, "S=", &_fu, false );
 };
void cEdit::CreateRGB () {
	_lrgb         = new TLayout( this );
	_lrgb->Parent = this;
	_lrgb->PosY   = this->Height + 1000;
	_lrgb->Align  = AL::Top;
	_lrgb->Height = 20;
	_lrgb->MarL   = 5;
	_lrgb->MarR   = 5;

	CreateEdit( _lrgb, &_lr, &_tr, "R=", &_fr, true  );
	CreateEdit( _lrgb, &_lg, &_tg, "G=", &_fg, false );
	CreateEdit( _lrgb, &_lb, &_tb, "B=", &_fb, false );
	CreateEdit( _lrgb, &_la, &_ta, "A=", &_fa, false );
 };
void cEdit::CreateHSL () {
	_lhsl         = new TLayout( this );
	_lhsl->Parent = this;
	_lhsl->PosY   = this->Height + 1000;
	_lhsl->Align  = AL::Top;
	_lhsl->Height = 20;
	_lhsl->MarL   = 5;
	_lhsl->MarR   = 5;

	CreateEdit( _lhsl, &_lh, &_th, "H=", &_fh, true  );
	CreateEdit( _lhsl, &_ls, &_ts, "S=", &_fs, false );
	CreateEdit( _lhsl, &_ll, &_tl, "L=", &_fl, false );
	CreateEdit( _lhsl, &_lo, &_to, "A=", &_fo, false );
 };

/*Creacion - public*/
__fastcall cEdit::cEdit( TComponent *owner ) : cBase(owner) {
	_dblclick = false;

	CreateThis();
	CreateHEX ();
	CreateRGB ();
	CreateHSL ();
 };
//###########################################################################

/*Intervalos - private*/
void __fastcall cEdit::timer_edit( TObject *sender ) {
	stopEdit;
 };
//###########################################################################


/*Eventos - private*/
void __fastcall cEdit::keyen_this( TObject *sender ) {
	if ( !onChangColor ) return;

	if      ( sender == _ff ) onChangColor( this, ctRGBA, sai( "0x" + _ff->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fw ) onChangColor( this, ctRGB , sai( "0x" + _fw->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fv ) onChangColor( this, ctBGR , sai( "0x" + _fv->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fu ) onChangColor( this, ctRGB , sai( "0x" + _fu->Text ), TPoint( 0, 0 ) );

	else if ( sender == _fa ) onChangColor( this, ctAlpha, sai( _fa->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fr ) onChangColor( this, ctRed  , sai( _fr->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fg ) onChangColor( this, ctGreen, sai( _fg->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fb ) onChangColor( this, ctBlue , sai( _fb->Text ), TPoint( 0, 0 ) );

	else if ( sender == _fh ) onChangColor( this, ctHue, sad( _fh->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fs ) onChangColor( this, ctSat, sad( _fs->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fl ) onChangColor( this, ctLum, sad( _fl->Text ), TPoint( 0, 0 ) );
	else if ( sender == _fo ) onChangColor( this, ctAlp, sad( _fo->Text ), TPoint( 0, 0 ) );
 };

void __fastcall cEdit::exitt_edit( TObject *sender                                                           ) {
	fLine   *lin = (fLine  *)sender;
	TLayout *lay = (TLayout*)lin->TagObject;

	lin->HitTest = false;
	lay->HitTest = true;

	_rback->SetFocus();
 };
void __fastcall cEdit::moudw_edit( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	TLayout *lay = (TLayout*)sender;
	fLine   *lin = (fLine  *)lay->TagObject;

	if ( !_dblclick ) {
		playEdit;

		varPom;
		float px1 = pom.x, py1 = pom.y;

		while ( whileDown ) {
			GetCursorPos( &pom );

			if (
				( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
				( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
			) {
				stopEdit;

				if ( IsColor( lin->Text ) ) {
					ColorDrop( null, lin->Text,
						px1 - fom.left - lay->AbsoluteRect.left - x + 25,
						py1 - fom.top  - lay->AbsoluteRect.top  - y + 25
					);
				}
				else wDragDrop::DoDragText( DROPEFFECT_COPY, true, null, 1, lin->Text );

				return;
			}

			Application->ProcessMessages();
		}
	}
	else {
		stopEdit;
		lin->HitTest = true;
		lin->SetFocus();
		lin->Select( 0, lin->Text.Length() );
	}
 };
//###########################################################################


/*Metodos - private*/
void cEdit::ChangeColor() {
	_ff->Text = IntToHex( _alpha, 2 ) + RGBaHEX( _red , _green, _blue           ); _ff->Fill = _preserveColor;
	_fw->Text =                         RGBaHEX( _red , _green, _blue           ); _fw->Fill = _preserveColor;
	_fv->Text =                         RGBaHEX( _blue, _green, _red            ); _fv->Fill = _preserveColor;
	_fu->Text =                         RGBaHEX( RGBaSAF( _red, _green, _blue ) ); _fu->Fill = _preserveColor;

	_fr->Text = _red  ; _fr->Fill = _preserveColor;
	_fg->Text = _green; _fg->Fill = _preserveColor;
	_fb->Text = _blue ; _fb->Fill = _preserveColor;
	_fa->Text = _alpha; _fa->Fill = _preserveColor;

	_fh->Text = String( _hue ).SubString( 1, 5 ); _fh->Fill = _preserveColor;
	_fs->Text = String( _sat ).SubString( 1, 5 ); _fs->Fill = _preserveColor;
	_fl->Text = String( _lum ).SubString( 1, 5 ); _fl->Fill = _preserveColor;
	_fo->Text = String( _alp ).SubString( 1, 5 ); _fo->Fill = _preserveColor;
 };
//###########################################################################