/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains all the shell commands and shell
 *structures required to start the DAS shell.
 */
/* 18-06-2012 - Riya Ray - The functions fpuTest and cmd_fputest have been added */

#include "das.h"

#ifndef SHELLCOMMANDS_H_
#define SHELLCOMMANDS_H_

#if DAS_USE_SHELL
#define SHELL_WA_SIZE   THD_WA_SIZE(2048)

extern const ShellCommand commands[] ;

extern const ShellConfig shell_cfg1 ;

#if CORTEX_USE_FPU && DAS_USE_FPUTEST
float fpuTest(BaseSequentialStream *bss, char *operand1, char oper, char *operand2);

void cmd_fputest(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*CORTEX_USE_FPU && DAS_USE_FPUTEST */

void cmd_mem(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_threads(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_clear(BaseSequentialStream *bss, int argc, char *argv[]);

#if DAS_USE_FATFS
void cmd_mount(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_unmount(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_tree(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*DAS_USE_FATFS */

#if DAS_USE_IMU
void cmd_imu(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*DAS_USE_ACCELEROMETER */

#if DAS_USE_MAGNETOMETER
void cmd_magnetometer(BaseSequentialStream *bss, int argc, char *argv[]);
#endif /*DAS_USE_MAGNETOMETER */

#if DAS_USE_BAROMETER
void cmd_barometer(BaseSequentialStream *bss, int argc, char *argv[]);
#endif /*DAS_USE_BAROMETER */

#if HAL_USE_PWM
void cmd_pwm(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*HAL_USE_PWM */

#if HAL_USE_ICU
void cmd_icu(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*HAL_USE_ICU */

#if DAS_USE_DCM
void cmd_attitude(BaseSequentialStream *bss, int argc, char *argv[]); /* print current attitude roll, pitch, yaw number of times */
void cmd_set_gain_kpi(BaseSequentialStream *bss, int argc, char *argv[]); /* proportional gain inner loop roll, pitch, yaw */
void cmd_set_gain_kii(BaseSequentialStream *bss, int argc, char *argv[]); /* integral gain inner loop roll, pitch, yaw */
void cmd_set_gain_kpo(BaseSequentialStream *bss, int argc, char *argv[]); /* proportional gain outer loop roll, pitch, yaw */
void cmd_set_gain_kio(BaseSequentialStream *bss, int argc, char *argv[]); /* integral gain outer loop roll, pitch, yaw */
#endif /* DAS_USE_DCM */

#endif  /*DAS_USE_SHELL */

#endif  /*SHELLCOMMANDS_H_ */
