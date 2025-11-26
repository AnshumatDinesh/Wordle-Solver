#include <stdio.h>
#include "../Header/WordTree.c"

int main(){
    WordTree* tree=initTree();
    fillTree(tree);
    printf("%d\n",findCount(tree,'a',0));
    // isBlack(tree,'a',1);
    // printf("%d\n",tree->count);
    // recount(tree);
    // printf("%d\n",tree->count);
    // isYellow(tree,'b',1);
    // recount(tree);
    // printf("%d\n",tree->count);
    // // printf("%d\n",findCount(tree,'x',0));
    // printf("%f\n",getProb(tree,'x',0));
    // printf("%s\n",getFastChoice(tree));
    // printf("%s\n",getTopChoice(tree));
    
}