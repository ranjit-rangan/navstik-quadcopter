/*
 * dcm_update.c
 *
 *  Created on: 25-Jun-2012
 *      Author: Riya
 */

#include <math.h>

#include "das.h"

// TODO - Print the gyro, accelerometer and magnetometer values separately

#if DAS_USE_DCM && DAS_USE_MAGNETOMETER && DAS_USE_IMU

current_attitude_struct current_attitude;
static WORKING_AREA(waUpdate, 512);

static msg_t Update(void *arg) {
    (void)arg; /* not used arg was BasicSequntialStream */

  chRegSetThreadName("DCMUpdate") ;
  float dcmMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0 ,1}} ;
  uint32_t start, end ;
  uint8_t first = 1 ;
  while(TRUE) {
    float interval, pitch, roll, yaw; /* Time between 2 measurements */
    if(first) {
      start = halGetCounterValue() ;
      first = 0 ;
    }
    // TODO try and read sensor data simultaneously !
    readAllIMUData(&IMUD1) ; /* Reads values from the accelerometer and gyroscope */
    chThdSleepMilliseconds(10) ;

    readMagnetometerData(&MD1) ; /* Reads values from the magnetometer */
    chThdSleepMilliseconds(10) ;

    end = halGetCounterValue() ;
    current_attitude.timestamp = end;
    interval = convertCounterToMilliseconds(start, end) / 1000.0f ;
    start = end ;

    dcmUpdate(dcmMatrix, IMUD1.ACCEL_X, IMUD1.ACCEL_Y, IMUD1.ACCEL_Z, IMUD1.GYRO_X, IMUD1.GYRO_Y, IMUD1.GYRO_Z, MD1.MAG_X, MD1.MAG_Y, MD1.MAG_Z, interval) ;

    if(dcmMatrix[2][2] >= 0) {
      pitch = -asinf(dcmMatrix[2][0]) - M_PI;
      roll  = asinf(dcmMatrix[2][1]) - M_PI;
    }
    else {
      pitch = asinf(dcmMatrix[2][0]);
      roll  = -(asinf(dcmMatrix[2][1])) ;
    }

    yaw = my_atan2f((-1.0f * dcmMatrix[1][0]), (-1.0f * dcmMatrix[0][0])) ;
    pitch = (180 * pitch) / M_PI ;
    roll  = (180 * roll ) / M_PI ;
    yaw   = (180 * yaw  ) / M_PI ;

    current_attitude.interval = interval * 1000.0f;
    current_attitude.attitude[0] = roll;  current_attitude.attitude[1] = pitch; current_attitude.attitude[2] = yaw;
    current_attitude.raw_accel_data[0] = IMUD1.ACCEL_X; current_attitude.raw_accel_data[1] = IMUD1.ACCEL_Y; current_attitude.raw_accel_data[2] = IMUD1.ACCEL_Z;
    current_attitude.raw_gyro_data[0] = IMUD1.GYRO_X * 180.0 / M_PI; current_attitude.raw_gyro_data[1] = IMUD1.GYRO_Y * 180.0 / M_PI; current_attitude.raw_gyro_data[2] = IMUD1.GYRO_Z * 180.0 / M_PI;
    current_attitude.raw_mag_data[0] = MD1.MAG_X; current_attitude.raw_mag_data[1] = MD1.MAG_Y; current_attitude.raw_mag_data[2] = MD1.MAG_Z;
  }
  return 0 ;
}

void startDCMThread(BaseSequentialStream *bss) {
  chThdCreateStatic(waUpdate, sizeof(waUpdate), HIGHPRIO, Update, bss) ;
}
#endif  /*DAS_USE_DCM && DAS_USE_MAGNETOMETER && DAS_USE_IMU */
