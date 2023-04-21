#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int isWord;
    struct Trie *children[ALPHABET_SIZE];
};

// Function Prototypes
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createNewTrieNode(void);

int main(void)
{
	//read the number of the words in the dictionary
	// parse line  by line, and insert each word to the trie data structure
    struct Trie *trie = NULL;
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

	for (int i = 0; i < 5; i++)
	{
        insert(&trie, pWords[i]);
		printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
	}
	
    trie = deallocateTrie(trie);
	if (trie != NULL)
		printf("There is an error in this program\n");
    
	return 0;
}

void insert(struct Trie **ppTrie, char *word)
{
	struct Trie *temp = *ppTrie;

	if (temp == NULL)
	{
		temp = createNewTrieNode();
		*ppTrie = temp;
	}

	for (int i = 0; word[i] != '\0'; i++)
	{
		int index = (int) word[i] - 'a';
		if (temp->children[index] == NULL)
			temp->children[index] = createNewTrieNode();

		temp = temp->children[index];
	}

	temp->isWord++;
}

// count the number of occurrences of a word if it exists in the dictionary
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	struct Trie *temp = pTrie;
	for (int i = 0; word[i] != '\0'; i++)
	{
		int index = word[i] - 'a';
		if (temp->children[index] == NULL)
			return 0;

		temp = temp->children[index];
	}

	return temp->isWord;
}

// deallocate the entirety of dictionary
struct Trie *deallocateTrie(struct Trie *pTrie)
{    
	if (pTrie == NULL)
		return NULL;
	
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
	return NULL;
}

// create new trie node
struct Trie *createNewTrieNode(void)
{
	// allocate memory for a TrieNode
	struct Trie *node = (struct Trie *) malloc(sizeof(struct Trie));
	for (int i = 0; i < ALPHABET_SIZE; i++)
		node->children[i] = NULL;
	node->isWord = 0;
	return node;
}