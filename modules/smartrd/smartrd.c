/*
 * This file is part of LAutopin. LAutopin is part of ENVELOPE Project.
 * (C) TU Muenchen. Lehrstuhl fuer Rechnertechnik und Rechnerorganisation
 *
 * @Author Dai Yang
 * @File smartrd.c
 * @bfief Implementation for SMART Reader
 * NOTE: smartmontools is required for this application.
 *
 * Simple SMART Counter Reader based on smartctl.
 * Provide Wrapper Functionalities parsing smartctl -a output.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "smartrd.h"


int get_smart_data(
  char * disk,
  char ** desc,
  int num_desc,
  int * values
)
{
    FILE * fp;
    char * st_command = "sudo smartctl -a ";
    char cmd[64];
    char buf[8196];
    char strtokBuf[8196];
    char s_b[64];
    int loc;
    char * oc;
    char * pch;
    int i,j;

    if(disk && desc && num_desc != 0)
    {
      memset(cmd, 0x0, 64);
      sprintf(cmd, "%s%s", st_command, disk);
      fp = popen(cmd, "r");
      if(fp!=0){
    	  memset(buf, 0x0, sizeof(buf));
    	  loc = 0;
    	  while(fgets(s_b, sizeof(s_b), fp)!=NULL){
          //TODO catch too long buffer.
    		  memcpy(buf+loc, s_b, strlen(s_b));
    		  loc += strlen(s_b);
    	  }

          fclose(fp);
          #ifdef DEBUG
          printf("[DEBUG] %s", buf);
          #endif
          if(!strstr(buf, "Permission denied"))
          {
            #ifdef DEBUG
            printf("[DEBUG] Entering PostProcessing\n");
            #endif
            for(i=0; i<num_desc; i++)
            {
              oc = 0;
              oc = strstr(buf, desc[i]);
              if(oc!=0){
                 memset(strtokBuf, 0x0, sizeof(strtokBuf));
                 strcpy(strtokBuf, oc);
                 pch = strtok(strtokBuf, " \t\n");
                 for(j=0; j<8; j++){
                   pch = strtok(NULL, " \t\n");
                 }
                 sscanf(pch, "%d", &(values[i]));
              }else{
                values[i] = -255;
              }
            }
            return 0;
          }else{
            printf("[ERROR] Permission denied, are you root?\n");
            return -12;
          }
      }else{
        printf("[ERROR] Cannot Open Smartctl. Try install smartmontools and try again. \n");
        return -11;
      }
    }else{
      return -10;
    }
    return 0;
}
