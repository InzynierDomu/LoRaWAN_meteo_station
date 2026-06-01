/**
 * @file Results.h
 * @brief Results from measurements
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 11-2019
 */

#pragma once

struct Results
{
  float temperature_ds;
  float temperature_bme;
  uint8_t humidity;
  uint16_t pressure;
  uint16_t light_intensity;
  uint16_t soil_moisture;
  uint32_t rain_pulses;
};
