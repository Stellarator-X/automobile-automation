//Path Maker - To only be used for Testing Path planning

#include<iostream.h>
#include<stdio.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>

void main()
{
	int gdrive = DETECT, gmode;
	initgraph(&gdrive, &gmode, "C:\\TURBOC3\\BGI");

	clrscr();
	cleardevice();

	char file_name[100];

	cout<<"Enter the name of the path you want to create - ";
	cin>>file_name;

	clrscr();
	cleardevice();
	setbkcolor(WHITE);
	setcolor(BLACK);

	ofstream locus;
	locus.open(file_name,ios::app);

	setfillstyle(1,14);
	//fillellipse(2,2,1,1);
	int ch=0, x=getmaxx()/2, y=getmaxy()/2, col=15;
	while(ch!=13)
	{
		setcolor(DARKGRAY);
		setfillstyle(1,col);
		fillellipse(x,y,15,15);
		if(kbhit())
		{
			ch=getch();
			switch(ch)
			{
			       case 80:
					setcolor(col);
					setfillstyle(1,col);
					fillellipse(x,y,15,15);
					y+=5;
					break;
				case 72:
					setcolor(col);
					setfillstyle(1,col);
					fillellipse(x,y,15,15);
					y-=5;
					break;
				case 77 :
					setcolor(col);
					setfillstyle(1,col);
					fillellipse(x,y,15,15);
					x+=5;
					break;
			       case 75 :
					setcolor(col);
					setfillstyle(1,col);
					fillellipse(x,y,15,15);
					x-=5;

					break;
			       case 101 :
			       case 69 :
						locus.close();
						if(remove(file_name))
							cout << "Eraser Used \n";
						locus.open(file_name, ios::app);
						cleardevice();
						break;
			       case 46 : if(col>0)
					col-=1;
					break;
			       case 44 : if(col<16)
					col+=1;
					break;
			}
			if(col!=1 && col!=15)
				locus<<x<<endl<<y<<endl<<col<<endl;
		}
	}
	//if(col!=1 && col!=15)
	locus<<9999<<endl<<9999<<endl<<9999;
	locus.close();
	clrscr();
	cleardevice();
	setbkcolor(BLACK);
	cout<<"Your Path has been saved as "<<file_name<<endl;
	cout<<"Enter any key to exit...";
	getch();
	clrscr();
}
