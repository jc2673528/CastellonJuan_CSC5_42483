/* 
 * File:   main.cpp
 * Author: Juan Castellon
 * Created on May 31, 2018, 11:00 AM
 * Purpose:  Yahtzee Game
 */

//System Libraries Here
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
const int GAME=1;//Number of games as columns

//123412341234123412341234123412341234123412341234123412341234123412341234123412
//Function Prototypes Here
//123412341234123412341234123412341234123412341234123412341234123412341234123412

//Starting the game
int pTotal(int [],int);
bool first(int [],int,string &,string &);

//Essentials for playing the game
int turn(int [],int,int,int,string,int);//Turns for the game
void rolDice(int [],int);           //Rolling the Dice

//Parallel Tracking
bool diceTrk(bool [],int);//Dice Tracking
bool upTrak(bool [],int); //Upper Section Tracking
bool loTrack(bool [],int);//Upper Section Tracking

//Scoring
int scre(int [],int, int);//Scoring Both Sections

//Sorting
void bubSort(int [],int);//Bubble Sort
void selSort(int [],int);//Selection Sort

//123412341234123412341234123412341234123412341234123412341234123412341234123412
//End of Function Prototypes
//123412341234123412341234123412341234123412341234123412341234123412341234123412

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //12341234123412341234123412341234123412341234123412341234123412341234123412
    //Declare all Variables Here
    //12341234123412341234123412341234123412341234123412341234123412341234123412
    
    //Array sizing constants
    const int UPSCRE=6;//Number of rows in upper score sheet
    const int LWSCRE=8;//Number of rows in the lower score sheet
    const int DICE=5;  //Number of dice thrown
    
    
    //Player Names
    string name1,name2,//Input names of the players
           ply1,ply2;  //Determines who goes 
    
    
    //Boolean Variables for checking things
    bool prime=false;      //Determines who goes first
    
    
    //Scoring and other game-related stuff
    int turns=1;              //Game lasts 26 turns, starts at 1
    int upper[UPSCRE][GAME]={};//Scoring for the upper section
    int lower[LWSCRE][GAME]={};//Scoring for the lower section
    int roll[DICE]={};
    int p1Tot,p2Tot;            //Total score for that game
    int yah=0;                  //How many Yahtzees scored in a game
    
    
    //12341234123412341234123412341234123412341234123412341234123412341234123412
    //End of Variable Declaring
    //12341234123412341234123412341234123412341234123412341234123412341234123412
    
    //Initialize
    p1Tot=p2Tot=0;
    
    //Bubble Sort Test:
    rolDice(roll,DICE);
    for(int count=0;count<DICE;count++){
        cout<<roll[count]<<" ";
    }
    cout<<endl;
    selSort(roll,DICE);
    for(int count=0;count<DICE;count++){
        cout<<roll[count]<<" ";
    }
    
    //Introduction
    cout<<"This program can play Yahtzee with 2 people."<<endl;
    cout<<"Please input player 1's name."<<endl;
    getline(cin,name1);
    cout<<"Please input player 2's name."<<endl;
    getline(cin,name2);
    
    
    //Roll to determine who goes first
    prime=first(roll,DICE,name1,name2);
    
    //Determines which player goes first
    if(prime==true){
        name1=ply1;
        name2=ply2;
        
    }else if(prime==false){
        name2=ply1;
        name1=ply2;
        
    }
    
    
    //Turns
    
    //Upper Section Turns
    do{
        p1Tot+=turn(roll,DICE,UPSCRE,LWSCRE,ply1,yah);
        turns++;
        p2Tot+=turn(roll,DICE,UPSCRE,LWSCRE,ply2,yah);
        turns++;
        
    }while(turns<26);

    //Exit
    return 0;
}

//First Player Function
bool first(int roll[],int dice,string &name1,string &name2){
    int p1Tot,p2Tot;//Roll totals for each player
    p1Tot=p2Tot=0;
    
    do{
        //Player 1 Roll and Total
        cout<<name1<<" now rolling..."<<endl;
        p1Tot=pTotal(roll,dice);
        
        cout<<"======================="<<endl;

        //Player 2 Roll and Total
        cout<<name2<<" now rolling..."<<endl;
        p2Tot=pTotal(roll,dice);
        
        cout<<"======================="<<endl;
    
    }while(p1Tot==p2Tot);
    
    if(p1Tot>p2Tot){
        return true;
    }else{
        return false;
    }
    
}

//Player Total Roll Function
int pTotal(int roll[],int dice){
    int tot=0;
    rolDice(roll,dice);
    for(int count=0;count<dice;count++){
        tot+=roll[count];
    }
    cout<<"Total = "<<tot<<endl;
    return tot;
}

//Dice Roll Function
void rolDice(int roll[],int dice){
    for(int count=0;count<dice;count++){
        roll[count]=rand()%6+1;
    }
    cout<<"Your roll is: ";
    for(int count=0;count<dice;count++){
        cout<<roll[count]<<" ";
    }
    cout<<endl;
}

