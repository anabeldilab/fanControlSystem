/**
 * @file networkHandler.h
 * @brief Network connectivity and HTTP request handling.
 *
 * Contains configurations and functions for connecting to WiFi,
 * as well as performing HTTP GET requests.
 */
void initializeWifiConnection();
void checkWifiConnection();
String httpGETRequest(const String& serverName);
void sendHttpGetRequest(const String& serverName, String& response);
bool isConnectedToWiFi();
