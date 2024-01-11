enum FanMode { AUTO, MANUAL };

void initializePWM();

bool isCurrentFanModeAuto();
bool isCurrentFanModeManual();

void setFanMode(FanMode mode);
void setFanSpeedManual(int speed);
void setFanSpeed(int speedPercentege);
void turnFanOff();
void turnFanOn();
void changeFanDirection();
void handleFanControl();