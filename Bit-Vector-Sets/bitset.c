#include "bitset.h"
#include <math.h>
#include <stdlib.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset * result;  //create a pointer to the new bitset
    result = malloc(sizeof(struct bitset)); //allocate memory for this new bitset
    float wordSize = sizeof(uint64_t) * 8; //get the word size by getting the uint64_t size (in bytes) and multiply it by 8 to get it in bits.
    int words = ceil(size/wordSize); //get the number of words by using the ceil function.
    result ->size_in_words = words; //set our bitset's size in words
    result ->universe_size = size; //set our bitset's universe size, this is given as a parameter.
    result ->bits = malloc(sizeof(uint64_t) * words); //we must not forget to allocate memory for the bits in our bitset.

    //finally, let's set all the bits to 0!
    for(int i = 0; i < words ; i++) {
        result -> bits[i] = 0;
    }
     return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
   int sizeOfUniverse =  this->universe_size; //simply return the universal size of the bitset.
   return sizeOfUniverse;
}
// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int numberOfItems = 0;     //make a counter for the number of items.
    int sizeInWords = this->size_in_words;  //get the size in words, so we can iterate over them.
    for(int i = 0; i < sizeInWords; i++) {      //outer-for loop: allows us to traverse through the words 
        for(int j = 0; j < (sizeof(uint64_t) * 8); j++ ) { //nested-for loop: allows us to traverse through the bits inside the words
            int bit = j % (sizeof(uint64_t) * 8);     //get the value of the bit we are looking at 
            uint64_t mask = 1ul << bit;     //make a mask with a 1 in the position where the bit we are looking at is.
            uint64_t answer = this->bits[i] & mask;     // "and" this mask with bits[i]
            if(answer) {                //if this answer is > 0, i.e. if it is true 
                numberOfItems++;            //then the item is stored in the set. Increase our counter!
            }
        }
    }
    return numberOfItems;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    int word_size = sizeof(uint64_t) *8; //get the word size by getting the uint64_t size (in bytes) and multiply it by 8 to get it in bits.
    int word = item/word_size; // this will tell us which word in the array we are looking at.
    int bit = item % word_size; //get the bit by getting the modulus of item and word_size.
    uint64_t mask = 1ul << bit; //make a mask and shift 1 left by the number from bit
    uint64_t value = this->bits[word] & mask;   // do an "and" with this mask and bits[word]
    int inTheList = value >> bit;       //shift value right by the number from bit, this will return 1 if it's in the set, and 0 if it's not.
    return inTheList;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
    int word_size = sizeof(uint64_t) *8;   //get the word size by getting the uint64_t size (in bytes) and multiply it by 8 to get it in bits.
    int word = item/word_size; //this will tell us which word in the array we are looking at.
    int bit = item % word_size;  //get the bit by getting the modulus of item and word_size.
    uint64_t old_val = this->bits[word];  //get the old value by storing bits[word]
    uint64_t mask = 1ul << bit;  //make a mask and shift 1 left by the number from bit.
    this->bits[word] = old_val | mask;  //use "or" to store the end result from bitset addition.
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
 int word_size = sizeof(uint64_t) *8;  //get the word size by getting the uint64_t size (in bytes) and multiply it by 8 to get it in bits.
    int word = item/word_size; //this will tell us which word in the array we are looking at.
    int bit = item % word_size;    //get the bit by getting the modulus of item and word_size.
    uint64_t old_val = this->bits[word];  //get the old value by storing bits[word]
    uint64_t mask = 1ul << bit;  //make a mask and shift 1 left by the number from bit.
    uint64_t val_If_Not_In_Set = old_val | mask; //use "or" first to make sure that it isn't removed already
    this->bits[word] = val_If_Not_In_Set ^ mask ; //Finally, use an "xor" to store the answer. 
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        int sizeInWords = dest->size_in_words;  //get the size of dest in words.
        for(int i = 0; i < sizeInWords; i++) { //this goes through the words in the array
            uint64_t result = src1->bits[i] | src2->bits[i];    //use "or" with the bits[i] (i.e. the word) from both src1 and src2, and store it in result.
            dest->bits[i] = result;     //get result and store it in dest.
        }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
       int sizeInWords = dest->size_in_words; //get the size of dest in words.
        for(int i = 0; i < sizeInWords; i++) { //this goes through the words in the array
            uint64_t result = src1->bits[i] & src2->bits[i]; //use "and" with the bits[i] (i.e. the word) from both src1 and src2, and store it in result.
            dest->bits[i] = result;     //get result and store it in dest.
        }
}
