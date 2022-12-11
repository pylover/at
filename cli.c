#include "clog.h"
#include "cli.h"

#include <stdlib.h>
#include <err.h>
#include <argp.h>


const char *argp_program_version = "v1.0.0";
const char *argp_program_bug_address = "http://github.com/pylover/upper";
static char doc[] = "Serial modem AT command sender.";
static char args_doc[] = "HOST";


#define DEFAULT_DEVICE   "/dev/ttymodem0"
#define DEFAULT_BAUDRATE    115200


struct Settings settings = {
    .device = DEFAULT_DEVICE,
    .baudrate = DEFAULT_BAUDRATE,
    .verbosity = CLOG_DEBUG,
    .stopword = "OK",
};


/* Used to create string literal from integer during preprocess. */
#define _STR(X) #X
#define STR(X) _STR(X)


/* Options definition */
static struct argp_option options[] = {
	{"device", 'd', "FILENAME", 0, 
        "Serial device path, default: "DEFAULT_DEVICE},
	{"baudrate", 'b', "BAUDRATE", 0, 
        "Baudrate, default: " STR(DEFAULT_BAUDRATE)},
    {"verbosity", 'v', "LEVEL", 0, "Verbosity level: 0-4. default: 3"},
	{0}
};


/* Parse a single option. */
static int 
parse_opt(int key, char *arg, struct argp_state *state) {
	switch (key) {
        
        case 'v':
            settings.verbosity = atoi(arg);
            break;

		case 'b':
			settings.baudrate = atoi(arg);
			break;
        
        case 'd':
            settings.device = arg;
            break;
        
		case ARGP_KEY_ARG:
			if (state->arg_num >= 1) {
				/* Too many arguments. */
		        argp_usage(state);
			    return ARGP_ERR_UNKNOWN;
			}
			settings.stopword = arg;
			break;
  
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}


static struct argp argp = {options, parse_opt, args_doc, doc};


void 
cliparse(int argc, char **argv) {
	int e = argp_parse(&argp, argc, argv, 0, 0, 0);
	if (e) {
        err(EXIT_FAILURE, "Cannot parse arguments");
	}

    /* Initialize the logging module */
    clog_verbosity = settings.verbosity;
}
