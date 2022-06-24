void setup(){ //328 레지스터로 변경
    pinMode(9, OUTPUT);
    pinMode(5, OUTPUT);
    TCCR0A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR0B = _BV(CS22);
}

void loop(){
    OCR2A = 180;
    OCR2B = 50;
    delay_ms(500);
    OCR2A = 180;
    OCR2B = 50;
    delay_ms(500);
    OCR2A = 180;
    OCR2B = 50;
    delay_ms(500);
    OCR2A = 180;
    OCR2B = 50;
    delay_ms(500);
    OCR2A = 180;
    OCR2B = 50;
    delay_ms(500);
}

// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=schmacher&logNo=221405989919 참고
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=schmacher&logNo=221405989919