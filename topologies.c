#include "graph.h"

graph_t* build_first_topo(){
#if 0

                          +----------+
                      0/4 |          |0/0
         +----------------+   R0_re  +---------------------------+
         |     40.1.1.1/24| 122.1.1.0|20.1.1.1/24                |
         |                +----------+                           |
         |                                                       |
         |                                                       |
         |                                                       |
         |40.1.1.2/24                                            |20.1.1.2/24
         |0/5                                                    |0/1
     +---+---+                                              +----+-----+
     |       |0/3                                        0/2|          |
     | R2_re +----------------------------------------------+    R1_re |
     |       |30.1.1.2/24                        30.1.1.1/24|          |
     +-------+                                              +----------+

#endif
	graph_t* topo = create_new_graph("Generic Graph");
	// create nodes
	node_t* R0 = create_graph_node(topo, "R0");
	node_t* R1 = create_graph_node(topo, "R1");
	node_t* R2 = create_graph_node(topo, "R2");
	// add links between nodes
	insert_link_between_two_nodes(R0, R1, "eth0/0", "eth0/1", 1);
	insert_link_between_two_nodes(R1, R2, "eth0/2", "eth0/3", 1);
	insert_link_between_two_nodes(R0, R2, "eth0/4", "eth0/5", 1);
	return topo;
}