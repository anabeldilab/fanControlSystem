/**
 * @file lightPriceDataHandler.h
 * @brief Handler for fetching and displaying light price data.
 *
 * This file contains functions to interact with light price data,
 * including fetching the price from an API and printing it.
 */

// URL of the API providing current light price data.
const String currentLightPriceUrl = "https://api.preciodelaluz.org/v1/prices/now?zone=PCB";

/**
 * @brief Fetches the light price from a JSON response.
 * 
 * @param jsonResponse The JSON string containing the light price.
 * @return The extracted light price as a float. Returns -1.0 if parsing fails.
 */
float fetchLightPrice(const String& jsonResponse);

/**
 * @brief Prints the current light price to the Serial monitor.
 * 
 * @param price The light price to be printed.
 */
void printLightPrice(float price);