#include "dust-op.h"

GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

void initDustSensor(void* pvParam){
    dustSensor.setBaseline(SHARP_BASELINE); // set no dust voltage according to your own experiments
    dustSensor.setCalibrationFactor(SHARP_CLBR_LVL); // calibrate against precision instrument
    dustSensor.begin();
    Serial.println("Sharp GP2Y dust sensor connected.");
    vTaskDelete(NULL);
}

void updateDustSensor(void* pvParam){
    while (1){
        dustSensor.getDustDensity();
        dustSensor.getRunningAverage();
        vTaskDelay(1000);
    }
}

uint16_t getPM2p5(){
    return dustSensor.getRunningAverage();
}

void dispPM2p5(){
    Serial.print("Running average: ");
    Serial.print(dustSensor.getRunningAverage());
    Serial.println(" ug/m3");
}