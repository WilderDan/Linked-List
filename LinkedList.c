#include <stdlib.h>
#include <stdio.h>

/* Basic Element of Linked List.
 */
struct node{
  int value;
  struct node* next;
};
 
/* Functions used
 */
int deleteNode(struct node *, int);
void displayList(struct node *);
void appendNode(struct node *, int);

/****************************************************************************
 * #!main                                                                   *   
 ****************************************************************************/
int main() {

  struct node *head, *tail;
  int i;

  // Start with empty list
  head = NULL;
  
  // Create 10 nodes; Initial Memory: [Tail node] [node] [node] ... [Head]
  for (i=9; i >= 0; i--) {
    tail =  (struct node *) malloc(sizeof(struct node));
    tail->value = i;
    tail->next = head;      
    head = tail;
  } 
  
  // Display List
  displayList(head);

  // Remove two nodes
  deleteNode(head, 4);
  deleteNode(head, 7);

  // Newline the display
  puts("\n");
  displayList(head);

  // Add some nodes
  for (i=15; i<20; i++) 
    appendNode(head, i);

  // Newline then display
  puts("\n");
  displayList(head);
}


/****************************************************************************
 * #!deleteNode                                                             *   
 ****************************************************************************/
   /* Delete ONLY FIRST OCCURRENCE of a node whose value matches passed value. 
    * Returns index referring to how many traversels happened. -1 is returned
    * if no such node is found/deleted.
    */
int deleteNode(struct node *head, int value) {

  struct node *traverse = head;
  struct node *previous = head;
  int index = 0;

  // Traverse the list
  while(traverse != NULL) {

    // Find First occurence
    if (traverse->value == value) {

      // Check if the head should be deleted
      if (traverse == head) 
        head = head->next;
      
      // Connect list segments before freeing node
      previous->next = traverse->next;
      free(traverse); // traverse will also be NULL
      return index;
    }
    
    // Node value wasn't here; let's check the next node
    previous = traverse;
    traverse = traverse->next;
    ++index;   
  }

  // No node with given value was found
  return -1; 
}

/****************************************************************************
 * #!displayList                                                            *   
 ****************************************************************************/
void displayList(struct node *head) {
  struct node *traverse = head;
  
  while (traverse != NULL) {
    printf("[Node @ %p] value: %d    next: %p\n",\
           traverse, traverse->value, traverse->next);
    traverse = traverse->next; 
  }  
}

/****************************************************************************
 * #!appendNode                                                             *   
 ****************************************************************************/
  /* Create new node with given value which becomes the new end of list.
   */
void appendNode(struct node *head, int value) {

  struct node *traverse;
  struct node *tail;

  // Create new node to be end of list
  tail = (struct node *) malloc(sizeof(struct node));
  tail->value = value;
  tail->next = NULL;

  // Check if list is empty 
  if (head == NULL)
    head = tail;
  
  // If not empty
  else {
    traverse = head;

    // Find end of list
    while (traverse->next != NULL)
      traverse = traverse->next;

    // Append to list
    traverse->next = tail;
  }
}
