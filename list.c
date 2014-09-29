#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_append(int *val, struct node **head){
    	struct node *new_node = malloc(sizeof(struct node)); //make space on heap
        new_node->value = val;
	new_node->next = *head; // make the new node point to the head
	*head = new_node; //  make it the new head
	}

void list_sort(struct node **head) { //sort 
  int tmp;
  struct node *new_node = *head;
  struct node *second_node = new_node->next; // node 1 ahead of other node
  for(; new_node->next !=NULL; new_node= new_node->next){ // itterate through list
      for(second_node = new_node->next; second_node != NULL; second_node= second_node->next){ // iterate 													through 												list
          if ((new_node->value) < (second_node->value)) { // compare the two 					  				  values and switch if out 								  of order
	tmp = new_node->value; // set the temporary to hold the value
	new_node->value = second_node->value; // set the first node to the value of 							the second node
	second_node->value = tmp; // set the second node to the value of the stored 					  temp
	}
      }
    }
 }
void list_print(const struct node *list) {
    int i = 0;
    printf("In list_print\n");
    while (list != NULL) {
        printf("List item %d: %d\n", i++, list->value);
        list = list->next;
    }
}

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}



