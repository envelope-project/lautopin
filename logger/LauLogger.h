#ifndef INC_LAULOGGER_H
#define INC_LAULOGGER_H

#define LAULOGGER_V "v 1.0\n"
#define LAULOGGER_GREET "(C) TUM-LRR 2017. LauLogger File"

typedef struct tag_ll_entry{
  unsigned long ts;
  unsigned char id;
  unsigned char length;
  void* value;
  int immut;
}ll_entry_t;


int laulogger_init(
  const char * file,
  int overwrite_f
);
void laulogger_cleanup();
int laulogger_log(
  const ll_entry_t * entry
);

#endif
