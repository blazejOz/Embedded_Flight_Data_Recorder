#pragma once

#include <iostream>
#include <vector>
#include <string.h>

#include "../imu/MPU6050.h"
#include "../utils/Utils.h"
#include "FatFsSd.h"


class Recorder {
public:
    Recorder();
    FatFsNs::SdCard* card_p = nullptr;

    void start_recording();
    void log_data(const Gyro_t& data);
    void stop_recording();

private:
    FatFsNs::File file; 
    bool is_open = false;
    int init_sd();

};