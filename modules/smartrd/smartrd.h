/*
 * This file is part of LAutopin. LAutopin is part of ENVELOPE Project.
 * (C) TU Muenchen. Lehrstuhl fuer Rechnertechnik und Rechnerorganisation
 *
 * @Author Dai Yang
 * @File smartrd.h
 * @bfief API for SMART Reader
 * NOTE: smartmontools is required for this application.
 *
 * Simple SMART Counter Reader based on smartctl.
 * Provide Wrapper Functionalities parsing smartctl -a output.
 *
*/


#ifndef SMARTRD_H
#define SMARTRD_H

/* FUNCTIONAL PROTOTYPE */

int get_smart_data(
  char * disk,    /* Path to the disk */
  char ** desc,   /* Name of relevant counters */
  int num_desc,   /* Number of relevant counters */
  int* values     /* Pre-Allocated Storage for Return Values */
);



#endif //SMARTRD_H
