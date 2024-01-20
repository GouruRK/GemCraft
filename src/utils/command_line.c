#include "utils/command_line.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils/errors.h"

Error command_line(bool* help, int argc, char* argv[]) {
    int opt, opt_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "h", long_options, &opt_index))
            != -1) {
        switch (opt) {
            case 'h':
                *help = true;
                return OK;
            case '?':
                return UNKNOWN_ARGUMENT;
        }
    }
    return OK;
}
