#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "helper_windows.h" //your header file
#define GREEN "\e[0;32m"   //green color 
#define Reset "\e[0;m"    //Ordinary font color

FILE *stream;
int mode,a,b,c;             //Most of the functions used use variables and arrays, so we define it global
char words[11][21]; 
char StarWords[3][21];    
int Score,NOW=0,LevelNum=1;   //NOW=Number Of Words
int NumofWave=1;
double lag;
FILE *sc;
int SpecialPlusScore,Freeze;  //Special Plus Score for !,@,&,^,$
int position=0;
int LagN1=1;    //for lag<=1

void gotoxy(int x, int y){     // Move letters on the page(position of words)
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorCoord;
cursorCoord.X=x;
cursorCoord.Y=y;
SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void my_callback_on_key_arrival(char c);
void Read_myWords();
void PrintWords();
void SelectStarWords();

int main(){
	printf("\t\t\t\t\t\t\t Hi \n \t\t\t\t\t\t Welcome to my Typing Game\n");
	printf("Please Enter:\n\n \t'1' For Easy mode \n\n OR \t '2'  For Intermediate mode\n\n OR \t '3' For Hard mode\n\n\n\n");
	do{
		printf("\t\t\t\tPlease enter the number corresponding to the desired level:\t");
		scanf("%d",&mode);
	}while (mode<1 || mode>3);
	if(mode==1){
		lag=10;	        //Easy mode
	}
	else if(mode==2){
		lag=8;          //Intermediate mode
	}
	else {
		lag=5;          //Hard mode
	}
	stream=fopen("Words.txt", "r");    // Open the file containing the words
	if(stream==NULL){
	printf("\t\t\t\t\t File Not found!\n \t\t\t\t\t Please check again\n");
	return 0;
	}
	Read_myWords();
	HANDLE thread_id = start_listening(my_callback_on_key_arrival);  //According to the file submitted by TA group
	SelectStarWords();
	while(1){
		if(position==9) {    //10=Wawe Length
		system("cls");
		printf("\t\t\t\t\t\tSorry\n \t\t\t\t\t\t You lost\n \t\t\t\t\t Please practice and start the game again\n");
		printf("\t\t\t\t\t\tYour Total Score= %d\n",Score);
		sleep(5);
		return 0;
	}
	PrintWords();
	gotoxy(60,position);
	for(int i=0;i<a;i++){
		printf(GREEN "%c" Reset,words[b][i]);
		}
	printf("%s\n", words[b]+a);	
	printf("\n");
	
	if(Freeze==1){
	sleep(lag*3);
	Freeze=0;
	}
	else{
	sleep(lag);
	}
	c++;
}
	WaitForSingleObject(thread_id, INFINITE);
	return 0;
}
void Read_myWords(){
	for(int i=0;i<10;i++){       // i<10 because Wave length=10
		fscanf(stream,"%s",words[i]);   //scan word number 1 to word numer 10 with strings
	}
}

void SelectStarWords(){
	srand(time(NULL));
	int S,M=-1;
	for(int i=0;i<3;i++){
		S=rand()%11 -1;        // Number between 0 and 9
		while(M==S){
			S=rand()%11 -1;
		}
		M=S;
		for(int j=0;j<strlen(words[S]);j++){
			StarWords[i][j]=words[S][j];
		}
	}
}
void my_callback_on_key_arrival(char k){
	if(k==words[b][a]){
		if(k==33 || k==36 || k==37 || k==38 || k==64 || k==94) // Acii codes of !,$,%,&,@,^
		++SpecialPlusScore;
		else if(k==35) //#
		++Freeze;
	a++;
	int s=strlen(words[b]);
	if(a==s){    //kalame kamel vared shode
		if(SpecialPlusScore!=0)
		Score+=3;
		else if(a>10 && a<=20)
		Score+=2;
		else if(a<=10)
		Score+=1;
		PrintWords();
		b++;
		a=0,SpecialPlusScore=0;
		
		NOW++;
		if(NOW==10){
			if(mode==3)   //Hard
			lag*=0.6;
			else if(mode==2) // Intermediate
			lag*=0.7;
			else if(mode==1)  //Easy
			lag*=0.8;
				if(lag<1 && LagN1==0){
					system("cls");
				printf("\t\t\t\t\t\t\tCongratulations!\n \t\t\t\t\t\tYou have reached a good level of typing\n");
				printf("\t\t\t\t\t\t\tYour Total Score in this Game=",Score);
				sleep(5);
				exit(0);
			}
			else if(lag<=1 && LagN1==1){
				lag=1;
				LagN1=0;
			}
			printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t Level %d Passed\n\n",LevelNum);
			++LevelNum;
			++NumofWave;
			printf("\n\n\t\t\t\t\t\t\t Level %d Started\n",LevelNum);
			a=0,b=0,NOW=0,c=0,Freeze=0,SpecialPlusScore=0,position=0;
			Read_myWords();
			SelectStarWords();
			return;
	}
}
		else{         //zamani ke hame kalame vared nashoda
			PrintWords();
			gotoxy(60,position);
			for(int i=0;i<a;i++){
				printf(GREEN "%c" Reset,words[b][i]);
			}
			printf("%s\n", words[b]+a);	//+a for pointer to string 
			printf("\n");
		}
	}
}
void PrintWords(){
	system("cls"); //clear screen
	for(int i=0;i<10;i++){
		printf("\t\t\t\t\t\t#                            #\n");
		}
			printf("\t\t\t\t\t\t##############################");	
			position=0;
	for(int i=c;i>b;i--){
		if (strcmp(words[i],StarWords[0])==0 || strcmp(words[i],StarWords[1])==0 || strcmp(words[i],StarWords[2])==0){
			gotoxy(49, position);
			printf("****************************");
		}	
		else {
			gotoxy(58, position);
			printf("%s\n", words[i]);   
		}		
		position++;	
	}
	gotoxy(0,5);
	printf("Your Score = %d\n",Score);
	printf("Numer of this wave = %d\n",NumofWave);
	printf("Lag = %.3lf sec\n",lag);   //3ragham aashar	
}