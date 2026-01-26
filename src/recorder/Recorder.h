#pragma once

#include <iostream>
#include <vector>
#include <string.h>

#include "../imu/MPU6050.h"
#include "../utils/utils.cpp"
#include "FatFsSd.h"


class Recorder {
public:
    Recorder();
    FatFsNs::SdCard* card_p = nullptr;

    int log_data(const Gyro_t& data);

private:
    int init_sd();

};