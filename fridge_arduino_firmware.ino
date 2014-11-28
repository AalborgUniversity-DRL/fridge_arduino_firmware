#include <OneWire.h>
#include <DallasTemperature.h>
#include <EmonLib.h>

EnergyMonitor emon;

const int TEMPERATURE_PRECISION = 12;
OneWire oneWireRoom(4);
DallasTemperature roomTempSensor(&oneWireRoom);
double roomTemp;
OneWire oneWireFridge(5);
DallasTemperature fridgeTempSensor(&oneWireFridge);
double fridgeTemp;

void setup()
{  
  Serial.begin(9600);
  
  // Set up a voltage and a current measurement.
  emon.voltage(1, 144.9, 1.8);// Voltage: input pin, calibration, phase_shift
  emon.current(0, 2.07);// Current: input pin, calibration.
  // Run VI calculation once and disregard the first (faulty) reading
  emon.calcVI(5,2000);
  
  // Set up the temperature sensors
  roomTempSensor.begin();
  fridgeTempSensor.begin();
}

void loop()
{
  // Calculate all. No.of crossings, time-out
  emon.calcVI(5,2000);
  
  // // Request the temp sensors to convert
  // roomTempSensor.requestTemperatures();
  // fridgeTempSensor.requestTemperatures();
  // delay(20);
  // roomTemp = roomTempSensor.getTempCByIndex(0);
  // fridgeTemp = fridgeTempSensor.getTempCByIndex(0);
  
  // Print the node number
  Serial.print("1 ");
  // Print out all variables from emon
  Serial.print(emon.realPower); Serial.print(' ');
  Serial.print(emon.apparentPower); Serial.print(' ');
  Serial.print(emon.Vrms); Serial.print(' ');
  Serial.print(emon.Irms); Serial.print(' ');
  Serial.print(emon.powerFactor); Serial.println(' ');
  // // Print Temperatures
  // Serial.print(roomTemp); Serial.print(' ');
  // Serial.print(fridgeTemp); Serial.println(' ');
  
  // // Wait a while
  // delay(10000);
  // don't: I'm running a high speed test
}
