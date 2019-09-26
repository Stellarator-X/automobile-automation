//Path Viewer

#include<iostream.h>
#include<process.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<fstream.h>
#include<dos.h>

void main()
{
	int gd=DETECT, gm;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	clrscr();

	cleardevice();

	ifstream readloc;
	char a[100];

	cout<<"Enter the name of the path you wish to view - ";
	cin>>a;

	setbkcolor(WHITE);
	clrscr();
	cleardevice();

	readloc.open(a);
	int x=0,y,col;
	char *i,*j,*k;
	while(x!=9999)
	{
		readloc>>i>>j>>k;

		x=atoi(i);
		y=atoi(j);
		col=atoi(k);

		setcolor(col);
		setfillstyle(1,col);
		fillellipse(x,y,15,15);
	}
	readloc.close();
	sound(1000);
	delay(10);
	nosound();
	char chn = 'a';
	while(1){
		while(!kbhit())
			chn = getch();
		if(chn==13)
			break;
	}
	setbkcolor(BLACK);
	cout<<"Enter any key to exit.";
	getch();
	closegraph();
	exit(0);
}