//Function for playing the game during the upper section
int turn(int roll[],int dice,int upRow,int loRow,string current,int yah){
    int choice,score,rolls;
    rolls=score=0;
    cout<<current<<"'s turn"<<endl;
    cout<<"Rolling dice..."<<endl;
    rolDice(roll,dice);
    
    if(choice==1){
        cout<<"Which upper category would you like to score?"<<endl;
        cout<<"Aces           = 1"<<endl;
        cout<<"Twos           = 2"<<endl;
        cout<<"Threes         = 3"<<endl;
        cout<<"Fours          = 4"<<endl;
        cout<<"Fives          = 5"<<endl;
        cout<<"Sixes          = 6"<<endl;
        cout<<"3 of a Kind    = 7"<<endl;
        cout<<"4 of a Kind    = 8"<<endl;
        cout<<"Full House     = 9"<<endl;
        cout<<"Small Straight = 10"<<endl;
        cout<<"Large Straight = 11"<<endl;
        cout<<"Yahtzee        = 12"<<endl;
        
        
        //Input Validation
        do{
        cin>>choice;
        }while(choice<1&&choice>12);
        score=scre(roll,dice,choice);
        
    }
    if(choice==2){
        cout<<"Which dice would you like to reroll?"<<endl;
        
    }
            
    
    cout<<"================"<<endl;
    
    return score;
    
    
}

//Scoring Function
int scre(int roll[],int dice,int choice){
    int total,counter;
    total=counter=0;
    switch(choice){
        case 1:{
            cout<<"Scoring Aces"<<endl;
            for(int count=0;count<dice;count++){
                roll[count]==1?total+=1:total+=0;
            }
            break;
        }
        case 2:{
            cout<<"Scoring Twos"<<endl;
            for(int count=0;count<dice;count++){
                roll[count]==2?total+=2:total+=0;
            }
            break;
        }
        case 3:{
            cout<<"Scoring Threes"<<endl;
            for(int count=0;count<dice;count++){
                roll[count]==3?total+=3:total+=0;
            }
            break;
        }
        case 4:{
            cout<<"Scoring Fours"<<endl;
            for(int count=0;count<dice;count++){
                roll[count]==4?total+=4:total+=0;
            }
            break;
        }
        case 5:{
            cout<<"Scoring Fives"<<endl;
            for(int count=0;count<dice;count++){
                roll[count]==5?total+=5:total+=0;
            }
            break;
        }
        case 6:{
            cout<<"Scoring Sixes"<<endl;
            for(int count=0;count<dice;count++){
                roll[count]==6?total+=6:total+=0;
            }
            break;
        }
        case 7:{
            cout<<"Scoring 3 of a Kind"<<endl;
            bubSort(roll,dice);
            int temp=roll[0];
            for(int count=0;count<dice;count++){
                if(roll[count]==temp){
                    counter++;    
                }else{
                    temp=roll[count];
                }
            }
            if(counter==3){
                for(int count=0;count<dice;count++){
                    total+=roll[count];
                }
            }
            break;
        }
        case 8:{
            cout<<"Scoring 4 of a Kind"<<endl;
            bubSort(roll,dice);
            int temp=roll[0];
            for(int count=0;count<dice;count++){
                if(roll[count]==temp){
                    counter++;    
                }else{
                    temp=roll[count];
                }
            }
            if(counter==4){
                for(int count=0;count<dice;count++){
                    total+=roll[count];
                }
            }
            break;
        }
        case 9:{
            cout<<"Scoring Full House"<<endl;
            if(roll[0]==roll[1]){
                if(roll[2]==roll[3]==roll[4]){
                    total=25;
                }
            }
            if(roll[0]==roll[1]==roll[2]){
                if(roll[4]==roll[5]){
                    total=25;
                }
            }
            break;
        }
        case 10:{
            cout<<"Scoring Small Straight"<<endl;
            bubSort(roll,dice);
            if((roll[4]-roll[3])==1){
                if((roll[3]-roll[2]==1)){
                    if((roll[2]-roll[1]==1)){
                        total=30;
                    }
                }
            }
            if((roll[3]-roll[2])==1){
                if((roll[2]-roll[1]==1)){
                    if((roll[1]-roll[0]==1)){
                        total=30;
                    }
                }
            }
            break;
        }
        case 11:{
            cout<<"Scoring Long Straight"<<endl;
            bubSort(roll,dice);
            if((roll[4]-roll[3])==1){
                if((roll[3]-roll[2]==1)){
                    if((roll[2]-roll[1]==1)){
                        if((roll[1]==roll[0])==1){
                            total=40;
                        }
                    }
                }
            }
            break;
        }
        case 12:{
            cout<<"Scoring Yahtzee"<<endl;
            if(roll[0]==roll[1]==roll[2]==roll[3]==roll[4]){
                if(yah>0){
                    
                }
                
            }
        }
    }
    cout<<"Score for this turn is : "<<total<<endl;
    return total;
}

void bubSort(int roll[],int dice){
    for(int count=0;count<dice-1;count++){
        for(int place=count+1;place<dice;place++){
            if(roll[count]>roll[place]){
                int temp=roll[count];
                roll[count]=roll[place];
                roll[place]=temp;
            }
        }
    }
}


