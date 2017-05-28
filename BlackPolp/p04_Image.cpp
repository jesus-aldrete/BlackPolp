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
#include "p04_Image.h"
#pragma package(smart_init)



//Otros #####################################################################
/*Definiciones*/
#define heightItem 25
#define preWid     500.0
#define preHei     500.0
#define setColors  i64[1]
#define setOrders  i64[2]
#define setTotals  i64[3]
#define setColor   i64[4]
#define setOrder   i64[5]
//###########################################################################



// class pImage : public cBase //############################################
/*Creacion - controles - private*/
void pImage::CreateThis   () {
	this->OnResize     = resiz_this;
	this->OnMouseWheel = mouwh_this;

	_rback           = new TRectangle( this );
	_rback->Parent   = this;
	_rback->Align    = AL::Contents;
	_rback->StrK     = BK::None;
	_rback->FilC     = colorBlack;
	_rback->TagFloat = dzCImage;
 };
void pImage::CreateDrop   () {
	_rdrop                  = new TRectangle( this );
	_rdrop->Parent          = this;
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
	_tdrop->Text         = "Arrastra imagen\naquí";
	_tdrop->Color        = colorGray2;
	_tdrop->Font->Family = fontFamily;
	_tdrop->Font->Size   = 14;
	_tdrop->HitTest      = false;
 };
void pImage::CreatePercent() {
	_lpercent               = new TLayout( this );
	_lpercent->Parent       = this;
	_lpercent->Align        = AL::MostLeft;
	_lpercent->Width        = 80;
	_lpercent->MarR         = 10;
	_lpercent->MarL         = 5;
	_lpercent->MarT         = 1;
	_lpercent->ClipChildren = true;

	_spercent         = new TLayout( this );
	_spercent->Parent = _lpercent;
	_spercent->Align  = AL::Top;

	_rscroll          = new TRectangle( this );
	_rscroll->Parent  = _lpercent;
	_rscroll->StrK    = BK::None;
	_rscroll->FilC    = _preserveColor;
	_rscroll->Width   = 3;
	_rscroll->PosY    = 0;
	_rscroll->PosX    = _lpercent->Width - _rscroll->Width;
	_rscroll->HitTest = false;
 };
void pImage::CreateColors () {
	_lpallet              = new TScaledLayout( this );
	_lpallet->Parent      = this;
	_lpallet->Align       = AL::Left;
	_lpallet->MarB        = 5;
	_lpallet->Width       = 40;
	_lpallet->OnMouseDown = moudw_pallet;
 };
void pImage::CreateImage  () {
	_limage         = new TLayout( this );
	_limage->Parent = this;
	_limage->Align  = AL::Client;

	_iimage          = new TImage( this );
	_iimage->Parent  = _limage;
	_iimage->Align   = AL::Contents;
	_iimage->MarL    = 5;
	_iimage->MarR    = 5;
	_iimage->MarB    = 5;
	_iimage->HitTest = false;
 };
void pImage::CreateButton () {
	_rbutton          = new TRectangle( this );
	_rbutton->Parent  = this;
	_rbutton->Height  = 30;
	_rbutton->Width   = 30;
	_rbutton->PosY    = this->Height - _rbutton->Height - 10;
	_rbutton->PosX    = this->Width  - _rbutton->Width  - 10;
	_rbutton->Anchors = TAnchors() << TAnchorKind::akRight << TAnchorKind::akBottom;
	_rbutton->StrK    = BK::None;
	_rbutton->FilC    = colorGray3;
	_rbutton->XRadius = 15;
	_rbutton->YRadius = 15;
	_rbutton->Cursor  = crHandPoint;
	_rbutton->OnClick = click_rbutton;

	_ebutton            = new TShadowEffect( this );
	_ebutton->Parent    = _rbutton;
	_ebutton->Direction = 0.001;
	_ebutton->Distance  = 0.001;
	_ebutton->Opacity   = 0.5  ;
	_ebutton->Softness  = 0.2  ;

	_pbutton             = new TPath( this );
	_pbutton->Parent     = _rbutton;
	_pbutton->Align      = AL::Center;
	_pbutton->StrK       = BK::None  ;
	_pbutton->FilC       = colorBlack;
	_pbutton->Width      = 30;
	_pbutton->Height     = 30;
	_pbutton->HitTest    = false;
	_pbutton->Data->Data = "M3.5,7.5c0-0.5,0.4-0.9,0.9-0.9C5,6.6,5.3,7,5.3,7.5C5.3,8,5,8.4,4.4,8.4 C3.9,8.4,3.5,8,3.5,7.5z M6.6,7.5C6.6,7,7,6.6,7.5,6.6C8,6.6,8.4,7,8.4,7.5C8.4,8,8,8.4,7.5,8.4C7,8.4,6.6,8,6.6,7.5z M9.7,7.5c0-0.5,0.4-0.9,0.9-0.9c0.5,0,0.9,0.4,0.9,0.9c0,0.5-0.3,0.9-0.9,0.9 C10,8.4,9.7,8,9.7,7.5z M0,0 M15,15";
 };

