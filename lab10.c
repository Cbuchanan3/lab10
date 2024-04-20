#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie *alphabet[26];
};

/*
Down to the end, insert the word.
if (k == strlen(word)) {
tree->isWord = 1;
return;
}
// See if the next place to go exists, if not, create it.
int nextIndex = word[k] - 'a';
if (tree->next[nextIndex] == NULL)
tree->next[nextIndex] = init();
*/

// Initializes a trie structure
struct Trie *createTrie()
{
    //printf("Test Create\n");
    struct Trie* Tree = malloc(sizeof(struct Trie));

    for (int i = 0; i < 26; i++)
        Tree->alphabet[i] = NULL;

    return Tree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    //printf("Test Insert\n");
    int next;

    for(int i = 0; i < strlen(word); i++)
    {
        next = word[i] - 'a';

        if(pTrie->alphabet[next] == NULL)
            pTrie->alphabet[next] = createTrie;

        pTrie = pTrie->alphabet[next];
    }
    pTrie->count = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    //printf("Test Number\n");
    int num = 0;
    int next;

    for(int i = 0; i < strlen(word); i++)
    {
        next = word[i] - 'a';

        if(pTrie->alphabet[next] != NULL)
        {
            pTrie = pTrie->alphabet[next];
        }
        else if(pTrie->count = 1 && pTrie->alphabet[next] != NULL)
        {
            num++;
        }
    }


    return num;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    //printf("Test Deallocate\n");
    if(pTrie == NULL)
    {
        printf("No Node Found\n");
    }
    else
    {
        for(int i = 0; i < 25; i++)
        {
            pTrie->alphabet[i] = NULL;
        }
    }
    pTrie = NULL;

    printf("Node Deleted!\n");

    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    //printf("Test Dictionary\n");
    FILE *fp = NULL;
    int n, len;
    char temp[20];

    fp = fopen(filename, "r");
        fscanf(fp, "%d", &n);

    for(int i = 0; i < n; i++)
    {
        fscanf(fp, "%s", temp);

        pInWords[i] = temp;
    }
    return n;
}

int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
