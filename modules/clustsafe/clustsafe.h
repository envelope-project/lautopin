#ifndef INC_CLUSTSAFE_H
#define INC_CLUSTSAFE_H

typedef struct tag_cs_config{
    char * host;
    short port;
    char * password;
    int * outlets;
    int num_outlets;
}cs_config_t;



#endif
