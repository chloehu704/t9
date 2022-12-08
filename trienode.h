/* trienode.h contains structure and function declarations for
   a trie implementation
   CSE374, HW5, 22au
*/

// Author: Chloe Hu
// 12/04/22
// UWNETID: xinyuh22
// HW5: trienode.h

#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define MAXLEN 50
#define BRANCHES 10

// trieNode is one node in an 9-tree, where branches correspond to
// # and the T9 alphabet.
typedef struct trieNode {
  struct trieNode *branches[BRANCHES];
  char *word;
} trieNode;

// given a word list (dict), build a trie that holds
// each word.  Return pointer to the root node.
trieNode* build_tree(FILE *dict);

// given a pattern, return the word stored in the
// appropriate trieNode
trieNode* get_word(trieNode* root, char *pattern);

// deletes the entire tree branching from root
void free_tree(trieNode *root);

#endif
