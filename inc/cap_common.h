#ifndef __PCAP_COMMON__
#define __PCAP_COMMON__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "pcap.h"


typedef struct ip_lst {
    char ip_str[INET6_ADDRSTRLEN];
    int  packet_count;
}ip_list;


typedef struct ipstats {
    ip_list ip_stat_list[1000];
    unsigned int curr_index;
}ip_stats;


typedef struct strct_list{
    const u_char        *data;
    bpf_u_int32         offset;
    struct strct_list   *next;
}struct_list;

int add_entry_to_ip_list(ip_stats* ip_st, char *ip);
int list_push(struct_list** head_ref, const u_char* new_data, bpf_u_int32 len);
struct_list* list_pop(struct_list** head_ref);
unsigned int list_size(struct_list** head_ref);



void account_packets_per_endpoint(struct_list** packet_list, unsigned int count, ip_stats* ip_st);


#endif // __PCAP_COMMON__
