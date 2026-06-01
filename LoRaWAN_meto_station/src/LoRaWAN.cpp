/**
 * @file LoRaWAN.cpp
 * @brief LoRaWAN communication
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 11-2019
 */

#include "LoRaWAN.h"

/**
 * @brief  setup and connect LoRa modem
 */
void LoRaWAN::setup()
{
  if (!m_modem.begin(EU868))
  {
    Serial.print("Failed to start module");
    while (1)
    {
      // TODO: error handling
    }
  };
  Serial.print("Module start correct");
  Serial.print("Module version is: ");
  Serial.println(m_modem.version());
  Serial.print("Device EUI is: ");
  Serial.println(m_modem.deviceEUI());

  int connected = 0;
  if (Config::auth == Authorization::OTAA)
  {
    connected = m_modem.joinOTAA(Config::app_eui, Config::app_key, Config::dev_eui);
  }
  else
  {
    connected = m_modem.joinABP(Config::dev_adr, Config::nw_s_key, Config::app_s_key);
  }

  if (!connected)
  {
    Serial.print("Something went wrong.");
    while (1)
    {
      // TODO: error handling
    }
  }

  if (Config::const_data_rate)
  {
    m_modem.dataRate(0);
  }

  delay(modem_dealy);
}

/**
 * @brief  Send measurements via LoRaWAN
 * @param  result: measurements to send
 */
void LoRaWAN::send_msg_measurements(const Results& result)
{
  String msg = convert_measurements_to_string(result);
  send_msg(msg);
}

/**
 * @brief  Send message via LoRaWAN
 * @param  msg: message to send
 */
void LoRaWAN::send_msg(const String msg)
{
  for (unsigned int i = 0; i < msg.length(); i++)
  {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
  }
  Serial.println();

  if (Config::const_data_rate)
  {
    m_modem.dataRate(0);
    delay(modem_dealy);
  }

  int err;
  m_modem.beginPacket();
  m_modem.print(msg);
  err = m_modem.endPacket(true);
  Serial.println(err);
  m_modem.sleep();
}

/**
 * @brief  Convert measurements to string, ready to send
 * @param  results: measurements to convert
 * @return assembled output string
 */
String LoRaWAN::convert_measurements_to_string(const Results& results)
{
  String msg;
  msg += "T" + String(results.temperature_ds);
  msg += "H" + String(results.humidity);
  msg += "P" + String(results.pressure);
  msg += "L" + String(results.light_intensity);
  msg += "M" + String(results.soil_moisture);
  msg += "R" + String(results.rain_pulses);

  return msg;
}
