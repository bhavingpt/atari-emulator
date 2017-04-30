#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct node {
    unsigned long long loc;
    char val;
    struct node* next;
} node;

node** memory;
int capacity = 4001;
int occupied;

// forward declarations
void resize();
int hash(unsigned long long loc);

void init() {
    memory = (node**) calloc(capacity, capacity*sizeof(node*));
}

void write(char byte, unsigned long long loc) {
    int index = hash(loc);
    char written = 0;
    node* current = memory[index];

    if (current == NULL) {
        node* new_node = (node*) malloc(sizeof(node));
        new_node->loc = loc;
        new_node->val = byte;
        new_node->next = NULL;
	      memory[index] = new_node;
	      occupied++;
    } else {
        if (current->loc == loc) {
	          written = 1;
	          current->val = byte;
        }
        while (current->next != NULL && !written) {
            current = current->next;
	          if (current->loc == loc) {
	              written = 1;
	              current->val = byte;
            }
        }

        if (!written) {
            node* new_node = (node*) malloc(sizeof(node));
            new_node->loc = loc;
            new_node->val = byte;
            new_node->next = NULL;
      	    current->next = new_node;
	          occupied++;
        }
    }

    if (capacity * 3 < occupied) resize();
}

unsigned char read(unsigned long long loc) {
    int index = hash(loc);
    node* current = memory[index];
    while (current != NULL) {
	      if (current->loc == loc) {
            return current->val;
        }
        current = current->next;
    }
    return 0;
}

void resize() {
    printf("You should implement resize!\n");
}

int hash(unsigned long long loc) {
    return (loc*37) % capacity;
}

