/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22au
*/

// Author: Chloe Hu
// 12/04/22
// UW NETID: xinyuh22
// HW5: tnine.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

void run_session(trieNode *root);

//build the tree by reading input from argument
//run the interactive session
//clean up
int main(int argc, char **argv) {
  trieNode* root = NULL;
  FILE *dictionary = fopen(argv[1], "r");
  if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
  } else {
      root = build_tree(dictionary);
  }
  //check if the root is null before running interactive session
  if (root) {
      run_session(root);
  }
  // clean up
  free_tree(root);
  free(root);
  return(EXIT_SUCCESS);
}

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build a root node to work.
void run_session(trieNode *root) {
  printf("Enter \"exit\" to quit.\n");
  char* input = (char*)malloc(50*sizeof(char));
  int in_session = 1;
  trieNode *current = root;
  while (in_session) {
      //prompts the user to give input repeatedly until they enter
      //exit
      printf("Enter Key Sequence (or \"#\" for next word): \n");
      scanf("%s", input);
      if (strcmp(input, "exit") != 0) {
          //start from current node to handle the situation 
          //where user enter # after they first put in a string
          //of key
          if (input[0] == '#') {
              current = get_word(current, input);
          //start from root to handle the situation where
          //user put in key for a new word    
          } else {
              current = get_word(root, input);
          }
          //check if the node is null before use it
          //handles all non-existent situation here
          if (current == NULL) {
              //print this when the string of key ending with
              //# is not present in the trie 
              if (input[strlen(input) - 1] == '#') {
                  printf("There are no more T9onyms\n");
              //print this when the string of key does not end with
              //# and is not present in the trie
              } else {
                  printf("Not found in current dictionary.\n");
              }
           //when the node is not null, check if the word
           //is not null before using it
          } else {
              if (current -> word) {
                  printf("\'%s\'\n", current -> word);
              } else {
                  printf("Not found in current dictionary.\n");
              }
          }
      } else {
          in_session = 0;
      }
  }

}

