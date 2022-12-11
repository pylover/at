#include "cli.h"
#include "serial.h"

#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char **argv) {
    int serialfd;
    // Parse command line arguments
    cliparse(argc, argv);

    printf("device: %s\n", settings.device);
    printf("stopword: %s\n", settings.stopword);

    serialfd = serial_open();
    
/*
struct termios termios;

tcgetattr(filedesc, &termios);
termios.c_lflag &= ~ICANON; // Set non-canonical mode
termios.c_cc[VTIME] = 100; // Set timeout of 10.0 seconds
tcsetattr(filedesc, TCSANOW, &termios);
*/

    return EXIT_SUCCESS;
}
