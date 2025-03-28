#include "net101.h"
#include <stdio.h>
#include <ifaddrs.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void setup_ifa_list(struct ifaddrs **ifa) 
{
    if (getifaddrs(ifa) == -1) {
        perror("getifaddrs() failed");
        exit(1);
    }
}

void freenames(NAME *name_set)
{
    while (name_set) {
        NAME *tmp = name_set;
        name_set = name_set->next;
        free(tmp);
    }
}

void setup_name_set(NAME **name_set) 
{
    NAME *tmp = (NAME *)malloc(sizeof(NAME));
    assert(tmp);
    tmp->next = NULL;
    *name_set = tmp;
}

/* flags defined in linux/if.h */
void flags2human(char *buffer, unsigned int flags) {
    unsigned int f;
    if (flags & (1<<0))
        strcat(buffer, "up ");
    if (flags & (1<<1))
        strcat(buffer, "broad ");
    if (flags & (1<<2))
        strcat(buffer, "dbg ");
    if (flags & (1<<3)) 
        strcat(buffer, "lo ");
    if (flags & (1<<4))
        strcat(buffer, "p2p ");
    if (flags & (1<<5))
        strcat(buffer, "notr ");
    if (flags & (1<<6))
        strcat(buffer, "run ");
    if (flags & (1<<7))
        strcat(buffer, "noarp ");
    if (flags & (1<<8))
        strcat(buffer, "prmsc ");
    if (flags & (1<<9))
        strcat(buffer, "allmlt ");
    if (flags & (1<<10))
        strcat(buffer, "mstr ");
    if (flags & (1<<11))
        strcat(buffer, "slve ");
    if (flags & (1<<12))
        strcat(buffer, "mltcst ");
    if (flags & (1<<13))
        strcat(buffer, "portsel ");
    if (flags & (1<<14))
        strcat(buffer, "autmdia ");
    if (flags & (1<<15))
        strcat(buffer, "dyn ");
    if (flags & (1<<16))
        strcat(buffer, "lowup ");
    if (flags & (1<<17))
        strcat(buffer, "dorm ");
    if (flags & (1<<18))
        strcat(buffer, "echo ");
}

void print_ifa_names(struct ifaddrs *ifa)
{
    struct ifaddrs *iterator;
    NAME *name_it;
    int ifa_counter = 0;
    int headline = 0;
    char flagbuffer[128] = {'\0'};
    printf("\n%6s%-10s\t%s\n","", "Name", "Flags");
    printf("%6s__________________________\n\n", "");
    for (iterator = ifa; iterator; iterator = iterator->ifa_next) {
        flags2human(flagbuffer, iterator->ifa_flags); 
        printf("%4d. %-10s\t%s\n", ++ifa_counter, iterator->ifa_name,
                   flagbuffer);
        strcpy(flagbuffer, "");
    }
    printf("\n");
}
