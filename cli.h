#ifndef H_CLI
#define H_CLI


#include <stdbool.h>


struct Settings {
    char *device;
    unsigned int baudrate;
    char verbosity;
    char *stopword;
};


extern struct Settings settings;


void cliparse(int argc, char **argv);


#endif
