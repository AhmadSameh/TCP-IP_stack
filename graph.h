#ifndef GRAPH_H
#define GRAPH_H

#include "gluethreads/glthreads.h"
#include "net.h"

#define NODE_NAME_SIZE	16
#define IF_NAME_SIZE	16
#define MAX_INTF_PER_NODE 10

typedef struct node node_t;
typedef struct link link_t;

typedef struct graph{
    char topology_name[32];
    glthread_t node_list;   
}graph_t;

typedef struct interface{
    char if_name[IF_NAME_SIZE];
    node_t* att_node;
    link_t* link;
	intf_nw_prop_t intf_nw_props;
}interface_t;

typedef struct link{
    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
}link_t;

typedef struct node{
    char node_name[NODE_NAME_SIZE];
    interface_t* intf[MAX_INTF_PER_NODE];
    glthread_node_t graph_glue;
	node_nw_prop_t node_nw_prop;
}node_t;


graph_t* create_new_graph(char* topology_name); 
node_t* create_graph_node(graph_t* graph, char* node_name);
void insert_link_between_two_nodes(node_t* node1, node_t* node2, char* from_if_name, char* to_if_name, unsigned int cost);
interface_t* get_node_if_by_name(node_t* node, char* local_if);

void dump_graph(graph_t* graph);
void dump_node(node_t* node);
void dump_interface(interface_t* interface);

#endif
