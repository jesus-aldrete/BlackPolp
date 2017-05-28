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

#ifndef sFieldsH
#define sFieldsH

#include <sField.hpp>
#include "sDef.h"

template<typename typeData>
class sBFields {
	/*Definiciones*/
	#define sBFields_start(x,y,z) \
		_index = x;\
		_count = y;\
		_field = z;
	//###########################################################################


	/*Variables*/protected:
	int                *_index;
	__int64            *_count;
	TList__1<typeData> *_field;
	//###########################################################################


	/*Creacion*/public:
	sBFields(                       ) {
		sBFields_start( new int, new __int64, new TList__1<typeData> );

		(*_count) = 1;
		(*_index) = 0;
	 };
	sBFields( const sBFields *point ) {
		if ( !point ) {
			sBFields_start( new int, new __int64, new TList__1<typeData> );

			(*_count) = 1;
			(*_index) = 0;
		}
		else {
			sBFields_start( point->_index, point->_count, point->_field );

			(*_count)++;
		}
	 };
	sBFields( const sBFields &point ) {
		sBFields_start( point._index, point._count, point._field );

		(*_count)++;
	 };
   ~sBFields(                       ) {
		Delete();
	 };
	//###########################################################################


	/*Propiedades - Salidas*/protected:
	bool     REnd  () {
		return (*_index) >= (*_field)->Count;
	 };
	int      RSize () {
		return _field->Count;
	 };
	int      RIndex() {
		return (*_index);
	 };
	typeData RValue() {
		if ( (*_index) >= 0 && (*_index) < _field->Count )
			return _field->Items[(*_index)++];

		return null;
	 };

	/*Propiedades*/public:
	__property bool     End   = { read = REnd   };
	__property int      Size  = { read = RSize  };
	__property int      Index = { read = RIndex };
	__property typeData Value = { read = RValue };
	//###########################################################################


	/*Operadores*/public:
	operator typeData() {
		return RValue();
	 };

	sBFields operator = ( typeData value ) {
		if ( (*_index) >= 0 && (*_index) < _field->Count )
			_field->Items[(*_index)++] = value;

		return this;
	 };
	sBFields operator = ( sBFields value ) {
		Delete();

		sBFields_start( value._index, value._count, value._field );

		return this;
	 };

	sBFields operator += ( typeData value                 ) {
		(*_index) = _field->Count + 1;

		_field->Add( value );

		return this;
	 };
	sBFields operator -= ( int      index                 ) {
		if ( index >= 0 && index < _field->Count )
			_field->Delete( index );

		return this;
	 };
	sBFields operator *= ( int      index                 ) {
		if ( index >= _field->Count ) index = _field->Count - 1;
		if ( index <  0             ) index = 0;

		(*_index) = index;

		return this;
	 };
	sBFields operator [] ( int      index                 ) {
		(*_index) = index;

		return this;
	 };
	sBFields operator () ( int      index, typeData value ) {
		if ( index >= _field->Count + 1 ) index = _field->Count;
		if ( index <  0                 ) index = 0;

		_field->Insert( index, value );

		return this;
	 };
	//###########################################################################


	/*Funciones*/private:
	void Delete() {
		if ( _count && --(*_count) == 0 ) {
			delete _count; _count = null;
			delete _index; _index = null;
			delete _field; _field = null;
		}
	 };
	//###########################################################################


	/*Metodos*/public:
	void Clear() {
		_field->Clear();

		(*_index) = 0;
	 };
	//###########################################################################
 };
class sIField : public sBFields<int       >{};
class sDField : public sBFields<double    >{};
class s6Field : public sBFields<__int64   >{};
class sUField : public sBFields<unsigned  >{};
class sSField : public sBFields<String    >{};
class s8Field : public sBFields<UTF8String>{};
class sAField : public sBFields<AnsiString>{};

#endif
