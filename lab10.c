#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int isWord;
    struct Trie *next[26];
};

// Function Prototypes
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie(void);
void freeTrie(struct Trie *node);

int main(void)
{
	//read the number of the words in the dictionary
	// parse line  by line, and insert each word to the trie data structure
    struct Trie* trie = createTrie();
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

	for (int i = 0; i < 5; i++)
	{
        insert(trie, pWords[i]);
		printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
	}
	
    trie = deallocateTrie(trie);
	if (trie != NULL)
		printf("There is an error in this program\n");
    
	return 0;
}

void insert(struct Trie *pTrie, char *word)
{
	struct Trie *temp = pTrie;

	for (int i = 0; word[i] != '\0'; i++)
	{
		int index = (int) word[i] - 'a';
		if (temp->next[index] == NULL)
			temp->next[index] = createTrie();

		temp = temp->next[index];
	}

	temp->isWord = 1;
}

// count the number of occurrences of a word if it exists in the dictionary
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	int counter = 0;
	struct Trie *temp = pTrie;
	for (int i = 0; word[i] != '\0'; i++)
	{
		int position = word[i] - 'a';
		if (temp->next[position] == NULL)
			return 0;

		temp = temp->next[position];
	}

	if (temp != NULL && temp->isWord == 1)
		return 1;
	return 0;
}

// deallocate the entirety of dictionary
struct Trie *deallocateTrie(struct Trie *pTrie)
{    
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);
        else
            continue;
    }
    freeTrie(pTrie);
	return pTrie;
}

// create new trie node
struct Trie *createTrie(void)
{
	// allocate memory for a TrieNode
	struct Trie *node = (struct Trie *) malloc(sizeof(struct Trie));
	for (int i = 0; i < 26; i++)
		node->next[i] = NULL;
	node->isWord = 0;
	return node;
}

// free trie node
void freeTrie(struct Trie *node)
{
	// free TrieNode sequence
	for (int i = 0; i < 26; i++)
	{
		if (node->next[i] != NULL)
			freeTrie(node->next[i]);
		else
			continue;
	}
	free(node);
}