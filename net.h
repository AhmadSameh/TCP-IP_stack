#ifndef NET_H
#define NET_H

#include "utils.h"
#include <memory.h>

#define L3_ROUTER	(1 << 0)
#define L2_SWITCH	(1 << 1)
#define HUB 		(1 << 2)

typedef struct graph graph_t;
typedef struct interface interface_t;
typedef struct node node_t;

typedef struct ip_add{
	char ip_addr[16];
}ip_add_t;

typedef struct mac_add{
	char mac[48];
}mac_add_t;

typedef struct node_nw_prop{
	unsigned int flags;
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
#define IF_IP_ADDR(intf_ptr) 	(intf_ptr->intf_nw_prop.ip_add.ip_addr)
#define IF_MAC(intf_ptr)		(intf_ptr->intf_nw_prop.mac_add.mac)

void init_node_nw_prop(node_nw_prop_t* node_nw_prop);
void init_intf_nw_prop(intf_nw_prop_t* intf_nw_prop);
bool_t node_set_loopback_address(node_t* node, char* ip_addr);
bool_t node_set_intf_ip_address(node_t* node, char* local_if, char* ip_addr, char mask);
bool_t set_device_type(node_t* node, unsigned int type);
bool_t node_unset_intf_ip_address(node_t* node, char* local_if);
bool_t interface_assign_mac(interface_t* intf);

void dump_nw_graph(graph_t* graph);

#endif
