/**
 * @file lightPriceDataHandler.h
 * @brief Handler for fetching and displaying light price data.
 *
 * This file contains functions to interact with light price data,
 * including fetching the price from an API and printing it.
 */

extern bool useLightMocks;

float fetchLightPrice(const String& jsonResponse);

float getCurrentLightPrice();

float getMaxLightPrice();

float getMinLightPrice();

float getCurrentPricePercentage();

void setMockLightPrice(float price);

void useMocksLightPrice(bool useMocks);

void printLightPrice(float price);