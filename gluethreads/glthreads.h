#ifndef GLTHREADS_H
#define GLTHREADS_H

typedef struct glthread_node_{
    struct glthread_node_ *next;
    struct glthread_node_ *prev;
}glthread_node_t;

typedef struct gldll_{
    glthread_node_t* head;
    glthread_node_t* tail;
	unsigned int offset;
}glthread_t;

void glthread_init(glthread_t* glthread);
void glthread_add(glthread_t* lst, glthread_node_t* glnode);
void glthread_remove(glthread_t* lst, glthread_node_t* glnode);


/* macro to iterate over the thread */
#define ITERATE_GLTHREAD_BEGIN(glthread_head, glthread_out_ptr) {\
	glthread_node_t* curr_node = glthread_head; \
	while(curr_node){ \
		glthread_out_ptr = curr_node; \
		curr_node = curr_node->next;
#define ITERATE_GLTHREAD_END }}

#define offsetof(struct_name, field_name)\
	    (char*)&(((struct_name *)0)->field_name)

/* macro to get node from a glue*/
#define GLTHREAD_TO_STRUCT(fn_name, structure_name, field_name) \
	static structure_name* fn_name(glthread_node_t* node){ \
		return (structure_name*)((char*) node - offsetof(structure_name, field_name)); \
	}
		 
#endif
