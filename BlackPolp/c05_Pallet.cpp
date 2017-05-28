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
#include "c05_Pallet.h"
#pragma package(smart_init)



//Otros #####################################################################
/*Definiciones*/
#define playTimer _dblclick=true ;SetTimeout("cPallet"+String((int)this),0.25,timer_stop);
#define stopTimer _dblclick=false;StopInterval("cPallet"+String((int)this));

#define widthColors int num=Palette->Colors.Size;float wid=this->Width-17;wid=num?wid/num:0.0;
//###########################################################################



// class cPallet : public cBase //###########################################
/*Creacion - controles - private*/
void cPallet::CreateFHex( TLayout *parent, TLayout **lline, fLine **fline, float width  ) {
	(*lline)              = new TLayout( this );
	(*lline)->Parent      = parent;
	(*lline)->PosX        = parent->Width + 1000;
	(*lline)->Align       = AL::Left;
	(*lline)->Width       = width;
	(*lline)->HitTest     = true;
	(*lline)->OnMouseDown = moudw_info;

	(*fline)           = new fLine( this );
	(*fline)->Parent   = (*lline);
	(*fline)->Align    = AL::Contents;
	(*fline)->Color    = colorGray3;
	(*fline)->Text     = "";
	(*fline)->HitTest  = false;
	(*fline)->NoRender = true;
	(*fline)->ReadOnly = true;
	(*fline)->onExit   = exitt_info;

	(*lline)->TagObject = (*fline);
	(*fline)->TagObject = (*lline);
 };
void cPallet::CreateFRGB( TLayout *parent, TLayout **lline, fLine **fline, String title ) {
	float    wil;
	TBitmap *bmp = new TBitmap;

	bmp->Canvas->Font->Family = fontFamily;
	bmp->Canvas->Font->Size   = fontSize;
	wil                       = bmp->Canvas->TextWidth( "00" ) - bmp->Canvas->TextWidth( "0" );
	delete bmp;

	(*lline)              = new TLayout( this );
	(*lline)->Parent      = parent;
	(*lline)->PosX        = -1000;
	(*lline)->Align       = AL::Right;
	(*lline)->Width       = ( wil * 6 ) + 5;
	(*lline)->HitTest     = true;
	(*lline)->OnMouseDown = moudw_info;

	(*fline)           = new fLine( this );
	(*fline)->Parent   = (*lline);
	(*fline)->Align    = AL::Client;
	(*fline)->Width    = ( wil * 3 ) + 1;
	(*fline)->Text     = "";
	(*fline)->Color    = colorGray3;
	(*fline)->HitTest  = false;
	(*fline)->NoRender = false;
	(*fline)->ReadOnly = true;
	(*fline)->onExit   = exitt_info;

	(*fline)->TagObject = (*lline);
	(*lline)->TagObject = (*fline);

	TText *
	tex               = new TText( this );
	tex->Parent       = (*lline);
	tex->Align        = AL::Left;
	tex->Width        = ( wil * 2 );
	tex->Color        = colorGray3;
	tex->Text         = title;
	tex->Font->Family = fontFamily;
	tex->Font->Size   = fontSize;
	tex->MarL         = 10;
 };

void cPallet::CreateThis  () {
	this->HitTest     = true;
	this->CanFocus    = true;
	this->TagFloat    = dzCPallet;
	this->OnResize    = resiz_this;
	this->OnMouseDown = moudw_this;

	_rback           = new TRectangle( this );
	_rback->Parent   = this;
	_rback->Align    = AL::Contents;
	_rback->FilC     = colorGray1;
	_rback->StrK     = BK::None;
	_rback->HitTest  = false;

	_rclose               = new TRectangle( this );
	_rclose->Parent       = this;
	_rclose->Align        = AL::MostLeft;
	_rclose->Width        = 5;
	_rclose->FilC         = colorGray2;
	_rclose->StrK         = BK::None;
	_rclose->MarL         = 3;
	_rclose->MarR         = 5;
	_rclose->OnClick      = click_close;
	_rclose->OnMouseEnter = mouen_close;
	_rclose->OnMouseLeave = moule_close;
 };
