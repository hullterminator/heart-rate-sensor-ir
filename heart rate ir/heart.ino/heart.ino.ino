#include <FreqMeasure.h>

const int sensorPin = A0;
int sensorVal;
float frequency;
float BMP;

void setup()
{
  Serial.begin(115200);
   FreqMeasure.begin();
  
}
double sum=0;
int count=0;

void loop()
{
  //creates a timer variable to keep track of time
  unsigned long timer = millis();
  
  if (FreqMeasure.available()) {
    sum = sum + FreqMeasure.read();
    count = count + 1;
     if (count >= 10) {
      frequency = FreqMeasure.countToFrequency(sum / count);
      BMP = (frequency*60);
      sum = 0;
      count = 0;
     }
   }
  
  sensorVal = analogRead(sensorPin);
  
  double voltage = convertToVoltage(sensorVal);
  
  double absorbance = calculateAbsorbance(voltage);
    
  displayPulseInLabVIEW(absorbance, BMP);
  
  //small delay to change our sampling rate
  //and stabilize our signal
  delay(25);  
}

void displayPulseInLabVIEW(double absorbance, float BMP)
{
  Serial.print(absorbance,5);
  Serial.print("\t");
  Serial.print(BMP,2);
  Serial.println();
}

double convertToVoltage(double ADC_Val)
{
  double volt = 0;
  
  volt = 5*(ADC_Val/1023);
  
  return volt;
}

double calculateAbsorbance(double volt)
{
  double absorbance = 0;
  
  absorbance = log10(5/volt);
  
  return absorbance;  
}
