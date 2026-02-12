// Project 3: DC/DC Power Monitoring
const int pinVIn = A0;
const int pinVSense = A1;
const int pinVSense2 = A2;

const float R_sense = 220.0; // Ohms
const float ADC_REF = 5.0;   // Arduino Nano reference voltage
const int ADC_MAX = 1023;    // 10-bit ADC

void setup() {
  Serial.begin(115200);
}

float readAverage(int pin, int samples=50) {
  float total = 0;
  for(int i=0; i<samples; i++){
    total += analogRead(pin);
  }
  return total / samples;
}

void loop() {
  float adcVIn = readAverage(pinVIn);

  float adcVSense = readAverage(pinVSense);
  float adcVSense2 = readAverage(pinVSense2);
    
  float V_in = 2 * adcVIn * ADC_REF / ADC_MAX;

  float V_sense = adcVSense * ADC_REF / ADC_MAX;
  float V_load = V_in - V_sense;

  float V_sense2 = adcVSense2 * ADC_REF / ADC_MAX;
  float V_load2 = V_in - V_sense2;
  
  float current = V_sense / R_sense; // in Amps
  float power = V_load * current;    // in Watts

  float current2 = V_sense2 / R_sense; // in Amps
  float power2 = V_load2 * current;    // in Watts
  
  // Serial.print("adcVIn: "); Serial.print(adcVIn); Serial.print(" V, ");
  // Serial.print("adcVSense: "); Serial.print(adcVSense); Serial.print(" V, ");
  // Serial.print("adcVLoad: "); Serial.print(adcVLoad); Serial.println(" V, ");
  Serial.print("V_in: "); Serial.print(V_in); Serial.print(" V, ");
  Serial.print("V_sense: "); Serial.print(V_sense); Serial.print(" V, ");
  Serial.print("V_load: "); Serial.print(V_load); Serial.print(" V, ");
  Serial.print("I: "); Serial.print(current*1000); Serial.print(" mA, ");
  Serial.print("P: "); Serial.print(power*1000); Serial.print(" mW");
  Serial.print("   ");
  Serial.print("V_sense2: "); Serial.print(V_sense2); Serial.print(" V, ");
  Serial.print("V_load2: "); Serial.print(V_load2); Serial.print(" V, ");
  Serial.print("I2: "); Serial.print(current2*1000); Serial.print(" mA, ");
  Serial.print("P2: "); Serial.print(power2*1000); Serial.println(" mW");
  
  delay(500);
}
