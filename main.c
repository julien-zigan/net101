#include "net101.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char usage[] =  
    "\n"
    "%s - CLI tool to explore network interfaces\n"
    "\n"
    "Usage: %s [Option]\n"
    "\n"
    "When used with no arguments %s lists "
    "all networkinterfaces with their SIOCGIFLAGS\n"
    "\n"
    "Options:\n"
    "-N\tlist interface names only\n"
    "-h\tshow this help menu\n"
    "\n";

void print_help(char * argv[])
{
    printf(usage, argv[0], argv[0], argv[0]);
}

int main(int argc, char *argv[])
{
    int opt;
    struct ifaddrs *ifa;

    setup_ifa_list(&ifa);
    opt = getopt(argc, argv, "nh");
    
    if ((opt == -1 && argc > 1) || argc > 2) {
        print_help(argv);
        goto cleanup;
    }

    switch (opt) {
    case -1:
        print_ifa_flags(ifa);
    case 'N':
        print_ifa_names(ifa);
        break;
    default:
        print_help(argv);
        break;
    }
    
cleanup:
    freeifaddrs(ifa);

    return EXIT_SUCCESS;
}
