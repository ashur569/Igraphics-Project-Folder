#include<stdio.h>

int i,j;

struct player{
	char name[50];
	int highscore;
};

struct player Player1[6];
struct player temp;


int main(){
    for(i=0;i<6;i++){
        scanf("%s",&Player1[i].name);
        scanf("%d", &Player1[i].highscore);
    }
    for(j=0;j<5;j++){
		struct player max= Player1[j];
		for(i=1;i<6;i++){
			if (Player1[i].highscore>max.highscore){
			max=Player1[i];
			temp=Player1[j];
			Player1[j]=Player1[i];
			Player1[i]=temp;
			}
		}
	}
    for(i=0;i<6;i++){
        printf("%s\n",Player1[i].name);
        printf("%d\n", Player1[i].highscore);
    }
}