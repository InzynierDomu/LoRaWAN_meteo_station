/**
 * @file PinConfig.h
 * @brief Pins configuration
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 11-2019
 */

#include <Arduino.h>

#pragma once

namespace Pins
{
const uint8_t one_wire = 0; ///< DS18B20 thermometer pin
const uint8_t soil_moisture_sensor = A5; ///< soil moisture pin
const uint8_t light_sensor = A6; ///< Photoresistor pin
const uint8_t rain_sensor = 5;   ///< Rain gauge pulse pin
} // namespace Pins
