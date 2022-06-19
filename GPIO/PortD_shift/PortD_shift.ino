void setup(){
    DDRD |= 0xFF;
}
void loop(){
    PORTD |= 0X02;
    delay(500);
    PORTD |= 0X04;
    delay(500);
    PORTD |= 0X08;
    delay(500);
}
