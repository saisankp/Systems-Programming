// simple C program that contains a hash table for strings
// David Gregg, November 2020                            

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"


// compute a hash of a string using a seed value, where the result
// falls between zero and range-1
int hash_string(char * string, int range)
{
  int i;
  int hash = 0;
  const int HASH_SEED = 19;

  // simple loop for mixing the input string
  for ( i = 0; string[i] != '\0'; i++ ) {
    hash = hash * HASH_SEED + string[i];
  }
  // check for unlikely case that hash is negative
  if ( hash < 0 ) {
    hash = -hash;
  }
  // bring the hash within the range 0..range-1
  hash = hash % range;

  //printf("str: \'%s\', hash: %d\n", string, hash);
  return hash;
}

// create a new empty hashtable
struct hashtable * hashtable_new(int size)
{
struct hashtable * result; //create the new hashtable being made.
result = malloc(sizeof(struct hashtable)); //allocate memory for the new hashtable
result -> size = size; //set the size given as a parameter
result -> table = malloc(sizeof(struct listset) * size); //allocate memory for the listsets in the table

//finally, set every listset to NULL to ensure that we can use the other hashtable functions properly.
for(int i = 0; i < size; i++) {
  (result -> table[i].head) = NULL;
}
return result;
}

// add an item to the hashtable
void hashtable_add(struct hashtable * this, char * item)
{
  int size = this->size; //retrieve the size of the hashtable
  int index = hash_string(item, size); //get the index using the hash_string function.

  //if the item being added isn't already in the hashtable, then add it!
  if(hashtable_lookup(this, item) == 0) {
    listset_add(&this->table[index], item);
  }
  else {
    //do nothing, we won't add the item if it's already in the hashtable.
  }
}

// return 1 if item is in hashtable, 0 otherwise
int hashtable_lookup(struct hashtable * this, char * item)
{
int size = this->size; //retrieve the size of the hashtable
int index = hash_string(item, size);  //get the index using the hash_string function.

//see if the item is in the hashtable using the listset_lookup function from last week.
int result = listset_lookup(&this->table[index], item); 

//return the int result from listset lookup.
return result;
}

// remove an item from the hash table; if the item is in the table
// multiple times, just remove the first one that we encounter
void hashtable_remove(struct hashtable * this, char * item)
{
int size = this->size; //retrieve the size of the hashtable
int index = hash_string(item, size); //get the index using the hash_string function.

//remove the hashtable using the listset_remove function from last week.
listset_remove(&this->table[index], item);
}

// print the elements of the hashtable set
void hashtable_print(struct hashtable * this) {
  for (int i = 0; i < this->size; i++ ) {
    listset_print(this->table+i);
  }
}

// The cardinality function for hashtables aren't included in the tests, 
// but I saw it in the header file so I implemented it anyways.

// get the cardinality of a hashtable
int hashtable_cardinality(struct hashtable * this) {
  int size = this->size;
  int cardinalityTotal;
   //go through all the listsets in the hashtable and get the caridnality of each.
  for(int i = 0; i < size; i++) {
    int cardinality = listset_cardinality(&this->table[i]);
    cardinalityTotal += cardinality; //get the sum of the cardinality of all the listsets.
  }
return cardinalityTotal;
}
