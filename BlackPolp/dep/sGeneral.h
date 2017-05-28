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

#ifndef sGeneralH
#define sGeneralH

#include "sFields.h"
#include "sDef.h"

/*Funciones - OTROS*/
extern "C++" __declspec(dllexport)String __stdcall ByteAStr( double bytes );

/*Funciones - COLORES*/
extern "C++" __declspec(dllexport)int __stdcall RGBaSAF( int color                    );
extern "C++" __declspec(dllexport)int __stdcall RGBaSAF( int red, int green, int blue );

//HEX
extern "C++" __declspec(dllexport)String __stdcall RGBaHEX( int color                               );
extern "C++" __declspec(dllexport)String __stdcall RGBaHEX( int red, int green, int blue            );
extern "C++" __declspec(dllexport)String __stdcall RGBaHEX( int red, int green, int blue, int alpha );
extern "C++" __declspec(dllexport)String __stdcall BGRaHEX( int color                               );
extern "C++" __declspec(dllexport)String __stdcall BGRaHEX( int red, int green, int blue            );
extern "C++" __declspec(dllexport)String __stdcall BGRaHEX( int red, int green, int blue, int alpha );

//HSL
extern "C++" __declspec(dllexport)double __stdcall HUEaRGB( double  pos, double  qua  , double  tem                                                        );
extern "C++" __declspec(dllexport)void   __stdcall RGBaHSL( double  red, double  green, double  blue, double &Hue, double &Sat, double &Lum                );
extern "C++" __declspec(dllexport)void   __stdcall RGBaHSL( int     red,                              double &Hue, double &Sat, double &Lum, double &Alpha );
extern "C++" __declspec(dllexport)void   __stdcall RGBaHSL( int     red,                              double &Hue, double &Sat, double &Lum                );
extern "C++" __declspec(dllexport)void   __stdcall HSLaRGB( double &Red, double &Green, double &Blue, double  hue, double  sat, double  lum                );
extern "C++" __declspec(dllexport)int    __stdcall HSLaRGB(                                           double  hue, double  sat, double  lum, double  alpha );

//HSV
extern "C++" __declspec(dllexport)void __stdcall RGBaHSV( double  red, double  green, double  blue, double &Hue, double &Sat, double &Val                );
extern "C++" __declspec(dllexport)void __stdcall RGBaHSV( int     red,                              double &Hue, double &Sat, double &Val, double &Alpha );
extern "C++" __declspec(dllexport)void __stdcall RGBaHSV( int     red,                              double &Hue, double &Sat, double &Val                );
extern "C++" __declspec(dllexport)void __stdcall HSVaRGB( double &Red, double &Green, double &Blue, double  hue, double  sat, double  val                );
extern "C++" __declspec(dllexport)int  __stdcall HSVaRGB(                                           double  hue, double  sat, double  val, double  alpha );

//XYZ
extern "C++" __declspec(dllexport)void __stdcall RGBaXYZ( double  red, double  green, double  blue, double &X, double &Y, double &Z                );
extern "C++" __declspec(dllexport)void __stdcall RGBaXYZ( int color,                                double &X, double &Y, double &Z, double &Alpha );
extern "C++" __declspec(dllexport)void __stdcall RGBaXYZ( int color,                                double &X, double &Y, double &Z                );
extern "C++" __declspec(dllexport)void __stdcall XYZaRGB( double &Red, double &Green, double &Blue, double  x, double  y, double  z                );
extern "C++" __declspec(dllexport)int  __stdcall XYZaRGB(                                           double  x, double  y, double  z, double  alpha );

