/*
 * dcm_update.h
 *
 *  Created on: 25-Jun-2012
 *      Author: riya
 */

#ifndef DCM_UPDATE_H_
#define DCM_UPDATE_H_

#if DAS_USE_DCM && DAS_USE_MAGNETOMETER && DAS_USE_IMU
float calc_gyro_rate(int16_t raw, float sens);
void startDCMThread(BaseSequentialStream *bss);
#endif  /*DAS_USE_DCM && DAS_USE_MAGNETOMETER && DAS_USE_IMU */

#endif /*DCM_UPDATE_H_ */
