void setup(){
    DDRB |= 0x20;
}
void loop(){
    PORTB ^= 0x20;
    delay(500);
}
