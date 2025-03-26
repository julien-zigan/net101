#include <stdio.h>
#include <ifaddrs.h>
#include <errno.h>

int main(void)
{
    struct ifaddrs *ifa;
    if (getifaddrs(&ifa) == -1) {
        perror("getifaddrs() failed");
        return 1;
    }
    struct ifaddrs *iterator;

    puts("");
    int ifa_counter = 0;
    for (iterator = ifa; iterator; iterator = iterator->ifa_next) {
        printf("%2d.\t%s\n", ++ifa_counter, iterator->ifa_name);
    }
    puts("");

    freeifaddrs(ifa);
    printf("Test: OK\n");
    return 0;
}
