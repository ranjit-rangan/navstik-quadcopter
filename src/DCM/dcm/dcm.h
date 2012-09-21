/*
 * dcm.h
 *
 *  Created on: 25-Jun-2012
 *      Author: riya
 */

#ifndef DCM_H_
#define DCM_H_

#include "das_conf.h"

#if DAS_USE_DCM
void dcmInit(void);
void dcmUpdate(float dcmEst[3][3], float xacc,  float yacc,  float zacc,\
        float xgyro, float ygyro, float zgyro,\
        float xmag,  float ymag,  float zmag,\
        float imu_interval);

typedef struct {
  float interval; // milliseconds
  uint32_t timestamp;
  float raw_gyro_data[3];  // deg per second - converting it from rad to deg in dcm_update.c
  float raw_accel_data[3]; // G
  float raw_mag_data[3];   // uT
  float attitude[3];       // roll. pitch, yaw
}current_attitude_struct;

#endif   /*DAS_USE_DCM */

#endif   /*DCM_H_ */