/*Creacion - public*/
__fastcall  pImage::pImage( TComponent *owner ) : cBase(owner) {
	CreateThis   ();
	CreateDrop   ();
	CreatePercent();
	CreateColors ();
	CreateImage  ();
	CreateButton ();
 };
//###########################################################################


/*Hilos - private*/
void __fastcall pImage::thini_image( wThread *sender ) {
	if ( !FileExist( _path ) ) return;

	sender->Cancel = true;

	TBitmap *bmap = new TBitmap(); try { bmap->LoadFromFile( _path ); } catch (...) {}

	TList__1<unsigned> *colors = new TList__1<unsigned>;
	TList__1<int     > *orders = new TList__1<int     >;

	if ( bmap->Width >= bmap->Height ) {
		if ( bmap->Width > preWid )
			bmap->Resize( preWid, ( preWid * bmap->Height ) / bmap->Width );
	}
	else if ( bmap->Height > preHei ) {
		bmap->Resize( preHei, ( preHei * bmap->Width ) / bmap->Height );
	}

	_totals = 0;

	GetColors   ( &colors, &orders, bmap , 24 );
	GetGradients( &colors, &orders, true , 24 );
	GetGradients( &colors, &orders, false, 24 );

	sender->setColors = (__int64)colors;
	sender->setOrders = (__int64)orders;

	_lpallet->OriginalWidth  = _lpallet->Width ;
	_lpallet->OriginalHeight = _lpallet->Height;

	/*Creacion*/
	sender->Sync( thsyn_imagd );

	for ( int i = 0; i < colors->Count; i++ ) {
		sender->setColor = colors->Items[i];
		sender->setOrder = orders->Items[i];

		sender->Sync( thsyn_imagp );

		_spercent->Height = _ppercent.Size * heightItem;

		_rscroll->BringToFront();
	}

	sender->Sync( thsyn_imagi );

    sender->Cancel = false;

	/*Final*/
	delete colors;
	delete orders;
	delete bmap;
 };
void __fastcall pImage::thsyn_imagd( wThread *sender ) {
	/*Colores*/
	for ( int i = 0; i < _ppercent.Size; i++ ) {
		delete (TText*  )_tpercent[i].Value;
		delete (TCircle*)_rpercent[i].Value;
		delete (TLayout*)_ppercent[i].Value;
	}

	_tpercent.Clear();
	_rpercent.Clear();
	_ppercent.Clear();

	/*Paleta*/
	for ( int i = 0; i < _ppallet.Size; i++ )
		delete (TRectangle*)_ppallet[i].Value;

	_ppallet.Clear();
 };
