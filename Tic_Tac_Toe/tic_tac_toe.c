#include<stdio.h>
#include<string.h>
int emt=9;
char a[9]={0};

int input(){
	char s[10000];
	while(1){
		printf("\nEnter room no : ");
		scanf("%s",&s);
		if(strlen(s)==1 && s[0]>'0' && s[0]<='9' && a[s[0]-49]==0)
			return s[0]-49;
		printf("\nWrong choice!! Try again");
	}	
}

void draw(){
printf("\n\tTurn : %d",10-emt);
	printf("\n\t---------------\n\t");
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{	if (a[3*i+j]<65)		printf("|   |");
			else 					printf("| %c |",a[3*i+j]);
		}
		printf("\n\t---------------\n\t");
	}
	printf("\n");
}

int check(){							
	int i;
	for(i=0;i<=2;i++)
		if(a[i]=='X' && a[i]==a[i+3] && a[i]==a[i+6])
			return 1;
		else if(a[i]=='O' && a[i]==a[i+3] && a[i]==a[i+6])
			return 0;
				
	for(i=0;i<=6;i+=3)
		if(a[i]=='X' && a[i]==a[i+1] && a[i]==a[i+2])
			return 1;
		else if(a[i]=='O' && a[i]==a[i+1] && a[i]==a[i+2])
			return 0;
			
	if(a[0]=='X' && a[0]==a[4] && a[0]==a[8])
		return 1;
	if(a[i]=='O' && a[0]==a[4] && a[0]==a[8])
		return 0;		
	if(a[2]=='X' && a[2]==a[4] && a[2]==a[6])
		return 1;
	if(a[2]=='O' && a[2]==a[4] && a[2]==a[6])
		return 0;
	return -1;							
}

int main(){
	int room;
	printf("\n\t---------------\n\t");
	int i,j,k=1;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("| %d |",k++);
		printf("\n\t---------------\n\t");
	}
	while(emt>0){
		printf("\nMove of player - %d : ",(emt+1)%2+1);
		room=input();
		a[room]=emt%2?'X':'O';
		draw();
		if(check()==emt%2){
			printf("\nPlayer - %d win.\nGAME END\n",(emt+1)%2+1);
			return 0;
		}
		emt--;
	}
	printf("\nMatch is draw\nGAME END\n");
			return 0;
}
