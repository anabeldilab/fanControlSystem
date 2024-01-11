void initializeMQTTConnection();
void establishMQTTConnection();
void checkMQTTConnection();
void handleMQTTLoop();

void callback(char *topic, byte *payload, unsigned int length);

void publishLightPriceData(float price);
void publishTemperatureData(float temperature);
void publishRPMData(int rpm);

