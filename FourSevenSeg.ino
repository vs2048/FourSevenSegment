/*
  FourSevenSeg.ino - tester for the quad seven segment
  */

#include "Arduino.h"
#include "FourSeven.h"


FourSeven FS(7, 8, 6, 9, 10, 11, 12);


void setup() {
	FS.setDisp(4321);
}

void loop() {
	FS.step();
	delay(7);
}