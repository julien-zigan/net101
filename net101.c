#include <stdio.h>
#include <ifaddrs.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct name {
    struct name *next;
    char name[32];
} NAME;

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

void print_ifa_names(struct ifaddrs *ifa)
{
    NAME *name_set;
    setup_name_set(&name_set);
    struct ifaddrs *iterator;
    NAME *name_it;
    int ifa_counter = 0;
    int headline = 0;
    for (iterator = ifa; iterator; iterator = iterator->ifa_next) {
        int add2set = 1;
        for (name_it = name_set; name_it; name_it = name_it->next) {
            if (strcmp(name_it->name, iterator->ifa_name) == 0) {
                add2set = 0;
                break;
            }
        }
        if (add2set) {
            NAME *new = (NAME *)malloc(sizeof(NAME));
            assert(new);
            strncpy(new->name, iterator->ifa_name, sizeof(new->name));
            new->next = name_set;
            name_set = new;
            if (headline == 0) {
                printf("\nInterface Names:\n\n");
                headline = 1;
            }
            printf("%4d. %s\n", ++ifa_counter, iterator->ifa_name);
        }
    }
    freenames(name_set);
    printf("\n");
}

int main(void)
{
    struct ifaddrs *ifa;
    setup_ifa_list(&ifa);
    print_ifa_names(ifa);
    freeifaddrs(ifa);
    return 0;
}
