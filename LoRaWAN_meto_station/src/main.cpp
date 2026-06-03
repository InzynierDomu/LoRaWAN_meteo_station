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
#include <RTCZero.h>

Measurements m_measurements;
LoRaWAN m_lorawan;
Results m_results;
RTCZero rtc;

volatile bool send_due = true;
volatile uint32_t rain_counter = 0;
volatile uint32_t last_pulse_ms = 0;
static const uint32_t debounce_ms = 50;

void on_send_alarm()
{
  send_due = true;
}

void on_rain_pulse()
{
  uint32_t now = millis();
  if (now - last_pulse_ms >= debounce_ms)
  {
    rain_counter++;
    last_pulse_ms = now;
  }
}

void arm_send_alarm()
{
  rtc.setAlarmEpoch(rtc.getEpoch() + Config::uplink_interval / 1000);
  rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
}

void setup()
{
  Serial.begin(9600);
  delay(60000); // TODO: test without this

  rtc.begin();
  rtc.attachInterrupt(on_send_alarm);

  pinMode(Pins::rain_sensor, INPUT_PULLUP);
  LowPower.attachInterruptWakeup(Pins::rain_sensor, on_rain_pulse, CHANGE);

  m_lorawan.setup();
  m_measurements.init_sensors();
}

void loop()
{
  if (send_due)
  {
    send_due = false;
    arm_send_alarm();

    m_measurements.measure(m_results);

    noInterrupts();
    m_results.rain_pulses = rain_counter;
    rain_counter = 0;
    interrupts();

    Serial.print("Rain pulses: ");
    Serial.println(m_results.rain_pulses);

    m_lorawan.send_msg_measurements(m_results);
  }

  LowPower.deepSleep();
}
