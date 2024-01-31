#ifndef NET_H
#define NET_H

#include "graph.h"
#include "utils.h"
#include <memory.h>

#define L3_ROUTER	(1 << 0)
#define L2_SWITCH	(1 << 1)
#define HUB 		(1 << 2)

typedef struct ip_add{
	char ip_addr[16];
}ip_add_t;

typedef struct mac_add{
	char mac[8];
}mac_add_t;

typedef struct node_nw_prop{
	// L3 properties
	bool_t is_lb_addr_config;
	// loop back address of a node
	ip_add_t lb_addr; 
}node_nw_prop_t;

typedef struct intf_nw_prop{
	// L2 property
	mac_add_t mac_add;
	// L3 properties
	bool_t is_ipadd_config; // set true if ip add is configured, intf operates in L3 mode if ip address is configured on it
	ip_add_t ip_add;
	char mask;
}intf_nw_prop_t;

#define NODE_LB_ADDR(node_ptr)	(node_ptr->node_nw_prop.lb_addr.ip_addr)

bool_t node_set_loopback_address(node_t* node, char* ip_addr);
bool_t node_set_intf_ip_address(node_t* node, char* local_if, char* ip_addr, char mask);
bool_t node_unset_intf_ip_address(node_t* node, char* local_if);

void dump_nw_graph(graph_t* graph);

#endif
