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
#include "p02_Pallets.h"
#pragma package(smart_init)



// class pPallets : public cBase //##########################################
/*Creacion - controls - protected*/
void pPallets::CreateThis   () {
	this->CanFocus     = true;
	this->OnResize     = resiz_this;
	this->OnMouseWheel = mouwh_this;

	_rback           = new TRectangle( this );
	_rback->Parent   = this;
	_rback->Align    = AL::Contents;
	_rback->StrK     = BK::None;
	_rback->FilC     = colorBlack;
	_rback->TagFloat = dzCPallets;

	_lback         = new TLayout( this );
	_lback->Parent = this;
	_lback->Align  = AL::Contents;
 };
void pPallets::CreateDrop   () {
	_rdrop                  = new TRectangle( this );
	_rdrop->Parent          = _lback;
	_rdrop->Align           = AL::Contents;
	_rdrop->StrokeDash      = TStrokeDash::Dash;
	_rdrop->StrokeThickness = 3;
	_rdrop->MarT            = 5;
	_rdrop->MarL            = 5;
	_rdrop->MarB            = 5;
	_rdrop->MarR            = 5;
	_rdrop->StrC            = colorGray2;
	_rdrop->FilC            = colorBlack;
	_rdrop->Opacity         = 0.4;
	_rdrop->HitTest         = false;

	_pdrop             = new TPath( this );
	_pdrop->Parent     = _rdrop;
	_pdrop->Align      = AL::Center;
	_pdrop->StrK       = BK::None;
	_pdrop->FilC       = colorGray2;
	_pdrop->Width      = 60;
	_pdrop->Height     = 60;
	_pdrop->MarT       = 30;
	_pdrop->HitTest    = false;
	_pdrop->Data->Data = "M436.6,291.8 436.6,0 169.6,0 169.6,291.8 0,291.8 303.1,594.9 606.2,291.8";

	_tdrop               = new TText( this );
	_tdrop->Parent       = _rdrop;
	_tdrop->Align        = AL::VertCenter;
	_tdrop->MarT         = -70;
	_tdrop->Text         = "Arrastra aquí";
	_tdrop->Color        = colorGray2;
	_tdrop->Font->Family = fontFamily;
	_tdrop->Font->Size   = 14;
	_tdrop->HitTest      = false;
 };
void pPallets::CreatePallets() {
	_lpallets               = new TLayout( this );
	_lpallets->Parent       = _lback;
	_lpallets->Align        = AL::Contents;
	_lpallets->ClipChildren = true;

	_rscroll         = new TRectangle( this );
	_rscroll->Parent = _lpallets;
	_rscroll->Width  = 3;
	_rscroll->StrK   = BK::None;
	_rscroll->PosY   = 0;
 };

/*Creacion - public*/
__fastcall pPallets::pPallets( TComponent *owner ) : cBase(owner) {
	CreateThis   ();
	CreateDrop   ();
	CreatePallets();
 };
//###########################################################################


/*Propiedades - private*/
void pPallets::WReadOnly( bool readOnly ) {
	_readOnly = readOnly;

	_rback->TagFloat = _readOnly ? 0 : dzCPallets;
 };
//###########################################################################


/*Intervalos - protected*/
void __fastcall pPallets::timer_scroll( TObject *sender ) {
	AnimO( _rscroll, 0.5, 0.3, sfSinusoidalOut );
 };
//###########################################################################


/*Eventos - protected*/
void __fastcall pPallets::resiz_this( TObject *sender                                                   ) {
	int      num = ( this->Height / heightPallet ) + 2;
	cPallet *pal;

	while ( _ppallets.Size < num ) {
		pal            = new cPallet( this );
		pal->Parent    = _lpallets;
		pal->Height    = heightPallet - 5;
		pal->PosX      = 0;
		pal->PosY      = 0;
		pal->Align     = AL::Horizontal;
		pal->TagObject = this;
		pal->ReadOnly  = ReadOnly;
		pal->onClose   = click_close;

		_ppallets+= (int)pal;
	}

	/*Scroll*/
	_rscroll->PosX = this->Width - _rscroll->Width; _rscroll->BringToFront();
	_heightView    = this->Height - _lpallets->MarT;
	_numberView    = int( _heightView / heightPallet ) + 1;

	Render();
 };
