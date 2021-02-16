#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
struct listset * result;
result = malloc(sizeof(struct listset));
assert(result != NULL);
result -> head = NULL;
return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
struct listnode * pointer;
int lookup = 0;
for(pointer = this -> head; pointer != NULL; pointer = pointer -> next) {
  if(strcmp(pointer -> str, item) == 0) {
    lookup = 1;
  }
}
return lookup;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
if(listset_lookup(this, item) == 0) {
  struct listnode * node;
  node = malloc(sizeof(struct listnode));
  node -> str = item;
  node -> next = this -> head;
  this -> head = node; 
}
else {
  //do nothing, the element we are adding is already there!
}
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {

if(listset_lookup(this, item)) {
   struct listnode * nodeBeforeDelete; //will store the element being removed.
   
   nodeBeforeDelete = this -> head;
   if(nodeBeforeDelete == NULL) { //if it's an empty list where the head is null, we can't delete anything.
     return; 
   }

   else if(strcmp(nodeBeforeDelete->str, item) == 0){ // if the item to be removed is the head
    this -> head = this -> head -> next; //the head will point to the next node, hence removing the old head.
    return;
   }

   else {
    //now let's try and find the data 

   while(true) {  //a risky but alright infinite while-loop since we already checked if the item being removed is inside the list.
     struct listnode * next; 
     next = nodeBeforeDelete -> next;
     if(next == NULL) { //if no data is found in the list, then we can't do anything.
       return;
     }
     else if(strcmp(next->str, item) == 0){ // once we find the data, we store it.
       break;
     }
     nodeBeforeDelete = next;
   }
  
  //finally, we have to link the nodes 
   struct listnode * next;
   next = nodeBeforeDelete -> next;
   nodeBeforeDelete -> next = next-> next;
   //next -> next = NULL; //make the node "next" equal to null to get rid of it.
   free(next); //another thing you could have done is set next to null, but for memory management you can free it
   return;
   }
   }
}


  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
          struct listnode * p;
          struct listnode * p2;
          struct listnode * p3;

          for(p = src1 -> head; p != NULL; p = p -> next) {
            listset_add(dest, p->str);
          }

          //now we just add the elements of B to the end of dest, but only if it's not in the list already.
          bool InListAlready = false;
          for(p2 = src2 -> head; p2 != NULL; p2 = p2 -> next) {
            for(p3 = dest -> head; p3 != NULL; p3 = p3 -> next) {
              if (strcmp(p2 -> str, p3 -> str) == 0) {
                InListAlready = true;
              }
            }
            if(InListAlready == false) {
              listset_add(dest, p2-> str);
            }
            InListAlready = false;
          }

          //finally, we reverse the listset dest, so that the output of A union B (i.e. dest) would be:
          // firstly, elements of A in order
          // secondly, the elements of B not in A, in the order of B.
          listset_reverse(dest);
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
    struct listnode *p;
    struct listnode *p2;

    for(p = src1 -> head; p != NULL; p = p -> next) {
      for(p2 = src2 -> head; p2 != NULL; p2 = p2 -> next) {
        if(strcmp(p2 -> str, p -> str) == 0) { //if a string is in both src1 and src2, add it to our intersection listset!
          listset_add(dest, p2->str);
        }
      }
    }
    listset_reverse(dest); //we reverse this too, just like for the union method. This makes sure that everything is in order!
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
      struct listnode * pointer = NULL;
      int size = 0;
      for(pointer = this -> head; pointer != NULL; pointer = pointer -> next) { //go through the listset and increment the size for every node.
        size++;
      }
      
    return size;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}

// extra method added to reverse a given list set
void listset_reverse(struct listset *this) {
 
 struct listnode * prev = NULL; //make a previous node pointer for reference.
 struct listnode * current = this -> head; //make a current node referencing the head of the listset given to the function.
 struct listnode * next = NULL; //make a next node pointer for reference.

 while(current != NULL){ 
   next = current -> next; //store the next variable
   current-> next = prev; // now we reverse the current node's pointer.
   prev = current; //now we move the pointers one position ahead.
   current = next; 
 }
 this -> head = prev;
}