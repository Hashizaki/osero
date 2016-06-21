#include <stdio.h>

#define NUM 10 //外壁含む
#define NO 0
#define OUT -1
#define B 1
#define W 2

const int vec_x[]={-1,-1,0,1,1,1,0,-1};
const int vec_y[]={0,1,1,1,0,-1,-1,-1};
int board[NUM][NUM]={{OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT},
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT}, 
		     {OUT,NO,NO,NO,NO,NO,NO,NO,NO,OUT},
		     {OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT}};
int turn=1; //turn_count
//int s_g=1; //先手,後手_count

typedef enum{
  Start,End,Exit,Set
}Menu;

typedef struct{
  int count;
  char name[100];
}player1;

typedef struct{
  int count;
  char name[100];
}player2;

void init(player1 *pl1,player2 *pl2);
void display(player1 *pl1,player2 *pl2);
void Input(int *x,int *y);
int Search_1(void);
int Search_2(void);
int Select(void);
int Put(void);
int Change(void);
  
main(){
  Menu menu;
  
  player1 pl1;
  player2 pl2;

  init(&pl1,&pl2);
  display(&pl1,&pl2);

  turn++;
}



void init(player1 *pl1,player2 *pl2){
  board[NUM/2-1][NUM/2] = B;
  board[NUM/2][NUM/2-1] = B;
  board[NUM/2][NUM/2] = W; 
  board[NUM/2-1][NUM/2-1] = W;

  pl1->count=0;
  pl2->count=0;

  printf("player1_name:"); gets(pl1->name); // scanf("%s",pl1.name);
  printf("player2_name:"); gets(pl2->name); // scanf("%s",pl2.name); 

  //debug
  //     printf("pl1.na:%s,pl2.na:%s,pl1.co:%d,pl2.co:%d",pl1.name,pl2.name,pl1.count,pl2.count);
}

void display(player1 *pl1,player2 *pl2){
  int i,j;
  if(turn%2 == 1) printf("%sの番(●)です.\n",pl1->name);
  else printf("%sの番(○)です.\n",pl2->name);
 
  for(i=1;i<9;i++){
    for(j=1;j<9;j++){
       switch(board[i][j]){
      case NO:
	printf("□ "); break;
      case B:
	printf("● "); break;
      case W:
	printf("○ "); break;
      default:
	printf("! "); break;
      }
    }
    putchar('\n');
  }
}

void Input(int *x,int *y){
  scanf("%d%d",x,y);
}

int Search_1(int *x,int *y){ //B
  int i,j;

  switch(borad[x][y]){
  case B: puts("err : おけません"); return(-1);
  case W: puts("err : おけません"); return(-1);
  case NO:
    for(i=1;i<NUM;i++){
      for(j=0;j<8;j++){
	if(borad[*x + vec_x[j]][*y + vec_y[j]] == NO) break;
	else if(borad[*x + vec_x[j]][*y + vec_y[j]] == B) break;
	else 

