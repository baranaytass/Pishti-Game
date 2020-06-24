#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
Deste için bir integer dizisi yaratip her bir elemana 3 basamakli bir sayi atadım.
Bu sayilarin yüzler basamagi kartlarin cinsini belirtecek.
Kupa>Karo>Maça>Sinek   >>>>  400>300>200>100
As>Papaz>Kiz>Vale   >>>> 14>13>12>11

*/

static int lastCaptured=0;
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
        printf("Yok   ");
    if(x/100==1)
        printf("Sinek ");
    else if(x/100==2)
        printf("Maca ");
    else if(x/100==3)
        printf("Karo ");
    else if(x/100==4)
        printf("Kupa ");
    if(x%100==14)
        printf("As   ");
    else if(x%100==13)
        printf("Papaz   ");
    else if(x%100==12)
        printf("Kiz   ");
    else if(x%100==11)
        printf("Vale   ");
    else{
        if(x!=0)
            printf("%d   ",x%100);
    }
}

void printCards(int *deck, int length){
    for(int i=0;i<length;i++){
        if(deck[i]!=0)
            printCard(deck[i]);
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
        printf("\nOyuncu Kalan Kartlari Topladi");
    if(player==ptrB)
        printf("\nBilgisayar Kalan Kartlari Topladi");

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
        printf("\nOyuncu Pisti Yapti!!\n");
        scoreA=scoreA+10;
        lastCaptured=0;
    }
    if(player==ptrB && howManyCard(ground)==2 && (getTop(ground))%100!=11){
        printf("\nBilgisayar Pisti Yapti!!\n");
        scoreB=scoreB+10;
        lastCaptured=1;
    }
    if(player==ptrA && howManyCard(ground)==2 && (getTop(ground))%100==11 && (ground[0])%100==11){
        printf("\nOyuncu Valeyle Pisti Yapti!!\n");
        scoreA=scoreA+20;
        lastCaptured=0;
    }
    if(player==ptrB && howManyCard(ground)==2 && (getTop(ground))%100==11 && (ground[0])%100==11){
        printCard(getTop(ground));
        printf("\nBilgisayar Valeyle Pisti Yapti!!\n");
        scoreA=scoreA+20;
        lastCaptured=1;
    }
    if(player==ptrA && howManyCard(ground)==2 && (getTop(ground))%100==11){
        printf("\nOyuncu Kartlari Topladi!!\n");
        lastCaptured=0;
    }
    if(player==ptrB && howManyCard(ground)==2 && (getTop(ground))%100==11){
        printCard(getTop(ground));
        printf("\nBilgisayar Kartlari Topladi!!\n");
        lastCaptured=1;
    }
    if(player==ptrA && howManyCard(ground)>2){
        printf("\nOyuncu Kartlari Topladi!!\n");
        lastCaptured=0;
    }
    if(player==ptrB && howManyCard(ground)>2){
        printCard(getTop(ground));
        printf("\nBilgisayar Kartlari Topladi!!\n");
        lastCaptured=1;
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
        printf("\n\nAtmak istediginiz Kartin numarasini girin :");
        scanf("%d",&num);
        switch (num) {
            case 1:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nGecersiz Kart!\n");
                break;
            case 2:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nGecersiz Kart!\n");
                break;
            case 3:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nGecersiz Kart!\n");
                break;
            case 4:
                if(hand[num-1]!=0)
                    return playCard(hand,num-1,ground,player);
                else
                    printf("\nGecersiz Kart!\n");
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
            printf("------ OYUN BASLADI ------");
        printf("\n\n\n--%d. TUR--\n",turn);
        printf("\nYerdeki En ustteki kart  : ");
        printCard(getTop(ground));
        deal(deck1,hand1);
        deal(deck1,hand2);

        for(int i=0;i<4;i++){
            printf("\n\nElinizdeki Kartlar  :   ");
            for(int i=0;i<4;i++){
                printf("%d- ",i+1);
                printCard(hand1[i]);
            }
            chooseCard(hand1,ground,player1);
            printf("\nEn Ustteki Kart :");
            printCard(getTop(ground));
            chooseComCard(hand2,ground,player2);
            printf("\n\nEn Ustteki Kart :");
            printCard(getTop(ground));
        }
        if(turn==6){
            if(lastCaptured==0)
                captureRemainedCards(player1,ground);
            if(lastCaptured==1)
                captureRemainedCards(player2,ground);
        }
        printf("\n\nOyuncu'nun Topladigi Kartlar  : ");
        printCards(player1,52);
        printf("\n\nBilgisayar'in Topladigi Kartlar  : ");
        printCards(player2,52);
    }
    scoreCalculator(player1,player2);
    printf("\nOYUNCUNUN SKORU  : %d",scoreA);
    printf("\nBILGISAYARIN SKORU  : %d",scoreB);
    if(scoreA>scoreB)
        printf("\n---  OYUNCU KAZANDI  ---");
    else if(scoreA<scoreB)
        printf("\n---  BILGISAYAR KAZANDI  ---");
    else
        printf("\n---  BERABERE  ---");
}
