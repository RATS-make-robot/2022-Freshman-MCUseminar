#include <stdint.h>
uint16_t sensor_value[5] = {0,};
void init_adc();
uint16_t read_adc();

void setup(){
    Serial.begin(9600);
}

void loop(){
    sensor_value[0] = read_adc(0b0000);
    sensor_value[1] = read_adc(0b0001);
    sensor_value[2] = read_adc(0b0010);
    sensor_value[3] = read_adc(0b0011);
    sensor_value[4] = read_adc(0b1000);

    Serial.println("%u\t%u\t%u\t%u\t%u" ,&sensor_value[0],&sensor_value[1],&sensor_value[2], &sensor_value[3],&sensor_value[4]);
    delay(100);
}

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