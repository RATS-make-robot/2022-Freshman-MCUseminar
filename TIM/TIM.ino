  bool LED_STATE = true;
  unsigned int count = 0;

  void setup() {
    pinMode(13, OUTPUT);
    cli();                      //전역인터럽트 정지

    TCCR0A = 0x0;                 // Reset entire TCCR1A to 0 
    TCCR0B = 0x00;                 // Reset entire TCCR1B to 0
    //일반 모드로 설정

    TCCR0B |= _BV(WGM02)|_BV(CS02)|_BV(CS00);        //프리스케일러 256 / CTC 모드
    TIMSK0 |= _BV(OCIE0A);        //compare match A 인터럽트

    OCR0A = 60;                //타켓 벨류
    sei();                     //전역 인터럽트 설정
  }
  
  void loop() {
    // put your main code here, to run repeatedly:
  }
  
  ISR(TIMER0_COMPA_vect){
    TCNT0  = 0;                  //TCNT랑 ocr이랑 체크하니깐 tcnt 초기화
    count++;
    if (count > 250) {
        LED_STATE = !LED_STATE;      //Invert LED state
        digitalWrite(13,LED_STATE);  //Write new state to the LED on pin D5
        count = 0;
    }    
}