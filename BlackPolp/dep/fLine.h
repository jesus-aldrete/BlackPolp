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

#ifndef fLineH
#define fLineH

#include <FMX.Layouts.hpp>
#include <sFields.h>
#include <wGeneral.h>
#include <wDragDrop.h>
#include <fAnim.h>

class PACKAGE fLine : public TLayout {
	/*Variables*/private:
	bool _readOnly;

	bool  _insert     ;
	float _widthLetter;
	float _widthCursor;

	float _position;
	int   _startPos;
	int   _finalPos;

	TPoint   _pointsDblDown;
	TObject *_senderDblDown;

	bool         _buttonSelDown;
	TShiftState  _shiftsSelDown;
	float        _pointxSelDown;
	TObject     *_senderSelDown;

	int     _undoIndex;
	bool    _undoDelay;
	sSField _undoTexts;
	sIField _undoStart;
	sIField _undoFinal;

	/*Variables*/public:
	bool NoRender;

	/*Variables - controles*/private:
	TRectangle *_rcursor;
	TRectangle *_rselect;
	TRectangle *_rscroll;
	TText      *_twords ;

	/*Variables - propiedades*/private:
	unsigned _fill  ;
	unsigned _color ;
	String   _text  ;
	String   _family;
	float    _size  ;

	/*Variables - Eventos*/public:
	TNotifyEvent onEnter;
	TNotifyEvent onExit;
	TNotifyEvent onKeyEnter;
	TNotifyEvent onKeyChange;
	//###########################################################################


	/*Creacion*/private:
	void CreateThis  ();
	void CreateCursor();
	void CreateText  ();
	void CreateSelect();
	void CreateScroll();

	/*Creacion*/public:
	__fastcall  fLine( TComponent *owner );
	__fastcall ~fLine(                   );
	//###########################################################################


	/*Propiedades*/private:
	void WFill  ( unsigned fill   );
	void WColor ( unsigned color  );
	void WText  ( String   text   );
	void WFamily( String   family );
	void WSize  ( float    size   );

	/*Propiedades*/public:
	__property unsigned Fill     = { read=_fill    , write=WFill     };
	__property unsigned Color    = { read=_color   , write=WColor    };
	__property String   Text     = { read=_text    , write=WText     };
	__property String   Family   = { read=_family  , write=WFamily   };
	__property float    Size     = { read=_size    , write=WSize     };
	__property bool     ReadOnly = { read=_readOnly, write=_readOnly };
	//###########################################################################


	/*Intervalos*/private:
	void __fastcall showw_cursor( TObject *sender );

	void __fastcall timer_undo( TObject *sender );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall resiz_this( TObject *sender                                                           );
	void __fastcall enter_this( TObject *sender                                                           );
	void __fastcall exitt_this( TObject *sender                                                           );
	void __fastcall wheel_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled         );
	void __fastcall moudw_this( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall keydw_this( TObject *sender, WORD &key, System::WideChar &keyChar, TShiftState shift  );

	void __fastcall click_edit( TObject *sender                                                           );
	void __fastcall dblcl_edit( TObject *sender                                                           );
	void __fastcall moudw_edit( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall click_select( TObject *sender                                                           );
	void __fastcall dblcl_select( TObject *sender                                                           );
	void __fastcall moudw_select( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	//###########################################################################


	/*Metodos*/public:
	void   Render  ( bool reposition      );
	void   Select  ( int start, int final );
	String Selected(                      );
	//###########################################################################


	/*Funciones*/private:
	void KeyInsert( bool    insert    );
	void KeyEnter (                   );
	void KeyAdd   ( wchar_t keyChar   );
	void KeyDelete( bool    saveUndo  );
	void KeyStart ( TShiftState shift );
	void KeyFin   ( TShiftState shift );
	void KeyLeft  ( TShiftState shift );
	void KeyRight ( TShiftState shift );
	void KeyAll   (                   );
	void KeySuprim(                   );
	void KeyCopy  (                   );
	void KeyPaste (                   );
	void KeyCut   (                   );
	void KeyUndo  ( TShiftState shift );

	float GetAjust( float x    );
	void  SetUndo ( bool timer );

	void ClickEdit( float x, TShiftState shift );
	void ViewPopUp( float x, float y           );
	//###########################################################################
 };

#endif
