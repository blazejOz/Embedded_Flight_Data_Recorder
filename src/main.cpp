#include "pico/stdlib.h"
#include "FatFsSd.h"
#include "imu/MPU6050.h"
#include "recorder/Recorder.h"
#include "utils/Utils.h"
#include "pinout.h"

//FREERTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

struct DataPack
{
    uint32_t timestamp;
    Gyro_t gyro;
    Accel_t accel;
};

QueueHandle_t dataQueue = nullptr;
TaskHandle_t xSensorTaskHandle = nullptr;

void vSensorTask(void* pvParam)
{
    MPU6050* imu = (MPU6050*)pvParam;
    DataPack pack;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(10);
    
    while(true){
        Utils::turnOn_green();
        pack.timestamp = to_ms_since_boot(get_absolute_time());
        imu->getGyro(&pack.gyro);
        imu->getAccel(&pack.accel);

        xQueueSend(dataQueue, &pack, 0);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }

}

void vLoggerTask(void *pvParameters) 
{
    Recorder* recorder = (Recorder*)pvParameters;
    DataPack pack;

    while (true) {
        if (xQueueReceive(dataQueue, &pack, portMAX_DELAY) == pdTRUE) {
            Utils::turnOff_green();
            
            // Log the data to the SD card
            recorder->log_data(pack.timestamp, pack.gyro, pack.accel);
            printf("Logged: %lu Gyro X:%d Y:%d Z:%d Accel X:%d Y:%d Z:%d \n", 
                   pack.timestamp, 
                   pack.gyro.x, pack.gyro.y, pack.gyro.z, 
                   pack.accel.x, pack.accel.y, pack.accel.z);
        }
    }
}

void vShutDownTask(void * pvParams)
{
    Recorder* recorder = (Recorder*)pvParams;

    while(true){
        if(Utils::is_button_clicked()){
            if(xSensorTaskHandle != nullptr){
                vTaskSuspend(xSensorTaskHandle);
            }

            DataPack leftover;
            while(uxQueueMessagesWaiting(dataQueue) > 0){
                if(xQueueReceive(dataQueue, &leftover, pdMS_TO_TICKS(10)) == pdTRUE){
                    recorder->log_data(leftover.timestamp, leftover.gyro, leftover.accel);
                }
            }

            recorder->stop_recording();

            Utils::turnOff_green();
            Utils::turnOn_red();
            printf("\n--- Flight Recorder Stopped Safely ---\n");
            vTaskSuspend(NULL);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }

}

int main() {
    stdio_init_all();
    sleep_ms(4000); 
    
    
    Utils::init(START_BTN_PIN, GREEN_LED_PIN, RED_LED_PIN);
    static MPU6050 mpu(MPU_I2C_PORT, MPU_SDA_PIN, MPU_SCL_PIN); 
    static Recorder recorder(SD_SPI_PORT, SD_MISO_PIN, SD_MOSI_PIN, SD_SCK_PIN, SD_CS_PIN);

    //Hold Button to start
    while(true){
        if(Utils::is_button_clicked()){
            Utils::turnOn_green();
            recorder.start_recording();
            printf("\n--- Starting Flight Recorder ---\n");
            break;
        }
        sleep_ms(50);
    }

    dataQueue = xQueueCreate(10, sizeof(DataPack) );
    if(dataQueue == NULL){
        Utils::handle_error("Create Queue\n");
        while(1);
    }

    xTaskCreate(
        vSensorTask,        // Function
        "IMU_READER",       // Name for debugging
        2048,               // Stack size
        &mpu,               // Param passed 
        2,                  // Priority
        &xSensorTaskHandle  // Task handle
    );

    xTaskCreate(
        vLoggerTask,        
        "SD_Logger",       
        4096,            
        &recorder,          
        1,                  
        NULL                
    );

    xTaskCreate(
        vShutDownTask,
        "ShutDown_Task",
        2048,
        &recorder,
        3,
        NULL
    );

    vTaskStartScheduler();
    while(1); 
}
   