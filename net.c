#include "net.h"
#include <string.h>
#include <stdio.h>

static void init_node_nw_prop(node_nw_prop_t* node_nw_prop){
	node_nw_prop->is_lb_addr_config = 0;
	memset(node_nw_prop->lb_addr.ip_addr, 0, 16);
}

static void init_intf_nw_prop(intf_nw_prop_t* intf_nw_prop){
	intf_nw_prop->is_ipadd_config = 0;
	intf_nw_prop->mask = 0;
	memset(intf_nw_prop->mac_add.mac, 0, 8);
	memset(intf_nw_prop->ip_add.ip_addr, 0, 16);
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
}

bool_t node_unset_intf_ip_address(node_t* node, char* local_if){

}

void dump_nw_graph(graph_t* graph){

}
