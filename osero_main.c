#include <stdio.h>

//Success : 0 false : 1

#define NUM 10 //外壁含む
#define NO 0
#define OUT -1
#define B 1
#define W 2

const int vec_x[8]={-1,-1,0,1,1,1,0,-1};
const int vec_y[8]={0,1,1,1,0,-1,-1,-1};
//int sflag[8]; //その方向に返せるかどうかのフラグ
int svec[8]; //返せる駒数 格納
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

/* typedef enum{ */
/*   Start,End,Exit,Set */
/* }Menu; */

typedef struct{
  int count;
  char name[100];
}player1;

typedef struct{
  int count;
  char name[100];
}player2;

void init(player1 *pl1,player2 *pl2);	 //定義済み
void init_svec(void);			 //定義済み
void display(player1 *pl1,player2 *pl2); //定義済み
void Input(int *x,int *y);		 //定義済み
int Search_1(int *x,int *y);		 //定義済み
int Search_2(int *x,int *y);		 //定義済み
int Pass(void);	                         //定義済み
//int Select(void);
void Put(int *x,int *y);	         //定義済み
void Change(int *x,int *y);              //定義済み
int Count(player1 *pl1,player2 *pl2);   //定義済み
  
int main(void){
  //  Menu menu;
  int x,y;
  player1 pl1;
  player2 pl2;

  init(&pl1,&pl2);
  //while
  while(1){
    if(Count(&pl1,&pl2)) break;
    display(&pl1,&pl2);
    Input(&x,&y);
    if(turn%2){
      if(Pass()==1){turn++; continue;}
      if(Search_1(&x,&y)==1){ printf("\nErr : おけません　もう一度入力\n\n"); continue;}
      else {
	Put(&x,&y);
	Change(&x,&y);
      }
    }
    else{
      if(Pass()==1){turn++; continue;}
      if(Search_2(&x,&y)==1){ printf("\nErr : おけません　もう一度入力\n\n"); continue;}
      else {
	Put(&x,&y);
	Change(&x,&y);
      }
    }
    turn++;
  }
  printf("\n結果\n");
  for(x=1;x<=8;x++){
    for(y=1;y<=8;y++){
      printf("　 1 2 3 4 5 6 7 8\n");
      for(x=1;x<9;x++){
	printf("%d ",x);
	for(y=1;y<9;y++){
	  switch(board[x][y]){
	  case NO:
	    printf("・"); break;
	  case B:
	    printf("● "); break;
	  case W:
	    printf("○ "); break;
	  default:
	    printf("! "); break;
	  }
	}
	printf("\n");
      }
    }
  }
  if(pl1.count > pl2.count) printf("%sさんの勝ち!!\n",pl1.name);
  if(pl1.count < pl2.count) printf("%sさんの勝ち!!\n",pl2.name);
  if(pl1.count == pl2.count) printf("引き分け");
  printf("お疲れさまでした.\n");
  return(0);
}

void init(player1 *pl1,player2 *pl2){
  board[NUM/2-1][NUM/2] = B;
  board[NUM/2][NUM/2-1] = B;
  board[NUM/2][NUM/2] = W; 
  board[NUM/2-1][NUM/2-1] = W;

  pl1->count=0;
  pl2->count=0;

  printf("\nようこそ!!\n");
  printf("名前を入力してください\n");

  printf("プレイヤー1:"); fgets(pl1->name,100,stdin); // scanf("%s",pl1.name);
  printf("プレイヤー2:"); fgets(pl2->name,100,stdin); // scanf("%s",pl2.name); 

  //debug
  //     printf("pl1.na:%s,pl2.na:%s,pl1.co:%d,pl2.co:%d",pl1.name,pl2.name,pl1.count,pl2.count);
}

void init_svec(void){
  int i;
  for(i=0;i<8;i++)svec[i]=0;
}

