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

#ifndef sDefH
#define sDefH

#include <Windows.h>

/*Definiciones*/
#define null 0
#define snan -12314

#define OCR_NORMAL 32512

#define sdo                      FILEOPENDIALOGOPTIONS
#define seOptionsDialog          FILEOPENDIALOGOPTIONS
#define odSobrescribirArchivo    FOS_OVERWRITEPROMPT
#define odEstrictoTipos          FOS_STRICTFILETYPES
#define odNoCargarDir            FOS_NOCHANGEDIR
#define odSeleccionarCarpetas    FOS_PICKFOLDERS
#define odVerArchivosSystema     FOS_FORCEFILESYSTEM
#define odSeleccionarTodosShell  FOS_ALLNONSTORAGEITEMS
#define odNoValidar              FOS_NOVALIDATE
#define odMultiSeleccion         FOS_ALLOWMULTISELECT
#define odCarpetaDebeExistir     FOS_PATHMUSTEXIST
#define odArchivoDebeExistir     FOS_FILEMUSTEXIST
#define odPreguntarCrear         FOS_CREATEPROMPT
#define odShareAware             FOS_SHAREAWARE
#define odNoDevolverSoloLectura  FOS_NOREADONLYRETURN
#define odNoEstrictoEnCreacion   FOS_NOTESTFILECREATE
#define odOcultarListaRecientes  FOS_HIDEMRUPLACES
#define odOcultarPaneles         FOS_HIDEPINNEDPLACES
#define odNoReferenciaDeLNK      FOS_NODEREFERENCELINKS
#define odNoAgregarRecientes     FOS_DONTADDTORECENT
#define odMostrarArchivosOcultos FOS_FORCESHOWHIDDEN
#define odDefaultNoModoMini      FOS_DEFAULTNOMINIMODE
#define odVerPanelVistaPrevia    FOS_FORCEPREVIEWPANEON
#define odForsarExtencion        0

/*Definiciones - Colores*/
#define ARGB(c      ) ((int(c)>>24)&0xFF)
#define RRGB(c      ) ((int(c)>>16)&0xFF)
#define GRGB(c      ) ((int(c)>>8 )&0xFF)
#define BRGB(c      ) ((int(c)    )&0xFF)
#define ACOL(a,r,g,b) (\
	((int(a) & 0xFF)<<24)+ \
	((int(r) & 0xFF)<<16)+ \
	((int(g) & 0xFF)<<8 )+ \
	((int(b) & 0xFF)    )  \
 )
#define RCOL(r,g,b  ) (\
	((int(r) & 0xFF)<<16)+ \
	((int(g) & 0xFF)<<8 )+ \
	((int(b) & 0xFF)    )  \
 )

/*Definiciones - Encriptación*/
#define RotateDC(x,n  ) ((x&0xFFFFFFFF)>>n)
#define RotateBY(x,n  ) (RotateDC(x,n)|(x<<(32-n)))
#define RotateYB(x    ) ((x>>24)|((x>>8)&0xFF00)|((x<<8)&0xFF0000)|(x<<24))
#define Fnumber0(x    ) (RotateBY(x,7 )^RotateBY(x,18)^RotateDC(x,3 ))
#define Fnumber1(x    ) (RotateBY(x,17)^RotateBY(x,19)^RotateDC(x,10))
#define Fnumber2(x,y,z) (z^(x&(y^z)))
#define Fnumber3(x,y,z) (x^y^z)
#define Fnumber4(x,y,z) ((x&y)|(z&(x|y)))
#define Snumber0(x    ) (RotateBY(x,2 )^RotateBY(x,13)^RotateBY(x,22))
#define Snumber1(x    ) (RotateBY(x,6 )^RotateBY(x,11)^RotateBY(x,25))
#define Hcharter(x,y,z) ((x&y)^(~x&z))
#define Majorend(x,y,z) ((x&y)^(x&z)^(y&z))

