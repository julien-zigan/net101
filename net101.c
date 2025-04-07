#include "net101.h"
#include <stdio.h>
#include <ifaddrs.h>
#include <sys/socket.h>
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
                printf("\n%6s%-10s\n","", "Name");
                printf("%6s_____\n\n", "");
                /*printf("\nInterface Names:\n\n");*/
                headline = 1;
            }
            printf("%4d. %s\n", ++ifa_counter, iterator->ifa_name);
        }
    }
    freenames(name_set);
    printf("\n");
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

void af2human(char *buff, int af) 
{
    switch (af) {
        case PF_UNSPEC        : {strcpy(buff, "UNSPEC")    ; break;    };
        case PF_LOCAL	        : {strcpy(buff, "LOCAL")	 ; break;  };
        case PF_INET		    : {strcpy(buff, "IPv4"  ) 	 ; break;  };
        case PF_AX25		    : {strcpy(buff, "AX25"  ) 	 ; break;  };
        case PF_IPX		    : {strcpy(buff, "IPX"   ) 	 ; break;      };
        case PF_APPLETALK     : {strcpy(buff, "APPLETALK") ; break;    };
        case PF_NETROM	    : {strcpy(buff, "NETROM")	 ; break;      };
        case PF_BRIDGE	    : {strcpy(buff, "BRIDGE")	 ; break;      };
        case PF_ATMPVC	    : {strcpy(buff, "ATMPVC")	 ; break;      };
        case PF_X25		    : {strcpy(buff, "X25"   ) 	 ; break;      };
        case PF_INET6	        : {strcpy(buff, "IPv6" )     ; break;  };
        case PF_ROSE		    : {strcpy(buff, "ROSE"  ) 	 ; break;  };
        case PF_DECnet	    : {strcpy(buff, "DECnet")	 ; break;      };
        case PF_NETBEUI	    : {strcpy(buff, "NETBEUI")	 ; break;      };
        case PF_SECURITY	    : {strcpy(buff, "SECURITY")	 ; break;  };
        case PF_KEY		    : {strcpy(buff, "KEY"   ) 	 ; break;      };
        case PF_NETLINK	    : {strcpy(buff, "NETLINK")	 ; break;      };
        case PF_PACKET	    : {strcpy(buff, "PACKET")	 ; break;      };
        case PF_ASH		    : {strcpy(buff, "ASH"   ) 	 ; break;      };
        case PF_ECONET	    : {strcpy(buff, "ECONET")	 ; break;      };
        case PF_ATMSVC	    : {strcpy(buff, "ATMSVC")    ; break;      };
        case PF_RDS		    : {strcpy(buff, "RDS"   ) 	 ; break;      };
        case PF_SNA		    : {strcpy(buff, "SNA"   ) 	 ; break;      };
        case PF_IRDA		    : {strcpy(buff, "IRDA"  ) 	 ; break;  };
        case PF_PPPOX	        : {strcpy(buff, "PPPOX" )    ; break;  };
        case PF_WANPIPE	    : {strcpy(buff, "WANPIPE")	 ; break;      };
        case PF_LLC		    : {strcpy(buff, "LLC"   ) 	 ; break;      };
        case PF_IB		    : {strcpy(buff, "IB"	   ) ; break;      };
        case PF_MPLS		    : {strcpy(buff, "MPLS"  ) 	 ; break;  };
        case PF_CAN		    : {strcpy(buff, "CAN"   ) 	 ; break;      };
        case PF_TIPC		    : {strcpy(buff, "TIPC"  ) 	 ; break;  };
        case PF_BLUETOOTH     : {strcpy(buff, "BLUETOOTH") ; break;    };
        case PF_IUCV		    : {strcpy(buff, "IUCV"  ) 	 ; break;  };
        case PF_RXRPC	        : {strcpy(buff, "RXRPC" )    ; break;  };
        case PF_ISDN		    : {strcpy(buff, "ISDN"  ) 	 ; break;  };
        case PF_PHONET	    : {strcpy(buff, "PHONET")	 ; break;      };
        case PF_IEEE802154    : {strcpy(buff, "IEEE80215") ; break;    };
        case PF_CAIF		    : {strcpy(buff, "CAIF"  ) 	 ; break;  };
        case PF_ALG		    : {strcpy(buff, "ALG"   ) 	 ; break;      };
        case PF_NFC		    : {strcpy(buff, "NFC"   ) 	 ; break;      };
        case PF_VSOCK	        : {strcpy(buff, "VSOCK" )    ; break;  };
        case PF_KCM		    : {strcpy(buff, "KCM"   ) 	 ; break;      };
        case PF_QIPCRTR	    : {strcpy(buff, "QIPCRTR")	 ; break;      };
        case PF_SMC		    : {strcpy(buff, "SMC"   ) 	 ; break;      };
        case PF_XDP		    : {strcpy(buff, "XDP"   ) 	 ; break;      };
        case PF_MCTP		    : {strcpy(buff, "MCTP"  ) 	 ; break;  };
    }
}

void print_ifa_flags(struct ifaddrs *ifa)
{
    struct ifaddrs *iterator;
    NAME *name_it;
    int ifa_counter = 0;
    int headline = 0;
    char flagbuffer[128] = {'\0'};
    printf("\n%6s%-10s %s\n","", "Name", "Flags");
    printf("%6s%-10s %s\n\n", "","_____", "______");
    for (iterator = ifa; iterator; iterator = iterator->ifa_next) {
        flags2human(flagbuffer, iterator->ifa_flags); 
        printf("%4d. %-10s %s\n", ++ifa_counter, iterator->ifa_name,
                   flagbuffer);
        strcpy(flagbuffer, "");
    }
    printf("\n");
}

void print_address_family(struct ifaddrs *ifa) 
{
    struct ifaddrs *iterator;
    NAME *name_it;
    int ifa_counter = 0;
    int headline = 0;
    char afbuffer[16] = {'\0'};
    printf("\n%6s%-10s %s\n","", "Name", "Address Family");
    printf("%6s%-10s %s\n\n", "","_____", "_______________");
    for (iterator = ifa; iterator; iterator = iterator->ifa_next) {
        af2human(afbuffer, iterator->ifa_addr->sa_family);
        printf("%4d. %-10s %s\n", ++ifa_counter, iterator->ifa_name,
                   afbuffer);
    }
    printf("\n");
}

void print_all(struct ifaddrs *ifa)
{
    struct ifaddrs *iterator;
    NAME *name_it;
    int ifa_counter = 0;
    int headline = 0;
    char afbuffer[16] = {'\0'};
    char flagbuffer[128] = {'\0'};
    printf("\n%6s%-10s %-10s %s\n","", "Name", "Addr Fam", "Flags");
    printf("%6s%-10s %-10s %s\n\n", "","_____", "_________", "______");
    for (iterator = ifa; iterator; iterator = iterator->ifa_next) {
        af2human(afbuffer, iterator->ifa_addr->sa_family);
        flags2human(flagbuffer, iterator->ifa_flags); 
        printf("%4d. %-10s %-10s %s\n", ++ifa_counter, 
               iterator->ifa_name, afbuffer, flagbuffer);
        strcpy(flagbuffer, "");
    }
    printf("\n");
    
}
