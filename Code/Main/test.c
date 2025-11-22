#include <stdio.h>
#include "../Header/Algorithm.c"

int main(){
    WordTree* tree=initTree();
    fillTree(tree);
    printf("%d\n",tree->wordCount);
    printf("%d\n",findCount(tree,'x',0));
    printf("%f\n",getProb(tree,'x',0));
    printf("%s\n",getFastChoice(tree));
    printf("%s\n",getTopChoice(tree));
    
}