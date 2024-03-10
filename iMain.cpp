# include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

int i,j,k,paddlelength;
double ballx=680.00,bally=20.00;
double paddlex,paddley=0.00;
int screenwidth=1360, screenheight=760;
double paddledx=20.00;
double balldx, balldy;
char ball[2][30]={"character\\Ball.bmp","character\\FireBall.bmp"};
int ballindex=0;
int charindex=0;
char background[14][40]={"background\\Starting.bmp","background\\Levels.bmp","background\\Instructionbg.bmp","background\\Gaming.bmp","background\\intro.bmp","background\\Congo.bmp","background\\Congo.bmp","background\\Congo.bmp","background\\Name.bmp","background\\Name.bmp","background\\Name.bmp","background\\Highscore1.bmp","background\\Highscore2.bmp","background\\Highscore3.bmp"};
char menu[8][50]={"Menu\\play.bmp","Menu\\instruction.bmp","Menu\\quit.bmp","Menu\\easy.bmp","Menu\\medium.bmp","Menu\\hard.bmp","Menu\\resume.bmp","Menu\\newgame.bmp"};
//char powerups[6][30]={"powerups\\FireBall.bmp","powerups\\SlowBall.bmp","powerups\\ZapBrick.bmp","powerups\\KillPaddle.bmp","powerups\\KillPaddle.bmp"};
char paddle[3][30]={"paddle\\normal.bmp","paddle\\long.bmp","paddle\\short.bmp"};
char brickbuild[14][30]={"bricks\\Brick1.bmp","bricks\\Brick2.bmp","bricks\\Brick3.bmp","bricks\\Brick4.bmp","bricks\\Brick5.bmp","bricks\\Brick6.bmp","bricks\\Brick7.bmp","bricks\\YellowBrick1.bmp","bricks\\YellowBrick2.bmp","bricks\\YellowBrick3.bmp","bricks\\FireBrick1.bmp","bricks\\FireBrick2.bmp","bricks\\FireBrick3.bmp","bricks\\FireBrick4.bmp"};
int paddleindex;
int gamestate=10;
//gamestate: 10=intro,0=startscreen,1=difficulty.2=instruction,3=easy,4=medium,5=hard,6=congoeasy,7=congomedium,8=congohard,9=nameinputeasy,11=nameinputmedium,12=nameinputhard,13=highscoreeasy,14=highscoremedium,15=highscorehard,16=pauseeasy,17=pausemedium,18=pausehard
int bgindex=4;
int playstate=0;
int collisioncnt=0;
int points=0;
int lives=3;
int level=0;
int brickleft;
int index;

char scr[15]="Points: ";
char life[15]="Lives: ";
char score[10];
char jibon[10];
char lvl[]="Level: ";
char board[10];

char name[100];
int nameidx=0;



char playername[7][100];
int playerscore[6];
char playerpoint[6][20];

struct options{
	int menux;
	int menuy;
}menucoordinate[6];

struct bricks{
	int brickx;
	int bricky;
	int bricklength=80;
	int brickwidth=40;
	bool show=true;
	int brickindex;
};
struct bricks brickmaze1[9][14];
struct bricks brickmaze2[9][14];
struct bricks brickmaze3[11][17];

void brickbuilding();
void Restart();

FILE *easy, *medium, *hard;

void scoreshort(){
	if(gamestate==13){
		easy=fopen("easy.txt","r");
		for(int i=0;i<5;i++){
        fscanf(easy,"%[^\n]",&playername[i]);
        fscanf(easy,"%d\n",&playerscore[i]);
    	} 
    	fclose(easy); 
		
		for(i=0;i<5;i++){
			int max=playerscore[i];
			int temp,index=i;
			char str[100];
			for(j=i+1;j<6;j++){
				if(playerscore[j]>max || playerscore[j]==max && strcmpi(playername[j],playername[i])<0){
					max=playerscore[j];
					index=j;
				}
			}
			temp=playerscore[i],playerscore[i]=playerscore[index],playerscore[index]=temp;
			strcpy(str,playername[i]);
			strcpy(playername[i],playername[index]);
			strcpy(playername[index],str);
		}

		easy=fopen("easy.txt","w");
		for(i=0;i<5;i++){
			fprintf(easy,"%s\n",playername[i]);
			fprintf(easy,"%d\n",playerscore[i]);
		}
		fclose(easy);
		for(i=0;i<5;i++){
			sprintf(playerpoint[i],"%d",playerscore[i]);
		}
	}
	else if(gamestate==14){
		medium=fopen("medium.txt","r");
		for(int i=0;i<5;i++){
        fscanf(medium,"%[^\n]",&playername[i]);
        fscanf(medium,"%d\n",&playerscore[i]);
    	} 
    	fclose(medium); 
		
		for(i=0;i<5;i++){
			int max=playerscore[i];
			int temp,index=i;
			char str[100];
			for(j=i+1;j<6;j++){
				if(playerscore[j]>max || playerscore[j]==max && strcmpi(playername[j],playername[i])<0){
					max=playerscore[j];
					index=j;
				}
			}
			temp=playerscore[i],playerscore[i]=playerscore[index],playerscore[index]=temp;
			strcpy(str,playername[i]);
			strcpy(playername[i],playername[index]);
			strcpy(playername[index],str);
		}

		medium=fopen("medium.txt","w");
		for(i=0;i<5;i++){
			fprintf(medium,"%s\n",playername[i]);
			fprintf(medium,"%d\n",playerscore[i]);
		}
		fclose(medium);
		for(i=0;i<5;i++){
			sprintf(playerpoint[i],"%d",playerscore[i]);
		}
	}
	else if(gamestate==15){
		hard=fopen("hard.txt","r");
		for(int i=0;i<5;i++){
        fscanf(hard,"%[^\n]",&playername[i]);
        fscanf(hard,"%d\n",&playerscore[i]);
    	} 
    	fclose(hard); 
		
		for(i=0;i<5;i++){
			int max=playerscore[i];
			int temp,index=i;
			char str[100];
			for(j=i+1;j<6;j++){
				if(playerscore[j]>max || playerscore[j]==max && strcmpi(playername[j],playername[i])<0){
					max=playerscore[j];
					index=j;
				}
			}
			temp=playerscore[i],playerscore[i]=playerscore[index],playerscore[index]=temp;
			strcpy(str,playername[i]);
			strcpy(playername[i],playername[index]);
			strcpy(playername[index],str);
		}

		hard=fopen("hard.txt","w");
		for(i=0;i<5;i++){
			fprintf(hard,"%s\n",playername[i]);
			fprintf(hard,"%d\n",playerscore[i]);
		}
		fclose(hard);
		for(i=0;i<5;i++){
			sprintf(playerpoint[i],"%d",playerscore[i]);
		}
	}
}

