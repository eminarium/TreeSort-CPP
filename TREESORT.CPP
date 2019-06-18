//*************************************************************************/
//	Sorts Input Numbers Constructing a Binary Tree. { Class Tree }
//	Draws a Binary Search Tree Using Input Numbers. { Class DrawTree }
//	Draws a Binary Search Tree Using Input Numbers. { Class TreeOut }

//	Author : Merdan Durdiyev
//	Contacts : merdan.durdiyev@gmail.com
//*************************************************************************/

#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define RADIUS 10

class Node
{
	public :
		int data;
		Node* Right;
		Node* Left;

		Node(int item) : data(item) { Left = NULL; Right = NULL;}
};
/**************************************************************************/
/************************** Tree Class Declaration ************************/
/**************************************************************************/
class Tree
{
	private :
		Node* Root;
		int Rlen;
		int Llen;
		int Length;
	public :
		Tree() : Root(NULL),Rlen(0),Llen(0), Length(0) {}
		Node* GetRoot() { return Root;}
		void Add(int);
		int GetLen(){ return Length; }
		void Display(Node*);
		void Display() { Display(Root);}
		int RightLen() { return Rlen; }
		int LeftLen()  { return Llen; }
		char* NumbToString(int);
};

void Tree::Add(int n)
{
	Node *q,*p = Root;

	if (!Root)
		Root = new Node(n);
	else
	{
		while (p)
		{
			q = p;
			if (p->data >= n)
				p = p->Left;
			else
				p = p->Right;
		}

		if (q->data >= n)
			q->Left  = new Node(n);
		else
			q->Right = new Node(n);
	}
	Length++;
}

char* Tree::NumbToString(int n)            // Converts Node data
{                                          // from integer to string.
	char *element;
	itoa(n,element,10);
	return element;
}



void Tree::Display(Node* ptr)              // Tree Passage is
{                                          // SubLeft-Root-SubRight.
	if (ptr)
	{
		Display(ptr->Left);
		cout<<ptr->data<<" ";
		Display(ptr->Right);
	}
}

/**********************************************************************/
/**************************** Tree Class Over *************************/
/**********************************************************************/

class TreeOut : public Tree
{
	public:
	void Display(Node*, int, int);
};

void TreeOut::Display(Node* ptr, int x, int y)
{
	if (ptr)
	{
		gotoxy(x,y);
		cout<<ptr->data;
		if (ptr->Left)
		{
			gotoxy(x-1, y+1);
			cout<<"/";
			Display(ptr->Left, x-2, y+2);
		}
		if (ptr->Right)
		{
			gotoxy(x+1, y+1);
			cout<<"\\";
			Display(ptr->Right, x+2, y+2);
		}
	}
}
/**********************************************************************/
/******************* DrawTree Class Declaration ***********************/
/**********************************************************************/

class DrawTree : public Tree
{
	public :
		void init();
		void Draw(Node*,int, int, int, int);

};

void DrawTree::Draw(Node* ptr, int X, int Y, int XStep, int YStep)
{
	if (ptr)
	{
		setcolor(YELLOW);
		outtextxy(X - RADIUS/4,Y - RADIUS/4,NumbToString(ptr->data));
		int NextXStep, NextYStep;
		if (XStep <=50 )
			NextXStep = 50;
		else
			NextXStep = XStep/2;
		if (YStep >=40)
			NextYStep = 40;
		else
			NextYStep = YStep+20;

		setcolor(WHITE);
		circle(X,Y,RADIUS);
		if (ptr->Left)
			line(X - RADIUS,Y + RADIUS, X - NextXStep + RADIUS , Y + NextYStep - RADIUS);
		if (ptr->Right)
			line(X + RADIUS,Y + RADIUS, X + NextXStep - RADIUS, Y + NextYStep - RADIUS);

		Draw(ptr->Left, X - NextXStep, Y + NextYStep, NextXStep, YStep+10);

		Draw(ptr->Right, X + NextXStep, Y + NextYStep, NextXStep, YStep+10);
	}
}

void DrawTree::init()
{
	int gdriver = DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "C:\\Progra~1\\BC311\\BGI");

	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
		cout<<"Graphics error:"<< grapherrormsg(errorcode)<<endl;
		cout<<"Press any key to halt:";
		getch();
		exit(1);             /* return with error code */
	}
}

/**********************************************************************/
/************************** DrawTree Class Over ***********************/
/**********************************************************************/

void main()
{
	Tree T;
	int i,k,l;

	clrscr();
	cout<<"How Many Numbers are you gonna enter:";
	cin>>l;
	cout<<"Now Enter Your Numbers:";
	for (i=0; i<l; i++)
	{
		cin>>k;
		T.Add(k);
	}

	cout<<"Here are Input Numbers in Increasing Order."<<endl;
	T.Display();
	cout<<endl<<"Press any key to take a look at the Binary Tree for these Numbers:";
	getch();
	/*
	DrawTree DT;
	DT.init();
	DT.Draw(T.GetRoot(), getmaxx()/2, RADIUS/2, getmaxx()/2, 20);
	getch();
	closegraph();
	*/
	getch();
	clrscr();
	TreeOut TO;
	TO.Display(T.GetRoot(), 40, 1);
}
