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

#ifndef fLoaderH
#define fLoaderH

#include <FMX.Layouts.hpp>
#include <fAnim.h>

class PACKAGE fLoader : public TLayout {
	/*Variables*/protected:
	double   _animMax; TTime _animDat;
	double   _animIn1; TTime _animDa1;
	double   _animIn2; TTime _animDa2;
	double   _animIn3; TTime _animDa3;
	bool     _animOut;
	bool     _showl  ;
	bool     _delete ;
	unsigned _fill   ;
	unsigned _color  ;

	/*Variables - controles*/protected:
	TRectangle *_rback;

	TEllipse *_eloader1;
	TEllipse *_eloader2;
	TEllipse *_eloader3;

	/*propiedades*/protected:
	bool _showLoader;
	bool _elipseIn  ;

	/*Eventos*/public:
	TNotifyEvent onShow;
	TNotifyEvent onHide;
	//###########################################################################


	/*Creacion - controles*/protected:
	void CreateElipse( TEllipse **elipse );

	void CreateThis   ();
	void CreateElipses();

	/*Creacion*/public:
	__fastcall fLoader( TComponent *owner );
	//###########################################################################


	/*Propiedades*/private:
	void __fastcall WColor( unsigned color );
	void __fastcall WFill ( unsigned fill  );

	/*Propiedades*/public:
	__property unsigned Color = { read=_color, write=WColor };
	__property unsigned Fill  = { read=_fill , write=WFill  };
	//###########################################################################


	/*Eventos*/protected:
	void __fastcall frame_this( fAnim *sender );
	void __fastcall inilo_this( fAnim *sender );
	void __fastcall finlo_this( fAnim *sender );
	//###########################################################################


	/*Metodos*/public:
	void ShowL( bool showl );
	void HideL( bool delet );
	//###########################################################################
 };

#endif
