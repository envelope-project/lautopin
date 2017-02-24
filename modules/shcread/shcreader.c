#include "shc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (
    int argc,
    char* argv)
{

  char* sbox[512];
  int n_v;
  int i;

  memset(sbox, 0x0, 512);

  #ifdef DEBUG
    printf("[DEBUG] Entry\n");
  #endif

  get_all_values(sbox, &n_v, 512);

  #ifdef DEBUG
    printf("[DEBUG] Exit\n");
  #endif

  for(i=0; i<n_v; i++)
  {
    if(sbox[i])
    {
      free(sbox[i]);
    }
  }

  return 0;

}
