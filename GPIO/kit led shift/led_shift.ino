void setup(){
    DDRD |= 0xFF;
}

void loop(){
    PORTD = 0X02;
    for (int i = 0; i < 4; i++) {
        PORTD<<1;
        delay(500);
    }
}
