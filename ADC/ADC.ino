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