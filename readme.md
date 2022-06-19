# 2022 RATS 신입생 MCU 세미나
* Work sheet origin
## GPIO
* 아트메가에서 GPIO를 변경할려면 아래의 레지스터를 제어해야한다.
* DDRx : 입출력 설정
* PORTx : HIGH / LOW 설정
* PINx : 값 입력4
* ![](2022-06-20-01-50-10.png)
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
* ![](2022-06-20-01-56-06.png)
* 아트메가에서 ADC를 수행할려면 아래의 레지스터를 제어해야한다.
* ![](2022-06-20-02-24-23.png)
* ADMUX
  * ![](2022-06-20-01-58-28.png)
  * ![](2022-06-20-02-01-01.png)
* ADCSRA
  * ![](2022-06-20-01-59-29.png)
  * ![](2022-06-20-01-59-39.png)
    * 결국 아래의 bit가 중요
    * ADPS0~2 : ADC에 공급할 클럭 설정을 위한 프리스케일러
    * ADEN : ADC Enable
    * ADCS : ADC start conversion
* ADCH/ADCL
  * ![](2022-06-20-01-59-54.png)
  * ![](2022-06-20-02-02-45.png)
* ![](2022-06-20-02-14-50.png)