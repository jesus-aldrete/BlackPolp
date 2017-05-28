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

#ifndef fAnimH
#define fAnimH

#include <FMX.Objects.hpp>

#include "sGeneral.h"
#include "wGeneral.h"

#define Configure                                              \
	if ( id != "" ) {                                          \
		for ( int i = 0; i < fAnimIDS->Count; i++ ) {          \
			if ( fAnimIDS->Items[i] == id )                    \
				((fAnim*)fAnimPOI->Items[i])->Final( false );  \
		}                                                      \
	}                                                          \
															   \
	ani           = new fAnim                         ;        \
	ani->_id      = id                                ;        \
	ani->_handle  = GetHandle()                       ;        \
	ani->_onFrame = onframe                           ;        \
	ani->_onFinal = onfinal                           ;        \
	ani->parent   = (TShape*)parent                   ;        \
	ani->Max      = duration * TTime( 0, 0, 1, 0 ).Val;        \
															   \
	fAnimIDS->Add( id           );                             \
	fAnimPOI->Add( (__int64)ani );

class PACKAGE fAnim {
	/*Variables*/private:
	String  _id      ;
	HWND    _handle  ;
	sfWave  _onFrame ;
	sfAnim  _onFinal ;
	sfAnim  _onCustom;

	double _startP;
	double _finalP;

	double _startL;
	double _startA;
	double _startB;
	double _startH;
	double _finalL;
	double _finalA;
	double _finalB;
	double _finalH;

	/*Variables*/public:
	double  Max    ;
	double  Percent;
	TTime   Date   ;
	TShape *parent ;
	//###########################################################################


	/*Creacion*/public:
	fAnim();
	//###########################################################################


	/*Metodos*/public:
	void onFrameHeight ();
	void onFrameWidth  ();
	void onFrameTop    ();
	void onFrameLeft   ();
	void onFrameMarginT();
	void onFrameOpacity();
	void onFrameFontC  ();
	void onFrameFillC  ();
	void onFrameStrokeC();
	void onFrameCustom ();

	void Final( bool exefinal = true );

	static void Height ( TShape *parent, String id, float duration, double   final, sfWave onframe, sfAnim onfinal = null );
	static void Width  ( TShape *parent, String id, float duration, double   final, sfWave onframe, sfAnim onfinal = null );
	static void Top    ( TShape *parent, String id, float duration, double   final, sfWave onframe, sfAnim onfinal = null );
	static void Left   ( TShape *parent, String id, float duration, double   final, sfWave onframe, sfAnim onfinal = null );
	static void MarginT( TShape *parent, String id, float duration, double   final, sfWave onframe, sfAnim onfinal = null );
	static void Opacity( TShape *parent, String id, float duration, double   final, sfWave onframe, sfAnim onfinal = null );
	static void FontC  ( TText  *parent, String id, float duration, unsigned final, sfWave onframe, sfAnim onfinal = null );
	static void FillC  ( TShape *parent, String id, float duration, unsigned final, sfWave onframe, sfAnim onfinal = null );
	static void StrokeC( TShape *parent, String id, float duration, unsigned final, sfWave onframe, sfAnim onfinal = null );
	static void Custom (                 String id, float duration                , sfAnim onframe, sfAnim onfinal = null );
	static void Stop   ( String id                                                                                        );
	//###########################################################################
 };

#endif
