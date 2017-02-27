#include <time.h>
#include <stdio.h>
#include "LauLogger.h"

int main(){
  ll_entry_t a;
  int i;
  long test1 = 0x1234567890ABCDEF;
  int test2 = 0xABCDABCD;
  double test3 = 0.123456789;
  char* test4 = "Hallo";

  laulogger_init("test.abc", 1);

  a.ts = time(0);
  a.id = 1;
  a.length = sizeof(long);
  a.value = (void*)&test1;
  a.immut = 0;

  laulogger_log(&a);

  a.ts = time(0);
  a.id = 2;
  a.length = sizeof(int);
  a.value = (void*)&test2;

  laulogger_log(&a);

  a.ts = time(0);
  a.id = 3;
  a.length = sizeof(double);
  a.value = (void*)&test3;


  laulogger_log(&a);

  a.ts = time(0);
  a.id = 4;
  a.length = sizeof(test4);
  a.value = (void*)test4;
  a.immut = 1;

  laulogger_log(&a);


  laulogger_cleanup();

}
