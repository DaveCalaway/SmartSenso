// shift register
void shift(int numberToDisplay, int bitOrder) {
  digitalWrite(latchPin, LOW);

  if (bitOrder == 0 ) // MSBF
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
  else
    shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);

  digitalWrite(latchPin, LOW);
}
