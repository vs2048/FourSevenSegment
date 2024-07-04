/*
  FourSeven.cpp - library to interface with 4 seven segmendt displays
*/

#include "FourSeven.h"

FourSeven::FourSeven(int dataPin, int clockPin, int latchPin, int d3, int d2, 
				int d1, int d0)
{
	// Copy variables
	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	select[3] = d3;
	select[2] = d2;
	select[1] = d1;
	select[0] = d0;
	
	
	// Set pinmodes
	pinMode(_dataPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	
	// initialize pins
	digitalWrite(_dataPin, 0);
	digitalWrite(_clockPin, 0);
	digitalWrite(_latchPin, 0);
	
	// repeate for digitals
	this->clear();
}

// clear the display and disable output
void FourSeven::clear()
{
	for(int i=0;i<4;i++) {
		pinMode(select[i], OUTPUT);
		digitalWrite(select[i], 1);
	}
	currentState = -1;
}

// setDisp(): Calculates what each digit should be
void FourSeven::setDisp(int num)
{
	int output;
	if(num < 0 && num > -999) {
		currentDisp[3] = 0x1;
		output = num *-1;
	}
	else if(num<9999) {
		output = num;
	}
	else{
		return;
	}
	
	if(num>999)
	{
		currentDisp[3] = num/1000;
	}
	else if (num > 0) {
		currentDisp[3] = 11;
	}
	
	if (output > 99) {
		currentDisp[2] = (output/100)%10;
	}
	else {
		currentDisp[2] = 11;
	}
	
	if (output > 9) {
		currentDisp[1] = (output/10) % 10;
	}
	else{
		currentDisp[1] = 11;
	}
	
	currentDisp[0] = output % 10;
	
	// Set the state to 3 to indicate it is time to write
	if(currentState == -1){
		currentState = 3;
	}
}

// step(): Pushes the data into the shift register.
void FourSeven::step()
{
	if(currentState == -1) {
		// -1 means the system is not ready
		return;
	}	
	int output = _intMap[currentDisp[currentState]] << 1;
	int pastState = currentState + 1;
	if(pastState == 4) {
		// Roll over if all 4 digits are written
		pastState = 0;
	}
	
	//shift in new number
	for (int i = 0; i < 8; i++)
	{
		int currBit = 0b1 & (output >> i);
		digitalWrite(_dataPin, currBit);
		digitalWrite(_clockPin, 1);
		digitalWrite(_clockPin, 0);
	}
	
	//clear the current display
	digitalWrite(select[pastState], 1);
	
	// pulse the latch
	digitalWrite(_latchPin, 1);
	digitalWrite(_latchPin, 0);
	
	//enable the current bit
	digitalWrite(select[currentState], 0);
	
	// Move on to the next digit
	currentState = currentState - 1;
	if(currentState == - 1) {
		currentState = 3;
	}
	
}