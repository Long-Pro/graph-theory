#include<graphics.h>
#include<cmath>
#include<cstring>
#include<iostream>
//#include <stdio.h>
//#include <stdlib.h>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
//typedef long long int ll;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool In_Rec(int x1,int y1,int x2,int y2,int x,int y){
	if(x1<x&&x<x2&&y1<y&&y<y2) return true;else return false;
}
bool In_Circle(int x,int y,int x1,int y1){
	if((x1-x)*(x1-x)+(y1-y)*(y1-y)<=20*20) return true;else return false;
}
void OutPut(int x,int y,char a){
	if(a=='1') outtextxy(x,y,"1");
	if(a=='2') outtextxy(x,y,"2");
	if(a=='3') outtextxy(x,y,"3");
	if(a=='4') outtextxy(x,y,"4");
	if(a=='5') outtextxy(x,y,"5");
	if(a=='6') outtextxy(x,y,"6");
	if(a=='7') outtextxy(x,y,"7");
	if(a=='8') outtextxy(x,y,"8");
	if(a=='9') outtextxy(x,y,"9");
	if(a=='0') outtextxy(x,y,"0");
}

int Kc(int x1,int y1,int x2,int y2){
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Create_DFS_BFS(){
	setfillstyle(1,15);
	bar(20,50,100,100);
	setcolor(2);
	rectangle(20,50,100,100);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(25,70,"DFS");
	outtextxy(70,70,"BFS");	
	setcolor(2);
	line(60,60,60,85);	
}
void Create_HL_DFS(){
	setfillstyle(1,2);
	bar(20,90,60,100);	
}
void Create_HL_BFS(){
	setfillstyle(1,2);
	bar(60,90,100,100);	
}
void Create_DinhThat(){
	setfillstyle(1,15);
	bar(120,50,200,100);
	setcolor(2);
	settextstyle(0,0, 1);
	rectangle(120,50,200,100);
	setcolor(0);
	outtextxy(125,70,"Dinh That");
}
void Create_HL_DinhThat(){
	setfillstyle(1,2);
	bar(120,90,200,100);	
}
void Create_XtoY(){
	setfillstyle(1,15);
	bar(220,50,300,100);
	setcolor(2);
	settextstyle(0,0, 1);
	rectangle(220,50,300,100);
	setcolor(0);
	outtextxy(235,70,"X -> Y");
}
void Create_HL_XtoY(){
	setfillstyle(1,2);
	bar(220,90,300,100);	
}
void Create_TopoSort(){
	setfillstyle(1,15);
	bar(20,120,100,170);
	setcolor(2);
	rectangle(20,120,100,170);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(25,140,"Topo Sort");
}
void Create_HL_TopoSort(){
	setfillstyle(1,2);
	bar(20,160,100,170);	
}
void Create_TPLT(){
	setfillstyle(1,15);
	bar(120,120,200,170);
	setcolor(2);
	rectangle(120,120,200,170);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(145,140,"TPLT");
}
void Create_HL_TPLT(){
	setfillstyle(1,2);
	bar(120,160,200,170);	
}
void Create_Hamilton(){
	setfillstyle(1,15);
	bar(220,120,300,170);
	setcolor(2);
	rectangle(220,120,300,170);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(230,140,"HAMILTON");
}
void Create_HL_Hamilton(){
	setfillstyle(1,2);
	bar(220,160,300,170);	
}
void Create_DinhTru(){
	setfillstyle(1,15);
	bar(20,190,100,240);
	setcolor(2);
	rectangle(20,190,100,240);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(25,210,"Dinh Tru");
}
void Create_HL_DinhTru(){
	setfillstyle(1,2);
	bar(20,230,100,240);	
}
void Create_Euler(){
	setfillstyle(1,15);
	bar(120,190,200,240);
	setcolor(2);
	rectangle(120,190,200,240);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(140,210,"EULER");
}
void Create_HL_Euler(){
	setfillstyle(1,2);
	bar(120,230,200,240);	
}
void Create_CanhCau(){
	setfillstyle(1,15);
	bar(220,190,300,240);
	setcolor(2);
	rectangle(220,190,300,240);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(230,210,"Canh Cau");
}
void Create_HL_CanhCau(){
	setfillstyle(1,2);
	bar(220,230,300,240);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Create_Node(int x,int y,int color){
	setlinestyle(0, 0, 1);
	setcolor(color);
	setfillstyle(1,color);
	FOR(i,0,1)circle(x,y,20-i);	
}

void Create_Triangle(int x1, int y1, int x2, int y2, int color){
	setfillstyle(1, color);
	int a[8];
	a[0] = x1 + y2 - y1;
	a[1] = y1 + x1 - x2;
	a[2] = x1 - y2 + y1;
	a[3] = y1 - x1 + x2;
	a[4] = x2; a[5] = y2;
	a[6] = a[0]; a[7] = a[1];
	setcolor(color);
	fillpoly(4,a);
}
void Create_Arrow(int x1, int y1, int x2, int y2,int s, int color){
	// BK = Ban kinh node
	int BK = 20;
	float corner = atan(float(abs(y1 - y2)) / abs(x1 - x2));
	float Ry = BK * sin(corner);
	float Rx = BK * cos(corner);
	int x11 = x1 + Rx;
	int y11 = y1 + Ry;
	int x22 = x2 - Rx;
	int y22 = y2 - Ry;
	if (x1 > x2){
		x11 = x1 - Rx;
		x22 = x2 + Rx;
	}
	if (y1 > y2){
		y11 = y1 - Ry;
		y22 = y2 + Ry;
	}
	//setlinestyle(0, 1, 2);
	setlinestyle(0, 0, 1);
	setcolor(color);
	line(x11, y11, x22, y22);
	int ox=(x1+x2)/2,oy=(y1+y2)/2;//d=length_int(s);
	char xau[10];
	itoa(s,xau,10);
	settextstyle(8,0,1);
	setcolor(4);
	outtextxy(ox-10,oy,xau);
	Create_Triangle(2 * x22 - (x2 + x22) / 2, 2 * y22 -(y22 + y2) / 2, x22, y22, color);
	
}
void drawCurvedLine2(int x1, int y1, int x2, int y2, int color, float w)
{
	int BK=20;
	setcolor(color);
	float xO = (x1 + x2) / 2 + (y1 - y2) / M_SQRT2; // or +
	float yO = (y1 + y2) / 2 + (x2 - x1) / M_SQRT2; // or +
	float r = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
	float d = sqrt(pow(x1 - xO, 2) + pow(y1 - yO, 2));
	float a = (pow(r, 2) - pow(BK, 2) + pow(d ,2)) / (2 * d);
	float h = sqrt(r * r - a * a);								//					 
	float tmpx1 = xO + a * (x1 - xO) / d;						//					   xT		  
	float tmpx2 = xO + a * (x2 - xO) / d;						//        *  * x3             x4*  *
	float tmpy1 = yO + a * (y1 - yO) / d;						//     *        *            *        *
	float tmpy2 = yO + a * (y2 - yO) / d;						//    *    x1    *          *     x2   *
	int x3 = tmpx1 - h* (y1 - yO) / d;   // -h					//    *          *          *          *
	int x4 = tmpx2 + h* (y2 - yO) / d;   // +h					//     *        *            *        *
	int y3 = tmpy1 + h * (x1 - xO) / d;  // 					//        *  *                  *  *
	int y4 = tmpy2 - h * (x2 - xO) / d;  // 					//				 	   xO          
	float stangle, endangle;									//					 
	float angle1 = float(x1 - xO) / r;
	float angle2 = 1 - float(pow(BK, 2)) / (2 * pow(r, 2));
	if (angle1 < -1 || angle1 > 1) angle1 = int(angle1);
	if (angle2 < -1 || angle2 > 1) angle2 = int(angle2);
	angle1 = acos(angle1) * 180 / M_PI;
	angle2 = acos(angle2) * 180 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	stangle = angle1 + angle2;
	angle1 = acos(1 - pow(sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)), 2) / (2 * pow(r, 2)));
	angle1 = angle1 * 180 / M_PI;
	stangle = stangle - angle1 - 2 * angle2;
	endangle = stangle + angle1;
	float theta = atan2((y1 + y2) / 2 - yO, (x1 + x2) / 2 - xO);
	float xT = xO + r * cos(theta);
	float yT = yO + r * sin(theta);
	setcolor(color);
	setlinestyle(0, 0, 1);
	arc(xO, yO, stangle, endangle, r);
	Create_Triangle(2 * x4 - (x2 + x4) / 2, 2 * y4 - (y2 + y4) / 2, x4, y4, color); // FINALY
	setcolor(4);
	int t=10;//length_int(w);
	char s[t];
	itoa(w,s,10);
	if(w==0)outtextxy(xT, yT,"0");else outtextxy(xT, yT,s);	
}
void Create_CurvedLine(int x1, int y1, int x2, int y2, int w,int color)
{	int BK=20;
	setcolor(color);
	float xO = (x1 + x2) / 2 + (y1 - y2) / -M_SQRT2; 
	float yO = (y1 + y2) / 2 + (x2 - x1) / -M_SQRT2; 
	float r = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
	float d = sqrt(pow(x1 - xO, 2) + pow(y1 - yO, 2));
	float a = (pow(r, 2) - pow(BK, 2) + pow(d ,2)) / (2 * d);
	float h = sqrt(r * r - a * a);												 
	float tmpx1 = xO + a * (x1 - xO) / d;					
	float tmpx2 = xO + a * (x2 - xO) / d;				
	float tmpy1 = yO + a * (y1 - yO) / d;			
	float tmpy2 = yO + a * (y2 - yO) / d;					
	int x3 = tmpx1 + h* (y1 - yO) / d;   					
	int x4 = tmpx2 - h* (y2 - yO) / d;   			
	int y3 = tmpy1 - h * (x1 - xO) / d;  				
	int y4 = tmpy2 + h * (x2 - xO) / d;  					          
	float stangle, endangle;												 
	float angle1 = float(x1 - xO) / r;
	float angle2 = 1 - float(pow(BK, 2)) / (2 * pow(r, 2));
	if (angle1 < -1 || angle1 > 1) angle1 = int(angle1);
	if (angle2 < -1 || angle2 > 1) angle2 = int(angle2);
	angle1 = acos(angle1) * 180 / M_PI;
	angle2 = acos(angle2) * 180 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	stangle = angle1 + angle2;
	angle1 = acos(1 - pow(sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)), 2) / (2 * pow(r, 2)));
	angle1 = angle1 * 180 / M_PI;
	endangle = stangle + angle1; 
	float theta = atan2((y1 + y2) / 2 - yO, (x1 + x2) / 2 - xO);
	float xT = xO + r * cos(theta);
	float yT = yO + r * sin(theta);
	if (xT <= 340 || xT >= getmaxx()-40 || yT <= 30 || yT >= 500-20)
		return drawCurvedLine2(x1, y1, x2, y2, color, w);
	//setlinestyle(0, 1, 2);
	setlinestyle(0, 0, 1);
	arc(xO, yO, stangle, endangle, r);
	Create_Triangle(2 * x4 - (x2 + x4) / 2, 2 * y4 - (y2 + y4) / 2, x4, y4, color); 
	setcolor(4);
	int t=10;//length_int(w);
	char s[t];
	itoa(w,s,10);
	if(w==0)outtextxy(xT, yT,"0");else outtextxy(xT, yT,s);	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Create_New(){
	setfillstyle(1,15);
	bar(340,505,380,545);
	setcolor(2);
	FOR(i,0,1)	circle(360,525,20-i);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(348,520,"NEW");
}
void Create_HL_New(){
	setcolor(2);
	FOR(i,0,1)	circle(360,525,20-i);
	setfillstyle(1,2);
	floodfill(360,525,2);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(348,520,"NEW");
}
void Create_Open(){
	setfillstyle(1,15);
	bar(400,505,440,545);
	setcolor(2);
	FOR(i,0,1)	circle(420,525,20-i);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(404,520,"OPEN");
}
void Create_HL_Open(){
	setcolor(2);
	FOR(i,0,1)	circle(420,525,20-i);
	setfillstyle(1,2);
	floodfill(420,525,2);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(404,520,"OPEN");
}
void Create_Save(){
	setfillstyle(1,15);
	bar(460,505,500,545);
	setcolor(2);
	FOR(i,0,1)	circle(480,525,20-i);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(464,520,"SAVE");
}
void Create_HL_Save(){
	setcolor(2);
	FOR(i,0,1)	circle(480,525,20-i);
	setfillstyle(1,2);
	floodfill(480,525,2);
	setcolor(0);
	settextstyle(0,0, 1);
	outtextxy(464,520,"SAVE");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Create_Add(){
	setfillstyle(1,15);
	bar(540,505,580,545);
	setcolor(2);
	FOR(i,0,1)	circle(560,525,20-i);
	setcolor(0);
	settextstyle(0,0,3);
	outtextxy(548,512,"+");
}
void Create_HL_Add(){
	setcolor(2);
	FOR(i,0,1)	circle(560,525,20-i);
	setfillstyle(1,2);
	floodfill(560,525,2);
	setcolor(0);
	settextstyle(0,0,3);
	outtextxy(548,512,"+");
}
void Create_Del(){
	setfillstyle(1,15);
	bar(600,505,640,545);
	setcolor(2);
	FOR(i,0,1)	circle(620,525,20-i);
	setcolor(0);
	settextstyle(0,0,3);
	outtextxy(608,512,"-");
}
void Create_HL_Del(){
	setcolor(2);
	FOR(i,0,1)	circle(620,525,20-i);
	setfillstyle(1,2);
	floodfill(620,525,2);
	setcolor(0);
	settextstyle(0,0,3);
	outtextxy(608,512,"-");
}
void Create_Link(){
	setfillstyle(1,15);
	bar(660,505,700,545);
	setcolor(2);
	FOR(i,0,1)	circle(680,525,20-i);
	setcolor(0);
	settextstyle(0,0,3);
	outtextxy(668,512,"/");
}
void Create_HL_Link(){
	setcolor(2);
	FOR(i,0,1)	circle(680,525,20-i);
	setfillstyle(1,2);
	floodfill(680,525,2);
	setcolor(0);
	settextstyle(0,0,3);
	outtextxy(668,512,"/");
}
void Create_Move(){
	setfillstyle(1,15);
	bar(720,505,760,545);
	setcolor(2);
	FOR(i,0,1)	circle(740,525,20-i);
	setcolor(0);
	settextstyle(0,0,1);
	outtextxy(728,520,"<->");
}
void Create_HL_Move(){
	setcolor(2);
	FOR(i,0,1)	circle(740,525,20-i);
	setfillstyle(1,2);
	floodfill(740,525,2);
	setcolor(0);
	settextstyle(0,0,1);
	outtextxy(728,520,"<->");
}
void Create_Rename(){
	setfillstyle(1,15);
	bar(780,505,820,545);
	setcolor(2);
	FOR(i,0,1)	circle(800,525,20-i);
	setcolor(0);
	////////////////// draw
	setlinestyle(0, 1, 2);
	line(804,515,810,521); 
	line(804,515,794,525);
	line(810,521,800,531);
	line(794,525,800,531);
	line(792,533,800,531);
	line(792,533,794,525);	
}
void Create_HL_Rename() {
	setfillstyle(1,15);
	bar(780,505,820,545);
	setcolor(2);
	FOR(i,0,1)	circle(800,525,20-i);
	setfillstyle(1,2);
	floodfill(800,525,2);
	setfillstyle(1,15);
	bar(787,512,813,538);
	
	setcolor(0);
	
	setlinestyle(0, 1, 2);
	line(804,515,810,521); 
	line(804,515,794,525);
	line(810,521,800,531);
	line(794,525,800,531);
	line(792,533,800,531);
	line(792,533,794,525);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Create_ToolBar(){
	Create_New();
	Create_Open();
	Create_Save();
	setcolor(2);
	FOR(i,0,3) line(518+i,505,518+i,545);
	Create_Add();
	Create_Del();
	Create_Link(); 	
	Create_Move();
	Create_Rename();

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Create_Mh_Work(){
	setfillstyle(1,15);
	bar(320,10,getmaxx()-10,500);
	setcolor(2);
	FOR(i,0,1) rectangle(320+i,10+i,getmaxx()-10-i,500-i);	
}
void Create_Mh_Algo(){
	setcolor(2);
	FOR(i,0,1) rectangle(10+i,10+i,310-i,250-i);
	FOR(i,0,1) line(11,40+i,310,40+i);
	setcolor(4);
	settextstyle(0,0,2);
	outtextxy(90,20,"ALGORITHM");
	settextstyle(0,0,1);
	Create_DFS_BFS();
	Create_DinhThat();
	Create_XtoY();
	Create_TopoSort();
	Create_TPLT();
	Create_Hamilton();
	Create_DinhTru();
	Create_Euler();
	Create_CanhCau();
}
void Create_Mh_AlTo(){
	Create_Mh_Algo();
	Create_ToolBar();
}
void Create_Mh_MaTran(){
	setfillstyle(1,15);
	bar(10,260,310,550);
	setcolor(2);
	FOR(i,0,1) rectangle(10+i,260+i,310-i,550-i);
	FOR(i,0,1) line(10,290-i,310,290-i);
	settextstyle(0,0,2);
	setcolor(4);
	outtextxy(30,270,"MA TRAN TRONG SO");
	settextstyle(0,0,1);
}
void Create_Mh_NoiDung(){
	setfillstyle(1,15);
	bar(10,560,getmaxx()-10,getmaxy()-10);
	setcolor(2);
	FOR(i,0,1) rectangle(10+i,560+i,getmaxx()-10-i,getmaxy()-10-i);
}

void Create_Mh_Start(){
	initwindow(1000, 720);
	int x,y;
	x=getmaxx();y=getmaxy();			// init window graphics
	setbkcolor(15);					// set background
   	cleardevice();
   	setcolor(2);
   	for(int i=0;i<=4;i++) rectangle(0+i,0+i,x-i,y-i)	;					
	
	Create_Mh_Algo();
	Create_Mh_Work();
	Create_ToolBar();
	Create_Mh_MaTran();
	Create_Mh_NoiDung();
	
	setcolor(4);
	settextstyle(0,0,2);
	outtextxy(20,570,"GUIDE:")	;
	//settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	settextstyle(8, HORIZ_DIR, 1);
	setcolor(1);
	char a[10][150]={
		"(+)  : Them dinh ","(-)  : Xoa dinh","(/)  : Tao cung va chinh sua","(<->): Di chuyen dinh","(pen): Doi ten dinh",
		"(NEW) : Tao do thi moi","(OPEN): Mo do thi da co","(SAVE): Luu do thi","(ESC) : Thoat chuong trinh"
	};
	FOR(i,0,4){
		outtextxy(20,570+20*(i+1),a[i]);
	}
	FOR(i,5,8){
		outtextxy(400,570+20*(i+1-5),a[i]);
	}
}





















//