void cPallet::CreateTitle () {
	_ltitle              = new TLayout( this );
	_ltitle->Parent      = this;
	_ltitle->Align       = AL::Top;
	_ltitle->Height      = 15;
	_ltitle->HitTest     = true;
	_ltitle->CanFocus    = true;
	_ltitle->Width       = 100;
	_ltitle->MarT        = 5;
	_ltitle->MarR        = 5;
	_ltitle->HitTest     = true;
	_ltitle->OnMouseDown = moudw_title;

	_ftitle              = new fLine( this );
	_ftitle->Parent      = _ltitle;
	_ftitle->Align       = AL::Contents;
	_ftitle->Color       = colorWhite;
	_ftitle->Fill        = _preserveColor;
	_ftitle->HitTest     = false;
	_ftitle->NoRender    = true;
	_ftitle->onExit      = exitt_title;
	_ftitle->onKeyChange = keych_title;
 };
void cPallet::CreateColors() {
	_lcolors            = new TLayout( this );
	_lcolors->Parent    = this;
	_lcolors->PosY      = this->Height + 1000;
	_lcolors->Align     = AL::Top;
	_lcolors->Height    = 15;
	_lcolors->MarT      = 2;
	_lcolors->MarR      = 5;
	_lcolors->HitTest   = true;
	_lcolors->TagFloat  = dzCPalletColor;
	_lcolors->TagObject = this;

	TResourceStream *
	rs           = new TResourceStream( (int)HInstance, "TRANSPARENCIA", L"PNG" );
	rs->Position = 0;

	_rtransp           = new TRectangle( this );
	_rtransp->Parent   = _lcolors;
	_rtransp->Align    = AL::Contents;
	_rtransp->StrK     = BK::None;
	_rtransp->FilK     = BK::Bitmap;
	_rtransp->HitTest  = false;
	_rtransp->SendToBack();
	_rtransp->Fill->Bitmap->Bitmap->LoadFromStream( rs );

	delete rs;

	for ( int i = 0; i < numberColors; i++ ) {
		_rcolors[i]              = new TRectangle( this );
		_rcolors[i]->Parent      = _lcolors;
		_rcolors[i]->PosY        = 0;
		_rcolors[i]->PosX        = 0;
		_rcolors[i]->StrK        = BK::None;
		_rcolors[i]->FilC        = colorHigh;
		_rcolors[i]->Height      = _lcolors->Height;
		_rcolors[i]->Tag         = i;
		_rcolors[i]->TagFloat    = dzCPalletColor;
		_rcolors[i]->OnMouseDown = moudw_color;
		_rcolors[i]->TagObject   = this;
		_rcolors[i]->CanFocus    = true;
	}
 };
void cPallet::CreateSelect() {
	_lselect         = new TLayout( this );
	_lselect->Parent = this;
	_lselect->PosY   = this->Height + 1000;
	_lselect->Align  = AL::Top;
	_lselect->Height = 2;
	_lselect->MarT   = 2;
	_lselect->MarR   = 5;

	_rselect          = new TRectangle( this );
	_rselect->Parent  = _lselect;
	_rselect->PosY    = 0;
	_rselect->PosX    = 0;
	_rselect->Height  = _lselect->Height;
	_rselect->StrK    = BK::None;
	_rselect->FilC    = colorWhite;
	_rselect->HitTest = false;
 };
void cPallet::CreateInfo  () {
	_linfo         = new TLayout( null );
	_linfo->Parent = this;
	_linfo->PosY   = this->Height + 1000;
	_linfo->Align  = AL::Top;
	_linfo->Height = 15;
	_linfo->MarT   = 5;
	_linfo->MarR   = 5;

	float    wil;
	TBitmap *bmp = new TBitmap;
	bmp->Canvas->Font->Family = fontFamily;
	bmp->Canvas->Font->Size   = fontSize;
	wil = bmp->Canvas->TextWidth( "00" ) - bmp->Canvas->TextWidth( "0" );
	delete bmp;

	CreateFHex( _linfo, &_lhex1, &_fhex1, ( wil * 2 ) + 1 );
	CreateFHex( _linfo, &_lhex2, &_fhex2, ( wil * 6 ) + 1 ); _lhex2->MarL = 5;
	CreateFRGB( _linfo, &_lrgb1, &_frgb1, "B="            );
	CreateFRGB( _linfo, &_lrgb2, &_frgb2, "G="            );
	CreateFRGB( _linfo, &_lrgb3, &_frgb3, "R="            );
 };

/*Creacion - public*/
__fastcall cPallet::cPallet( TComponent *owner ) : cBase(owner) {
	Palette = null;

	CreateThis  ();
	CreateTitle ();
	CreateColors();
	CreateSelect();
	CreateInfo  ();
 };
//###########################################################################