void __fastcall pPallets::mouwh_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled ) {
	if ( !this->IsFocused ) this->SetFocus();

	_position-= wheelDelta;

	Render();
 };

void __fastcall pPallets::click_close( TObject *sender, int index ) {
	if ( ReadOnly ) return;

	this->Delete( index )->Render();
 };
//###########################################################################


/*Metodos - private*/
void pPallets::ChangeColor() {
	_rscroll->FilC = _preserveColor;

	cPallet *pal;

	for ( int i = 0; i < _ppallets.Size; i++ )
		((cPallet*)_ppallets[i].Value)->ChangeHSLA( this->Hue, this->Sat, this->Lum, this->Alp );
 };

/*Metodos - public*/
pPallets *pPallets::Add   ( unsigned color                 ) {
	if ( ReadOnly ) return this;

	cPalette *
	pal         = new cPalette;
	pal->Title  = "Paleta de colores " + String( Palettes.Size + 1 );
	pal->Select = 0;
	pal->Colors+= color;

	Palettes+= (int)pal;

	return this;
 };
pPallets *pPallets::Add   ( String palette                 ) {
	if ( ReadOnly ) return this;

	Palettes+= (int)GetPalette( palette );

	return this;
 };
pPallets *pPallets::Add   ( sSField titles, sIField colors ) {
	int poc = 0;

	for ( int i = 0; i < titles.Size; i++ ) {
		cPalette *
		pal         = new cPalette;
		pal->Title  = titles[i].Value;
		pal->Select = 0;

		for ( ;poc < colors.Size && colors.Size < numberColors; ) {
			if ( colors[poc] == -1 ) {
				poc++;

				if ( poc == 1 ) continue; else break;
			}
			else pal->Colors+= colors[poc++].Value;
		}

		Palettes+= (int)pal;
	}

	return this;
 };
pPallets *pPallets::Insert( String palette, int index      ) {
	if ( ReadOnly ) return this;

	Palettes( index, (int)GetPalette( palette ) );

	return this;
 };
pPallets *pPallets::Delete(                 int index      ) {
	if ( ReadOnly || index < 0 || index >= Palettes.Size ) return this;

	delete (cPalette*)Palettes[index].Value;

	Palettes-= index;

	return this;
 };
pPallets *pPallets::Clear (                                ) {
	if ( ReadOnly ) return this;

	for ( int i = 0; i < Palettes.Size; i++ )
		delete (cPalette*)Palettes[i].Value;

	Palettes.Clear();

	return this;
 };

void pPallets::Drop      ( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	if      ( IsColor ( texts[0] ) ) DropColor ( texts, files, point, effects, accept );
	else if ( IsPallet( texts[0] ) ) DropPallet( texts, files, point, effects, accept );
 };
void pPallets::DropColor ( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	IControl   *con = ObjectAtPoint( TPoint( point.x, point.y ) );
	TFmxObject *obj = con ? con->GetObjectW() : NULL;
	unsigned    col = sau( ( texts[0].Value.Length() <= 6 ? "0xFF" : "0x" ) + texts[0].Value );
	TRectangle *res =       dynamic_cast<TRectangle*>( (TRectangle*)sai( texts[1].Value ) ); if ( obj && obj == res ) return;
	cPallet    *pas = res ? dynamic_cast<cPallet   *>( res->TagObject ) : null;

	if ( obj && obj != _rback ) {
		varPom;
		TRectangle *rec = (TRectangle*)obj;
		cPallet    *pal = (cPallet   *)rec->TagObject;
		float       pun = point.x - fom.left - rec->AbsoluteRect.left;
		bool        pre = pun <= rec->Width / 2;

		if ( pas ) {
			if ( pas != pal ) {
				pal->Insert( col, rec->Tag + ( pre ? 0 : 1 ) )->Render();
				pas->Delete( res->Tag )->Render();
			}
			else {
				if ( res->Tag - rec->Tag == 1 || res->Tag - rec->Tag == -1 ) {
					if ( pal->Palette ) {
						pal->Palette->Colors[res->Tag] = pal->Palette->Colors[rec->Tag].Value;
						pal->Palette->Colors[rec->Tag] = col;
                    }

					pal->Render();
				}
				else {
					pal->Insert( col, rec->Tag + ( pre ? 0 : 1 ) )->Render();
					pas->Delete( res->Tag + ( rec->Tag < res->Tag ? 1 : 0 ) )->Render();
				}
			}
		}
		else pal->Insert( col, rec->Tag + ( pre ? 0 : 1 ) )->Render();
	}
	else {
		if ( pas ) pas->Delete( res->Tag )->Render();

		String hex = IntToHex( (int)col, 8 );

		this->Add( col )->Render();
	}
 };