void iDraw() {
	//place your drawing codes here
	iClear();
	if (gamestate==10){
		iShowBMP(0,0,background[bgindex]);
	}
	else if (gamestate==0){
		iShowBMP(0,0,background[bgindex]);
		for(i=0;i<3;i++){
			iShowBMP2(menucoordinate[i].menux,menucoordinate[i].menuy,menu[i],0);
		}			
	}
	else if (gamestate==1){
		iShowBMP(0,0,background[bgindex]);
		for(i=3;i<6;i++){
			iShowBMP2(menucoordinate[i].menux,menucoordinate[i].menuy,menu[i],0);
		}					
	}
	else if (gamestate==2){
		iShowBMP(0,0,background[bgindex]);
	}
	else if (gamestate>=3 && gamestate<=5){
		iShowBMP(0,0,background[bgindex]);
		iShowBMP2(ballx,bally,ball[ballindex],0);
		if(paddleindex==0){
			iShowBMP2(paddlex,paddley,paddle[paddleindex],0);
		}
		else if(paddleindex==1){
			iShowBMP2(paddlex,paddley,paddle[paddleindex],0);
		}
		else if(paddleindex==2){
			iShowBMP2(paddlex,paddley,paddle[paddleindex],0);
		}
		if(level==1){
			for(j=0;j<9;j++)
				for(k=0;k<14;k++){
					if(brickmaze1[j][k].show){
					iShowBMP(brickmaze1[j][k].brickx,brickmaze1[j][k].bricky,brickbuild[brickmaze1[j][k].brickindex]);
					}
				}
		}
		else if(level==2){
			for(j=0;j<9;j++)
				for(k=0;k<14;k++){
					if(brickmaze2[j][k].show){
					iShowBMP(brickmaze2[j][k].brickx,brickmaze2[j][k].bricky,brickbuild[brickmaze2[j][k].brickindex]);
					}
				}
		}
		else if(level==3){
			for(j=0;j<11;j++)
				for(k=0;k<17;k++){
					if(brickmaze3[j][k].show){
					iShowBMP(brickmaze3[j][k].brickx,brickmaze3[j][k].bricky,brickbuild[brickmaze3[j][k].brickindex]);
					}
				}
		}
		sprintf(score, "%d",points);
		sprintf(jibon, "%d",lives);
		sprintf(board, "%d",level);
		iText(1190,720,scr,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1070,720,life,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1270,720,score,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1150,720,jibon,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(20,720,lvl,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,720,board,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (gamestate>=6 && gamestate<=8){
		iShowBMP2(0,0,background[bgindex],0);			
	}
	else if (gamestate==9 || gamestate==11 || gamestate==12){
		iShowBMP2(0,0,background[bgindex],0);	
		iText(172,375,name,GLUT_BITMAP_TIMES_ROMAN_24)	;	
	}
	else if (gamestate>=13 && gamestate<=15){
		iShowBMP2(0,0,background[bgindex],0);	
		for(i=0;i<5;i++){
			iText(172, 440-i*55,playername[i],GLUT_BITMAP_TIMES_ROMAN_24);
			iText(1100, 440-i*55,playerpoint[i],GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	else if(gamestate>=16 && gamestate<=18){
		iShowBMP2(0,0,background[bgindex],0);
		iShowBMP2(200,120,menu[2],0);
		iShowBMP2(200,270,menu[7],0);
		iShowBMP2(200,420,menu[6],0);
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if(gamestate==10){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			gamestate=0;
			bgindex=0;
			PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
	}
	else if(gamestate==0){
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(mx>330 && mx<596 && my>429 && my<484) {
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			gamestate=1;
			bgindex=1;
		}
		else if(mx>330 && mx<596 && my>279 && my<334) {
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			gamestate=2;
			bgindex=2;
		}	
		else if(mx>330 && mx<596 && my>129 && my<184) {
			exit(0);
		}		
	}
	}
	else if(gamestate==1){
		//PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if(mx>330 && mx<596 && my>429 && my<484) {
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			gamestate=3,level=1,points=0,lives=3;
			balldx=0.00, balldy=10.00;
			bgindex=3;
			paddleindex=1;
			paddlex=505,paddlelength=350;
			playstate=0;
			}
			else if(mx>330 && mx<596 && my>279 && my<334) {
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			gamestate=4,level=1,points=0,lives=3;
			balldx=0.00, balldy=10.00;
			bgindex=3;
			paddleindex=0;
			paddlex=555,paddlelength=250;
			playstate=0;
			}	
			else if(mx>330 && mx<596 && my>129 && my<184) {
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			gamestate=5,level=1,points=0,lives=3;
			balldx=0.00, balldy=10.00;
			bgindex=3;
			paddleindex=2;
			paddlex=605,paddlelength=150;
			playstate=0;
			}
			nameidx=0,name[nameidx]=0;		
		}
	}
	else if(gamestate>=3 && gamestate<=5 && playstate==0){
		PlaySound(0,0,0);
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			//PlaySound("music\\boing.wav",NULL,SND_ASYNC);
			playstate=1;
		}
	}
	else if(gamestate>=16 && gamestate<=18){
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(mx>330 && mx<596 && my>429 && my<484) {
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			if(gamestate==16) gamestate=3;
			else if(gamestate==17) gamestate=4;
			else if(gamestate==18) gamestate=5;
			PlaySound(0,0,0);
			bgindex=3;
			if(playstate==2) playstate=1; 
		}
		else if(mx>330 && mx<596 && my>279 && my<334) {
			// PlaySound("music\\starting.wav",NULL,SND_ASYNC);
			gamestate=1;
			bgindex=1;
			Restart();
			brickbuilding();
			ballx=680.00,bally=20.00;
		}	
		else if(mx>330 && mx<596 && my>129 && my<184) {
			exit(0);
		}		
	}
	}	
	
	
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == '\r') {
		if (gamestate==10){ 
			gamestate=0;
			bgindex=0;
			PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
		else if(gamestate==6){
			gamestate=9;
			bgindex=8;
			PlaySound("music\\ending.wav",NULL,SND_ASYNC);
		}
		else if(gamestate==7){
			gamestate=11;
			bgindex=9;
			PlaySound("music\\ending.wav",NULL,SND_ASYNC);
		}
		else if(gamestate==8){
			gamestate=12;
			bgindex=10;
			PlaySound("music\\ending.wav",NULL,SND_ASYNC);
		}
		else if(gamestate>=13 && gamestate<=15){
			gamestate=0;
			bgindex=0;
			PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
	}
	if (key == '\b') {
		if (gamestate==1||gamestate==2){ 
			gamestate=0;
			bgindex=0;
			//PlaySound("music\\menuclick.wav",NULL,SND_ASYNC);
			//PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
		else if(gamestate==0){
			exit(0);
		}
		else if(gamestate==3){
			gamestate=16;
			bgindex=0;
			if(playstate==1) playstate=2; 
			PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
		else if(gamestate==4){
			gamestate=17;
			bgindex=0;
			if(playstate==1) playstate=2; 
			PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
		else if(gamestate==5){
			gamestate=18;
			bgindex=0;
			if(playstate==1) playstate=2; 
			PlaySound("music\\starting.wav",NULL,SND_ASYNC);
		}
	}
	if(gamestate>=3 && gamestate<=5){
		if (key == 'd') {
		paddlex+=paddledx;
		}
		else if (key == 'a') {
		paddlex-=paddledx;
		}
		if(key=='l') level++;
		if(key=='k') {
			Restart();
			playstate=0;
			if(gamestate==3) gamestate=6,bgindex=5;
			else if(gamestate==4) gamestate=7,bgindex=6;
			else if(gamestate==5) gamestate=8,bgindex=7;
			PlaySound("music\\congo.wav",NULL,SND_ASYNC);
			brickbuilding();
		}
	}
	if(gamestate>=9 && gamestate<=12){
		if(key!='\b' && key!='\r'){
			name[nameidx]=key;
			nameidx++;
			name[nameidx]=0;
		}
		else if(key=='\b' && nameidx>0){
			nameidx--;
			name[nameidx]=0;
		}
		else if(key=='\r' && nameidx>0){
			strcpy(playername[5],name);
			playerscore[5]=points;
			if(gamestate==9) gamestate=13,bgindex=11;
			else if(gamestate==11) gamestate=14,bgindex=12;
			else if(gamestate==12) gamestate=15,bgindex=13;
			scoreshort();
		}
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {
    if(gamestate>=3 && gamestate<=5){
	if (key == GLUT_KEY_RIGHT) {
		if(paddleindex==0){
			if(paddlex>=1091) paddlex=1110;
			else {
				paddlex+=paddledx;
				if(playstate==0) ballx+=paddledx;
			}		
		}
		else if(paddleindex==1){
			if(paddlex>=991) paddlex=1010;
			else {
				paddlex+=paddledx;
				if(playstate==0) ballx+=paddledx;
			}		
		}
		else if(paddleindex==2){
			if(paddlex>=1191) paddlex=1210;
			else {
				paddlex+=paddledx;
				if(playstate==0) ballx+=paddledx;
			}		
		}
	}
	else if (key == GLUT_KEY_LEFT) {
		if(paddlex<=19) paddlex=0;
		else {
			paddlex-=paddledx;
			if(playstate==0) ballx-=paddledx;
		}		
	}
	}
	//place your codes for other keys here
}

void Restart(){
	if(gamestate==3){
			balldx=0.00, balldy=10.00;
			paddleindex=1;
			paddlex=505,paddlelength=350;
			ballx=680.00,bally=20.00;
	}
	else if(gamestate==4){
			balldx=0.00, balldy=10.00;
			paddleindex=0;
			paddlex=555,paddlelength=250;
			ballx=680.00,bally=20.00;
	}
	else if(gamestate==5){
			balldx=0.00, balldy=10.00;
			paddleindex=2;
			paddlex=605,paddlelength=150;
			ballx=680.00,bally=20.00;
	}			
}

void brickbuilding(){
	for(j=0;j<9;j++){
		for(k=0;k<14;k++){
			brickmaze1[j][k].show=true;
			brickmaze1[j][k].brickx=120+k*80;
			brickmaze1[j][k].bricky=240+j*40;
			if(j==0) brickmaze1[j][k].brickindex=7;
			else if(j>0 && k==0) brickmaze1[j][k].brickindex=4;
			else if(j>0 && (k==1||k==12)||(j==1||j==8)&& k>0 && k<13) brickmaze1[j][k].brickindex=6;
			else if((j==1||j==8) && k>0 && k<13) brickmaze1[j][k].brickindex=6;
			else if(j>0 && k==13) brickmaze1[j][k].brickindex=5;
			else if(j==2 && k>1 && k<12) brickmaze1[j][k].brickindex=1;
			else if(j==3 && k>1 && k<12) brickmaze1[j][k].brickindex=3;
			else if(j==4 && k>1 && k<12) brickmaze1[j][k].brickindex=10;
			else if(j==5 && k>1 && k<12) brickmaze1[j][k].brickindex=2;
			else if(j==6 && k>1 && k<12) brickmaze1[j][k].brickindex=7;
			else if(j==7 && k>1 && k<12) brickmaze1[j][k].brickindex=0;
		}
	}	
	for(j=0;j<9;j++){
		for(k=0;k<14;k++){
			brickmaze2[j][k].show=true;
			brickmaze2[j][k].brickx=120+k*80;
			brickmaze2[j][k].bricky=240+j*40;
			if(j==0) {
				if(k==0||k==13) brickmaze2[j][k].brickindex=1;
				else brickmaze2[j][k].brickindex=0;
			}
			else if(j==1 && (k==0||k==13)) brickmaze2[j][k].show=false;
			else if(j==1 && (k==1||k==12)) brickmaze2[j][k].brickindex=1;
			else if(j==1) brickmaze2[j][k].brickindex=2;
			else if(j==2 &&(k==0||k==1||k==12||k==13)) brickmaze2[j][k].show=false;
			else if(j==2) brickmaze2[j][k].brickindex=1;
			else if(j==3 && (k==0||k==13)) brickmaze2[j][k].show=false;
			else if(j==3) brickmaze2[j][k].brickindex=3;
			else if(j==4 && (k==0||k==13)) brickmaze2[j][k].brickindex=3;
			else if(j==4 && (k==1||k==2||k==11||k==12)) brickmaze2[j][k].brickindex=2;
			else if(j==4) brickmaze2[j][k].brickindex=10;
			else if(j==5 &&(k==2||k==5||k==8||k==11)) brickmaze2[j][k].brickindex=2;
			else if(j==5 &&(k==6||k==7)) brickmaze2[j][k].brickindex=7;	 
			else if(j==5) brickmaze2[j][k].show=false;
			else if(j==6 &&(k==3||k==10)) brickmaze2[j][k].show=false;
			else if(j==6 &&(k==6||k==7)) brickmaze2[j][k].brickindex=10;
			else if(j==6) brickmaze2[j][k].brickindex=7;
			else if(j==7 &&(k==0||k==2||k==13||k==11)) brickmaze2[j][k].brickindex=7;
			else if(j==7 &&(k==1||k==5||k==8||k==12)) brickmaze2[j][k].brickindex=10;
			else if(j==7 &&(k==3||k==10)) brickmaze2[j][k].show=false;
			else if(j==7) brickmaze2[j][k].brickindex=0;
			else if(j==8 &&(k>=5&&k<=8)) brickmaze2[j][k].show=false;
			else if(j==8 &&(k==4||k==9)) brickmaze2[j][k].brickindex=10;
			else if(j==8 &&(k==3||k==10)) brickmaze2[j][k].brickindex=0;
			else if(j==8) brickmaze2[j][k].brickindex=7;
		}
	}
	for(j=0;j<11;j++){
		for(k=0;k<17;k++){
			brickmaze3[j][k].show=true;
			brickmaze3[j][k].brickx=k*80;
			brickmaze3[j][k].bricky=240+j*40;
			if(j==0||j==10||k==0||k==16) brickmaze3[j][k].brickindex=7;
			else if(k==1||k==15) brickmaze3[j][k].brickindex=6;
			else if(j==1||j==9) brickmaze3[j][k].brickindex=4;
			else if(k==2||k==14||j==2||j==8) brickmaze3[j][k].brickindex=7;
			else if(j==7||j==5||j==3) brickmaze3[j][k].brickindex=10;
			else brickmaze3[j][k].brickindex=5;			
		}
	}
}

void collision(){
	if(level==1) {for(j=0;j<9;j++)
		for(k=0;k<14;k++){
			if(brickmaze1[j][k].show){					
				if((ballx==brickmaze1[j][k].brickx+80 || ballx+20==brickmaze1[j][k].brickx) && ((bally+10)>=brickmaze1[j][k].bricky && (bally+10)<=(brickmaze1[j][k].bricky+40))){				
					
					if(brickmaze1[j][k].brickindex==7 || brickmaze1[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze1[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze1[j][k].brickindex>=10 && brickmaze1[j][k].brickindex<=13){
						int firecount=0;
						for(int m=3;m<6;m++)
							for(int n=1;n<13;n++){
								if(brickmaze1[m][n].show==true) {
									brickmaze1[m][n].brickindex=10;
									firecount++;
									}
							}
							
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
						for(int m=3;m<6;m++)
							for(int n=1;n<13;n++){
								brickmaze1[m][n].show=false;
							}
						points+=firecount*100;
					}
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze1[j][k].show=false;
						points+=50;
					}
					balldx*=-1;
					if(balldx==0) balldy*=-1;
				}
				
				else if((bally==brickmaze1[j][k].bricky+40 || bally+20==brickmaze1[j][k].bricky) && (ballx+10)>=brickmaze1[j][k].brickx && (ballx+10)<=(brickmaze1[j][k].brickx+80)){
					
					if(brickmaze1[j][k].brickindex==7 || brickmaze1[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze1[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze1[j][k].brickindex>=10 && brickmaze1[j][k].brickindex<=13){
						int firecount=0;
						for(int m=3;m<6;m++)
							for(int n=1;n<13;n++){
								if(brickmaze1[m][n].show==true) {
									brickmaze1[m][n].brickindex=10;
									firecount++;
									}
							}
							
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
						for(int m=3;m<6;m++)
							for(int n=1;n<13;n++){
								brickmaze1[m][n].show=false;
							}
						points+=firecount*100;
					}
					
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze1[j][k].show=false;
						points+=50;
					}
					balldy*=-1;				
				}
				else if(ballx<brickmaze1[j][k].brickx+80 && ballx+20>brickmaze1[j][k].brickx && bally<brickmaze1[j][k].bricky+40 && bally+20>brickmaze1[j][k].bricky){
					if(brickmaze1[j][k].brickindex==7 || brickmaze1[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze1[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze1[j][k].brickindex>=10 && brickmaze1[j][k].brickindex<=13){
						int firecount=0;
						for(int m=3;m<6;m++)
							for(int n=1;n<13;n++){
								if(brickmaze1[m][n].show==true) {
									brickmaze1[m][n].brickindex=10;
									firecount++;
									}
							}
							
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
						for(int m=3;m<6;m++)
							for(int n=1;n<13;n++){
								brickmaze1[m][n].show=false;
							}
						points+=firecount*100;
					}
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze1[j][k].show=false;
						points+=50;
					}
					balldx*=-1;
					balldy*=-1;
				}
			}
		}

		brickleft=0;
		for(j=0;j<9;j++)
			for(k=0;k<14;k++)
				if(brickmaze1[j][k].show==true) brickleft++;
		if(brickleft==0){
			PlaySound("music\\boing.wav",NULL,SND_ASYNC);
			Sleep(500);
			level=2;
			Restart();
			playstate=0;
		}
	}
	else if(level==2) {for(j=0;j<9;j++)
		for(k=0;k<14;k++){
			if(brickmaze2[j][k].show){					
				if((ballx==brickmaze2[j][k].brickx+80 || ballx+20==brickmaze2[j][k].brickx) && ((bally+10)>=brickmaze2[j][k].bricky && (bally+10)<=(brickmaze2[j][k].bricky+40))){				
					
					if(brickmaze2[j][k].brickindex==7 || brickmaze2[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze2[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze2[j][k].brickindex>=10 && brickmaze2[j][k].brickindex<=13){
						int firecount=0;						
						if(j==7 && k==1) {
							for(int m=6;m<9;m++){
								for(int n=0;n<3;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
						
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=0;n<3;n++){									
									brickmaze2[m][n].show=false;									
								}
							}
							points+=firecount*100;
						}
						else if(j==7 && k==12){ 
							for(int m=6;m<9;m++){
								for(int n=11;n<14;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=11;n<14;n++){									
									brickmaze2[m][n].show=false;									
								}
							}
							points+=firecount*100;
						}
						else if(j==4){
						 	for(int m=3;m<6;m++){
								for(int n=2;n<12;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
						 	}
						
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=3;m<6;m++){
								for(int n=2;n<12;n++){
									brickmaze2[m][n].show=false;
								}
						 	}
							points+=firecount*100;
						}
						else {
							for(int m=5;m<9;m++){
								for(int n=3;n<11;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
						
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=5;m<9;m++){
								for(int n=3;n<11;n++){
									brickmaze2[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
					}
					
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze2[j][k].show=false;
						points+=50;
					}
					balldx*=-1;
					if(balldx==0) balldy*=-1;
				}
				else if((bally==brickmaze2[j][k].bricky+40 || bally+20==brickmaze2[j][k].bricky) && (ballx+10)>=brickmaze2[j][k].brickx && (ballx+10)<=(brickmaze2[j][k].brickx+80)){
					if(brickmaze2[j][k].brickindex==7 || brickmaze2[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze2[j][k].brickindex++;
						points+=25;
					}
					else if(brickmaze2[j][k].brickindex>=10 && brickmaze2[j][k].brickindex<=13){
						int firecount=0;						
						if(j==7 && k==1) {
							for(int m=6;m<9;m++){
								for(int n=0;n<3;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=0;n<3;n++){									
									brickmaze2[m][n].show=false;									
								}
							}
							points+=firecount*100;
							
						}
						else if(j==7 && k==12){ 
							for(int m=6;m<9;m++){
								for(int n=11;n<14;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=11;n<14;n++){									
									brickmaze2[m][n].show=false;									
								}
							}
							points+=firecount*100;
						}
						else if(j==4){
						 	for(int m=3;m<6;m++){
								for(int n=2;n<12;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
						 	}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=3;m<6;m++){
								for(int n=2;n<12;n++){
									brickmaze2[m][n].show=false;
								}
						 	}
							points+=firecount*100;
						}
						else {
							for(int m=5;m<9;m++){
								for(int n=3;n<11;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=5;m<9;m++){
								for(int n=3;n<11;n++){
									brickmaze2[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
					}
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze2[j][k].show=false;
						points+=50;
					}
					balldy*=-1;				
				}
				else if(ballx<brickmaze2[j][k].brickx+80 && ballx+20>brickmaze2[j][k].brickx && bally<brickmaze2[j][k].bricky+40 && bally+20>brickmaze2[j][k].bricky){
					if(brickmaze2[j][k].brickindex==7 || brickmaze2[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze2[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze2[j][k].brickindex>=10 && brickmaze2[j][k].brickindex<=13){
						int firecount=0;						
						if(j==7 && k==1) {
							for(int m=6;m<9;m++){
								for(int n=0;n<3;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
						
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=0;n<3;n++){									
									brickmaze2[m][n].show=false;									
								}
							}
							points+=firecount*100;
						}
						else if(j==7 && k==12){ 
							for(int m=6;m<9;m++){
								for(int n=11;n<14;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=11;n<14;n++){									
									brickmaze2[m][n].show=false;									
								}
							}
							points+=firecount*100;
						}
						else if(j==4){
						 	for(int m=3;m<6;m++){
								for(int n=2;n<12;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
						 	}
						
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=3;m<6;m++){
								for(int n=2;n<12;n++){
									brickmaze2[m][n].show=false;
								}
						 	}
							points+=firecount*100;
						}
						else {
							for(int m=5;m<9;m++){
								for(int n=3;n<11;n++){
									if(brickmaze2[m][n].show==true) {
										brickmaze2[m][n].brickindex=10;
										firecount++;
									}
								}
							}
						
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=5;m<9;m++){
								for(int n=3;n<11;n++){
									brickmaze2[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
					}
					
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze2[j][k].show=false;
						points+=50;
					}
					balldx*=-1;
					balldy*=-1;
				}
			}
		}

		brickleft=0;
		for(j=0;j<9;j++)
			for(k=0;k<14;k++)
				if(brickmaze2[j][k].show==true) brickleft++;
		if(brickleft==0){
			PlaySound("music\\boing.wav",NULL,SND_ASYNC);
			Sleep(500);			
			level=3;
			Restart();
			playstate=0;
		}
	}

	else if(level==3) {for(j=0;j<11;j++)
		for(k=0;k<17;k++){
			if(brickmaze3[j][k].show){					
				if((ballx==brickmaze3[j][k].brickx+80 || ballx+20==brickmaze3[j][k].brickx) && ((bally+10)>=brickmaze3[j][k].bricky && (bally+10)<=(brickmaze3[j][k].bricky+40))){				
					
					if(brickmaze3[j][k].brickindex==7 || brickmaze3[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze3[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze3[j][k].brickindex>=10 && brickmaze3[j][k].brickindex<=13){
						int firecount=0;
						if(j==3){
							for(int m=2;m<5;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=2;m<5;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
						else if(j==5){
							for(int m=4;m<7;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=4;m<7;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
						else if(j==7){
							for(int m=6;m<9;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
					}

					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze3[j][k].show=false;
						points+=50;
					}
					balldx*=-1;
					if(balldx==0) balldy*=-1;
				}
				
				else if((bally==brickmaze3[j][k].bricky+40 || bally+20==brickmaze3[j][k].bricky) && (ballx+10)>=brickmaze3[j][k].brickx && (ballx+10)<=(brickmaze3[j][k].brickx+80)){
					
					if(brickmaze3[j][k].brickindex==7 || brickmaze3[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze3[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze3[j][k].brickindex>=10 && brickmaze3[j][k].brickindex<=13){
						int firecount=0;
						if(j==3){
							for(int m=2;m<5;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=2;m<5;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
						else if(j==5){
							for(int m=4;m<7;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=4;m<7;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
						else if(j==7){
							for(int m=6;m<9;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
					}
					
					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze3[j][k].show=false;
						points+=50;
					}
					balldy*=-1;				
				}
				else if(ballx<brickmaze3[j][k].brickx+80 && ballx+20>brickmaze3[j][k].brickx && bally<brickmaze3[j][k].bricky+40 && bally+20>brickmaze3[j][k].bricky){
					if(brickmaze3[j][k].brickindex==7 || brickmaze3[j][k].brickindex==8) {
						PlaySound("music\\brickchange.wav",NULL,SND_ASYNC);
						brickmaze3[j][k].brickindex++;
						points+=25;
					}
					
					else if(brickmaze3[j][k].brickindex>=10 && brickmaze3[j][k].brickindex<=13){
						int firecount=0;
						if(j==3){
							for(int m=2;m<5;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=2;m<5;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
						else if(j==5){
							for(int m=4;m<7;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=4;m<7;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
						else if(j==7){
							for(int m=6;m<9;m++){
								for(int n=2;n<15;n++){
									if(brickmaze3[m][n].show==true) {
										brickmaze3[m][n].brickindex=10;
										firecount++;
									}
								}
							}
							PlaySound("music\\fire.wav",NULL,SND_ASYNC);
							for(int m=6;m<9;m++){
								for(int n=2;n<15;n++){
									brickmaze3[m][n].show=false;
								}
							}
							points+=firecount*100;
						}
					}

					else {
						PlaySound("music\\brickbreak.wav",NULL,SND_ASYNC);
						brickmaze3[j][k].show=false;
						points+=50;
					}
					balldx*=-1;
					balldy*=-1;
				}
			}
		}

		brickleft=0;
		for(j=0;j<11;j++)
			for(k=0;k<17;k++)
				if(brickmaze3[j][k].show==true) brickleft++;
		if(brickleft==0){
			Restart();
			playstate=0;
			if(gamestate==3) gamestate=6,bgindex=5;
			else if(gamestate==4) gamestate=7,bgindex=6;
			else if(gamestate==5) gamestate=8,bgindex=7;
			PlaySound("music\\congo.wav",NULL,SND_ASYNC);
			brickbuilding();
		}
	}


}

void firechange(){
	if(level==1) for(int m=0;m<9;m++)
	for(int n=0;n<14;n++){
		if(brickmaze1[m][n].show==true){
			if(brickmaze1[m][n].brickindex>=10 && brickmaze1[m][n].brickindex<13) brickmaze1[m][n].brickindex++;
			if(brickmaze1[m][n].brickindex==13) brickmaze1[m][n].brickindex=10;
		}
	}
	else if(level==2) for(int m=0;m<9;m++)
	for(int n=0;n<14;n++){
		if(brickmaze2[m][n].show==true){
			if(brickmaze2[m][n].brickindex>=10 && brickmaze2[m][n].brickindex<13) brickmaze2[m][n].brickindex++;
			if(brickmaze2[m][n].brickindex==13) brickmaze2[m][n].brickindex=10;
		}
	}
	else if(level==3) for(int m=0;m<11;m++)
	for(int n=0;n<17;n++){
		if(brickmaze3[m][n].show==true){
			if(brickmaze3[m][n].brickindex>=10 && brickmaze3[m][n].brickindex<13) brickmaze3[m][n].brickindex++;
			if(brickmaze3[m][n].brickindex==13) brickmaze3[m][n].brickindex=10;
		}
	}
}

void change(){	
	if(playstate==1){
		ballx+=balldx;
		bally+=balldy;
		collision();
		if(ballx+20>=screenwidth||ballx<=0) balldx*=-1;
		if(bally+20>=screenheight) balldy*=-1;
		if(bally<=20 && (ballx+10)>=paddlex && (ballx+10)<=paddlex+paddlelength) {
			PlaySound("music\\boing.wav",NULL,SND_ASYNC);
			balldy=abs(balldy);
			if(gamestate==4){
				if((ballx+10)>=paddlex && (ballx+10)<=paddlex+50) {
					if(balldx==10.00) balldx=0.00;
					else if(balldx==5.00) balldx=-5.00;
					else if(balldx==0.00) balldx=-10.00;
					else balldx=-10.00;
				}
				else if((ballx+10)>paddlex+50 && (ballx+10)<=paddlex+100) {
					if(balldx==10.00) balldx=5.00;
					else if(balldx==5.00) balldx=0.00;
					else if(balldx==0.00) balldx=-5.00;
					else balldx=-10.00;
				}
				else if((ballx+10)>paddlex+150 && (ballx+10)<=paddlex+200) {
					if(balldx==-10.00) balldx=-5.00;
					else if(balldx==-5.00) balldx=0.00;
					else if(balldx==0.00) balldx=5.00;
					else if(balldx==5.00) balldx=10.00;
					else balldx=10.00;
				}
				else if((ballx+10)>paddlex+200 && (ballx+10)<=paddlex+250) {
					if(balldx==-10.00) balldx=0.00;
					else if(balldx==-5.00) balldx=5.00;
					else if(balldx==0.00) balldx=10.00;
					else balldx=10.00;
				}
			}
			else if(gamestate==5){
				if((ballx+10)>=paddlex && (ballx+10)<=paddlex+30) {
					if(balldx==10.00) balldx=0.00;
					else if(balldx==5.00) balldx=-5.00;
					else if(balldx==0.00) balldx=-10.00;
					else balldx=-10.00;
				}
				else if((ballx+10)>paddlex+30 && (ballx+10)<=paddlex+60) {
					if(balldx==10.00) balldx=5.00;
					else if(balldx==5.00) balldx=0.00;
					else if(balldx==0.00) balldx=-5.00;
					else balldx=-10.00;
				}
				else if((ballx+10)>paddlex+90 && (ballx+10)<=paddlex+120) {
					if(balldx==-10.00) balldx=-5.00;
					else if(balldx==-5.00) balldx=0.00;
					else if(balldx==0.00) balldx=5.00;
					else if(balldx==5.00) balldx=10.00;
					else balldx=10.00;
				}
				else if((ballx+10)>paddlex+120 && (ballx+10)<=paddlex+150) {
					if(balldx==-10.00) balldx=0.00;
					else if(balldx==-5.00) balldx=5.00;
					else if(balldx==0.00) balldx=10.00;
					else balldx=10.00;
				}
			}
			else if(gamestate==3){
				if((ballx+10)>=paddlex && (ballx+10)<=paddlex+70) {
					if(balldx==10.00) balldx=0.00;
					else if(balldx==5.00) balldx=-5.00;
					else if(balldx==0.00) balldx=-10.00;
					else balldx=-10.00;
				}
				else if((ballx+10)>paddlex+70 && (ballx+10)<=paddlex+140) {
					if(balldx==10.00) balldx=5.00;
					else if(balldx==5.00) balldx=0.00;
					else if(balldx==0.00) balldx=-5.00;
					else balldx=-10.00;
				}
				else if((ballx+10)>paddlex+210 && (ballx+10)<=paddlex+280) {
					if(balldx==-10.00) balldx=-5.00;
					else if(balldx==-5.00) balldx=0.00;
					else if(balldx==0.00) balldx=5.00;
					else if(balldx==5.00) balldx=10.00;
					else balldx=10.00;
				}
				else if((ballx+10)>paddlex+280 && (ballx+10)<=paddlex+350) {
					if(balldx==-10.00) balldx=0.00;
					else if(balldx==-5.00) balldx=5.00;
					else if(balldx==0.00) balldx=10.00;
					else balldx=10.00;
				}
			}
		}
		if(bally+20<=0) {
			PlaySound("music\\byeball.wav",NULL,SND_ASYNC);
			playstate=0; 
			lives--;
			if(lives>0) Restart();
			else if(lives==0){
				Restart();
				brickbuilding();
				if(gamestate==3) gamestate=9,bgindex=8;
				else if (gamestate==4) gamestate=11,bgindex=9;
				else if (gamestate==5) gamestate=12,bgindex=10;
				Sleep(200);
				PlaySound("music\\ending.wav",NULL,SND_ASYNC);
			}
		}
	}
}

int main(){
	//place your own initialization codes here.
	int gap=120;
	for(i=6;i>0;i--){
		if(i==3) gap=120;
		menucoordinate[i-1].menux=200;
		menucoordinate[i-1].menuy=gap;;
		gap+=150;		
	}
	brickbuilding();
	iSetTimer(1,change);
	iSetTimer(500,firechange);
	iInitialize(screenwidth, screenheight, "DxBall");	
	return 0;
}
