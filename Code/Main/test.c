#include <stdio.h>
#include "../Header/WordTree.c"

int main(){
    WordTree* tree=initTree();
    fillTree(tree);
    
    printf("%d",tree->wordCount);
    
}