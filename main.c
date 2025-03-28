#include "net101.h"
#include <stdlib.h>

int main(void)
{
    struct ifaddrs *ifa;
    setup_ifa_list(&ifa);
    print_ifa_names(ifa);
    print_ifa_flags(ifa);
    freeifaddrs(ifa);
    return EXIT_SUCCESS;
}