/*Definiciones - FMX*/
#define co        "\""
#define cd        "\\\""
#define PosX      Position->X
#define PosY      Position->Y
#define MarG(x,m) x->Margins->Top=(m);x->Margins->Left=(m);x->Margins->Right=(m);x->Margins->Bottom=(m);
#define MarT      Margins->Top
#define MarL      Margins->Left
#define MarR      Margins->Right
#define MarB      Margins->Bottom
#define PadG(x,m) (x->Padding->Top=(m);x->Padding->Left=(m);x->Padding->Right=(m);x->Padding->Bottom=(m);)
#define StrK      Stroke->Kind
#define StrC      Stroke->Color
#define FilK      Fill->Kind
#define FilC      Fill->Color
#define FonC      Font->Color
#define FonF      Font->Family
#define FonS      Font->Size
#define DatD      Data->Data
#define BK        TBrushKind
#define AL        TAlignLayout
#define TA        TTextAlign
#define varPom    TPoint pom;GetCursorPos(&pom);TRect fom,bor;GetWindowRect(GetHandle(),&fom);GetClientRect(GetHandle(),&bor);bor.left=((fom.right-fom.left)-bor.right)/2;
#define whileDown ((!GetSystemMetrics(SM_SWAPBUTTON)!=0&&GetAsyncKeyState(VK_LBUTTON)!=0)||(GetSystemMetrics(SM_SWAPBUTTON)!=0&&GetAsyncKeyState(VK_RBUTTON)!=0))

#define AnimC(          duration       , onwave ) fAnim::Custom (                  (String)(__int64)this  , duration       , onwave );
#define AnimO(  parent, duration, final, onwave ) fAnim::Opacity( (TShape*)parent, (String)(__int64)parent, duration, final, onwave );
#define AnimW(  parent, duration, final, onwave ) fAnim::Width  ( (TShape*)parent, (String)(__int64)parent, duration, final, onwave );
#define AnimL(  parent, duration, final, onwave ) fAnim::Left   ( (TShape*)parent, (String)(__int64)parent, duration, final, onwave );
#define AnimT(  parent, duration, final, onwave ) fAnim::Top    ( (TShape*)parent, (String)(__int64)parent, duration, final, onwave );
#define AnimFC( parent, duration, final, onwave ) fAnim::FillC  ( (TShape*)parent, (String)(__int64)parent, duration, final, onwave );

/*Definiciones - Variables*/
#define fontFamily "Consolas"
#define fontSize   12
#define maxbuf     5*1024*1024
#define gmod       (*sfeModules())
#define gbas       (*sfeBase())
#define gopc       (*sfeOptions())
#define gses       (*sfeSessions())
#define pe         (*_petition)
#define me         ResponceSock

#define sene(title,code,error)            \
	pe.me( "error",                       \
		co"notify"co":{"                  \
			co"title"  co":"co title co","\
			co"code"   co":"   code    ","\
			co"type"   co":"co"Error"co","\
			co"message"co":"co error co   \
		"}"                               \
	);

/*Enumeraciones*/
enum seValueType  { vlNull, vlNothing, vlTemporary, vlInt, vlFloat, vlNumber, vlText, vlBool, vlChild, vlObject, vlArray };
enum seTypeLink   { tlShellLink, tlShellItem };
enum seTypeProg   { tpNoProgress = 0x00000000, tpIndeterminate = 0x00000001, tpNormal = 0x00000002, tpError = 0x00000004, tpPaused = 0x00000008 };
enum seTypeDrop   { tdNone = 0, tdCopy = 1, tdMove = 2, tdLink = 4, tdScroll = 0x80000000 };
enum seContentType{ ctHTML, ctWOFF, ctTXT, ctCSS, ctJS, ctJSON, ctSVG, ctPNG, ctJPG, ctICO, ctOTF, ctTTF, ctBIN, ctPDF };
enum seMessageType{ mtWarning, mtAccept, mtInfo, mtError };

