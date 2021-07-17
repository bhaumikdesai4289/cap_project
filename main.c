#include "cap_common.h"

/**
  * @brief The decode_packet
  *
  * This method will calculate and update number of packets sent from a source ip 
  *
  * @param packet_list - This is a linked-list consisting packets to be processed
  *        count - count consist total number of packets available in the packet_list
  *        ip_st - ip_st is a data structure which will hold packet_count and ip 
  *        details of processed packet
  */
void decode_packet(struct_list** packet_list, unsigned int count, ip_stats* ip_st)
{
    while (count > 0) {

        struct_list* packet = (struct_list *)(list_pop(packet_list));
        if(packet != NULL) {
            const struct ether_header* ethernet_header = (const struct ether_header *)packet->data;
            if (ntohs(ethernet_header->ether_type) == ETHERTYPE_IP) {
                const struct ip* ipHeader = (const struct ip *)(packet->data + sizeof(struct ether_header));

                char src_buffer[INET6_ADDRSTRLEN] = "";
                inet_ntop(AF_INET, &(ipHeader->ip_src), src_buffer, INET_ADDRSTRLEN);

                add_entry_to_ip_list(ip_st, src_buffer);
            }

            if (packet->data != NULL) {
                free((void*)packet->data);
                packet->data = NULL;
            }

            free(packet);
            packet = NULL;
            count--;
        } else {
            break;
        }
    }
}


/**
  * @brief The usage
  *
  * This method is printing the usage to consol end quits the application with exit code 1
  *
  * @param application_name the name of application to be used in print out
  */
void usage(char* application_name)
{
  printf ("Usage: <application_name> <capture_file>\n");
  exit (1);
}

//main
int main (int argc, char *argv[])
{
  char pcap_err_buffer[PCAP_ERRBUF_SIZE];
  pcap_t* pcap_hndl = NULL;
  struct_list* packet_list = NULL;

  ip_stats ip_statistics = {0};
  // Check the number of parameters
  if (argc < 2) {
    usage(argv[0]);
  }

  struct stat buffer;
  if (stat(argv[1], &buffer) != 0) {
    perror("ERROR: ");
    return 2;
  }

  // Clear the error buffer
  memset(pcap_err_buffer, 0, PCAP_ERRBUF_SIZE);

  printf ("Filename to be parsed: %s\n",argv[1]);
  // Open the capture file for offline parsing
  pcap_hndl = pcap_open_offline(argv[1], pcap_err_buffer);
  if (pcap_hndl == NULL) {
    perror("ERROR: ");
    return 3;
  }

  // The pcap header structure
  struct pcap_pkthdr packet_hdr;

  const u_char *packet;
  unsigned int count = 0;

  while (1) {

    // Next packet from capture file
    packet = pcap_next(pcap_hndl, &packet_hdr);
    if (((count % 1000) == 0) || packet == NULL) {
      decode_packet(&packet_list, count, &ip_statistics);
    }

    if (packet == NULL) {
      // EOF 
      printf("Complete file has been processed! Number of packets processed: %d!\n",count);
      break;
    }

    const u_char* dump = (const u_char*)malloc(packet_hdr.len);
    memcpy((void*)dump,(void*)packet,packet_hdr.len);
    list_push(&packet_list, dump, packet_hdr.len);
    count++;
  }


  /*! Display Stats*/
  unsigned int idx = 0;
  printf ("# of packets from source ip:\n\n");
  for (idx = 0; idx < ip_statistics.curr_index; idx++)
  {
      printf ("src ip address: %15s\t\t# of Packet(s): %d\n",ip_statistics.ip_stat_list[idx].ip_str, ip_statistics.ip_stat_list[idx].packet_count);
  }

  // Close the pcap file handle
  pcap_close(pcap_hndl);

  return 0;
}
