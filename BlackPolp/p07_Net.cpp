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
#include "p07_Net.h"
#pragma package(smart_init)



//Otros #####################################################################
/*Definiciones*/
#define setRequest  Str[0]
#define setResponce Str[1]
//###########################################################################



// class pNet : public pPallets //###########################################
/*Creacion - controles - private*/
void pNet::CreateButton( TText **butext, TLayout *parent, float width, String title, String id ) {
	(*butext)               = new TText( this );
	(*butext)->Parent       = parent;
	(*butext)->PosX         = parent->Width + 1000;
	(*butext)->Align        = AL::Right;
	(*butext)->Width        = width;
	(*butext)->Cursor       = crHandPoint;
	(*butext)->Text         = title;
	(*butext)->Color        = colorWhite;
	(*butext)->Font->Family = fontFamily;
	(*butext)->Font->Size   = fontSize;
	(*butext)->TagString    = id;
	(*butext)->OnClick      = click_button;
 };

void pNet::CreateThis   () {
	this->ReadOnly = true;

	_rdrop->StrK = BK::None;
	_rdrop->FilK = BK::None;
	_tdrop->Text = "Descargar de\n" + String( _adobe ? "www.color.adobe.com" : "www.colourlovers.com" );

	_ledit         = new TLayout( this );
	_ledit->Parent = this;
	_ledit->Align  = AL::Top;
	_ledit->Height = 20;
 };
void pNet::CreateNPP    () {
	widthLetter;

	_lnpp         = new TLayout( this );
	_lnpp->Parent = _ledit;
	_lnpp->Align  = AL::Left;
	_lnpp->Width  = ( wil * 7 ) + 1;

	_tnpp               = new TText( this );
	_tnpp->Parent       = _lnpp;
	_tnpp->Align        = AL::Left;
	_tnpp->Width        = ( wil * 4 );
	_tnpp->Text         = "NPP:";
	_tnpp->Font->Family = fontFamily;
	_tnpp->Font->Size   = fontSize;
	_tnpp->Color        = colorWhite;

	_fnpp         = new fLine( this );
	_fnpp->Parent = _lnpp;
	_fnpp->Align  = AL::Client;
	_fnpp->Text   = "50";
	_fnpp->Color  = colorWhite;
	_fnpp->Fill   = _preserveColor;
 };
void pNet::CreateButtons() {
	#define widthLButtons 35

	_lbuttons         = new TLayout( this );
	_lbuttons->Parent = _ledit;
	_lbuttons->Align  = AL::Client;
	_lbuttons->MarR   = 2;

	_rselect            = new TRectangle( this );
	_rselect->Parent    = _lbuttons;
	_rselect->PosY      = 1;
	_rselect->PosX      = 0;
	_rselect->Height    = _lbuttons->Height - 1;
	_rselect->Width     = widthLButtons;
	_rselect->StrC      = _preserveColor;
	_rselect->FilC      = colorGray1;
	_rselect->Opacity   = 0.5;
	_rselect->XRadius   = 5;
	_rselect->YRadius   = 5;
	_rselect->Opacity   = 0;
	_rselect->TagString = _adobe ? "popular" : "new";
	_rselect->Anchors   = TAnchors() << TAnchorKind::akRight << TAnchorKind::akBottom;

	if ( !_adobe ) CreateButton( &_tnew, _lbuttons, widthLButtons, "New", _adobe ? ""        : "new" );
	if ( !_adobe ) CreateButton( &_ttop, _lbuttons, widthLButtons, "Top", _adobe ? ""        : "top" );
	if (  _adobe ) CreateButton( &_tpop, _lbuttons, widthLButtons, "Pop", _adobe ? "popular" : ""    );
	if (  _adobe ) CreateButton( &_trec, _lbuttons, widthLButtons, "Rec", _adobe ? "recent"  : ""    );
	if (  _adobe ) CreateButton( &_tcla, _lbuttons, widthLButtons, "Cla", _adobe ? "rating"  : ""    );

	CreateButton( &_tran, _lbuttons, widthLButtons, "Ran", "random" );
 };

/*Creacion - public*/
__fastcall pNet::pNet( TComponent *owner, String type ) : pPallets(owner) {
	_adobe = type == "adobe";

	CreateThis   ();
	CreateNPP    ();
	CreateButtons();

	_lpallets->MarT = _ledit->Height + 1;
 };
