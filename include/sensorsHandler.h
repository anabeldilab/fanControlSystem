extern float mockTemperature;

void initializeDHTSensor();
void initializeSpeedSensor();

void useMocksTemperature(bool useMocks);

float setMockTemperature(float temperature);
float getTemperature();
float getHumidity();

void calculateRPM();
int getRPM();

void printTemperature(float temperature);
void printHumidity(float humidity);