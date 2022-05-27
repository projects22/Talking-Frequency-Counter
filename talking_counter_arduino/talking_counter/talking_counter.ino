/*
 * talking Frequency Counter
 * Created: 9/04/2022
 *  Author: moty22.co.uk
*/


  unsigned char overF=0;
  unsigned int freq=0;

void setup() {
    Serial.begin(9600);
    
          //set timer0 in=250Hz out=1Hz
    OCR0A = 249;
    TCCR0A=0b1000011;  
    TCCR0B=0b1110;  //  PWM mode, input T0 pin D4
    pinMode(6, OUTPUT);
    
      // set timer2 in=16MHz out=250Hz
    OCR2A =249;
    OCR2B = 125;  
    TCCR2A=0b110011;  //output B in phase, fast PWM mode
    TCCR2B=0b1110; // set prescaler to 256 and start the timer
    pinMode(3, OUTPUT);
    
        //  set timer1
    OCR1A = 32767;   //32768 counts
    TCCR1A = 0b1000011;  
    TCCR1B = 0b11110; //input pin D5
    pinMode(9, OUTPUT);
    
}

void loop() {
    
      while(digitalRead(6)){} //wait for port low 
      while(!digitalRead(6)){} //wait for port high
   
      TIFR1 |= _BV(1);    //reset interrupt
      OCR1A = 65535;  //32767
      TCNT1=0;
      overF=0;
      while(digitalRead(6)){
        if(TIFR1 & _BV(1)) {++overF; TIFR1 |= _BV(1);}   //on overflow reset interrupt  
       }
      freq = TCNT1 ; 
  
      Serial.write(50); //a marker
      Serial.write(overF);
      Serial.write(highByte(freq));
      Serial.write(lowByte(freq));

}
