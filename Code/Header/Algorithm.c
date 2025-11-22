#include <math.h>
#include <stdio.h>
#include "WordTree.c"
char getMaxCount(WordTreeNode** roots){
    int max=0;
    char maxChar='\0';
    for(int i=0;i<26;i++){
        if(roots[i]==NULL){
            continue;
        }
        if(roots[i]->count>max){
            maxChar=roots[i]->letter;
            max=roots[i]->count;
        }
    }
    return maxChar;
}
char* getTopChoice(WordTree* wt){
    char * word= (char*) malloc(sizeof(char)*6);
    word[5]='\0';
    WordTreeNode* trav;
    word[0]=getMaxCount(wt->roots);
    trav=wt->roots[word[0]-97];
    for(int i=1;i<5;i++){
        word[i]=getMaxCount(trav->roots);
        trav=trav->roots[word[i]-97];
    }
    return word;
}
