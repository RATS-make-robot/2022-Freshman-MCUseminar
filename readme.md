# 2022 RATS 신입생 MCU 세미나
* Work sheet origin
# Aduino 공식 doc
* [PWM](https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm).
# GPIO
* 아트메가에서 GPIO를 변경할려면 아래의 레지스터를 제어해야한다.
* DDRx : 입출력 설정
* PORTx : HIGH / LOW 설정
* PINx : 값 입력4
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-01-50-10.png)
* 아두이노 내장 LED는 PB5이다.
* 그럼 얘를 제어할려면?
* ```ino
    //일반적인 아두이노 버전
    #define LED_BUILTIN 13
    void setup() {
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void loop() {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }
  ```
* ```ino
    //레지스터 레벨에서 접근
    void setup(){
        DDRB |= 0x20;
    }
    void loop(){
        PORTB ^= 0x20;
        delay(500);
    }
  ```
# ADC
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-01-56-06.png)
* 아트메가에서 ADC를 수행할려면 아래의 레지스터를 제어해야한다.
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-02-24-23.png)
* ADMUX
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-01-58-28.png)
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-02-01-01.png)
* ADCSRA
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-01-59-29.png)
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-01-59-39.png)
    * 결국 아래의 bit가 중요
    * ADPS0~2 : ADC에 공급할 클럭 설정을 위한 프리스케일러
    * ADEN : ADC Enable
    * ADCS : ADC start conversion
* ADCH/ADCL
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-01-59-54.png)
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-02-02-45.png)
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-02-14-50.png)
  
* ```ino
  void init_adc(){
      ADCSRA |= 0x07; //분주비 128
      ADMUX  |= 0x40; //ADC AVCC(5V) 기준 
      ADCSRA |= 0x80; //ADC Conversion start
  }

  uint16_t read_adc(unsigned char channel){
      uint8_t adc_L, adc_H;
      uint16_t ADC;
      ADMUX &= 0xF0;          //ADMUX 0~3 bit 초기화 MUX 채널 셋팅
      ADMUX |= channel;
      ADCSRA |= 0x80;         //ADC Conversion start
      while(ADCSRA & 0x80);	//변환 ㄱㄷ
      /*
      ADSC: ADC Start Conversion
      When the conversion is complete, it returns to zero.
      */
      adc_L = ADCL;
      adc_H = ADCH;
      ADC = (adc_H<<8) | adc_L;
      return ADC;	//ADC값 반환
  }
  ```
  * |ADC Channel|Channel Bit|
    |-----------|-----------|
    |ADC0 (A0)  |0000       |
    |ADC1 (A1)  |0001       |
    |ADC2 (A2)  |0010       |
    |ADC3 (A3)  |0011       |
    |ADC4 (A4)  |0100       |
    |ADC5 (A5)  |0101       |
    |ADC6 (A6)  |0110       |
    |ADC7 (A7)  |0111       |
    |ADC8 : 아두이노에선 인터페이싱 X| 1000 |

# TIM
* 외부 인터럽트는 애들 보드로 설명하기 솔직히 애매함
* 걍 인터럽트 개념 설명하고 내부 외부가 있다~ 외부는 이렇고~ 내부는 이렇다~ 한뒤에
* 코드는 내부만 ㄲㄲ
* 일단 타이머가 8bit TIM 그리고 16bit TIM가 있음
* 8bit tim은 0~255 / 16bit time 0~65536
* 우린 8-bit T/C TIM0 쓰자
* TIM 모드는 몇개가 있는데 아래 이미지 참고 ㄲㄱ
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-03-50.png)
* 우린 CTC모드 쓸꺼임...
* CTC모드가 뭐라면 클럭마다 TCNT가 한개씩 증가함,,,그러다가 OCR 또는 ICR이 일치하면 INT발생  
    -> 여기선 아래의 IRQ 벡터 ㅇㅇ
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-45-06.png)
* 왜하필 얘냐면 TIMSK0 떄문임 ㅇㅇ
* 사용해야할 레지스터는 아래와 같음
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-29-27.png)
* TCCRA~B / TCNT / OCR / TIMSK0
* TCCRA~B
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-38-49.png)
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-40-40.png)
  * 솔직히 얘는 데이터시트보다 아래표가 더 잘 정리되어있음ㅋㅋ
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-03-50.png)

