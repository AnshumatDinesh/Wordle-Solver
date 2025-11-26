#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
typedef struct node_tree
{
    char letter;
    int count;

    struct node_tree* parent;
    struct node_tree** children;

}WordTreeNode;

typedef struct node_tree WordTree;


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
    new->count=0;
    new->children=(WordTreeNode**) malloc(26*sizeof(WordTreeNode*));
    for(int i=0;i<26;i++){
        new->children[i]=NULL;

    }
    new->parent=NULL;
    new->letter='\0';
    return new;
}

void addWordrecursive(WordTree*wt,char * word){
    if(word[0]=='\0'){
        return;
    }
    if(wt->children[word[0]-97]==NULL){
        wt->children[word[0]-97]=initTreeNode(word[0]);
        wt->children[word[0]-97]->parent=wt;
    }
    WordTreeNode* trav=wt->children[word[0]-97];
    trav->count++;
    if(wt->parent==NULL){
        wt->count++;
    }
    addWordrecursive(trav,word+1);
}
void addWord(WordTree*wt,char * word){
    int i=0;
    WordTreeNode* trav=wt;
    wt->count++;
    while(i<5){
        if(trav->children[word[i]-97]==NULL){
            trav->children[word[i]-97]=initTreeNode(word[i]);
            trav->children[word[i]-97]->parent=trav;
        }
        trav=trav->children[word[i]-97];
        trav->count++;
        i++;
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
    return;
}
int findCount(WordTreeNode* root,char letter, int pos){
    if(root==NULL){
        return 0;
    }
    if (pos==-1){
        if(root->letter==letter){
            return root->count;
        }
        return 0;
    }
    int count=0;
    for(int i=0;i<26;i++){
        count+=findCount(root->children[i], letter, pos-1);
    }
    return count;
}

float getProb(WordTree* wt, char letter, int pos){
    return ((float)findCount(wt,letter,pos))/((float)wt->count);
}
float calculateInfo(float probability){
    if(probability==0.0){
        return 0;
    }
    if(probability==1.0){
        return INFINITY;
    }
    return (-1*log2f(probability));
}
float getInfo(WordTree* wt, char letter, int pos){
    float prob=((float)findCount(wt,letter,pos))/((float)wt->count);
    return calculateInfo(prob)*prob;
}
void deleteNode(WordTreeNode* node){
    if(node==NULL){
        return;
    }
    for(int i=0;i<26;i++){
        deleteNode(node->children[i]);
    }
    node->parent->children[node->letter-97]=NULL;
    node->parent=NULL;
    free(node);
    return;
}
void deleteLeaf(WordTreeNode* node){
    if(node==NULL){
        return;
    }
    node->parent->children[node->letter-97]=NULL;
    if(isLeaf(node->parent)){
        deleteNode(node->parent);
    }
    node->parent=NULL;
    free(node);
    return;
}
WordTreeNode* getNode(WordTree* wt, char letter, int pos){
    if(wt==NULL){
        return NULL;
    }
    if(pos==0){
        return wt->children[letter-97];
    }
    int i=0;
    while(getNode(wt->children[i],letter,pos-1)==NULL){
        i++;
        if(i==26){
            break;
        }
    }
    if(i==26){
        return NULL;
    }
    return getNode(wt->children[i],letter,pos-1);

}
void recount(WordTree* wt){
    if(wt==NULL){
        return;
    }
    wt->count=0;
    for(int i=0;i<26;i++){
        recount(wt->children[i]);
        if(wt->children[i]!=NULL){
            wt->count+=wt->children[i]->count;
        }
    }
    if(wt->count==0){
        wt->count=1;
    }
    return;
}
int isLeaf(WordTreeNode*root){
    if(root==NULL){
        return 0;
    }
    int ret=1;
    for(int i=0;i<26;i++){
        if(root->children[i]!=NULL){
            ret=0;
        }
    }
    return ret;
}
WordTreeNode* findWordWithout(WordTreeNode* root, char letter){
    if(root==NULL){
        return NULL;
    }
    if (root->letter==letter){
        return NULL;
    }
    if(isLeaf(root)){
        return root;
    }

    int i=0;
    WordTreeNode* ret=findWordWithout(root->children[i],letter);
    while (ret==NULL){
        i++;
        if(i==26){
            break;
        }
        ret=findWordWithout(root->children[i],letter);
    }
    return ret;
}
void removeLetter(WordTree* wt, char letter , int pos){
    WordTreeNode* toRemove=getNode(wt,letter,pos);
    while(toRemove!=NULL){
        deleteNode(toRemove);
        toRemove=getNode(wt,letter,pos);
    }
}
void pruneBlack(WordTree* wt , char letter, int pos){
    for(int i=0;i<5;i++){
        removeLetter(wt,letter,i);
    }
}
void pruneGreen(WordTree* wt, char letter,int pos){
    for(int i=0;i<26;i++){
        if(i+97!=letter){
            removeLetter(wt,i+97,pos);
        }
    }
}

void pruneYellow(WordTree* wt, char letter, int pos){
    WordTreeNode* wordwithout= findWordWithout(wt,letter);
    int i=0;
    while( wordwithout !=NULL){
        deleteNode(wordwithout);
        wordwithout=findWordWithout(wt,letter);
        i++;
    }
    removeLetter(wt,letter,pos);
}

void clean(WordTree* root, int pos){
    if(root==NULL){
        return;
    }
    if(isLeaf(root)){
        if(pos!=5){
            deleteNode(root);
        }
        return;
    }
    for(int i=0;i<26;i++){
        clean(root->children[i],pos+1);
    }
    if(isLeaf(root)){
        if(pos!=5){
            deleteNode(root);
        }
        return;
    }
    return;
}