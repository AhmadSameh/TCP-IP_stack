#include "glthreads.h"
#include <stdlib.h>

void glthread_init(glthread_t* glthread){
	glthread->head = NULL;
	glthread->tail = NULL;
}

/* private function to add a new_node to the right of the curr_node */
static void glthread_add_next(glthread_node_t* curr_node, glthread_node_t* new_node){
    // if current node is the head simply add it to the right
    if(!curr_node->next){
        curr_node->next= new_node;
		new_node->prev = curr_node;
		return;
    }
    // insert node in between 2 nodes
    glthread_node_t* tmp = curr_node->next;
    curr_node->next = new_node;
    new_node->prev = curr_node;
    new_node->next = tmp;
    tmp->prev = new_node;
}

/* private function to remove the glthread */
/*
static void remove_glthread(glthread_node_t* glnode){
    if(!glnode->left && !glnode->right){
	return;
    }
    if(glnode->right){ 
	glnode->right->left = NULL;
	glnode->right = NULL;
	return;
    }
    if(!glnode->right){
        glnode->left->right = NULL;
	glnode->left = NULL;
	return;
    }
    glnode->left->right = glnode->right;
    glnode->right->left = glnode->left;
    glnode->left = NULL;
    glnode->right = NULL:
}
*/

/*function to insert a new glnode into a glthread*/
void glthread_add(glthread_t* lst, glthread_node_t *glnode){
    // set both next and prev to NULLs, for any new node
	glnode->next = NULL;
    glnode->prev = NULL;
    // if list is empty, set head to given node then return
    if(!lst->head){
        lst->head = glnode;
		lst->tail = glnode;
		return;
    }
	// if thread is not empty, add to thread
    glthread_node_t* tail = lst->tail;
    glthread_add_next(tail, glnode);
    lst->tail = glnode;
}

/*function to remove a glnode from glthread*/
/*
void glthread_remove(glthread_t* lst, glthread_node_t *glnode){
    glthread_node_t *head = lst->head;
    if(head == glnode)
        lst->head = head->right;
    remove_glthread(glnode);
}
*/