void __fastcall pImage::thsyn_imagp( wThread *sender ) {
	widthLetter;

	/*Colores*/
	TLayout *
	lay         = new TLayout( null );
	lay->Parent = _spercent;
	lay->PosY   = this->Height + 1000;
	lay->Align  = AL::Top;
	lay->Height = 20;
	lay->MarT   = 5;

	TCircle *
	cir              = new TCircle( null );
	cir->Parent      = lay;
	cir->Align       = AL::Left;
	cir->StrC        = colorGray2;
	cir->FilC        = sender->setColor;
	cir->Width       = 20;
	cir->OnMouseDown = moudw_rcolor;

	TText *
	tex                = new TText( null );
	tex->Parent        = lay;
	tex->Align         = AL::Client;
	tex->Color         = colorGray3;
	tex->Font->Family  = fontFamily;
	tex->Font->Size    = fontSize;
	tex->Text          = FormatFloat( "0.000", ( float(sender->setOrder) * 100 ) / ( _totals ? float(_totals) : 1 ) ) + "%";
	tex->Width         = wil * 8;
	tex->HorzTextAlign = TTextAlign::Trailing;

	_ppercent+= (int)lay;
	_rpercent+= (int)cir;
	_tpercent+= (int)tex;

	/*Paleta*/
	float hei = ( float(sender->setOrder) * _lpallet->Height ) / ( _totals ? float(_totals) : 1.0 );

	if ( hei >= 1 && _ppallet.Size < numberColors ) {
		TRectangle *
		rec          = new TRectangle( null );
		rec->Parent  = _lpallet;
		rec->PosY    = this->Height + 1000;
		rec->Align   = _ppallet.Size == 0 ? AL::Client : AL::Bottom;
		rec->StrK    = BK::None;
		rec->FilC    = sender->setColor ? sender->setColor : claBlue;
		rec->Height  = hei;
		rec->HitTest = false;
		rec->Tag     = sender->setOrder;

		_ppallet+= (int)rec;
	}
 };
void __fastcall pImage::thsyn_imagi( wThread *sender ) {
	try { _iimage->Bitmap->LoadFromFile( _path ); } catch (...) {}
 };
void __fastcall pImage::thfin_image( wThread *sender ) {
	if ( !sender->Cancel ) {
		_rdrop  ->Visible = false;
		_lpallet->HitTest = true ;
	}

	_loader->HideL( true );

	_loader   = null;
	_thread   = null;
	_position = 0;

	Render();
 };
//###########################################################################


/*Intervalos - private*/
void __fastcall pImage::timer_scroll( TObject *sender ) {
	AnimO( _rscroll, 0.5, 0, sfBackOut );
 };
//###########################################################################


/*Eventos - private*/
void __fastcall pImage::resiz_this( TObject *sender                                                   ) {
	Render();
 };
void __fastcall pImage::mouwh_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled ) {
	_position-= ( wheelDelta / 3 );

	Render();
 };

