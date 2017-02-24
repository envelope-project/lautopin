/*
 * This file is part of LAutopin. LAutopin is part of ENVELOPE Project.
 * (C) TU Muenchen. Lehrstuhl fuer Rechnertechnik und Rechnerorganisation
 *
 * @Author Dai Yang
 * @File shc.h
 * @bfief API for Health sensor reader.
 *
 * Simple Health Sensor Reader.
 * Provide Wrapper Functionalities for reading /sys/class/hw_mon data.
 * This implementation uses the libsensors version 4 from lm-sensors.
 *
*/


#ifndef SHC_H
#define SHC_H

#ifdef __cplusplus
extern "C"{
#endif



typedef struct tag_s_value{
  char* prefix;
  char* path;
  char* feat_name;
  int feat_number;
  char* subf_name;
  int subf_number;
  double value;
}s_value_t;

/* --------- function prototype --------- */

/* Get string representation of all found sensors.
 * Note: Strings are malloced and shall be freed by user!
 */
void get_all_values(
  char ** values,         /* Container for Values Storage */
  int* num_values,        /* Number of Values and Sensors */
  int upperbound          /* size of outer array (array of values) */
);

int get_by_sensor(

);

int get_by_feature(

);


#ifdef __cplusplus
}
#endif

#endif
