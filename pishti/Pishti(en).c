#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
Created an integer array for the deck and assign a 3-digit number to each element.
Hundreds digits of these numbers will represent the type of card.
Hearts>Diamonds>Spades>Clubs   >>>>  400>300>200>100
Ace>King>Queen>Jack   >>>> 14>13>12>11


*/

static int lastCapture=0;
static int *ptrA;
static int scoreA=0;
static int *ptrB;
static int scoreB=0;

int deal(int *deck, int *hand){
    int x=0;
    for(int i=0;i<52;i++){
        if(deck[i]!=0){
            for(int j=i;j<i+4;j++){
                hand[x++]=deck[j];
                deck[j]=0;
            }
            return 0;
        }
    }
    return 0;
}

void createDeck(int *deck){
    for(int i=0;i<52;i++){
        deck[i]=(100*((i/13)+1))+(i%13)+2;
    }
}

void createEmpityDeck(int *deck){
    for(int i=0;i<52;i++)
        deck[i]=0;
}

void shuffleDeck(int *deck){
    srand(time(NULL));
    int temp;
    for(int i=0;i<52;i++){
        int random1 = rand()%(52-i);
        int random2 = rand()%(52-i);
        temp=deck[random1];
        deck[random1]=deck[random2];
        deck[random2]=temp;
    }
}

void printCard(int x){
    if(x==0)
        printf("Empity   ");
    if(x/100==1)
        printf("Clubs ");
    else if(x/100==2)
        printf("Spades ");
    else if(x/100==3)
        printf("Diamonds ");
    else if(x/100==4)
        printf("Hearts ");
    if(x%100==14)
        printf("Ace   ");
    else if(x%100==13)
        printf("King   ");
    else if(x%100==12)
        printf("Queen   ");
    else if(x%100==11)
        printf("Jack   ");
    else{
        if(x!=0)
            printf("%d   ",x%100);
    }
}

void printCards(int *deck, int length){
    for(int i=0;i<length;i++){
        if(deck[i]!=0){
            printCard(deck[i]);
            printf("-   ");
        }
    }
}

int getTop(int *deck){
    if(deck[0]==0){
        return 0;
    }
    for(int i=0;i<52;i++){
        if(deck[i]==0){
            return deck[i-1];
        }
    }
}

void captureRemainedCards(int *player, int *ground){
    if(player==ptrA)
        printf("\nPlayer Captured The Remaining Cards!!");
    if(player==ptrB)
        printf("\nComputer Captured The Remaining Cards!!");

    int t=0;
    while(1==1){
        if(player[t]==0)
            break;
        t++;
    }
    int i=0;
    while(ground[i]!=0)
        player[t++]=ground[i++];
    createEmpityDeck(ground);
}

void captureCards(int *player, int *ground){
    if(player==ptrA && howManyCard(ground)==2 && (getTop(ground))%100!=11){
        printf("\nPlayer Got a Pishti!!\n");
        scoreA=scoreA+10;
        lastCapture=0;
    }
    if(player==ptrB && howManyCard(ground)==2 && (getTop(ground))%100!=11){
        printf("\nComputer Got a Pishti!!\n");
        scoreB=scoreB+10;
        lastCapture=1;
    }
    if(player==ptrA && howManyCard(ground)==2 && (getTop(ground))%100==11 && (ground[0])%100==11){
        printf("\nPlayer Got a Pishti With Jack!!\n");
        scoreA=scoreA+20;
        lastCapture=0;
    }
    if(player==ptrB && howManyCard(ground)==2 && (getTop(ground))%100==11 && (ground[0])%100==11){
        printCard(getTop(ground));
        printf("\nComputer Got a Pishti With Jack!!\n");
        scoreA=scoreA+20;
        lastCapture=1;
    }
    if(player==ptrA && howManyCard(ground)==2 && (getTop(ground))%100==11){
        printf("\nPlayer Captured Cards!!\n");
        lastCapture=0;
    }
    if(player==ptrB && howManyCard(ground)==2 && (getTop(ground))%100==11){
        printCard(getTop(ground));
        printf("\nComputer Captured Cards!!\n");
        lastCapture=1;
    }
    if(player==ptrA && howManyCard(ground)>2){
        printf("\nPlayer Captured Cards!!\n");
        lastCapture=0;
    }
    if(player==ptrB && howManyCard(ground)>2){
        printCard(getTop(ground));
        printf("\nComputer Captured Cards!!\n");
        lastCapture=1;
    }
    int t=0;
    while(1==1){
        if(player[t]==0)
            break;
        t++;
    }
    int i=0;
    while(ground[i]!=0)
        player[t++]=ground[i++];
    createEmpityDeck(ground);

}

