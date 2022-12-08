/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22au
*/

// Author: Chloe Hu
/* 12/04/22 */
// UW NETID: xinyuh22
// HW5: trie.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"


/* You'll want to prototype any helper functions you need here */
trieNode* getNewNode();
int keyMap(char test);

//creates a new node and malloc memory
//return the node
trieNode* getNewNode() {
    trieNode* node = (trieNode*)malloc(sizeof(trieNode));
    node -> word = NULL;
    for (int i = 0; i < 10; i++) {
        node -> branches[i] = NULL;
    }
    return node;
}

//this array corresponds each letter to the numeric key
//using the ASCII table
int keyMap(char text) {
    char map[26] = {
            2, 2, 2,
            3, 3, 3,
            4, 4, 4,
            5, 5, 5,
            6, 6, 6,
            7,  7, 7, 7,
            8, 8, 8,
            9, 9, 9, 9
    };
    int i = text - 'a';
    return map[i];
}

//build the tree by reading word to word in the input file
//create new node for letters that have not been visited before
//keep going to the rightmost branch for words that are in the linked
//list with shared pref
trieNode* build_tree(FILE *dict) {
    trieNode* root = getNewNode();
    char* key = (char*)malloc(50*sizeof(char));
    while( fscanf(dict, "%s", key) != EOF ) {
        trieNode* curr = root;
        int string_len = strlen(key) + 1;
        char* text = (char*) malloc(string_len*sizeof(char));
        strncpy(text, key, string_len);
        for (int i = 0; i < strlen(key); i++) {
            int num = keyMap(key[i]);
            if (curr -> branches[num] == NULL) {
                curr -> branches[num] = getNewNode();
            }
            curr = curr -> branches[num];

        }
        while (curr -> branches[9] != NULL) {
            curr = curr -> branches[9];
        }
        if (curr -> word == NULL) {
            curr -> word = text;
        } else {
            curr -> branches[9] = getNewNode();
            curr = curr -> branches[9];
            curr -> word = text;
        }
    }
    return root;
}

//traverse the trie based on the given pattern
//and return the word stored in the destination
//node
trieNode* get_word(trieNode* root, char* pattern) {
    trieNode* temp = root;
    for (int i = 0; i < strlen(pattern); i++) {
        if (pattern[i] != '#') {
            int branch_num = (pattern[i] - '0');
            if (temp -> branches[branch_num] == NULL) {
                return NULL;
            }
            temp = temp -> branches[branch_num];
        } else {
            if (temp -> branches[9] == NULL) {
                return NULL;
            }
            temp = temp -> branches[9];
        }
    }
    return temp;
}

//manually free all the node and branches
void free_tree(trieNode* root) {
   for (int i = 0; i < 10; i++) {
        if (root -> branches[i] != NULL) {
            free_tree(root -> branches[i]);
            free(root -> branches[i]);
        }
   }
   if (root -> word != NULL) {
        free(root -> word);
   }
}

