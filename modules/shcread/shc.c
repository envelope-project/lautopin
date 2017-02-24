/*
 * This file is part of LAutopin. LAutopin is part of ENVELOPE Project.
 * (C) TU Muenchen. Lehrstuhl fuer Rechnertechnik und Rechnerorganisation
 *
 * @Author Dai Yang
 * @File shc.c
 * @bfief Implementation for Health sensor reader.
 *
 * Simple Health Sensor Reader.
 * Provide Wrapper Functionalities for reading /sys/class/hw_mon data.
 * This implementation uses the libsensors version 4 from lm-sensors.
 *
*/



#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../../sensors.h"
#include "shc.h"

#ifdef DEBUG
char dbgStr[256];
#endif

static int init_libSensor = 0;

/* Basic Implementation for a Libsensors wrapper */
void get_all_values(
  char ** values,         /* Container for Values Storage */
  int* num_values,        /* Number of Values and Sensors */
  int upperbound          /* size of outer array (array of values) */
){
  sensors_chip_name const * cn;
  int c = 0;
  *num_values = 0;

  #ifdef DEBUG
  printf("[DEBUG] inside func %s\n", __func__);
  #endif

  if(!init_libSensor){
    sensors_init(NULL);
  }

  while (
    (cn = sensors_get_detected_chips(0, &c)) != 0)
  {
    // Sensor Level
    #ifdef DEBUG
    sprintf(dbgStr, "Found Device %s/%s\n", cn->prefix, cn->path);
    printf("%s", dbgStr);
    #endif
    sensors_feature const * feat;
    int f = 0;

    while (
      (feat = sensors_get_features(cn, &f)) != 0)
    {
      // Feature Level
      #ifdef DEBUG
      sprintf(dbgStr, "\tFound Feature %s: %s\n", cn->path, feat->name);
      printf("%s", dbgStr);
      #endif

      sensors_subfeature const * subf;
      int s = 0;

      // Subfeature Level
      while (
        (subf = sensors_get_all_subfeatures(cn, feat, &s)) != 0)
      {
        #ifdef DEBUG
        sprintf(dbgStr, "\t\tFound Subfeature %s/%s\n", feat->name, subf->name);
        printf("%s", dbgStr);
        #endif

        double val;
        if (subf->flags & SENSORS_MODE_R) {
          // Value Level
            int rc = sensors_get_value(cn, subf->number, &val);
            #ifdef DEBUG
            sprintf(dbgStr, "\t\t\tValue of Feature %s: %lf\n", subf->name, val);
            printf("%s", dbgStr);
            #endif

            if (rc >= 0) {
              char * buffer = (char*) malloc (1024);
              //fileformat!
              sprintf(buffer, "Prefix %s, Path %s, Feature %s, Num Feature %d,\n Subfeature %s, Num Subfeature %d, Value %lf \n",
                        cn->prefix, cn->path,
                        feat->name, feat->number,
                        subf->name, subf->number,
                        val);
              printf("ID: %d, %s\n", *num_values, buffer);
              if(*num_values<upperbound)
              {

                values[*num_values] = buffer;
                (*num_values)++;
              }else{
                printf("[WARN] Data storage is too small to store all found values");
                sensors_cleanup();
                return ;
              }
             //TODO Hier mittels Datenstruktur Daten uebergeben statt mit string.
            } else {
              //TODO: Error Handling!
            }
        }
      }
    }
  }

  if(init_libSensor)
  {
    sensors_cleanup();
  }
}