/*Clases*/
class sSField  ;
class wThread  ;
class fAnim    ;
class ePetition;

/*Tipos*/
typedef void   __fastcall (__closure *sfNotify  )( TObject *sender, String message );
typedef void   __fastcall (__closure *sfAnim    )( fAnim *anim );
typedef void   __fastcall (__closure *sfDrag    )( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
typedef void   __fastcall (__closure *sfThread  )( wThread *thread );
typedef double __stdcall  (__stdcall *sfWave    )( double progres, double start, double final_start, double max );
typedef void   __stdcall  (__stdcall *sfPetition)( ePetition *peticion );
typedef void   __stdcall  (__stdcall *sfLoad    )( String *name );

/*Funciones*/
inline int           sai       ( String string ) { int           res = 0; TryStrToInt  ( string, res ); return res; };
inline double        sad       ( String string ) { double        res = 0; TryStrToFloat( string, res ); return res; };
inline unsigned long sau       ( String string ) { unsigned long res; try { res = strtoul( AnsiString( string ).c_str(), NULL, 0 ); } catch( ... ){ res = 0; } return res; };
inline int           sround    ( double number ) { return number > 0.f ? floor( number + 0.5 ) : ceil( number - 0.5 ); };
inline String        uniqueName(               ) { return Sysutils::FormatDateTime("yyyymmdd",Date())+Sysutils::FormatDateTime("hhnnsszz",Time())+(String)random(1000); };
inline String        uniqueName( bool hour     ) { if(!hour)return Sysutils::FormatDateTime("yyyy-mm-dd",Date()); else return Sysutils::FormatDateTime("yyyy-mm-dd_hh.mm.ss.ampm",Date()+Time()); };

/*Estructuras*/
#pragma pack( push )
#pragma pack( 2 )

typedef struct {
	BYTE  bWidth;       // Width of the image
	BYTE  bHeight;      // Height of the image (times 2)
	BYTE  bColorCount;  // Number of colors in image (0 if >=8bpp)
	BYTE  bReserved;    // Reserved
	WORD  wPlanes;      // Color Planes
	WORD  wBitCount;    // Bits per pixel
	DWORD dwBytesInRes; // how many bytes in this resource?
	WORD  nID;          // the ID
} MEMICONDIRENTRY, *LPMEMICONDIRENTRY, GRPICONDIRENTRY, *LPGRPICONDIRENTRY;

typedef struct {
	WORD            idReserved;   // Reserved
	WORD            idType;       // resource type (1 for icons)
	WORD            idCount;      // how many images?
	MEMICONDIRENTRY idEntries[1]; // the entries for each image
} MEMICONDIR, *LPMEMICONDIR, GRPICONDIR, *LPGRPICONDIR;

typedef struct {
	BYTE  bWidth;        // Width of the image
	BYTE  bHeight;       // Height of the image (times 2)
	BYTE  bColorCount;   // Number of colors in image (0 if >=8bpp)
	BYTE  bReserved;     // Reserved
	WORD  wPlanes;       // Color Planes
	WORD  wBitCount;     // Bits per pixel
	DWORD dwBytesInRes;  // how many bytes in this resource?
	DWORD dwImageOffset; // where in the file is this image
} ICONDIRENTRY, *LPICONDIRENTRY;

typedef struct {
  BITMAPINFOHEADER icHeader;
  RGBQUAD          icColors[1];
  BYTE             icXOR[1];
  BYTE             icAND[1];
} ICONIMAGE, *LPICONIMAGE;

typedef struct {
	WORD         idReserved;   // Reserved
	WORD         idType;       // resource type (1 for icons)
	WORD         idCount;      // how many images?
	ICONDIRENTRY idEntries[1]; // the entries for each image
} ICONDIR, *LPICONDIR;

#pragma pack( pop )

#endif