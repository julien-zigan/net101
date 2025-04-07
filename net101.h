
#ifndef __NET101_H__
#define __NET101_H__

#include <ifaddrs.h>

typedef struct name {
    struct name *next;
    char name[32];
} NAME;

extern void setup_ifa_list(struct ifaddrs **ifa);
extern void freenames(NAME *name_set);
extern void setup_name_set(NAME **name_set);
extern void print_ifa_names(struct ifaddrs *ifa);
extern void print_ifa_flags(struct ifaddrs *ifa);
extern void flags2human(char *buffer, unsigned int flags);
extern void print_address_family(struct ifaddrs *ifa);
extern void af2human(char *buff, int af);
extern void print_all(struct ifaddrs *ifa);
extern void print_addr(struct ifaddrs *ifa);
extern void ipv42human(char *buff, unsigned int addr);

#endif
