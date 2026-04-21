#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

void main()
{
	srand(time(NULL));
	//printf("\033[5;10Hx");
	int i, j, xsize, ysize;
	char *col, *lin;
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	xsize = w.ws_col;
	ysize = w.ws_row;
	//printf("cols=%i\nlins=%i\n",x,y);
	xsize = xsize/2-1;

  //struct timespec req, rem;
  //req.tv_sec = 0;
  //req.tv_nsec = 1000000;
	//int *grid;
	//grid = (int *)malloc(sizeof(int)*xsize*ysize);

	//printf("\033[1H");
	system("clear");
	for (i=0;i<xsize;i++)
		printf("--");
	printf("--\n");
	for (j=0;j<ysize-2;j++) {
		printf("|");
		for (i=0;i<xsize;i++)
			 printf("  ");
		printf("|\n");
	}
	for (i=0;i<xsize;i++)
		printf("--");
	printf("--");

//ACORN seed
	int exs[7] = {0,1,1,3,4,5,6};
	int wys[7] = {0,0,2,1,0,0,0};

	int *world, *lworld, *nworld;
	int N,M;
	N = xsize;
	M = ysize;
	
	int minsize;
	if (xsize<ysize)
		minsize=xsize;
	else
		minsize=ysize;

	if (N>M)
		M=N;
	else
		N=M;

	lworld = (int *)malloc(sizeof(int)*N*M);
	world = (int *)malloc(sizeof(int)*N*M);
	nworld = (int *)malloc(sizeof(int)*N*M);



	for (i=0; i<N; i++)
		for (j=0; j<M; j++) {
			lworld[i*M+j]=0;
			world[i*M+j]=0;
			nworld[i*M+j]=0;
		}

	int origin,xorg,yorg;
	origin = ysize/2*xsize+xsize/2;
	xorg = origin%xsize;
	yorg = origin/xsize;
	//printf("ORIGIN: x:%i y:%i\n",xorg,yorg);

	//printf("\033[%i;%iHo",origin/N,origin%N*2);
	//printf("\033[H");

	int born[N*M];
	int lalive[N*M];
	int alive[N*M];
	int died[N*M];
	int *bp, *lp, *ap, *dp, *p;

	bp=&born[0];
	lp=&lalive[0];
	ap=&alive[0];
	dp=&died[0];

	for (i=0; i<7; i++) {
		*(ap++)=(xorg+exs[i])+(yorg-wys[i])*N;
		//printf("x:%i y:%i\n",xorg+exs[i],(yorg-wys[i]));
	}

//	for (p=&alive[0]; p<ap; p++)
//		printf("\033[%i;%iH#",*p/N,*p%N*2);

	printf("\033[H");

	int x,y,xm,xp,ym,yp;
	int k;
	k=0;
	ap=&alive[0];
	for (i=2; i<N; i++)
		for (j=2; j<M; j++) {
			if (i>=ysize || j>=xsize) break;
			if (rand()%2)
				*(ap++)=i*N+j;
		}
	
	for (p=&alive[0]; p<ap; p++)
		printf("\033[%i;%iH#",*p/N,*p%N*2);

	for (p=&alive[0]; p<ap; p++) {
		x=*p%N*1; y=*p/N;
		lworld[y*N+x] = 1;
		nworld[y*N+x] = 1;
	}
	getchar();
for (;;) {
  //nanosleep(&req,&rem);
	for (p=&alive[0]; p<ap; p++) {
		x=*p%N*1; xm=x-1; xp=x+1;
		y=*p/N; ym=y-1; yp=y+1;

		/*if (world[ym*M+xm]<4) */world[ym*M+xm]++;
		/*if (world[ym*M+x]<4) */world[ym*M+x]++;
		/*if (world[ym*M+xp]<4) */world[ym*M+xp]++;
		/*if (world[y*M+xp]<4) */world[y*M+xp]++;
		/*if (world[yp*M+xp]<4) */world[yp*M+xp]++;
		/*if (world[yp*M+x]<4) */world[yp*M+x]++;
		/*if (world[yp*M+xm]<4) */world[yp*M+xm]++;
		/*if (world[y*M+xm]<4) */world[y*M+xm]++;
	}
	ap=&alive[0];
	for (i=2; i<N; i++)
		for (j=2; j<M; j++) {
			if (i>=ysize || j>=xsize) break;
			if (world[i*M+j]==3 || (world[i*M+j]==2 && lworld[i*M+j]==1)) {
				nworld[i*M+j]=1;
				*(ap++)=i*M+j;
			}
			else
				nworld[i*M+j]=0;
			if (nworld[i*M+j]!=lworld[i*M+j]) {
				lworld[i*M+j]=nworld[i*M+j];
				printf("\033[%i;%iH%c",i,j*2,(nworld[i*M+j]==1)?'#':' ');
			}
			//else
			//	printf("\033[%i;%iH%c",i,j*2,(nworld[i*M+j]==1)?'#':' ');
			world[i*M+j]=0;
			nworld[i*M+j]=0;
		}
}
}
