void setup(){ //328 레지스터로 변경
    DDRB = 0xFF;  // OC0(PB4)출력설정-> 변경필요

    TCCR0A |= (1<<WGM01) | (0<<WGM00);
    TCCR0B |= (1<<WGM02) | (0<<WGM03);   //16진수 떄려박기로 변경
    TCCR0B |= (1<<CS022);
    TCCR0 = 0b01111010;    // fast PWM mode : 3,6(WGM01,00)
                            // - 11, 5,4(COM ) - 11, 2-0(CS) - 010
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

// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=schmacher&logNo=221405989919 참고
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=schmacher&logNo=221405989919