#pragma once

#include <iostream>
#include <string.h>

#include "../imu/MPU6050.h"
#include "FatFsSd.h"


class Recorder {
public:
    FatFsNs::SdCard* card_p = nullptr;
    Recorder();
    int write_to_sd();

private:
    int init_sensor();

};