void display(player1 *pl1,player2 *pl2){
  int i,j;
  if(turn%2 == 1) printf("%sの番(● )です.\n",pl1->name);
  else printf("%sの番(○ )です.\n",pl2->name);
  printf("　 1 2 3 4 5 6 7 8\n");
  for(i=1;i<9;i++){
    printf("%d ",i);
    for(j=1;j<9;j++){
       switch(board[i][j]){
      case NO:
	printf("・"); break;
      case B:
	printf("● "); break;
      case W:
	printf("○ "); break;
      default:
	printf("! "); break;
      }
    }
    printf("\n");
  }
  printf("現在の状況: ● :%d  ○ :%d\n",pl1->count,pl2->count);
}

void Input(int *x,int *y){
  while(1){
    printf("(行/列)で入力:");
    if(scanf("%d/%d",x,y) != 2){
      scanf("%*s");
      puts("Err : 入力内容に問題があります.");
      continue;
    }
    break;
  }
  putchar('\n');
}

int Search_1(int *x,int *y){ //B
  int i,j;
  int n;
  int sflag = 0;
  init_svec();
  switch(board[*x][*y]){
  case B: return(1);		/* Err */
  case W:  return(1);		/* Err */
  case OUT: return(1);		/* Err */
  case NO:

    for(i=0;i<8;i++){
      n=1;
      for(j=1;j<=8;j++){
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == NO) break;
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == OUT) break;
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == B) break;
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == W){
	  if(board[*x + ((n+1) * vec_x[i])][*y + ((n+1) * vec_y[i])] == B){
	    svec[i]=j;
	    sflag=1;
	  }
	  n++;
	}
      }
      //    printf("debug:%d\n",svec[i]);
    }
    break;
  default: return(1); //puts("err : おけません"); return(1);
  }
  if(sflag) return(0); else {return(1);}
}

int Search_2(int *x,int *y){ //W
  int i,j;
  int n;
  int sflag = 0;
  init_svec();
  switch(board[*x][*y]){
  case B: return(1);		/* Err */
  case W: return(1);		/* Err */
  case OUT: return(1);		/* Err */
  case NO:
    for(i=0;i<8;i++){
      n=1;
      for(j=1;j<=8;j++){
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == NO) break;
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == OUT) break;
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == W) break;
	if(board[*x + (n * vec_x[i])][*y + (n * vec_y[i])] == B){
	  if(board[*x + ((n+1) * vec_x[i])][*y + ((n+1) * vec_y[i])] == W){
	    svec[i]=j;
	    sflag=1;
	  }
	  n++;
	}
      }
      // printf("debug:%d\n",svec[i]);
    }
    break;
  default: return(1); //puts("err : おけません"); return(1);
  }
  if(sflag) return(0); else {return(1);}
}

int Pass(void){ 
  int i,j;
  int flag=0;
  for(i=1;i<=8;i++){
    for(j=1;j<=8;j++){
      if(turn%2){
	if(Search_1(&i,&j)==0) {flag=1; break;}
	  }
      else{
	if(Search_2(&i,&j)==0) {flag=1; break;}
	  }
    }
    if(flag) return(0);
  }
  return(1); //Pass
}

void Put(int *x,int *y){
   if(turn%2)  board[*x][*y]=B;
   else board[*x][*y] = W;
 }

void Change(int *x,int *y){
  int i,j;
  for(i=0;i<8;i++){
    for(j=1;j<=svec[i];j++){
      if(svec[i]==0)break;
      if(turn%2) board[*x + ( j * (vec_x[i]))][*y + (j * vec_y[i])] = B;
      else board[*x + ( j * (vec_x[i]))][*y + (j * vec_y[i])] = W;
    }
  }
}

int Count(player1 *pl1,player2 *pl2){
  int i,j;
  int cnt[2]={0};
  for(i=1;i<=8;i++){
    for(j=1;j<=8;j++){
      if(board[i][j] == B) cnt[0]++;
      if(board[i][j] == W) cnt[1]++;
    }
  }
  pl1->count=cnt[0]; 
  pl2->count=cnt[1]; 
  if(pl1->count == 0 || pl2->count == 0) return(1); //End
  if(pl1->count + pl2->count == 64) return(1);      //End
  return(0);
}
