#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

static int get_node_intf_available(node_t* node){
	for(int i=0; i<MAX_INTF_PER_NODE; i++){
		if(node->intf[i])
			continue;
		return i;
	}
	return -1;
}

node_t* get_nbr_node(interface_t* intf){
	link_t* link = intf->link;
	if(intf == &link->intf1)
		return link->intf2.att_node;
	else
		return link->intf1.att_node;
}

graph_t* create_new_graph(char* topology_name){
	graph_t* graph = calloc(1, sizeof(graph_t));
	strncpy(graph->topology_name, topology_name, 32);
	graph->topology_name[32] = '\0';
	glthread_init(&graph->node_list);
	return graph;
}

node_t* create_graph_node(graph_t* graph, char* node_name){
	node_t* node = calloc(1, sizeof(node_t));
	strncpy(node->node_name, node_name, NODE_NAME_SIZE);
	node->node_name[NODE_NAME_SIZE] = '\0';
	init_node_nw_prop(&node->node_nw_prop);
	glthread_add(&graph->node_list, &node->graph_glue);
	return node;
}

void insert_link_between_two_nodes(node_t* node1, node_t* node2, char* from_if_name, char* to_if_name, unsigned int cost){
	link_t* link = calloc(1, sizeof(link_t));
	link->cost = cost;
	// add names of nodes between the interface
	strncpy(link->intf1.if_name, from_if_name, IF_NAME_SIZE);
	link->intf1.if_name[IF_NAME_SIZE] = '\0';
	strncpy(link->intf2.if_name, to_if_name, IF_NAME_SIZE);
	link->intf2.if_name[IF_NAME_SIZE] = '\0';
	// add the link between the two interfaces
	link->intf1.link = link;
	link->intf2.link = link;
	// attach the nodes between the two links
	link->intf1.att_node = node1;
	link->intf2.att_node = node2;
	// add the cost of the link
	link->cost = cost;
	// add interfaces to nodes
	unsigned int empty_intf_slot = get_node_intf_available(node1);
	node1->intf[empty_intf_slot] = &link->intf1;
	empty_intf_slot = get_node_intf_available(node2);
	node2->intf[empty_intf_slot] = &link->intf2;
	
	init_intf_nw_prop(&link->intf1.intf_nw_prop);
	init_intf_nw_prop(&link->intf2.intf_nw_prop);
	interface_assign_mac(&link->intf1);
	interface_assign_mac(&link->intf2);
}

void dump_graph(graph_t* graph){
	node_t* node;
	glthread_node_t* curr;
	printf("Topology Name: %s\n", graph->topology_name);
	ITERATE_GLTHREAD_BEGIN(graph->node_list.head, curr)
		node = graph_glue_to_node(curr);
		dump_node(node);
	ITERATE_GLTHREAD_END	
}

void dump_node(node_t* node){
	interface_t* intf;
	printf("Node Name = %s :\n", node->node_name);
	for(int i=0; i<MAX_INTF_PER_NODE; i++){
		intf = node->intf[i];

		if(!intf)
			break;
		
		dump_interface(intf);
	}
}

void dump_interface(interface_t* intf){
	node_t* nbr_node = get_nbr_node(intf);
	printf(" Local Node: %s, ", intf->att_node->node_name);
	printf("Interface Name: %s, ", intf->if_name);
	printf("Nbr Node: %s, ", nbr_node->node_name);
	printf("Cost: %d\n", intf->link->cost);
}

interface_t* get_node_if_by_name(node_t* node, char* local_if){
	for(int i=0; i<MAX_INTF_PER_NODE; i++){
		if(strncmp(node->intf[i]->if_name, local_if, IF_NAME_SIZE) == 0)
			return node->intf[i];
	}
	return NULL;
}