//LAB
extern "C++" __declspec(dllexport)void __stdcall LABaXYZ( double &X, double &Y, double &Z,          double  lum, double  red, double  blue                );
extern "C++" __declspec(dllexport)void __stdcall RGBaLAB( double red, double green, double blue,    double &Lum, double &Red, double &Blue                );
extern "C++" __declspec(dllexport)void __stdcall RGBaLAB( int color,                                double &Lum, double &Red, double &Blue, double &Alpha );
extern "C++" __declspec(dllexport)void __stdcall RGBaLAB( int color,                                double &Lum, double &Red, double &Blue                );
extern "C++" __declspec(dllexport)void __stdcall LABaRGB( double &Red, double &Green, double &Blue, double  lum, double  red, double  blue                );
extern "C++" __declspec(dllexport)int  __stdcall LABaRGB(                                           double  lum, double  red, double  blue                );
extern "C++" __declspec(dllexport)int  __stdcall LABaRGB(                                           double  lum, double  red, double  blue, double  alpha );

//CMY
extern "C++" __declspec(dllexport)void __stdcall RGBaCMY( double red, double green, double blue,    double &Cyan, double &Magenta, double &Yellow                );
extern "C++" __declspec(dllexport)void __stdcall RGBaCMY( int color,                                double &Cyan, double &Magenta, double &Yellow, double &Alpha );
extern "C++" __declspec(dllexport)void __stdcall RGBaCMY( int color,                                double &Cyan, double &Magenta, double &Yellow                );
extern "C++" __declspec(dllexport)void __stdcall CMYaRGB( double &Red, double &Green, double &Blue, double  cyan, double  magenta, double  yellow                );
extern "C++" __declspec(dllexport)int  __stdcall CMYaRGB(                                           double  cyan, double  magenta, double  yellow, double  alpha );

//CMYK
extern "C++" __declspec(dllexport)void __stdcall RGBaCMYK( double red, double  green, double  blue,  double &Cyan, double &Magenta, double &Yellow, double &Key                );
extern "C++" __declspec(dllexport)void __stdcall RGBaCMYK( int color,                                double &Cyan, double &Magenta, double &Yellow, double &Key, double &Alpha );
extern "C++" __declspec(dllexport)void __stdcall RGBaCMYK( int color,                                double &Cyan, double &Magenta, double &Yellow, double &Key                );
extern "C++" __declspec(dllexport)void __stdcall CMYKaRGB( double &Red, double &Green, double &Blue, double  cyan, double  magenta, double  yellow, double  key                );
extern "C++" __declspec(dllexport)int  __stdcall CMYKaRGB(                                           double  cyan, double  magenta, double  yellow, double  key, double  alpha );
//###########################################################################


/*Funciones - Encriptación*/
extern "C++" __declspec(dllexport)String __stdcall AHexStr( __int32 number );
extern "C++" __declspec(dllexport)String __stdcall SHA256 ( String cadena  );
extern "C++" __declspec(dllexport)String __stdcall MD5    ( String cadena  );
//###########################################################################


/*Funciones - Animacion*/
extern "C++" __declspec(dllexport)Variant __stdcall GetPropValueSub( TObject *object, String property, bool preferStrings );
extern "C++" __declspec(dllexport)void    __stdcall SetPropValueSub( TObject *object, String property, Variant &value     );

extern "C++" __declspec(dllexport)double __stdcall sfBackIn          ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfBackOut         ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfBackInOut       ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfBounceOut       ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfBounceIn        ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfBounceInOut     ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfCircularIn      ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfCircularOut     ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfCircularInOut   ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfCubicIn         ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfCubicOut        ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfCubicInOut      ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfElasticIn       ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfElasticOut      ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfElasticInOut    ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfExponentialIn   ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfExponentialOut  ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfExponentialInOut( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfLinear          ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuadraticIn     ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuadraticOut    ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuadraticInOut  ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuarticIn       ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuarticOut      ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuarticInOut    ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuinticIn       ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuinticOut      ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfQuinticInOut    ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfSinusoidalIn    ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfSinusoidalOut   ( double progres, double start, double final_start, double max );
extern "C++" __declspec(dllexport)double __stdcall sfSinusoidalInOut ( double progres, double start, double final_start, double max );
//###########################################################################


/*Otros*/
extern "C++" __declspec(dllexport)String __stdcall Cifrar   ( String Cadena );
extern "C++" __declspec(dllexport)String __stdcall Descifrar( String Cadena );
//###########################################################################

#endif