* TCNT / OCR
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-37-45.png)
  * TCNT가 결국 클럭이 몇개 지나갔는지 카운트 되는 레지스터 ㅇㅇ
  * OCR은 타겟 벨류 ㅇㅇ
  * CTC모드에서는 결국 TCNT 랑 우리가 셋팅해준 OCR이 맞는지 chk 맞다면 인터럽트 발생
* TIMSK
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-36-59.png)
  * OCIE0A를 설정했기 때문에 아래의 INT가 발생한거임 ㅇㅇ
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-45-06.png)
* ```ino
    TCNT0 = 0;  //TCNT0 initialize
    OCR0A= 255; 

    TCCR0A |= 0x00; //TCCR0A initialize
    TCCR0B |= (1<<WGM02);   //16진수 떄려박기로 변경
    TCCR0B |= (1<<CS02) | (0<<CS00); //256
    TIMSK0 |= (1<<OCIE0A);

    sei(); //전역 인터럽트 활성
  ```
# PWM
* 뭐 사실 PWM이랑 TIM랑 개똑같은거 설명 ㄲㄱ
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-55-53.png)
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-56-19.png)
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-57-24.png)
* ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-57-58.png)
* 우리 라트 4번 LED는 D6(=PD6)에 결선, 해당 포트는 OC0A(TIM 8BIT COUNTER 0, COMPARE MATCH A INT )
* 우선 PWM 모드는 2개가 있음 : 우린 걍 FAST PWM ㄲㄲ

* FAST PWM
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-04-01-04.png)
  * TCNTn은 여전히 냅두면 0x00~0xFF까지 갔다가 오버플로우되는것을 반복합니다.
  * 이제 OCRn 값이 중요한데요, OCRn값과 TCNTn값이 일치하면(비교 매치) OCn핀의 출력값이 바뀝니다.
  * 여기서 출력값이 어떻게 바뀌느냐는 모드마다 다른데,
  * 비반전 비교 출력모드(TCNTn 밑에 있는 그림)일 경우에는
  * HIGH가 출력되다가, 비교 매치에서 OCn핀에 0이 출력됩니다. TCNTn이 0xFF에서 0x00으로 떨어질 때 다시 HIGH가 출력되고요.
  * 반전 비교 출력모드(세번째 그림)일 경우에는
  * LOW가 출력되다가, 비교 매치에서 OCn핀에 1이 출력됩니다. TCNTn이 0xFF에서 0x00으로 떨어질 때 다시 LOW가 출력됩니다.
  * https://m.blog.naver.com/ga1267/220079623919 참고
* 사용해야할 레지스터는 아래와 같음
* TCNT/OCR/TCCR
* TIM이랑 거의 비슷함
* TCCRA~B
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-25-01-00-59.png)
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-38-49.png)
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-40-40.png)

* TCNT / OCR
  * ![](https://github.com/RATS-make-robot/2022-Freshman-MCUseminar/blob/main/assets/2022-06-20-03-37-45.png)
  * TCNT가 결국 클럭이 몇개 지나갔는지 카운트 되는 레지스터 ㅇㅇ
  * OCR은 타겟 벨류 ㅇㅇ
* ```ino
    //레지스터 레벨에서 접근
    pinMode(3, OUTPUT);
    pinMode(11, OUTPUT);
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS22);
    OCR2A = 180;
    OCR2B = 50;
    /*
      Output A frequency: 16 MHz / 64 / 256 = 976.5625Hz
      Output A duty cycle: (180+1) / 256 = 70.7%
      Output B frequency: 16 MHz / 64 / 256 = 976.5625Hz
      Output B duty cycle: (50+1) / 256 = 19.9%
    */
  ```
* |Timer output|Arduino output|Chip pin|Pin name|
  |------------|--------------|--------|--------|
  |OC0A        |9             |12      |PD6     |
  |OC0B        |5             |11      |PD5     |
  |OC1A        |9             |15      |PB1     |
  |OC1B        |10            |16      |PB2     |
  |OC2A        |11            |17      |PB3     |
  |OC2B        |3             |5       |PD3     |
* [PWM REF](https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm).
