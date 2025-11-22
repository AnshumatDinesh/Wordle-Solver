#include <stdio.h>
#include <stdlib.h>

typedef struct node_tree
{
    char letter;
    int count;

    struct node_tree* parent;
    struct node_tree** children;

}WordTreeNode;

typedef struct tree_word
{
    WordTreeNode** roots;
    int wordCount;
}WordTree;


WordTreeNode* initTreeNode(char letter){
    WordTreeNode* new = (WordTreeNode*) malloc(sizeof(WordTreeNode));
    new->letter=letter;
    new->count=0;
    new->parent=NULL;
    new->children=(WordTreeNode**) malloc(26*sizeof(WordTreeNode*));
    for(int i=0;i<26;i++){
        new->children[i]=NULL;
    }
    return new;
}

WordTree* initTree(){
    WordTree* new= (WordTree*) malloc(sizeof(WordTree));
    new->wordCount=0;
    new->roots=(WordTreeNode**) malloc(26*sizeof(WordTreeNode*));
    for(int i=0;i<26;i++){
        new->roots[i]=initTreeNode(97+i);
    }
    return new;
}

void addWord(WordTree*wt,char * word){
    WordTreeNode* trav=wt->roots[word[0]-97];
    trav->count++;
    wt->wordCount++;
    for(int i=1;i<5;i++){
        char letter=word[i];
        if(trav->children[letter-97]==NULL){
            trav->children[letter-97]=initTreeNode(letter);
            trav->children[letter-97]->parent = trav;
            trav=trav->children[letter-97];
            
        }
        trav->count++;
    }
}

void fillTree(WordTree* wt){
    FILE *fptr = fopen("../../Data/words.txt", "r");
    if (!fptr) {
        printf("Unable ot open the word file \n");
        return;
    }
    char word[5000][5];
    int it=0;
    while (fscanf(fptr, "%5s", word[it]) == 1) {
        it++;
    };
    fclose(fptr);
    for(int i=0;i<it;i++){
        addWord(wt,word[i]);
    }
}
