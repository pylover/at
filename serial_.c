#include "cli.h"
#include "serial_.h"
#include "clog.h"

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <linux/serial.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>


int termiosbaudrate(int b) {
    switch (b) {
        case 57600:
            return B57600;

        case 115200:
            return B115200;

        case 230400:
            return B230400;

        case 460800:
            return B460800;

        case 500000:
            return B500000;

        case 576000:
            return B576000;

        case 921600:
            return B921600;

        case 1000000:
            return B1000000;

        case 1152000:
            return B1152000;

        case 1500000:
            return B1500000;

        case 2000000:
            return B2000000;

        case 2500000:
            return B2500000;

        case 3000000:
            return B3000000;

        case 3500000:
            return B3500000;

        case 4000000:
            return B4000000;
        
        default:
            return -1;
    }
}


int 
serial_open() {
    struct termios options;
    int baudrate = termiosbaudrate(settings.baudrate);
    if (baudrate == -1) {
        ERROR("Invalid baudrate: %d", settings.baudrate);
        return -1;
    }

    INFO("Serial device: %s, %d", settings.device, settings.baudrate);
    int fd = open(settings.device, O_RDWR); // | O_NDELAY); // | O_NOCTTY | O_NONBLOCK);
    if (fd == -1) {
        ERROR("Can't open serial device: %s", settings.device);
        return -1;
    }

    // speed_t speed;
    // struct serial_struct ss;
    // ioctl(fd, TIOCGSERIAL, &ss);
    // ss.flags = (ss.flags & ~ASYNC_SPD_MASK) | ASYNC_SPD_CUST;
    // ss.custom_divisor = (ss.baud_base + (speed / 2)) / speed;
    // closestSpeed = ss.baud_base / ss.custom_divisor;

    // if (closestSpeed < speed * 98 / 100 || closestSpeed > speed * 102 / 100) {
    //     ERROR("Set serial port speed to %d. Closest possible is %d\n", speed, 
    //             closestSpeed));
    // }

    // ioctl(fd, TIOCSSERIAL, &ss);
    // cfsetispeed(&tios, baudrate);
    // cfsetospeed(&tios, baudrate);

    tcgetattr(fd, &options);
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);

    // // options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);     /*Input*/
    // // options.c_oflag &= ~OPOST;                              /*Output*/
    // tcsetattr(fd, TCSANOW, &options);
    // tcflush(fd, TCOFLUSH);

    return fd;
}