void __fastcall pImage::moudw_pallet( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	varPom;
	TLayout *rec = (TLayout*)sender;
	float    px1 = pom.x, py1 = pom.y;

	while ( whileDown ) {
		GetCursorPos( &pom );

		if (
			( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
			( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
		) {
			wDragDrop::DoDragText( DROPEFFECT_COPY | DROPEFFECT_MOVE, true, BMPaDBM( _lpallet->MakeScreenshot(),
				pom.x - fom.left - rec->AbsoluteRect.left,
				pom.y - fom.top  - rec->AbsoluteRect.top
			), 2, GetPallet(), (String)(int)this );
			break;
		}
	}
 };
void __fastcall pImage::moudw_rcolor( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	varPom;
	TCircle *rec = (TCircle*)sender;
	float    px1 = pom.x, py1 = pom.y;

	while ( whileDown ) {
		GetCursorPos( &pom );

		if (
			( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
			( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
		) {
			ColorDrop( null, IntToHex( (int)rec->FilC, 8 ),
				pom.x - fom.left - rec->AbsoluteRect.left - x + 25,
				pom.y - fom.top  - rec->AbsoluteRect.top  - y + 25,
			null );
			break;
		}
	}
 };

void __fastcall pImage::showl_cloader( TObject *sender ) {
	_iimage->Bitmap->Clear(0);

	if ( _thread )
		_thread->Play();
 };

void __fastcall pImage::click_rbutton( TObject *sender ) {
	wDialog*
	dig             = new wDialog;
	dig->Filter     = "*.jpg;*.jpeg;|Imagen|*.png|Imagen|*.bmp|Mapa de bits";
	dig->AllFiles   = "Todos los archivos";
	dig->AllFormats = "Todos los formatos";
	dig->Index      = 3;

	if ( dig->RunOP() )
		GetImage( dig->Path );

	delete dig;
 };
//###########################################################################


/*Metodos - private*/
void pImage::ChangeColor() {
	_rscroll->FilC = _preserveColor;

	if ( _loader )
		_loader->Fill = _preserveColor;
 };

/*Metodos - public*/
void pImage::GetImage( String path                                                              ) {
	if ( _thread ) return;

	_loader         = new fLoader( null );
	_loader->Parent = this;
	_loader->Fill   = colorBlack;
	_loader->Color  = _preserveColor;
	_loader->onShow = showl_cloader;
	_loader->ShowL( true );

	_path             = path;
	_thread           = new wThread;
	_thread->onThread = thini_image;
	_thread->onFinal  = thfin_image;
 };
void pImage::Render  (                                                                          ) {
	StopInterval( (String)(unsigned)this );

	float max = _ppercent.Size * heightItem;
	float mam = _ppercent.Size * heightItem - _lpercent->Height + 5;

	if ( _position > mam ) _position = mam;
	if ( _position < 0   ) _position = 0;

	_spercent->PosY = -_position;

	_rscroll->Height  = ( _lpercent->Height * _lpercent->Height ) / ( max ? max : 1 ); if ( _rscroll->Height < 10 ) _rscroll->Height = 10;
	_rscroll->Visible = _rscroll->Height < _lpercent->Height;

	if ( _rscroll->Visible ) {
		_rscroll->PosY    = ( _position * ( _lpercent->Height - _rscroll->Height ) ) / ( mam ? mam : 1 );

		AnimO( _rscroll, 0.3, 0.8, sfBackOut );
		SetTimeout( (String)(unsigned)this, 0.8, timer_scroll );
	}
 };
void pImage::Drop    ( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	int ind = IsImages( files );

	if ( ind > -1 )
		GetImage( files[ind] );
 };
//###########################################################################


/*Funciones - private*/
String pImage::GetPallet   (                                                                                  ) {
	String res = ExtractFileName( _path ) + "|0|";

	for ( int i = 0; i < _ppallet.Size; i++ )
		res+= IntToHex( (int)((TRectangle*)_ppallet[i].Value)->FilC, 8 ) + ",";

	return res;
 };
void   pImage::GetColors   ( TList__1<unsigned> **colors, TList__1<int> **orders, TBitmap *bmap, float delta  ) {
	if ( !colors || !orders || !bmap ) return;

	int         ind;
	float       red, gre, blu, hde;
	unsigned    col;
	TBitmapData bda;

	if ( delta > 2 ) hde = delta / 2.0 - 1.0;
	else             hde = 0.0;

	_totals = 0;

	if ( bmap->Map( TMapAccess::ReadWrite, bda ) ) {
		try {
			for ( int y = 0; y < bmap->Height; y++ ) {
				for ( int x = 0; x < bmap->Width; x++ ) {
					_totals++;

					col = bda.GetPixel( x, y );

					if ( delta > 1 ) {
						red = int( ( RRGB(col) + hde ) / delta ) * delta;
						gre = int( ( GRGB(col) + hde ) / delta ) * delta;
						blu = int( ( BRGB(col) + hde ) / delta ) * delta;

						if ( red > 255 ) red = 255;
						if ( gre > 255 ) gre = 255;
						if ( blu > 255 ) blu = 255;

						col = ACOL( 255, red, gre, blu );
					}

					ind = (*colors)->IndexOf( col );

					if ( ind == -1 ) {
						(*colors)->Add( col );
						(*orders)->Add( 1   );
					}
					else (*orders)->Items[ind] = (*orders)->Items[ind] + 1;
				}
			}
		}
		__finally {
			bmap->Unmap( bda );
		}
	}
 };
void   pImage::GetGradients( TList__1<unsigned> **colors, TList__1<int> **orders, bool gradients, float delta ) {
	QuickSort( colors, orders, 0, (*orders)->Count - 1 );

	TList__1<unsigned> *cog = new TList__1<unsigned>;
	TList__1<unsigned> *con = new TList__1<unsigned>;

	for ( int i = 0; i < (*colors)->Count; i++ ) {
		unsigned nco, col = (*colors)->Items[i];
		int      ind = con->IndexOf( col );

		if ( ind == -1 ) {
			nco = gradients ? FindAdjacent( cog, con, col, delta ) : Normalize( cog, con, col, delta );

			con->Add( col );
			cog->Add( nco );
		}
		else nco = cog->Items[ind];

		if ( nco != col ) {
			ind = (*colors)->IndexOf( nco );

			if ( ind == -1 ) {
				(*colors)->Add( nco );
				(*orders)->Add( (*orders)->Items[i] );
			}
			else (*orders)->Items[ind] = (*orders)->Items[ind] + (*orders)->Items[i];

			(*orders)->Delete( i   );
			(*colors)->Delete( i-- );
		}
	}

	delete cog;
	delete con;
 };

int      pImage::Partition   ( TList__1<unsigned> **colors, TList__1<int     > **orders, int p, int r                ) {
	int piv = (*orders)->Items[r];

	while ( p < r ) {
		while ( (*orders)->Items[p] > piv ) p++;
		while ( (*orders)->Items[r] < piv ) r--;

		if      ( (*orders)->Items[p] == (*orders)->Items[r] ) p++;
		else if ( p < r ) {
			int      tmn = (*orders)->Items[p];
			unsigned tmc = (*colors)->Items[p];

			(*orders)->Items[p] = (*orders)->Items[r];
			(*colors)->Items[p] = (*colors)->Items[r];

			(*orders)->Items[r] = tmn;
			(*colors)->Items[r] = tmc;
		}
	}

	return r;
 };
void     pImage::QuickSort   ( TList__1<unsigned> **colors, TList__1<int     > **orders, int p, int r                ) {
	if ( p < r ) {
		int j = Partition( colors, orders, p, r );

		QuickSort( colors, orders, p    , j - 1 );
		QuickSort( colors, orders, j + 1, r     );
	}
 };
unsigned pImage::FindAdjacent( TList__1<unsigned>  *colors, TList__1<unsigned>  *orders, unsigned color, float delta ) {
	int      red = RRGB(color);
	int      gre = GRGB(color);
	int      blu = BRGB(color);
	int      ind;
	unsigned nco;

	if ( red > delta ) { nco = ACOL( 255, red - delta, gre        , blu         ); ind = orders->IndexOf( nco ); if ( ind > -1 ) return orders->Items[ind]; }
	if ( gre > delta ) { nco = ACOL( 255, red        , gre - delta, blu         ); ind = orders->IndexOf( nco ); if ( ind > -1 ) return orders->Items[ind]; }
	if ( blu > delta ) { nco = ACOL( 255, red        , gre        , blu - delta ); ind = orders->IndexOf( nco ); if ( ind > -1 ) return orders->Items[ind]; }

	if ( red < 255 - delta ) { nco = ACOL( 255, red + delta, gre        , blu         ); ind = orders->IndexOf( nco ); if ( ind > -1 ) return colors->Items[ind]; }
	if ( gre < 255 - delta ) { nco = ACOL( 255, red        , gre + delta, blu         ); ind = orders->IndexOf( nco ); if ( ind > -1 ) return colors->Items[ind]; }
	if ( blu < 255 - delta ) { nco = ACOL( 255, red        , gre        , blu + delta ); ind = orders->IndexOf( nco ); if ( ind > -1 ) return colors->Items[ind]; }

	return color;
 };
unsigned pImage::Normalize   ( TList__1<unsigned>  *colors, TList__1<unsigned>  *orders, unsigned color, float delta ) {
	int lowest  = 255;
	int highest = 0  ;
	int red     = RRGB( color );
	int gre     = GRGB( color );
	int blu     = BRGB( color );

	if ( red < lowest ) { lowest = red; }
	if ( gre < lowest ) { lowest = gre; }
	if ( blu < lowest ) { lowest = blu; }

	if ( red > highest ) { highest = red; }
	if ( gre > highest ) { highest = gre; }
	if ( blu > highest ) { highest = blu; }

	if ( lowest == highest ) {
		if ( delta <= 32 ) {
			if ( lowest == 0 || highest >= ( 255 - delta ) ) {
				return color;
			}
		}
		else return color;
	}

	for ( ; highest < 256; lowest += delta, highest += delta ) {
		unsigned nco = ACOL( 255, red - lowest, gre - lowest, blu - lowest );

		if ( orders->IndexOf( nco ) > -1 ) {
			return nco;
		}
	}

	return color;
 };
//###########################################################################