void pPallets::DropPallet( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	IControl   *con = ObjectAtPoint( TPoint( point.x, point.y ) );
	TFmxObject *obj = con ? con->GetObjectW() : NULL;
	TRectangle *res =       dynamic_cast<TRectangle*>( (TRectangle*)sai( texts[1].Value ) ); if ( obj && obj == res ) return;

	if ( obj ) {
		if ( res && res->TagObject == this ) {
			if ( obj->ClassType() == __classid( cPallet ) ) {
				this->
				Delete( res->Tag )->
				Insert( texts[0], ((cPallet*)obj)->Tag )->
				Render();
			}
			else {
				this->
				Delete( res->Tag )->
				Add   ( texts[0] )->
				Render();
			}
		}
		else this->Add( texts[0] )->Render();
	}
	else this->Add( texts[0] )->Render();
 };

void pPallets::Render() {
	StopInterval( (String)(int)_rscroll );

	cPallet *pal;
	int      siz = _ppallets.Size;
	int      num = Palettes.Size;
	float    msc = num * heightPallet;
	float    hba = msc ? ( _heightView * _heightView ) / msc : 0; if ( hba < 20 ) hba = 20; if ( hba >= _heightView ) hba = 0;
	float    max = ( num * heightPallet ) - _heightView; if ( _position > max ) _position = max; if ( _position < 0 ) _position = 0;
	float    ini = int( _position / heightPallet ); if ( ini < 0 ) ini = 0;
	float    fin = int( ini + _numberView ) + 1;  if ( fin > Palettes.Size ) fin = Palettes.Size;
	float    pos = ( ini * heightPallet ) - _position;

	msc = _heightView - hba;

	for ( int x = 0; x < siz; x++, ini++ ) {
		pal = (cPallet*)_ppallets[x].Value;

		if ( ini < fin ) {
			pal->Visible = true;
			pal->PosY    = pos;
			pal->Tag     = ini;
			pal->Palette = (cPalette*)Palettes[ini].Value;
			pal->Render();

			pos+= heightPallet;
		}
		else {
			pal->Visible = false;
			pal->Palette = null;
		}
	}

	_rscroll->PosY    = max ? ( _position * msc ) / max : 0;
	_rscroll->Height  = num ? hba : 0;
	_rdrop  ->Visible = num == 0;

	AnimO( _rscroll, 0.3, 1, sfExponentialOut );
	SetTimeout( (String)(int)_rscroll, 0.8, timer_scroll );
 };
//###########################################################################


/*Funciones - private*/
cPalette *pPallets::GetPalette( String palette ) {
	if ( palette == "" ) return null;
	if ( palette.Length() && palette.w_str()[palette.Length() - 1] != ',' ) palette += ",";

	int       pos = 0;
	int       len = palette.Length();
	wchar_t  *cad = palette.w_str();
	String    tem = "";
	cPalette *pal = new cPalette;

	for ( ;pos<len; pos++ ) {
		if ( cad[pos]=='|' ) {
			if ( pal->Title == "" ) pal->Title  = tem;
			else                    pal->Select = sai( tem );

			tem = "";
		}
		else if ( cad[pos]==',' ) {
			pal->Colors+= sai( "0x" + tem );
			tem         = "";
		}
		else tem+= cad[pos];
	}

	return pal;
 };
//###########################################################################