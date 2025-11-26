#include <stdio.h>
#include "../Header/Algorithm.c"
int isdone(char * result){
    int gCount=0;
    for(int i=0;i<5;i++){
        if(result[i]=='g' || result[i]=='G'){
            gCount++;
        }
    }
    if(gCount==5){
        return 1;
    }
    return 0;
}
int main(){
    WordTree* Tree=initTreeNode('\0');
    printf("Loading the Data\n");
    fillTree(Tree);
    printf("Data Loaded Completed\n");
    int run=1;
    int steps=1;
    while(run){
        int menu=0;
        int invalid=0;
        char* word=(char*) malloc(sizeof(char)*6);
        char* guess=(char*) malloc(sizeof(char)*6);
        word[5]='\0';
        guess[5]='\0';
        printf("Select\n");
        printf("1.Fast Guess\n");
        printf("2.Best Guess\n");
        printf("3.Enter Your own Guess\n");
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            word=getFastChoice(Tree);
            printf("The fast choice is %s\n",word);
            printf("%d possible words\n",Tree->count);
            break;
        case 2:
            word=getTopChoice(Tree);
            printf("The top choice is %s\n",word);
            printf("%d possible words\n",Tree->count);
            break;
        case 3:
            printf("Enter your guess\n");
            scanf("%5s",word);
            printf("%d possible words\n",Tree->count);
            break;
        default:
            break;
        }
        printf("Enter the result\n");
        printf("use g or G for green\n");
        printf("use b or B for black\n");
        printf("use y or Y for yellow\n");
        printf("Leave no spaces\n");
        scanf("%5s",guess);
        if (isdone(guess)){
            run=0;
            printf("Coongratulations the word was %s reach in %d steps\n",word,steps);
            break;
        }
        prune(Tree,word,guess);
        printf("Narrowed down possible words to %d\n",Tree->count);
        steps++;
    }

}

