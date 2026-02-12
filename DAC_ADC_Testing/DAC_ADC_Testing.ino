/* Code tested on Arduino DUE, for its better built-in DAC and ADC
*/

#include <DueTimer.h>
int PB1 = 10 ;
int i ,j ,k,l; //k is to store the state of the LEDs 
void setup() {
  // put your setup code here, to run once:
pinMode(DAC0, OUTPUT);
pinMode(DAC1, OUTPUT);
pinMode(PB1,HIGH);
attachInterrupt(digitalPinToInterrupt(PB1),pattern,CHANGE);



}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(DAC0,LOW);
  pinMode(DAC1,LOW);
}
void pattern(){
  pattern1(255);
  pattern2(0);
  }
void pattern1(int k){
    if(k == 0){
      for(i=0;++i;i<256){
      analogWrite(DAC0,i);
      delay()
      }
      k = 255;
      }
      else {
       for(i=256;--i;i>0){
      analogWrite(DAC0,i);
      delay()
      k = 0
      }
        }
   
}
void pattern2(int l){
  if(l == 255){      
    for(i=256;--i;i>0){
      analogWrite(DAC1,i);
      delay();
      l = 0;
    }
     }
     else{
       for(i=0;++i;i<256){
      analogWrite(DAC1,i);
      delay();
      l = 255;
    }
      }
    
}
