/**
 * @file networkHandler.h
 * @brief Network connectivity and HTTP request handling.
 *
 * Contains configurations and functions for connecting to WiFi,
 * as well as performing HTTP GET requests.
 */

// WiFi network credentials.
extern const char* ssid;
extern const char* password;

/**
 * @brief Connects to the WiFi network using predefined credentials.
 */
void connectWifi();

/**
 * @brief Checks if the device is currently connected to WiFi.
 * 
 * @return True if connected, false otherwise.
 */
bool isConnectedToWiFi();

/**
 * @brief Performs an HTTP GET request to the specified server.
 * 
 * @param serverName The URL of the server to which the request is sent.
 * @return The server's response as a String.
 */
String httpGETRequest(const String& serverName);

/**
 * @brief Helper function to send an HTTP GET request and store the response.
 * 
 * @param serverName The URL of the server.
 * @param response String reference to store the server response.
 */
void sendHttpGetRequest(const String& serverName, String& response);
