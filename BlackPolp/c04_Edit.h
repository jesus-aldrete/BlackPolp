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

#ifndef c04_EditH
#define c04_EditH

#include "def.h"
#include "c01_base.h"

class cEdit : public cBase {
	/*Variables*/private:
	bool _dblclick;

	/*Variables - controles*/private:
	TRectangle *_rback;

	TLayout *_lhex;
	TLayout *_lf; TText *_tf; fLine *_ff;
	TLayout *_lw; TText *_tw; fLine *_fw;
	TLayout *_lv; TText *_tv; fLine *_fv;
	TLayout *_lu; TText *_tu; fLine *_fu;

	TLayout *_lrgb;
	TLayout *_lr; TText *_tr; fLine *_fr;
	TLayout *_lg; TText *_tg; fLine *_fg;
	TLayout *_lb; TText *_tb; fLine *_fb;
	TLayout *_la; TText *_ta; fLine *_fa;

	TLayout *_lhsl;
	TLayout *_lh; TText *_th; fLine *_fh;
	TLayout *_ls; TText *_ts; fLine *_fs;
	TLayout *_ll; TText *_tl; fLine *_fl;
	TLayout *_lo; TText *_to; fLine *_fo;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateEdit( TLayout *lparent, TLayout **lbox, TText **ttitle, String title, fLine **fline, bool max );

	void CreateThis();
	void CreateHEX ();
	void CreateRGB ();
	void CreateHSL ();

	/*Creacion*/public:
	__fastcall cEdit( TComponent *owner );
	//###########################################################################


	/*Intervalos*/private:
	void __fastcall timer_edit( TObject *sender );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall keyen_this( TObject *sender );

	void __fastcall exitt_edit( TObject *sender                                                           );
	void __fastcall moudw_edit( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();
	//###########################################################################
};

#endif