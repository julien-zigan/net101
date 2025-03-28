#include "net101.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char usage[] =  
    "\n"
    "%s - CLI tool to explore network interfaces\n"
    "\n"
    "Usage: %s [Options]\n"
    "\n"
    "When used with no arguments %s lists "
    "all networkinterfaces with their SIOCGIFLAGS\n"
    "\n"
    "Options:\n"
    "-n\tlist interface names only\n"
    "-h\tshow this help menu\n"
    "\n";

void show_usage(char * argv[])
{
    printf(usage, argv[0], argv[0], argv[0]);
}

int main(int argc, char *argv[])
{
    int opt;
    opt = getopt(argc, argv, "nh");
    if (opt == 'h') {
        show_usage(argv);
    }
    else {
        struct ifaddrs *ifa;
        setup_ifa_list(&ifa);
        if (opt == 'n')
            print_ifa_names(ifa);
        else
            print_ifa_flags(ifa);
        freeifaddrs(ifa);
    }
    return EXIT_SUCCESS;
}
