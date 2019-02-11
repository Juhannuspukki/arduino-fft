#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1(A0);           //xy=233,304
AudioAnalyzeFFT1024      myFFT;      //xy=420,304
AudioConnection          patchCord1(adc1, myFFT);
// GUItool: end automatically generated code

void setup() {
  // put your setup code here, to run once:
  AudioMemory(12);
  myFFT.windowFunction(AudioWindowHanning1024);
}

void loop() {
  float n;
  int i;
  float blue = 0;
  float green = 0;
  float red = 0;

  if (myFFT.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    Serial.print("FFT: ");
    for (i=0; i<511; i++) {
      n = myFFT.read(i);
      
      if (i < 7) {
        //if (n > 0.02) {
          blue += n; 
        //}
      }
      if (i < 43) {
        if (i > 15){
          red += n;  
        }
      }
      if (i < 200){
        if (i > 50) {
           green += n;
        }
      }
      
    }
    
    Serial.print("blue1: ");
    Serial.print((blue));
    Serial.print(" green1: ");
    Serial.print((green));
    Serial.print(" red1: ");
    Serial.print((red));

    blue = constrain(floor((blue-0.2)*30), 0, 50);
    green = constrain(floor((green-0.83)*35), 0, 50);
    red = constrain(floor((red-0.52)*28), 0,35);


    Serial.print(" blue: ");
    Serial.print((blue));
    analogWrite(3, blue);
    Serial.print(" green: ");
    Serial.print((green));
    analogWrite(6, green);
    Serial.print(" red: ");
    Serial.print((red));
    analogWrite(10, red);

    Serial.println();
  }
}
