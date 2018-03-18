/*
 ============================================================================
 Name        : Trie.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define WORDS_LENGTH 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode {
	struct TrieNode* children[WORDS_LENGTH];
	bool endOfNode;
};

struct TrieNode* getNode (){
	struct TrieNode* node = (struct TrieNode*) malloc (sizeof (struct TrieNode));

	for (int i = 0 ; i < WORDS_LENGTH; i++){
		node->children[i] = NULL;
	}

	node->endOfNode = true;

	return node;
}

void insert(struct TrieNode *root, const char *key){
	int length = strlen(key);
	int level;
	int index;

	struct TrieNode * pCrawl = root;

	for (level = 0; level < length; level++){
		index = CHAR_TO_INDEX(key[level]);
		if (! pCrawl->children[index]){
			pCrawl->children[index] = getNode();
		}
		pCrawl = pCrawl->children[index];
	}

	pCrawl->endOfNode = true;
}

bool search (struct TrieNode* root, const char *key){
	int length = strlen(key);
	int level;
	int index;

	struct TrieNode * pCrawl = root;

	for (level = 0; level < length; level++){
		index = CHAR_TO_INDEX(key[level]);
		if (! pCrawl->children[index]){
			return false;
		}
		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->endOfNode);
}


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	// Input keys (use only 'a' through 'z' and lower case)
	char keys[][8] = {"the", "a", "there", "answer", "any",
					 "by", "bye", "their"};

	char output[][32] = {"Not present in trie", "Present in trie"};

	struct TrieNode* root = getNode();

	int i;

	for (i = 0; i< ARRAY_SIZE(keys); i++){
		insert (root, keys[i]);
	}

	// Search for different keys
	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "these", output[search(root, "these")] );
	printf("%s --- %s\n", "their", output[search(root, "their")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );

	return EXIT_SUCCESS;
}
