//   list_string.c
//   David Gregg
//   January 2021

//Student Name: Prathamesh Sai Sankar
//Student ID: 19314123

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list_string.h"

// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string *new_list_string(char *text)
{
    //declare a new list string
    struct list_string *result;
    //allocate memory for the new list string.
    result = malloc(sizeof(struct list_string));
    //make sure the list string is not null.
    assert(result != NULL);
    //set the head of the list string to null, to ensure it is a new list string.
    result->head = NULL;

    //declare a node to point to the previous node when setting the nodes.
    struct ls_node *previous = NULL;

    //iterate through the text, to set the nodes.
    for (int i = 0; text[i] != '\0'; i++)
    {
        //declare a node to insert into the list string.
        struct ls_node *newNode = NULL;
        //allocate memory for the new node.
        newNode = malloc(sizeof(struct ls_node));
        //set the char in the new node to the text character.
        newNode->c = text[i];

        if (previous != NULL){        //if we are adding to an existing list string. (i.e. there is no previous nodes)
            newNode->next = NULL;     //the node being added has no next node.
            previous->next = newNode; //the previous node's next node will be the new node that is being added.
            previous = newNode;       //make the previous node equal to the new node that was added (so that future iterations of this for-loop work!).
        }
        else{                       //if we are adding to a new list string where the head is null (i.e. the previous node is null).
            newNode->next = NULL;   //the node being added has no next node.
            result->head = newNode; //the head of the new list string now points to the new node being added.
            previous = newNode;     //make the previous node equal to the current node, so that we can use it in future iterations of the for-loop.
        }
    }

    return result;
}

// find the length of the list string
int list_string_length(struct list_string *this)
{
    //declare a pointer to iterate through the list string.
    struct ls_node *pointer;
    //declare a integer variable to count the length.
    int length = 0;

    //iterate through the list string, incrementing the counter with each node.
    for (pointer = this->head; pointer != NULL; pointer = pointer->next){
        length++;
    }

    return length;
}

// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd".
int list_string_compare(struct list_string *s1, struct list_string *s2)
{

    //declare two pointers, one for each list string (to iterate through both simultaneously).
    struct ls_node *pointer;
    struct ls_node *pointer2;

    //declare an integer variable to store the answer.
    int answer;

    //iterate through both s1 and s2, to check which string is lexicographically greater and which is lexicographically less.
    for (pointer = s1->head, pointer2 = s2->head; (pointer != NULL) & (pointer2 != NULL); pointer = pointer->next, pointer2 = pointer2->next){

        //note: to get the ASCII value of a character, we simply cast it as an integer.

        if ((int)pointer->c == (int)pointer2->c){ //if the two characters are equal (i.e. the first characters are equal in "abc" and "abC" since a=a)
            if ((pointer->next == NULL) & (pointer2->next == NULL)){  // if we have s1 = "a" and s2 = "a", then the next node to both a's are null. Hence they are both the same lexicographically.
                answer = 0; //lexicographically equal
                break;      //break out of the loop.
            }
            if ((pointer->next == NULL) & (pointer2->next != NULL)){  //if we have s1 = "a" and s2 = "aa", then the next node of s1 is null, but the next node of s2 is NOT null. Hence s2 is lexicographically greater than s1.
                answer = -1; //first string is lexicographically less than the second.
                break;       //break out of the loop
            }
            if ((pointer->next != NULL) & (pointer2->next == NULL)){  //if we have s1 = "aa" and s2 = "a", then the next node of s1 is NOT null, but the next node of s2 is null. Hence s1 is lexicographically greater than s2.
                answer = 1; //first string is lexicographically greater than the second.
                break;      //break out of the loop.
            }
        }

        if ((int)pointer->c < (int)pointer2->c){  //if s1 = "C" and s2 = "c", then s1 = 67 and s2 = 99 as an integer. Therefore s1 is lexicographically less than s2.
            answer = -1; //first string is lexicographically less than the second.
            break;       //break out of the loop.
        }

        if ((int)pointer->c > (int)pointer2->c){  //if s1 = "c" and s2 = "C", then s1 = 99 and s2 = 67 as an integer. Therefore s1 is lexicographically greater than s2.
            answer = 1; //first string is lexicographically greater than the second.
            break;      //break out of the loop.
        }
    }
    return answer;
}

// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string *text, struct list_string *str)
{

    //use our previous function to find the length of both list string data structures.
    int M = list_string_length(str);
    int N = list_string_length(text);

    //declare character variables to hold the characters at particular places in our list string.
    char s1;
    char s2;

    for (int i = 0; i <= N - M; i++){   //used to iterate through s2.
        int j; //declare a variable to find the position of a character in s1.
        for (j = 0; j < M; j++){ //used to iterate through both s1 and s2.

            //declare a node to point to the head of the bigger list string (text).
            struct ls_node *currentNodeInText = text->head;

            //iterate through the list string "text" to find the character at index "i+j"
            int countForText = 0;
            while (currentNodeInText != NULL){ //as long as we haven't reached the end of the list string.
                if (countForText == i + j){
                    s2 = (currentNodeInText->c); //we got the character at that index!
                }
                countForText++;                              //increment the counter.
                currentNodeInText = currentNodeInText->next; //move to the next node.
            }

            //now do the same for s1.

            //declare a node to point to the head of the smaller list string (str).
            struct ls_node *currentNodeinStr = str->head;

            //iterate through the list string "str" to find the character at index "j"
            int countForStr = 0;
            while (currentNodeinStr != NULL){ //as long as we haven't reached the end of the list string.
                if (countForStr == j){
                    s1 = (currentNodeinStr->c); //we got the character at that index!
                }
                countForStr++;                             //increment the counter.
                currentNodeinStr = currentNodeinStr->next; //move to the next node.
            }

            //if both the characters are not equal, then break the loop.
            if (s2 != s1){
                break;
            }
        }
        //if the for-loop above iterated all the way up to str.length, then j will be equal to M.
        if (j == M){
            return 1;
        }
    }
    //otherwise, a substring was not found.
    return 0;
}
