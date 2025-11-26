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
char getMaxInfoGlobal(WordTree* wt, int pos, WordTree* node){
    float max=0.0;
    char maxChar='\0';
    for(int i=0;i<26;i++){
        if(node->children[i]!=NULL){
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
    word[0]=getMaxInfoLocal(wt->children,wt->count);
    trav=wt->children[word[0]-97];
    for(int i=1;i<5;i++){
        word[i]=getMaxInfoLocal(trav->children,trav->count);
        trav=trav->children[word[i]-97];
    }
    return word;
}
char* getTopChoice(WordTree* wt){
    char * word= (char*) malloc(sizeof(char)*6);
    word[5]='\0';
    WordTreeNode*trav=wt;
    for(int i=0;i<5;i++){
        word[i]=getMaxInfoGlobal(wt,i,trav);
        trav=trav->children[word[i]-97];
    }
    return word;
}

void prune(WordTree* tree,char* word, char* result){
    for(int i=0;i<5;i++){
        switch (result[i])
        {
        case 'b':
            pruneBlack(tree,word[i],i);
            break;
        case 'B':
            pruneBlack(tree,word[i],i);
            break;
        case 'g':
            pruneGreen(tree,word[i],i);
            break;
        case 'G':
            pruneGreen(tree,word[i],i);
            break;
        case 'y':
            pruneYellow(tree,word[i],i);
            break;
        case 'Y':
            pruneYellow(tree,word[i],i);
            break;
        default:
            break;
        }
    }
    clean(tree,0);
    recount(tree);
}