//###########################################################################


/*Hilos*/
void __fastcall pNet::thini_net( wThread *thread ) {
	if ( thread->setRequest == "" ) return;

	/*Librerias*/
	TResourceStream *rs;

	if ( !FileExists( ".\\libeay32.dll" ) ) {
		rs           = new TResourceStream( (int)HInstance, "LIBEAY32", L"DLL" );
		rs->Position = 0;
		rs->SaveToFile( ".\\libeay32.dll" );
		delete rs;
	}

	if ( !FileExists( ".\\ssleay32.dll" ) ) {
		rs           = new TResourceStream( (int)HInstance, "SSLEAY32", L"DLL" );
		rs->Position = 0;
		rs->SaveToFile( ".\\ssleay32.dll" );
		delete rs;
	}

	/*Descarga*/
	this->ReadOnly = false;
	this->Clear();

	TIdSSLIOHandlerSocketOpenSSL *
	hso                          = new TIdSSLIOHandlerSocketOpenSSL( NULL );
	hso->SSLOptions->Method      = sslvSSLv23;
	hso->SSLOptions->Mode        = sslmUnassigned;
	hso->SSLOptions->VerifyMode  = TIdSSLVerifyModeSet();
	hso->SSLOptions->VerifyDepth = 0;
	hso->Host                    = "";

	TIdHTTP *
	htt                                   = new TIdHTTP( NULL );
	htt->IOHandler                        = hso;
	htt->AllowCookies                     = true;
	htt->ProxyParams->BasicAuthentication = false;
	htt->ProxyParams->ProxyPort           = 0;
	htt->Request->ContentLength           = -1;
	htt->Request->ContentRangeEnd         = 0;
	htt->Request->ContentRangeStart       = 0;
	htt->Request->Accept                  = "text/html, */*";
	htt->Request->BasicAuthentication     = false;
	htt->Request->UserAgent               = "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36";
	htt->HTTPOptions                      = TIdHTTPOptions() << hoForceEncodeParams;

	thread->setResponce = htt->Get( thread->setRequest );

	if ( _adobe ) this->GetAdobe( thread ); else this->GetLover( thread );

	delete htt;
	delete hso;
 };
void __fastcall pNet::thfin_net( wThread *thread ) {
	if ( !thread->Cancel ) {
		this->ReadOnly = true;
		this->Render();

		_loader->HideL( true );
		_loader = null;
	}
 };
//###########################################################################


/*Eventos - private*/
void __fastcall pNet::click_button( TObject *sender ) {
	TText *tex = (TText*)sender;
	int    cou = sai( _fnpp->Text );

	if ( cou < 1   ) cou = 1;
	if ( cou > 100 ) cou = 100;

	this->QueryNet(
		_adobe ?
			"https://kuler-api.adobe.com/rss/get.cfm?"
			"listtype=" + tex->TagString + "&"
			"startIndex=0&"
			"itemsPerPage=" + String(cou) + "&"
			"key=CBJCHBCAABAAtxw4H7UgWFWvhIISqtn48F4U8EhR6q_g"
			:
			"http://www.colourlovers.com/api/palettes/" + tex->TagString + "?format=xml&numResults=" + String(cou)
	);

	_rselect->TagObject = tex;

	if ( !_rselect->Opacity ) {
		_rselect->PosX = tex->PosX;

		AnimO( _rselect, 0.5, 1, sfSinusoidalOut );
	}
	else AnimL( _rselect, 0.5, tex->PosX, sfSinusoidalOut );
 };
void __fastcall pNet::showl_loader( TObject *sender ) {
	_thread->Play();
 };
//###########################################################################


/*Metodos - private*/
void pNet::ChangeColor() {
	pPallets::ChangeColor();

	_fnpp->Fill = _preserveColor;

	_rselect->StrC = _preserveColor;
 };

void pNet::QueryNet( String url      ) {
	if ( _thread )
		_thread->Cancel = true;

	_thread             = new wThread;
	_thread->setRequest = url;
	_thread->onThread   = thini_net;
	_thread->onFinal    = thfin_net;

	if ( !_loader ) {
		_loader         = new fLoader( null );
		_loader->Parent = _lpallets;
		_loader->Color  = _preserveColor;
		_loader->Fill   = colorBlack;
		_loader->onShow = showl_loader;
		_loader->ShowL( true );
		_loader->BringToFront();
	}
	else _thread->Play();
 };
