/**
 * @file LoRaWAN_meteo_station.ino
 * @brief LoRaWAN meteo station main
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 11-2019
 */

#include "ArduinoLowPower.h"
#include "Config.h"
#include "LoRaWAN.h"
#include "Measurements.h"
#include "Pin_config.h"
#include "Results.h"

#include <Arduino.h>

Measurements m_measurements;
LoRaWAN m_lorawan;
Results m_results;

volatile uint32_t rain_counter = 0;

void on_rain_pulse()
{
  rain_counter++;
}

void setup()
{
  Serial.begin(9600);
  delay(60000); // TODO: test without this

  pinMode(Pins::rain_sensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Pins::rain_sensor), on_rain_pulse, FALLING);

  m_lorawan.setup();
  m_measurements.init_sensors();
}

void loop()
{
  Serial.print("Rain pulses: ");
  Serial.println(rain_counter);

  m_measurements.measure(m_results);
  m_lorawan.send_msg_measurements(m_results);
  LowPower.deepSleep(Config::uplink_interval);
}
