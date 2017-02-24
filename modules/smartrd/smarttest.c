/*
 * This file is part of LAutopin. LAutopin is part of ENVELOPE Project.
 * (C) TU Muenchen. Lehrstuhl fuer Rechnertechnik und Rechnerorganisation
 *
 * @Author Dai Yang
 * @File smarttest.c
 * @bfief Test Cases for smartrd.c
 *
*/

#include <stdio.h>

#include "smartrd.h"

int main(
  int argc,
  char** argv
)
{
	int result[2];
	char *cmd[2] = {"Retired_Block_Count", "Unexpect_Power_Loss_Ct"};
  int ret = -255;

  ret = get_smart_data("/dev/sda", cmd, 2, result);
  if(!ret){
    printf("Result: %d\n", result[1]);
  }

  return ret;

}
