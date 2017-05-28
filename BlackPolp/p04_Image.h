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

#ifndef p04_ImageH
#define p04_ImageH

#include "def.h"
#include "c01_base.h"

class pImage : public cBase {
	/*Variables*/private:
	__int64 _totals;
	float   _position;

	String   _path;
	wThread *_thread;
	fLoader *_loader;

	/*Variables - controles*/private:
	TRectangle *_rback;

	TRectangle *_rdrop;
	TPath      *_pdrop;
	TText      *_tdrop;

	sIField     _ppercent;
	sIField     _rpercent;
	sIField     _tpercent;
	TLayout    *_spercent;
	TLayout    *_lpercent;
	TRectangle *_rscroll ;

	sIField        _ppallet;
	TScaledLayout *_lpallet;

	TLayout *_limage;
	TImage  *_iimage;

	TRectangle    *_rbutton;
	TPath         *_pbutton;
	TShadowEffect *_ebutton;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateThis   ();
	void CreateDrop   ();
	void CreatePercent();
	void CreateColors ();
	void CreateImage  ();
	void CreateButton ();

	/*Creacion*/public:
	__fastcall  pImage( TComponent *owner );
	//###########################################################################


	/*Hilos*/private:
	void __fastcall thini_image( wThread *sender );
	void __fastcall thsyn_imagd( wThread *sender );
	void __fastcall thsyn_imagp( wThread *sender );
	void __fastcall thsyn_imagi( wThread *sender );
	void __fastcall thfin_image( wThread *sender );
	//###########################################################################


	/*Intervalos*/private:
	void __fastcall timer_scroll( TObject *sender );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall resiz_this( TObject *sender                                                   );
	void __fastcall mouwh_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled );

	void __fastcall moudw_pallet( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall moudw_rcolor( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall showl_cloader( TObject *sender );

	void __fastcall click_rbutton( TObject *sender );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();

	/*Metodos*/public:
	void GetImage( String path                                                              );
	void Render  (                                                                          );
	void Drop    ( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	//###########################################################################


	/*Funciones*/private:
	String GetPallet   (                                                                                  );
	void   GetColors   ( TList__1<unsigned> **colors, TList__1<int> **orders, TBitmap *bmap, float delta  );
	void   GetGradients( TList__1<unsigned> **colors, TList__1<int> **orders, bool gradients, float delta );

	int      Partition   ( TList__1<unsigned> **colors, TList__1<int     > **orders, int p, int r                );
	void     QuickSort   ( TList__1<unsigned> **colors, TList__1<int     > **orders, int p, int r                );
	unsigned FindAdjacent( TList__1<unsigned>  *colors, TList__1<unsigned>  *orders, unsigned color, float delta );
	unsigned Normalize   ( TList__1<unsigned>  *colors, TList__1<unsigned>  *orders, unsigned color, float delta );
	//###########################################################################
 };

#endif