/*Propiedades - private*/
void cPallet::WReadOnly( bool readOnly ) {
	_readOnly         = readOnly;
	_ftitle->ReadOnly = readOnly;
	_rclose->Opacity  = readOnly ? 0 : 1;

	this    ->TagFloat = readOnly ? 0 : dzCPallet;
	_lcolors->TagFloat = readOnly ? 0 : dzCPalletColor;

	for ( int i = 0; i < numberColors; i++ )
		_rcolors[i]->TagFloat = readOnly ? 0 : dzCPalletColor;
 };
//###########################################################################

/*Intervalos - private*/
void __fastcall cPallet::timer_stop( TObject *sender ) {
	stopTimer;
 };
//###########################################################################


/*Eventos - private*/
void __fastcall cPallet::resiz_this( TObject *sender                                                           ) {
	if ( !Palette ) return;

	widthColors

	_rselect->PosX  = Palette->Select * wid;
	_rselect->Width = wid;

	for ( int x = 0; x < numberColors; x++ ) {
		if ( _rcolors[x]->Visible ) {
			_rcolors[x]->Width   = wid;
			_rcolors[x]->PosX    = wid * x;
		}
	}
 };
void __fastcall cPallet::moudw_this( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	varPom;
	TLayout *rec = (TLayout*)sender;
	float    px1 = pom.x, py1 = pom.y;

	while ( whileDown ) {
		GetCursorPos( &pom );

		if (
			( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
			( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
		) {
			wDragDrop::DoDragText(
				DROPEFFECT_COPY | DROPEFFECT_MOVE,
				true,
				BMPaDBM( this->MakeScreenshot(), pom.x - fom.left - rec->AbsoluteRect.left, pom.y - fom.top  - rec->AbsoluteRect.top ),
				2,
				GetPallet(),
				(String)(int)this
			);

			break;
		}
	}
 };

void __fastcall cPallet::click_close( TObject *sender ) {
	if ( ReadOnly ) return;

	if ( onClose )
		onClose( this, this->Tag );
 };
void __fastcall cPallet::mouen_close( TObject *sender ) {
	if ( ReadOnly ) return;

	AnimFC( _rclose, 1, colorGray3, sfExponentialOut );
 };
void __fastcall cPallet::moule_close( TObject *sender ) {
	if ( ReadOnly ) return;

	AnimFC( _rclose, 1, colorGray2, sfExponentialOut );
 };

void __fastcall cPallet::exitt_title( TObject *sender                                                           ) {
	_ftitle->HitTest  = false;
	_ftitle->NoRender = true;

	this->SetFocus();
 };
void __fastcall cPallet::keych_title( TObject *sender                                                           ) {
	if ( ReadOnly ) return;

	if ( Palette )
		Palette->Title = _ftitle->Text;
 };
void __fastcall cPallet::moudw_title( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	if ( !_dblclick ) {
		playTimer;

		varPom;
		float px1 = pom.x, py1 = pom.y;

		while ( whileDown ) {
			GetCursorPos( &pom );

			if (
				( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
				( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
			) {
				stopTimer;

				wDragDrop::DoDragText( DROPEFFECT_COPY, true, null, 1, _ftitle->Text );

				return;
			}

			Application->ProcessMessages();
		}
	}
	else {
		stopTimer;

		_ftitle->HitTest  = true;
		_ftitle->NoRender = false;
		_ftitle->SetFocus();
		_ftitle->Select( 0, _ftitle->Text.Length() );
	}
 };

void __fastcall cPallet::moudw_color( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	TRectangle *rec = (TRectangle*)sender;

	if ( !_dblclick ) {
		playTimer;

		varPom;
		float px1 = pom.x, py1 = pom.y;

		while ( whileDown ) {
			GetCursorPos( &pom );

			if (
				( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
				( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
			) {
				stopTimer;

				px1 = pom.x - fom.left - rec->AbsoluteRect.left;
				py1 = pom.y - fom.top  - rec->AbsoluteRect.top ;

				ColorDrop( rec, IntToHex( (int)rec->FilC, 8 ), px1, py1, BMPaDBM( rec->MakeScreenshot(), px1, py1 ) );

				return;
			}

			Application->ProcessMessages();
		}
	}
	else {
		stopTimer;

		if ( Palette )
			Palette->Select = rec->Tag;

		AnimL( _rselect, 0.5, rec->PosX, sfSinusoidalOut );

		_colorSelect = rec->FilC;
		_fhex1->Text = IntToHex( (int)ARGB( _colorSelect ), 2 );
		_fhex2->Text = IntToHex( (int)RRGB( _colorSelect ), 2 ) + IntToHex( (int)GRGB( _colorSelect ), 2 ) + IntToHex( (int)BRGB( _colorSelect ), 2 );
		_frgb1->Text = BRGB( _colorSelect );
		_frgb2->Text = GRGB( _colorSelect );
		_frgb3->Text = RRGB( _colorSelect );
	}
 };

void __fastcall cPallet::exitt_info( TObject *sender                                                           ) {
	fLine *lin = (fLine*)sender;

	lin->HitTest  = false;
	lin->NoRender = true;

	this->SetFocus();
 };
void __fastcall cPallet::moudw_info( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	TLayout *lay = (TLayout*)sender;
	fLine   *lin = (fLine  *)lay->TagObject;

	if ( !_dblclick ) {
		playTimer;

		varPom;
		float px1 = pom.x, py1 = pom.y;

		while ( whileDown ) {
			GetCursorPos( &pom );

			if (
				( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
				( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
			) {
				stopTimer;

				if ( lay == _lhex2 ) {
					ColorDrop( null, _fhex2->Text,
						px1 - fom.left - lay->AbsoluteRect.left - x + 25,
						py1 - fom.top  - lay->AbsoluteRect.top  - y + 25
					);
				}
				else {
					ColorDrop( null, IntToHex( (int)_colorSelect, 8 ),
						px1 - fom.left - lay->AbsoluteRect.left - x + 25,
						py1 - fom.top  - lay->AbsoluteRect.top  - y + 25
					);
				}

				return;
			}

			Application->ProcessMessages();
		}
	}
	else {
		stopTimer;

		lin->HitTest  = true;
		lin->NoRender = false;
		lin->SetFocus();
		lin->Select( 0, lin->Text.Length() );
	}
 };
//###########################################################################


/*Metodos - private*/
void cPallet::ChangeColor() {
	_ftitle->Fill = _preserveColor;
	_fhex1 ->Fill = _preserveColor;
	_fhex2 ->Fill = _preserveColor;
	_frgb1 ->Fill = _preserveColor;
	_frgb2 ->Fill = _preserveColor;
	_frgb3 ->Fill = _preserveColor;
 };

/*Metodos - public*/
void   cPallet::Render   () {
	if ( !Palette ) return;

	widthColors;

	if ( Palette->Select >= Palette->Colors.Size     ) Palette->Select = Palette->Colors.Size - 1;
	if ( Palette->Select < 0 && Palette->Colors.Size ) Palette->Select = 0;

	_colorSelect       = Palette->Colors[Palette->Select];
	_rselect->PosX     = Palette->Select * wid;
	_rselect->Width    = wid;
	_rselect->Visible  = Palette->Select >= 0;
	_ftitle ->NoRender = true; _ftitle->Text = Palette->Title;
	_fhex1  ->NoRender = true; _fhex1 ->Text = IntToHex( (int)ARGB( _colorSelect ), 2 );
	_fhex2  ->NoRender = true; _fhex2 ->Text = IntToHex( (int)RRGB( _colorSelect ), 2 ) + IntToHex( (int)GRGB( _colorSelect ), 2 ) + IntToHex( (int)BRGB( _colorSelect ), 2 );
	_frgb1  ->NoRender = true; _frgb1 ->Text = BRGB( _colorSelect );
	_frgb2  ->NoRender = true; _frgb2 ->Text = GRGB( _colorSelect );
	_frgb3  ->NoRender = true; _frgb3 ->Text = RRGB( _colorSelect );

	for ( int x = 0; x < numberColors; x++ ) {
		if ( x < num ) {
			_rcolors[x]->Visible = true;
			_rcolors[x]->Width   = wid;
			_rcolors[x]->PosX    = wid * x;
			_rcolors[x]->FilC    = Palette->Colors[x];
		}
		else _rcolors[x]->Visible = false;
	}
 };
String cPallet::GetPallet() {
	if ( !Palette ) return "";

	String res = Palette->Title + "|" + Palette->Select + "|";

	for ( int i = 0; i < Palette->Colors.Size; i++ )
		res += IntToHex( (int)Palette->Colors[i].Value, 8 ) + ",";

	return res;
 };

cPallet *cPallet::Add   ( unsigned color            ) {
	if ( _readOnly || !Palette || Palette->Colors.Size >= numberColors ) return this;

	Palette->Colors+= color;

	return this;
 };
cPallet *cPallet::Insert( unsigned color, int index ) {
	if ( _readOnly || !Palette ) return this;

	Palette->Colors( index, color );

	return this;
 };
cPallet *cPallet::Delete( int      index            ) {
	if ( _readOnly || !Palette || !Palette->Colors.Size || index < 0 || index >= Palette->Colors.Size ) return this;

	Palette->Colors-= index;

	return this;
 };
//###########################################################################