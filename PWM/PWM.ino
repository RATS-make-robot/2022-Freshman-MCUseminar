void setup(){
    pinMode(5, OUTPUT);
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B = _BV(CS02);
}

void loop(){
    OCR0B = 128;
    delay(1000);
    OCR0B = 0;
    delay(1000);
}