# NOTICE
1. delay(); 에 문제가 있음 사용 지양 바람.
# LAB
## GPIO
### GPIO LAB - 1
1. 내부 LED BLINK

### GPIO LAB - 2
* ![](assets/2022-07-28-00-42-47.png)
  * ![](assets/2022-07-28-00-43-19.png)
  * 위와 같이 저항 값 수정가능
  * LED는 꺽다리가 양극임
* ![](assets/2022-07-28-00-44-42.png)
* 위와 같이 회로 구성하여 상단의 비트쉬프트 기능을 이용하여 LED 쉬프트 구현하면 좋을듯~
* ```ino
    #define PIN 0x02
    int pin = PIN << 5;

    void setup(){
        DDRD |= 0xFF;
    }
    void loop(){
        PORTD |= pin;
    }
    ```
* Point : 직접 회로도 확인하여 D0~7이 PORT D인 것을 찾는 실습 수행 필요

## ADC
* 앞으로 모든 LAB은 아래 회로를 구성하여 진행가능
* 불가능 D2가 아닌 D5로 해둬야 회로 수정 안함.
* ![](assets/2022-07-28-00-48-23.png)

### ADC LAB - 1
* ![](assets/2022-07-28-00-49-51.png)
* 위와  같이 회로 구성하여 포텐셜 미터 돌려가며 전압 바뀌는 것 관찰
  * 실제 Vpp가 바뀌는것이 아니다는 것을 언급 필요
* ADC핀 변경해가며 ch 변수 바꾸는거 확인
  * Point : 직접 회로도 확인하여 A0~7이 ADC0~7 인 것을 회로도 보며 찾는 실습 수행 필요

* ```ino
    void setup() {
    Serial.begin(9600);
    ADMUX |= _BV(REFS0); //Vref = 5V
    ADCSRA |= _BV(ADEN); //AD-conv start
    ADCSRB = 0x00;
    }

    void loop() {
    uint16_t sensorValue = adc_read(7);
    Serial.println(sensorValue);
    delay(1000);
    }

    uint16_t adc_read(uint8_t ch) {
    ADMUX = (ADMUX & 0xF8)|ch;

    ADCSRA |= _BV(ADSC);

    while (ADCSRA & (1 << ADSC)); //wait for conv done!
    ADC = (ADCL | (ADCH << 8));
    return (ADC);
    }
    ```
### ADC LAB - 2
* ![](assets/2022-07-28-00-58-34.png)
* GPIO LAB -2 와 ADC LAB -1 결합
* ADC로 읽은 전압값이 n 이상일때 LED 키는 거 실습
* ```ino
    #define PIN 0x02
    int pin = PIN << 1; //D5 기준으로 수정완료

    void setup() {
    Serial.begin(9600);
    DDRD |= 0xFF;

    ADMUX |= _BV(REFS0); //Vref = 5V
    ADCSRA |= _BV(ADEN); //AD-conv start
    ADCSRB = 0x00;
    }

    void loop() {
    uint16_t sensorValue = adc_read(7);
    if(sensorValue > 512){
        PORTD |= 0xFF;
    }
    else
        PORTD = 0x00;
    Serial.println(sensorValue);
    }

    uint16_t adc_read(uint8_t ch) {
    ADMUX = (ADMUX & 0xF8)|ch;

    ADCSRA |= _BV(ADSC);

    while (ADCSRA & (1 << ADSC)); //wait for conv done!
    ADC = (ADCL | (ADCH << 8));
    return (ADC);
    }
    ```

# TIM
## TIM LAB
* 그냥 인터널 LED 블링크 예제 ㄱㄱ
* GPIO LAB1-1이랑 비교하면 될듯

# PWM
## PWM LAB 1-1
* ![](assets/2022-07-28-01-06-58.png)
* 요렇게 for 문으로 점점 밝아지는 LED PWM ㄱㄱ
* ```ino
    void setup(){
        pinMode(5, OUTPUT);
        TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
        TCCR0B = _BV(CS02);
    }

    void loop(){
        for(int i = 0; i < 255; i++){
            OCR0B = i;
            delay(2);
        }
    }
    ```
## PWM LAB 1-2
* ![](assets/![](2022-07-28-01-08-20.png).png)
* pinmode를 REG 제어로 ㄱㄱ
* ```ino
    void setup(){
        DDRD = 0xFF;
        //pinMode(5, OUTPUT);
        TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
        TCCR0B = _BV(CS02);
    }

    void loop(){
        for(int i = 0; i < 255; i++){
            OCR0B = i;
            delay(2);
        }
    }
    ```

## PWM LAB 1-3
* ![](assets/2022-07-28-01-14-04.png)
* POT로 ADC로 읽어서 ADC값대로 PWM 출력
* ADC는 10bit, PWM는 8bit
* 0~1023를 0~255로 맵핑 필요
* 해당 함수 직접 구현하여 출력 실습 ㄱㄱ
* ```ino
    #define PIN 0x02
    int pin = PIN << 5;

    uint16_t adc_read(uint8_t ch);
    int mapping(uint16_t val);

    void setup(){
        Serial.begin(9600);

        DDRD = 0xFF;

        ADMUX |= _BV(REFS0); //Vref = 5V
        ADCSRA |= _BV(ADEN); //AD-conv start
        ADCSRB = 0x00;

        TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
        TCCR0B = _BV(CS02);
    }

    void loop(){
        uint16_t sensorValue = adc_read(7);
        OCR0B = mapping(sensorValue);
        Serial.println(OCR0B);
    }

    uint16_t adc_read(uint8_t ch) {
    ADMUX = (ADMUX & 0xF8)|ch;

    ADCSRA |= _BV(ADSC);

    while (ADCSRA & (1 << ADSC)); //wait for conv done!
    ADC = (ADCL | (ADCH << 8));
    return (ADC);
    }

    int mapping(uint16_t val){
        return val / 4;
    }
    ```
