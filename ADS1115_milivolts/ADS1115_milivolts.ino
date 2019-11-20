#include "ADS1115.h"
ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);
const int alertReadyPin = 2;

void setup() 
{
    Wire.begin();
    Serial.begin(9600); // initialize serial communication   
   // Serial.println("Testing device connections...");
   // Serial.println(adc0.testConnection() ? "ADS1115 connection successful" : "ADS1115 connection failed");    
    adc0.initialize(); // initialize ADS1115 16 bit A/D chip
    adc0.setMode(ADS1115_MODE_SINGLESHOT);
    adc0.setRate(ADS1115_RATE_8);
    adc0.setGain(ADS1115_PGA_6P144);    
    pinMode(alertReadyPin,INPUT_PULLUP);
    adc0.setConversionReadyPinMode();
    #ifdef ADS1115_SERIAL_DEBUG
    adc0.showConfigRegister();
   // Serial.print("HighThreshold="); Serial.println(adc0.getHighThreshold(),BIN);
   // Serial.print("LowThreshold="); Serial.println(adc0.getLowThreshold(),BIN);
    #endif
}
void pollAlertReadyPin() 
{
  for (uint32_t i = 0; i<100000; i++)
    if (!digitalRead(alertReadyPin)) return;
//   Serial.println("Failed to wait for AlertReadyPin, it's stuck high!");
}

void loop() {
       
    // The below method sets the mux and gets a reading.
    adc0.setMultiplexer(ADS1115_MUX_P0_NG);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A0: "); Serial.print(adc0.getMilliVolts(false)); Serial.println("mV\t");
    Serial.println("deneme");
    delay(20);
}
  

  
