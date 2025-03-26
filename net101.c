#include <stdio.h>
#include <ifaddrs.h>
#include <errno.h>

void setup_ifa_list(struct ifaddrs **ifa) 
{
    if (getifaddrs(ifa) == -1) {
        perror("getifaddrs() failed");
        exit(1);
    }
}

int main(void)
{
    struct ifaddrs *ifa;
    setup_ifa_list(&ifa);

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
