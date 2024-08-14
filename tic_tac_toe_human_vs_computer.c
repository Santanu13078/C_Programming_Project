#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int stack[10],top=-1,turn=0,emt=9;
char a[9]={0},hum,comp;
int inputroom(){
	char s[10000];
	while(1){
		printf("\nEnter room no : ");
		gets(s);
		if(strlen(s)==1 && s[0]>'0' && s[0]<='9' && a[s[0]-49]==0)
			return s[0]-49;
		printf("\nWrong choice!! Try again");
	}	
}


int inputlevel(){
	char s[10000];
	printf("\n********************************LEVEL********************************\n");
	printf("\n1.press 1 for EASY\n2.press 2 for MEDIUM\n3.press 3 for IMPOSSIBLE");
	while(1){
		printf("\nEnter level : ");
		gets(s);
		if(strlen(s)==1)
			if(s[0]=='1')
				return 0;
			if(s[0]=='2')
				return 2;
			if(s[0]=='3')
				return 7;
		printf("\nWrong choice!! Try again");
	}	
}



int inputmode(){
	char s[10000];
	int mode;
	printf("\n********************************MODE OF GAME********************************\n");
	printf("\nWho will play first : \n1. Press 1 for Human \n2. Press 2 for Computer : ");
	while(1){
		printf("\nEnter number : ");
		gets(s);
		if(strlen(s)==1 && s[0]>'0' && s[0]<='2'){
				mode=s[0]-48;
				break;
		}
		printf("\nWrong choice!! Try again");
	}	
	hum=mode%2?'X':'O';
	comp=(hum=='O')?'X':'O';
	return mode;
}



void draw(){
printf("\n\tTurn : %d",turn);
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
	turn++;
	printf("\n");
}

int check(){							
	int i;
	for(i=0;i<=2;i++)
		if(a[i]==comp && a[i]==a[i+3] && a[i]==a[i+6])
			return 1;
		else if(a[i]==hum && a[i]==a[i+3] && a[i]==a[i+6])
			return -1;
				
	for(i=0;i<=6;i+=3)
		if(a[i]==comp && a[i]==a[i+1] && a[i]==a[i+2])
			return 1;
		else if(a[i]==hum && a[i]==a[i+1] && a[i]==a[i+2])
			return -1;
			
	if(a[0]==comp && a[0]==a[4] && a[0]==a[8])
		return 1;
	if(a[0]==hum && a[0]==a[4] && a[0]==a[8])
		return -1;		
	if(a[2]==comp && a[2]==a[4] && a[2]==a[6])
		return 1;
	if(a[2]==hum && a[2]==a[4] && a[2]==a[6])
		return -1;
	return 0;							
}

int think_upto_level(int level){
	if(emt==0 || top==level-1){
		return check();}								

	if(top&1){
		int i,k,best=-2,bestmove;						
		for(i=0;i<9;i++){
			if(a[i]==0){
				a[i]=comp;top++;stack[top]=i;emt--;
				if(check()==1){
						a[i]=0;top--;emt++;stack[top+1]=i;return 1;
					}
					k=think_upto_level(level);
					if(k==1){
						a[i]=0;top--;stack[top+1]=i;emt++;return 1;	
					}
					if(k>best){
						best=k;bestmove=i;
					}
				a[i]=0;top--;emt++;
			}
		}
		stack[top+1]=bestmove;
		return best;
	}
	
	if(top%2==0){
		int i,k,best=2,bestmove;
		for(i=0;i<9;i++){
			if(a[i]==0){
				a[i]=hum;top++;emt--;stack[top]=i;
				if(check()==-1){
						a[i]=0;top--;emt++;stack[top+1]=i;return -1;
					}
					k=think_upto_level(level);
					if(k==-1){
						a[i]=0;top--;emt++;stack[top+1]=i;return -1;
					}
					if(k<best){
						best=k;bestmove=i;
					}
					a[i]=0;top--;emt++;
				}
		}
		stack[top+1]=bestmove;
		return best;
	}
}

void play(int level){
	if(emt==0)		return ;
	if(level==0){
		int st[9],top=-1,i;
		for(i=0;i<9;i++)
			if(a[i]==0)
				st[++top]=i;
		a[st[rand()%top]]=comp;
		emt--;
	}
	else{
		think_upto_level(level);
		a[stack[0]]=comp;
		emt--;
	}
}
int main(){
	int room,level,i,j,k=1,mode;
	printf("\n********************************Room allotement :********************************\n");
	printf("\n\t---------------\n\t");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("| %d |",k++);
		printf("\n\t---------------\n\t");
	}
	
	mode=inputmode();
	level=inputlevel();
	printf("\n********************************GAME STARTS********************************\n");
	while(emt>0){
		printf("\nMove of %s : ",(mode+emt)&1?"Computer ":"Human" );
		if((mode+emt)&1)
			play(level);
		else{
			room=inputroom();
			emt--;
			a[room]=hum;
		}
		draw();
		int p=check();
		if(p==1){
			printf("\nYOU LOOSE.\nGAME END\n");
			return 0;
		}
		else if(p==-1){
			printf("\nYOU WIN.\nGAME END\n");
			return 0;
		}
	}
	printf("\nMatch is draw\nGAME END\n");
			return 0;
			
}
