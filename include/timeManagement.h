/**
 * @file timeManagement.h
 * @brief Time synchronization and retrieval functions.
 *
 * Includes functions for synchronizing the system time with an NTP server
 * and obtaining the current hour as a string.
 */

/**
 * @brief Synchronizes the system time with an NTP server.
 */
void syncTime();

/**
 * @brief Retrieves the current hour as a string.
 * 
 * @return The current hour in "HH" format as a String.
 */
String getCurrentHour();
