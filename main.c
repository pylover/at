#include "cli.h"
#include "clog.h"
#include "serial_.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>


#define MAXEVENTS 2
#define CHUNKSIZE   2048
static char buff[CHUNKSIZE];
static int epollfd;


static int
serial_read(int fd) {
    ssize_t bytes = read(fd, buff, CHUNKSIZE);
    if (bytes == -1) {
        return -1;
    }

    write(STDOUT_FILENO, buff, bytes);
}

static int
arm(int fd) {
    struct epoll_event ev;

    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        ERROR("epoll_ctl: EPOLL_CTL_ADD, fd: %d", fd);
        return -1;
    }
    return 0;
}


int
main(int argc, char **argv) {
    int serialfd;
    int fdcount;
    int i;
    struct epoll_event events[MAXEVENTS];
    struct epoll_event *e;

    // Parse command line arguments
    cliparse(argc, argv);

    printf("device: %s\n", settings.device);
    printf("stopword: %s\n", settings.stopword);

    // Create epoll instance
    epollfd = epoll_create1(0);
    if (epollfd < 0) {
        FATAL("Cannot create epoll file descriptor");
    }

    serialfd = serial_open();
    if (arm(serialfd)) {
        FATAL("Cannot arm serial fd: %d", serialfd);
    }
    
    /* Main Loop */
    while (1) {
        fdcount = epoll_wait(epollfd, events, MAXEVENTS, -1);
        if (fdcount == -1) {
            FATAL("epoll_wait returned: %d", fdcount);
        }

        for (i = 0; i < fdcount; i++) {
            e = &events[i];
            if (e->events & EPOLLERR) {
                FATAL("EPOLLERR");
            }
            if (e->data.fd == serialfd) {
                if (serial_read(serialfd) == -1) {
                    FATAL("serial_read");
                }
            }
            // else if (e->data.fd == STDIN_FILENO) {
            // }
        }
    }
    return EXIT_SUCCESS;
}
