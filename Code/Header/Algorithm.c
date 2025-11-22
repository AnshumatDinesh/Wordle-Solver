#include <math.h>
#include <stdio.h>
#include "WordTree.c"

char getMaxInfoLocal(WordTreeNode** roots, int count){
    float max=0.0;
    char maxChar='\0';
    for(int i=0;i<26;i++){
        if(roots[i]==NULL){
            continue;
        }
        float prob=((float)roots[i]->count)/((float)count);
        float info=calculateInfo(prob);
        if(info*prob>max){
            maxChar=roots[i]->letter;
            max=info*prob;
        }
    }
    return maxChar;
}
char getMaxInfoGlobal(WordTree* wt, int pos, WordTreeNode** roots){
    float max=0.0;
    char maxChar='\0';
    for(int i=0;i<26;i++){
        if(roots[i]!=NULL){
            float info= getInfo(wt,97+i,pos);
            if(info>max){
                maxChar=97+i;
                max=info;
            }
        }
    }
    return maxChar;
}
char* getFastChoice(WordTree* wt){
    char * word= (char*) malloc(sizeof(char)*6);
    word[5]='\0';
    WordTreeNode* trav;
    word[0]=getMaxInfoLocal(wt->roots,wt->wordCount);
    trav=wt->roots[word[0]-97];
    for(int i=1;i<5;i++){
        word[i]=getMaxInfoLocal(trav->children,trav->count);
        trav=trav->children[word[i]-97];
    }
    return word;
}
char* getTopChoice(WordTree* wt){
    char * word= (char*) malloc(sizeof(char)*6);
    word[5]='\0';
    WordTreeNode** roots=wt->roots;
    for(int i=0;i<5;i++){
        word[i]=getMaxInfoGlobal(wt,i,roots);
        roots=roots[word[i]-97]->children;
    }
    return word;
}

