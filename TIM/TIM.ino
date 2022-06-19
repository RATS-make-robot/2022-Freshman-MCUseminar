unsigned int count=0;
char toggle0=1;

void setup() {
    pinMode(13, OUTPUT);
    TCNT0 = 0;  //TCNT0 initialize
    OCR0A= 255; 

    TCCR0A |= 0x00; //TCCR0A initialize
    TCCR0B |= (1<<WGM02);
    TCCR0B |= (1<<CS02) | (0<<CS00);
    TIMSK0 |= (1<<OCIE0A);

    sei(); //전역 인터럽트 활성
}

ISR(TIMER0_COMPA_vect){ //나중에 레지스터 레벨로 변경 바람
    count++;
    if(count > 250) {
        if (toggle0){ 
            digitalWrite(13,HIGH);
            toggle0 = 0;
        }

        else{
            digitalWrite(13,LOW);
            toggle0 = 1;
        }
        count=0;
        TCNT0=0;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
}

//https://diyver.tistory.com/140 참고