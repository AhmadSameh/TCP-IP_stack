#include "graph.h"
#include "utils.h"
#include <memory.h>
#include <stdio.h>

void init_node_nw_prop(node_nw_prop_t* node_nw_prop){
	node_nw_prop->flags = FALSE;
	node_nw_prop->is_lb_addr_config = FALSE;
	memset(node_nw_prop->lb_addr.ip_addr, 0, 16);
}

void init_intf_nw_prop(intf_nw_prop_t* intf_nw_prop){
	intf_nw_prop->is_ipadd_config = FALSE;
	intf_nw_prop->mask = 0;
	memset(intf_nw_prop->mac_add.mac, 0, 48);
	memset(intf_nw_prop->ip_add.ip_addr, 0, 16);
}

static unsigned int hash_code(void* ptr, unsigned int size){
	unsigned int value = 0, i;
	char* str = (char*)ptr;
	for(i=0; i<size; i++){
		value += *str;
		value *= 97;
		str++;
		i++;
	}
	return value;
}

bool_t interface_assign_mac(interface_t* intf){
	/*node_t* node = intf->att_node;

	if(!node)
		return FALSE;
	
	unsigned int hash_code_val = hash_code(node->node_name, NODE_NAME_SIZE);
	hash_code_val *= hash_code(intf->if_name, IF_NAME_SIZE);
	memset(IF_MAC(intf), 0, sizeof(IF_MAC(intf)));
	memcpy(IF_MAC(intf), (char*)&hash_code_val, sizeof(unsigned int));
	return TRUE;*/
	memset(IF_MAC(intf), 0, 48);
    strcpy(IF_MAC(intf), intf->att_node->node_name);
    strcat(IF_MAC(intf), intf->if_name);
}

bool_t node_set_loopback_address(node_t* node, char* ip_addr){
	assert(ip_addr);

	// a hub has no ip address
	if(IS_BIT_SET(node->node_nw_prop.flags, HUB))
		assert(0);
	// L3 routing must be enabled to device first
	if(!IS_BIT_SET(node->node_nw_prop.flags, L3_ROUTER))
		assert(0);

	node->node_nw_prop.is_lb_addr_config = TRUE;
	strncpy(NODE_LB_ADDR(node), ip_addr, 16);
	NODE_LB_ADDR(node)[16] = '\0';
	return TRUE;
}

bool_t node_set_intf_ip_address(node_t* node, char* local_if, char* ip_addr, char mask){
	interface_t* intf = get_node_if_by_name(node, local_if);
	
	if(!intf)
		assert(0);

	strncpy(IF_IP_ADDR(intf), ip_addr, 16);
	IF_IP_ADDR(intf)[16] = '\0';
	intf->intf_nw_prop.mask = mask;
	intf->intf_nw_prop.is_ipadd_config = TRUE;
	return TRUE;
}

bool_t set_device_type(node_t* node, unsigned int type){
	SET_BIT(node->node_nw_prop.flags, type);
	return TRUE;
}

bool_t node_unset_intf_ip_address(node_t* node, char* local_if){

}

void dump_nw_interface(interface_t* intf){
	node_t* nbr_node = get_nbr_node(intf);
	printf("Interface Name: %s\n", intf->if_name);
	printf("\tNbr Node: %s, ", nbr_node->node_name);
	printf(" cost = %d\n", intf->link->cost);
	if(intf->intf_nw_prop.is_ipadd_config)
		printf("\tIP add: %s/%d,", IF_IP_ADDR(intf), intf->intf_nw_prop.mask);
	else
		printf("\tIP add: Nil/%d,", intf->intf_nw_prop.mask);
	printf(" MAC: %u:%u:%u:%u:%u:%u\n",
			 IF_MAC(intf)[0], IF_MAC(intf)[1],
			 IF_MAC(intf)[2], IF_MAC(intf)[3],
			 IF_MAC(intf)[4], IF_MAC(intf)[5]);
}

void dump_nw_node(node_t* node){
	interface_t* intf;
	printf("\nNode Name: %s\n", node->node_name);
	printf("\tNode Flags: %d", node->node_nw_prop.flags);
	if(node->node_nw_prop.is_lb_addr_config)
		printf(", LB add: %s/32\n", NODE_LB_ADDR(node));
	for(int i=0; i<MAX_INTF_PER_NODE; i++){
		intf = node->intf[i];

		if(!intf)
			break;

		dump_nw_interface(intf);
	}
	printf("----------------------------------------\n");
}

void dump_nw_graph(graph_t* graph)	{
	node_t* node;
	glthread_node_t* curr;
	printf("Toplogy Name: %s\n", graph->topology_name);
	ITERATE_GLTHREAD_BEGIN(graph->node_list.head, curr)
		node = graph_glue_to_node(curr);
		dump_nw_node(node);
	ITERATE_GLTHREAD_END
}