void playCard(int *hand,int t,int *ground,int *player){
    int x = getTop(ground);
    for(int i=0;i<52;i++){
        if(ground[i]==0){
            ground[i]=hand[t];
            hand[t]=0;
            break;
        }
    }
    if(x%100==(getTop(ground))%100)
        captureCards(player,ground);
    if((getTop(ground))%100==11 && howManyCard(ground)>1)
        captureCards(player,ground);

}

int howManyCard(int *deck){
    int i=0;
    while(1){
        if(deck[i]==0)
            break;
        i++;
    }
    return i;
}

int chooseComCard(int *hand, int *ground, int *player){
    srand(time(NULL));
    for(int i=0;i<4;i++){
        if((getTop(ground))%100==(hand[i])%100 && hand[i]!=0){
            playCard(hand,i,ground,player);
            return 0;
        }
    }
    for(int i=0;i<4;i++){
        if((hand[i])%100==11){
            if(howManyCard(ground)>=3){
                playCard(hand,i,ground,player);
                return 0;
            }
        }
    }
    for(int i=0;i<4;i++){
        if((hand[i])%100!=11 && hand[i]!=0){
            while(1){
                int random2 = rand()%4;
                if((hand[random2])%100!=11 && hand[random2]!=0){
                    playCard(hand,random2,ground,player);
                    return 0;
                }
            }
        }
    }
    while(1){
        int random1 = rand()%4;
        if(hand[random1]!=0){
            playCard(hand,random1,ground,player);
            break;
        }
    }
}

void chooseCard(int *hand,int *ground, int *player){
    while(1==1){
        int num;
        printf("\n\nInput The Card You Want to Discard. :");
        scanf("%d",&num);
        switch (num) {
            case 1:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nInvalid Choice!\n");
                break;
            case 2:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nInvalid Choice!\n");
                break;
            case 3:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nInvalid Choice!\n");
                break;
            case 4:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nInvalid Choice!\n");
                break;
        }
    }
}

void scoreCalculator(int *player1,int *player2){
    if(howManyCard(player1)>howManyCard(player2))
        scoreA=scoreA+3;
    if(howManyCard(player1)<howManyCard(player2))
        scoreB=scoreB+3;
    for(int i=0;i<52;i++){
        if(player1[i]==202)
            scoreA=scoreA+2;
        if(player1[i]==310)
            scoreA=scoreA+3;
        if((player1[i])%100==14 || (player1[i])%100==11)
            scoreA=scoreA+1;

        if(player2[i]==202)
            scoreB=scoreB+2;
        if(player2[i]==310)
            scoreB=scoreB+3;
        if((player2[i])%100==14 || (player2[i])%100==11)
            scoreB=scoreB+1;
    }
}

int main(){
    int deck1[52]; createDeck(deck1); shuffleDeck(deck1);
    int player1[52]; createEmpityDeck(player1);
    int hand1[4];
    int player2[52]; createEmpityDeck(player2);
    int hand2[4];
    int ground[52]; createEmpityDeck(ground);

    ptrA=player1;
    ptrB=player2;

    deal(deck1,ground);

    for(int turn=1;turn<7;turn++){
        if(turn==1)
            printf("------ GAME ON! ------");
        printf("\n\n\n-- %d. TURN --\n",turn);
        printf("\nThe Top Card on The Ground  : ");
        printCard(getTop(ground));
        deal(deck1,hand1);
        deal(deck1,hand2);

        for(int i=0;i<4;i++){
            printf("\n\nThe Cards in Your Hand  :   ");
            for(int i=0;i<4;i++){
                printf("%d- ",i+1);
                printCard(hand1[i]);
            }
            chooseCard(hand1,ground,player1);
            printf("\nThe Top Card on The Ground :");
            printCard(getTop(ground));
            chooseComCard(hand2,ground,player2);
            printf("\n\nThe Top Card on The Ground :");
            printCard(getTop(ground));
        }
        if(turn==6){
            if(lastCapture==0)
                captureRemainedCards(player1, ground);
            if(lastCapture==1)
                captureRemainedCards(player2, ground);
        }
        printf("\n\nThe Cards Captured by The Player  : ");
        printCards(player1,52);
        printf("\n\nThe Cards Captured by The Computer  : ");
        printCards(player2,52);
    }

    scoreCalculator(player1,player2);
    printf("\nPLAYER'S SCORE  : %d",scoreA);
    printf("\nCOMPUTER'S SCORE  : %d",scoreB);
    if(scoreA>scoreB)
        printf("\n---  PLAYER WON  ---");
    else if(scoreA>scoreB)
        printf("\n---  COMPUTER WON  ---");
    else
        printf("\n---  DRAW  ---");
}