void pNet::GetAdobe( wThread *thread ) {
	#define thc !thread->Cancel

	int      pos = 0;
	int      len = thread->setResponce.Length();
	wchar_t *str = thread->setResponce.w_str();

	for ( ;pos<len && thc; pos++ ) {
		if ( str[pos]=='<' && pos+16<len &&
			str[pos+1 ]=='k' && str[pos+2 ]=='u' && str[pos+3 ]=='l' && str[pos+4 ]=='e' && str[pos+5 ]=='r' && str[pos+6 ]==':' &&
			str[pos+7 ]=='t' && str[pos+8 ]=='h' && str[pos+9 ]=='e' && str[pos+10]=='m' && str[pos+11]=='e' && str[pos+12]=='T' &&
			str[pos+13]=='i' && str[pos+14]=='t' && str[pos+15]=='l' && str[pos+16]=='e'
		) {
			pos+= 18;

			cPalette *pal = new cPalette;
			String    tem = "";

            pal->Select = 0;

			for ( ;pos<len && thc && str[pos]!='<'; pos++ ) pal->Title+= str[pos]; pos++;
			for ( ;pos<len && thc; pos++ ) {
				if ( str[pos]=='<' && pos+5<len && str[pos+1]=='/' && str[pos+2]=='i' && str[pos+3]=='t' && str[pos+4]=='e' && str[pos+5]=='m' ) break;
				else if ( str[pos]=='<' && pos+20<len &&
					str[pos+1 ]=='k' && str[pos+2 ]=='u' && str[pos+3 ]=='l' && str[pos+4 ]=='e' && str[pos+5 ]=='r' && str[pos+6 ]==':' &&
					str[pos+7 ]=='s' && str[pos+8 ]=='w' && str[pos+9 ]=='a' && str[pos+10]=='t' && str[pos+11]=='c' && str[pos+12]=='h' &&
					str[pos+13]=='H' && str[pos+14]=='e' && str[pos+15]=='x' && str[pos+16]=='C' && str[pos+17]=='o' && str[pos+18]=='l' &&
					str[pos+19]=='o' && str[pos+20]=='r'
				) {
					pos+= 22;

					for ( tem = ""; pos<len && thc && str[pos]!='<'; pos++ ) tem+= str[pos]; pos++;

					pal->Colors+= sai( "0xFF" + tem );
				}
			}

			if ( thc ) Palettes+= (int)pal;
		}
	}
 };
void pNet::GetLover( wThread *thread ) {
	#define thc !thread->Cancel

	int      pos = 0;
	int      len = thread->setResponce.Length();
	wchar_t *str = thread->setResponce.w_str();

	for ( ;pos<len && thc; pos++ ) {
		if ( str[pos]=='<' && pos+15<len &&
			str[pos+1 ]=='t' && str[pos+2 ]=='i' && str[pos+3 ]=='t' && str[pos+4 ]=='l' && str[pos+5 ]=='e' && str[pos+6 ]=='>' &&
			str[pos+7 ]=='<' && str[pos+8 ]=='!' && str[pos+9 ]=='[' && str[pos+10]=='C' && str[pos+11]=='D' && str[pos+12]=='A' &&
			str[pos+13]=='T' && str[pos+14]=='A' && str[pos+15]=='['
		) {
			pos+= 16;

			String    tem = "";
			cPalette *pal = new cPalette;

			pal->Select = 0;

			for ( ;pos<len && thc && ( str[pos]!=']' || ( pos+1<len && str[pos+1]!=']' ) ); pos++ ) pal->Title+= str[pos]; pos++;
			for ( ;pos<len && thc; pos++ ) {
				if ( str[pos]=='<' && pos+7<len && str[pos+1]=='/' && str[pos+2]=='c' && str[pos+3]=='o' && str[pos+4]=='l' && str[pos+5]=='o' && str[pos+6]=='r' && str[pos+7]=='s' ) break;
				else if ( str[pos]=='<' && pos+3<len && str[pos+1]=='h' && str[pos+2]=='e' && str[pos+3]=='x' ) {
					pos+= 5;

					for ( tem = ""; pos<len && thc && str[pos]!='<'; pos++ ) tem+= str[pos]; pos++;

					pal->Colors+= sai( "0xFF" + tem );
				}
			}

			if ( thc ) Palettes+= (int)pal;
		}
	}
 };
//###########################################################################