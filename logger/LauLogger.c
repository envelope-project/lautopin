/* simple logger module for persistant storage or monitoring data.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "LauLogger.h"

static FILE* ll_file = 0;
static char* ll_f_name = 0;

/* use stat() to check if file exists */
static inline int chkFileExist(
  const char *filename
) {
    struct stat st;
    int result = stat(filename, &st);
    return (result == 0);
}

/* Check endianness, 1 is little, -1 is big */
static inline int chkEndianess()
{
  int num = 1;
  if (*(char *)&num == 1)
  {
    return 1;
  }
  return -1;
}

static inline void swap(
  unsigned char * d1,
  unsigned char * d2
)
{
  unsigned char a;
  a = *d1;
  *d1 = *d2;
  *d2 = a;
}

static void byteSwap(
  void* array,
  int num
){
  unsigned char * a = (unsigned char*) array;
  int i = 0;
  for(i; i<num/2; i++)
  {
    swap(&a[i], &a[num-1-i]);
  }
}

static unsigned char chkSum(
  void * data,
  int num_data
){
  int i;
  unsigned char * p = (unsigned char*) data;
  unsigned char ret = 0 ;
  if(p){
    for(i=0;i<num_data;i++){
      ret += p[i];
    }
  }
  return ret;
}

/* create file */
static int ll_createfile(
  const char * filename
){
  ll_file = fopen(filename, "wb+");
  if(ll_file){
    ll_f_name = (char*) malloc ((strlen(filename)+1)*sizeof(char));
    memset(ll_f_name, 0x0, (strlen(filename)+1));
    memcpy(ll_f_name, filename, strlen(filename));
    fputs(LAULOGGER_GREET, ll_file);
    fputs("\n", ll_file);
    fputs(LAULOGGER_V, ll_file);
  }else{
    return -12;
  }
  return 0;
}

/* Find a postfix 0-999 and create file */
static int ll_createfile_postfix(
  const char * filename
){
   int i = 0;
   char* fn;
   int fl = (strlen(filename) + 4);
   fn = (char*) malloc (fl*sizeof(char));
   memset(fn, 0x0, fl);
   do{
     if(i==999){
       break;
     }
     sprintf(fn, "%s_%d", filename, i);
     if(chkFileExist(fn))
     {
       continue;
     }else{
       return ll_createfile(fn);
     }
   }while(i<=999);
   free (fn);
   return -13;
}

/* close the logger function */
void laulogger_cleanup(){
  fclose(ll_file);
  free(ll_f_name);
}

/* initialization */
int laulogger_init(
  const char * file,
  int overwrite_f
){
  int ret = 0;
  if(file)
  {
    if(!chkFileExist(file)){
        ret = ll_createfile(file);
    }else{
      if(overwrite_f){
        ret = ll_createfile(file);
      }else{
        ret = ll_createfile_postfix(file);
      }
    }
  }else{
    return -10;
  }
  return 0;
}

int laulogger_log(
  const ll_entry_t * entry
){
    int ret = 0;
    if(ll_file){
      unsigned char * buffer;
      unsigned char chksum;
      buffer = (unsigned char*) malloc (11 + (entry->length));
      memset(buffer, 0xFF, 11+(entry->length));
      if(chkEndianess() == 1){
        memcpy(buffer, &(entry->ts), 4);
        memcpy(buffer+8, &(entry->id), 1);
        memcpy(buffer+8+1, &(entry->length), 1);
        memcpy(buffer+8+1+1, entry->value, entry->length);
        chksum = chkSum(buffer, 10 + (entry->length));
        memcpy(buffer+10+(entry->length), &chksum, 1);
      }else{
        if(!entry->immut){
          unsigned long ts = __builtin_bswap64(entry->ts);
          byteSwap(entry->value, entry->length);
          memcpy(buffer, &ts, 4);
        }else{
            memcpy(buffer, &(entry->ts), 4);
        }
		memcpy(buffer+8, &(entry->id), 1);
		memcpy(buffer+8+1, &(entry->length), 1);
		memcpy(buffer+8+1+1, entry->value, entry->length);
		chksum = chkSum(buffer, 10 + (entry->length));
		memcpy(buffer+10+(entry->length), &chksum, 1);
      }
      ret = fwrite(buffer, 1, 11 + (entry->length), ll_file);
      free(buffer);
      if(ret != 11 + (entry->length))
      {
        return -15;
      }
    }else{
      return -14;
    }
    return 0;
}
