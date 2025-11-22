#include <stdio.h>
#include "../Header/Algorithm.c"

int main(){
    WordTree* tree=initTree();
    fillTree(tree);
    printf("%d\n",tree->wordCount);
    printf("%d\n",findCount(tree,'a',1));
    printf("%f\n",getProb(tree,'a',1));
    printf("%s",getTopChoice(tree));
    
}