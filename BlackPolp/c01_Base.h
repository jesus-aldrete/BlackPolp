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

#ifndef c01_BaseH
#define c01_BaseH

#include "def.h"

class cBase : public TLayout {
	/*Variables - propiedades*/protected:
	unsigned _color        ;
	unsigned _preserveColor;
	double   _hue          ;
	double   _sat          ;
	double   _lum          ;
	double   _alp          ;
	int      _red          ;
	int      _green        ;
	int      _blue         ;
	int      _alpha        ;
	bool     _updateRender ;

	/*Variables - Eventos*/public:
	gfEventColor onStartColor;
	gfEventColor onChangColor;
	gfEventColor onFinalColor;
	//###########################################################################


	/*Creacion*/public:
	__fastcall cBase( TComponent *owner );
	//###########################################################################


	/*Propiedades - Entradas*/protected:
	virtual void WColor( unsigned color );
	virtual void WHue  ( double   hue   );
	virtual void WSat  ( double   sat   );
	virtual void WLum  ( double   lum   );
	virtual void WAlp  ( double   alp   );
	virtual void WRed  ( int      red   );
	virtual void WGreen( int      green );
	virtual void WBlue ( int      blue  );
	virtual void WAlpha( int      alpha );

	/*Propiedades*/public:
	__property unsigned PreserveColor = { read=_preserveColor               };
	__property unsigned Color         = { read=_color        , write=WColor };
	__property double   Hue           = { read=_hue          , write=WHue   };
	__property double   Sat           = { read=_sat          , write=WSat   };
	__property double   Lum           = { read=_lum          , write=WLum   };
	__property double   Alp           = { read=_alp          , write=WAlp   };
	__property int      Red           = { read=_red          , write=WRed   };
	__property int      Green         = { read=_green        , write=WGreen };
	__property int      Blue          = { read=_blue         , write=WBlue  };
	__property int      Alpha         = { read=_alpha        , write=WAlpha };
	//###########################################################################


	/*Metodos*/public:
	virtual void Render     ();
	virtual void ChangeColor();

	void ChangeHSLA( double hue, double sat, double lum, double alp );
	//###########################################################################
 };

#endif
