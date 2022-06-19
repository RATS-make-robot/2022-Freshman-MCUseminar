void setup(){
    DDRB = 0xFF;  // OC0(PB4)출력설정-> 변경필요
    TCCR0 = 0b01111010;    // fast PWM mode : 3,6(WGM01,00) - 11, 5,4(COM ) - 11, 2-0(CS) - 010
}

void loop(){
    OCR0 = 0x00;    //0 -> 0/255 = 0%
    delay_ms(500);
    OCR0 = 0x3F;    //63-> 63/255 = 25%
    delay_ms(500);
    OCR0 = 0x7F;    //127-> 127/255 = 50%
    delay_ms(500);
    OCR0 = 0xBF;    //191-> 191/255 = 75%
    delay_ms(500);
    OCR0 = 0xFF;    //255-> 255/255 = 100%
    delay_ms(500);
}
