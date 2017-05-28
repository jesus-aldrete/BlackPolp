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

#ifndef p05_SchemesH
#define p05_SchemesH

#include "def.h"
#include "p02_pallets.h"

class pSchemes : public pPallets {
	/*Creacion*/public:
	__fastcall pSchemes( TComponent *owner );
	//###########################################################################


	/*Metodos*/private:
	void ChangeColor();
	//###########################################################################
 };

#endif