#include "cap_common.h"

/**
  * @brief The add_entry_to_ip_list
  *
  * This method will and update number of packets sent from a source ip 
  *
  * @param ip_st - ip_st is a data structure which will hold packet_count and ip 
  *        details of processed packet
  *        ip - ip consists the ip address against which count has to be pegged
  */
int add_entry_to_ip_list(ip_stats* ip_st, char *ip)
{
    // If curr_index is zero add at zeroth index
    if (ip_st->curr_index == 0) {
        memcpy(ip_st->ip_stat_list[ip_st->curr_index].ip_str,ip,INET6_ADDRSTRLEN);
        ip_st->ip_stat_list[ip_st->curr_index].packet_count++;
        ip_st->curr_index++;
    }
    else {
        // Traverse till curr_index and if ip is found update the packet_count
        unsigned int idx = 0;
        u_char is_found = 0;
        for (idx = 0; idx < ip_st->curr_index+1; idx++) {
            if (memcmp(ip_st->ip_stat_list[idx].ip_str, ip, INET6_ADDRSTRLEN) == 0) {
                is_found = 1;
                ip_st->ip_stat_list[idx].packet_count++;
                break;
            }
        }

        // Ip is not found after traversal then add data to new index
        if (is_found == 0 ) {
            memcpy(ip_st->ip_stat_list[ip_st->curr_index].ip_str,ip,INET6_ADDRSTRLEN);
            ip_st->ip_stat_list[ip_st->curr_index].packet_count++;
            ip_st->curr_index++;
        }
    }
    return 0;
}
 
/**
  * @brief The list_push
  *
  * This method will push new_data to the end of the linked list 
  *
  * @param head_ref - linked-list head pointer 
  *        new_data - pointer holds the address of new data 
  *        len      - offset of new_data (new_data start address + len)
  */
int list_push(struct_list** head_ref, const u_char* new_data, bpf_u_int32 len)
{
    // Allocate node
    struct_list* new_node = (struct_list*) malloc(sizeof(struct_list));
 
    struct_list *last = *head_ref;  /* used in step 5*/
  
    // Put in the data
    new_node->data    = new_data;
    new_node->offset  = len;
 
    /* This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;
 
    // If the Linked List is empty, then make the new node as head
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return 0;
    } 
      
    // Else traverse till the last node
    while (last->next != NULL)
        last = last->next;
  
    // Change the next of last node
    last->next = new_node;

    return 0;
}
 
/**
 * @brief The list_pop
 *
 * This method will return front node and update
 *     head_ref to next node
 *
 * @param head_ref - linked-list head pointer 
 */
struct_list* list_pop(struct_list** head_ref)
{
    if (head_ref == NULL)
        return NULL;
 
    // Move the head pointer to the next node
    struct_list* temp = *head_ref;
    if (temp != NULL) {
        *head_ref = (*head_ref)->next;
    }
    return temp;
}

/**
 * @brief The list_size
 *
 * This method will return size of head_ref linked list 
 *
 * @param head_ref - linked-list head pointer 
 */
unsigned int list_size(struct_list** head_ref)
{
    unsigned int count = 0;
    struct_list* temp = *head_ref;

    while (temp != NULL) {
        temp = temp->next;
        count++;
    }

    return count;
}
