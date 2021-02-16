#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "listset.h"

void test();

// main function to test the listset ADT
int main(int argc, char ** argv) {
  struct listset * myset;
  struct listset * myset2;

  if ( argc < 2 ) {
    fprintf(stderr, "Usage: ./listset <command> [<string>]\n");
    fprintf(stderr, "       where <command> is + (add following string)");
    fprintf(stderr, "                          - (remove following string)");
    fprintf(stderr, "                          = (print set)");
    exit(1);
  }

  // create a test to see if the listset union, intersection, and cardinality work.
  myset = listset_new();
   int i = 1;
  if(argv[i][0] == 't' & argv[i][1] == 'e' & argv[i][2] == 's' & argv[i][3] == 't') {
   test();
  }

 else {
  while ( i < argc ) {
    if ( argv[i][0] == '+' ) {
      assert( i+1 < argc );
      listset_add(myset, argv[i+1]);
      i = i + 2;
    }
    else if (argv[i][0] == '-' ) {
      assert( i+1 < argc );
      listset_remove(myset, argv[i+1]);
      i = i + 2;
    }
    else if (argv[i][0] == '=' ) {
      listset_print(myset);
      i++;
    }

    else {
      fprintf(stderr, "Error: Unknown command %s\n", argv[i]);
      exit(1);
    }
//    assert( 0 ); // we should never get here
  }
 }
  return 0;
}

void test () {
//first make the new listset src1 and check cardinality.
 printf("First let's make the listset src1\n");
 struct listset * src1 = listset_new();
 listset_add(src1, "spoon");
 listset_add(src1, "no");
 listset_add(src1, "is");
 listset_add(src1, "there");
 printf("src1: ");
 listset_print(src1);
 printf("Number of elements in src1: %i\n", listset_cardinality(src1));

 struct listset * src2 = listset_new();
 struct listset * destForUnion = listset_new();
 struct listset * destForIntersection = listset_new();

 //now let's make another listset src2 and check cardinality.
 printf("\nNext, Make a listset src2..\n");
 listset_add(src2, "spoon");
 listset_add(src2, "are");
 listset_add(src2, "which");
 listset_add(src2, "there");
 printf("src2: ");
 listset_print(src2);
 printf("Number of elements in src2: %i\n", listset_cardinality(src2));

 //next, use listset src1 and src2 to check the union of both.
 printf("\nMaking listset src1 Union src2: \n");
 listset_union(destForUnion, src1, src2);
 printf("src1 Union src2: ");
 listset_print(destForUnion); //output should be "there, is, no, spoon, which, are", since its elements of scr1 in order of src1 + elements of scr2 but not scr1, in the order of scr2.
 printf("Number of elements in scr1 Union src2: %i\n", listset_cardinality(destForUnion));

 //finally, use listset src1 and src2 to check the intersection of both.
 printf("\nMaking listset src1 Intersection src2: \n");
 listset_intersect(destForIntersection, src1, src2);
 printf("src1 Intersect src2: ");
 listset_print(destForIntersection); //output should be "there, spoon" since that those are the only elements in both src1 and src2. Also note it's in the order of A.
 printf("Number of elements in scr1 Intersection src2: %i\n", listset_cardinality(destForIntersection));
 }
