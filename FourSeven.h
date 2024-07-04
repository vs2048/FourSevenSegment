/*
  FourSeven.h - library to interface with 4 seven segmendt displays using a shift register.
*/

#ifndef FOURSEVEN_H
#define FOURSEVEN_H

#include "Arduino.h"

class FourSeven
{
	public:
		FourSeven(int dataPin, int clockPin, int latchPin, int d3, int d2, 
				int d1, int d0);
		void clear();
		void setDisp(int num);
		void step();
	private:
		int _dataPin, _clockPin, _latchPin;
		int select[4];
		char currentDisp[4];	// Status: -9:99, -100:unknown -200:clear
		char currentState;
		const char _intMap[12] = { 0x7e, //0
									0x30, //1
									0x6d, //2
									0x79, //3
									0x33, //4
									0x5b, //5
									0x5f, //6
									0x70, //7
									0x7f, //8
									0x7b, //9
									0x1, //-
									0x0}; //nothing
};

#endif