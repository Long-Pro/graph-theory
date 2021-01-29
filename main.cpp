#include<graphics.h>
#include "lib.h"
#include "queue.h"
#include "stack.h"
#include<iostream>
//#include<cstring>
#include<fstream>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
// ---------------------------------------------------------------------------
//                          const valriable
// ---------------------------------------------------------------------------
const int MAX_IN=1000;
const int TIME=1000;
const int INT_MAX_N=1e8;
const int NODE_MAX=15;
// ---------------------------------------------------------------------------
//                          DOTHI dt
// ---------------------------------------------------------------------------
struct Node{
	int x,y;
	char name[2];
};
struct DoThi{
	Node *node;
	int stt_Node;
	int **MT;	
	/*		------method------		*/
	void delete_Data(){
		delete [] node;
		FOR(i,0,stt_Node) delete[] MT[i];
		delete[] MT;
	}
	void init_Node(int t,int ind){
		if(t==1){// TANG NODE LEN 1
			Node *node2=new Node[stt_Node+1];
			FOR(i,0,stt_Node-1) node2[i]=node[i];
			delete[] node;
			node=node2;
		}
		if(t==-1){//GIAM NODE XUONG 1
			Node *node2=new Node[stt_Node+1];
			FOR(i,0,ind-1) node2[i]=node[i];
			FOR(i,ind,stt_Node) node2[i]=node[i+1];
			delete[] node;
			node=node2;
		}
		if(t==0){// CAP NHAT NODE KHI OPEN FILE
			Node *node2=new Node[stt_Node+1];
			
			delete[] node;
			node=node2;
		}
	}
	void reset_MT(int **MT1){
		FOR(i,0,stt_Node)
			FOR(j,0,stt_Node) 			
				MT1[i][j]=0;
	}
	void init_MT(int t,int ind){
		if(t==1){//TANG MT LEN 1
			int **MT2=new int *[stt_Node+1];
			FOR(i,0,stt_Node) MT2[i]=new int[stt_Node+1];
			reset_MT(MT2);
			FOR(i,0,stt_Node-1)
				FOR(j,0,stt_Node-1) 
					MT2[i][j]=MT[i][j];
				
			FOR(i,0,stt_Node-1) delete[] MT[i];
			delete[] MT;
			MT=MT2;
		}
		if(t==-1){//GIAM MT DI 1
			int **MT2=new int *[stt_Node+1];
			FOR(i,0,stt_Node) MT2[i]=new int[stt_Node+1];
			
			FOR(j,0,stt_Node+1) {
					MT[ind][j]=0;
					MT[j][ind]=0;
			}
			FOR(l1,0,stt_Node+1) FOR(l2,0,stt_Node+1) if(MT[l1][l2]!=0){
				int t1,t2;
				t1=(l1>ind?l1-1:l1);
				t2=(l2>ind?l2-1:l2);
				if(l1>ind||l2>ind){
					MT[t1][t2]=MT[l1][l2];
					MT[l1][l2]=0;
				}
			}
			
			reset_MT(MT2);
			FOR(i,0,stt_Node)
				FOR(j,0,stt_Node) 
					MT2[i][j]=MT[i][j];
			FOR(i,0,stt_Node+1) delete[] MT[i];
			delete[] MT;
			MT=MT2;
		}
		if(t==0){//KHOI TAO LAI MT KHI OPEN FILE
			FOR(i,0,ind) delete[] MT[i];
			delete[] MT;
			int **MT2=new int *[stt_Node+1];
			FOR(i,0,stt_Node) MT2[i]=new int[stt_Node+1];
			reset_MT(MT2);
			MT=MT2;
		}
	}
	~DoThi(){
		delete [] node;
		FOR(i,0,stt_Node) delete[] MT[i];
		delete[] MT;
	}
	
} dt;
// ---------------------------------------------------------------------------
//                          Variables
// ---------------------------------------------------------------------------
int x, y,tam,dem=0,tam1=-1,tam2=-1;
bool working=false;
char tenfile[50];
bool kt_Del=false,kt_Add=false,kt_Move=false,kt_Link=false,kt_Rename=false,kt_New=false,kt_Save=false,kt_Open=false;
bool kt_DFS=false,kt_BFS=false,kt_DThat=false,kt_XY=false,kt_TPLT=false,kt_Ham=false,kt_Dtru=false,kt_Eurle=false,kt_CCau=false;

// ---------------------------------------------------------------------------
//                          Algogrimth
// ---------------------------------------------------------------------------
void DFS(int);
void BFS(int);
int TPLT(int **,bool);
void Dinh_That(int,int);
void Dinh_Tru();
void Canh_Cau();
void Hamilton(int);
void Euler(int);
void Topo_Sort();
void Dijkstra(int, int);

// ---------------------------------------------------------------------------
//                          I/O File
// ---------------------------------------------------------------------------
void Open();
void Save();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_Word(int font,int color){
	settextstyle(font,0,1);
	setcolor(color);
}
bool check_Word(char s){
	if (int(s)==0){
		s=getch();
		return true;
	}
	if(!(('0'<=s&&s<='9')||('a'<=s&&s<='z')||('A'<=s&&s<='Z')||s=='_'||s==13||s==8)) return true;
	return false;
}
void set_TF(bool &a){
	kt_Del=false;kt_Add=false;kt_Move=false;kt_Link=false;kt_Rename=false;
	kt_DFS=false;kt_BFS=false;kt_DThat=false;kt_XY=false;kt_TPLT=false;kt_Ham=false;kt_Dtru=false;kt_Eurle=false;kt_CCau=false;
	a=true;
}
void set_F(){
	kt_Del=false;kt_Add=false;kt_Move=false;kt_Link=false;kt_Rename=false;
	kt_DFS=false;kt_BFS=false;kt_DThat=false;kt_XY=false;kt_TPLT=false;kt_Ham=false;kt_Dtru=false;kt_Eurle=false;kt_CCau=false;
}


void Load_Node(){//////////////////////////																									lOAD NODE
	Create_Mh_Work();
	FOR(i,0,dt.stt_Node)  {
		Create_Node(dt.node[i].x,dt.node[i].y,1);
		set_Word(8,4);
		outtextxy(dt.node[i].x-11,dt.node[i].y-10,dt.node[i].name);
	}
	FOR(i,0,dt.stt_Node)FOR(j,0,dt.stt_Node){
		if(dt.MT[i][j]!=0&&dt.MT[j][i]==0)          	Create_Arrow(dt.node[i].x,dt.node[i].y,dt.node[j].x,dt.node[j].y,dt.MT[i][j],4);
		if(dt.MT[i][j]!=0&&dt.MT[j][i]!=0&&i<=j)   	    Create_Arrow(dt.node[i].x,dt.node[i].y,dt.node[j].x,dt.node[j].y,dt.MT[i][j],4);
		if(dt.MT[i][j]!=0&&dt.MT[j][i]!=0&&i>j) 		Create_CurvedLine(dt.node[i].x,dt.node[i].y,dt.node[j].x,dt.node[j].y,dt.MT[i][j],4);		
	}	
}
void Load_MT(){//////////////////////////																									lOAD MA TRAN
	Create_Mh_MaTran();
	if(dt.stt_Node>=0){
		setcolor(4);
		//set_Word(0,4);
		int b=min(10,dt.stt_Node);
		FOR(i,0,b)
			FOR(j,0,b)
				if(dt.MT[i][j]!=0){
					char a[10];
					itoa(dt.MT[i][j],a,10);
					outtextxy(35+25*j+1,320+20*i+3,a);
				}
		FOR(i,0,b)	 {
			setcolor(4);
			outtextxy(35+25*i+3,300+3,dt.node[i].name);	
		}
		int a=min(dt.stt_Node+1,11);
		FOR(i,0,a){
			setcolor(2);
			line(35+25*i,300,35+25*i,300+20*(a+1));
		}
		FOR(i,0,b){
			setcolor(4);
			outtextxy(15+1,320+20*i+3,dt.node[i].name);
		}
		FOR(i,0,a)	 {
			setcolor(2);
			line(15,320+20*i,15+25*(a+1)-5,320+20*i);
		}	
	}	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				SAVE FILE
void updateChar(int i, char s[]){
	for (;i<50;i++)	s[i]='\0';
}
void reset_tenfile(char tenfile[]){
	FOR(i,0,50) tenfile[i]='\0';
}
void Link_File(char linkFile[], char fileName[]){
	strcpy (linkFile,"./saves/");
	strcat (linkFile,fileName);
	strcat (linkFile,".graph");
}
void Save_DoThi(char fileName[]){
	char linkFile[100];
	Link_File(linkFile,fileName);
	ofstream saveFile;
	saveFile.open(linkFile,ios::out|ios::trunc);
	saveFile<<dt.stt_Node<<"\n";
	FOR(i,0,dt.stt_Node){
		saveFile<<dt.node[i].name<<" "<<dt.node[i].x<<" "<<dt.node[i].y;
		saveFile<<"\n";
		
	}
	FOR(i,0,dt.stt_Node){
		FOR(j,0,dt.stt_Node){
				saveFile<<dt.MT[i][j]<<" ";
		}
		saveFile<<"\n";
	}
	saveFile.close();
}

void Save(){
	Create_Mh_NoiDung();
	set_Word(8,1);
	outtextxy(20,570,"Nhap ten file (Do dai ten file <=30): ")	;
	set_Word(8,4);
	fflush(stdin);
	char s[50];s[50]='\0';
	reset_tenfile(tenfile);
	int d=0;
	while(true){
		s[d]=getch();
		if(check_Word(s[d])) continue;
		if(d==30){
			if(s[d]!=13&&s[d]!=8){
				s[29]=s[30];
				d--;
				goto longdz1111;
			} 
		}
		if(s[d]==13){
			if(d==0) goto longdz11;
			FOR(i,0,50) tenfile[i]='\0';	
			FOR(i,0,d-1){
				tenfile[i]=s[i];tenfile[d]='\0';
			} 	
			Create_Mh_NoiDung();		
			set_Word(8,1);
			outtextxy(20,570,"Da luu file")	;
			delay(1000);	
			Create_Mh_NoiDung();
			break;
		}
		else if(s[d]==8){
			longdz11:
			d--;
			Create_Mh_NoiDung();
			set_Word(8,1);
			outtextxy(20,570,"Nhap ten file (Do dai ten file <=30): ")	;
			set_Word(8,4);
			updateChar(d,s);
			outtextxy(20,590,s  );	
			if(d==-1) d=0;
			continue;
		}
		else {
			longdz1111:
			updateChar(d+1,s);
			outtextxy(20,590,s);
		}						
		d++;
	}	
	kt_Save=true;
	Save_DoThi(tenfile);	
}
void Save2(){
	Save_DoThi(tenfile);
	Create_Mh_NoiDung();
	set_Word(8,1);
	outtextxy(20,570,"Da luu file")	;	
	delay(TIME);
	Create_Mh_NoiDung();
}
//////////////////////////////////////////////////////////////																			OPEN FILE
void Open_DoThi(char fileName[]){

	Create_Mh_NoiDung();
	//////////////
	char linkFile[100];
	Link_File(linkFile,fileName);
	ifstream openFile;
	openFile.open(linkFile,ios::in);
	if(!openFile.good()){
		set_Word(8,1);
		outtextxy(20,570,"File khong ton tai");
		delay(1000);
		kt_Save=false;
		Create_Mh_AlTo(); 
		return ;
	}
	////////////
	int t=dt.stt_Node;
	//////////
	openFile>>dt.stt_Node;
	dt.init_Node(0,0);
	dt.init_MT(0,t);
	FOR(i,0,dt.stt_Node) FOR(j,0,dt.stt_Node) dt.MT[i][j]=0;
	FOR(i,0,dt.stt_Node){
		openFile>>dt.node[i].name>>dt.node[i].x>>dt.node[i].y;
	}
	FOR(i,0,dt.stt_Node){
		FOR(j,0,dt.stt_Node){
			openFile>>dt.MT[i][j];
		}
	}
	openFile.close();
	Load_Node();
}
void Open(){
	Create_Mh_NoiDung();
	set_Word(8,1);
	FOR(i,0,50) tenfile[i]='\0';
	outtextxy(20,570,"Nhap ten file (Do dai ten file <=30): ")	;
	set_Word(8,4);
	char s[50];s[50]='\0';FOR(i,0,50) s[i]='\0';
	int d=0;
	while(true){
		s[d]=getch();
		if(check_Word(s[d])) continue;
		if(d==30){
			if(s[d]!=13&&s[d]!=8){
				s[29]=s[30];
				d--;
				goto longdz111;
			} 
		}
		if(s[d]==13){	
		
			FOR(i,0,50) tenfile[i]='\0';
			FOR(i,0,d-1) tenfile[i]=s[i];
			Create_Mh_NoiDung();	
			break;
		}
		else if(s[d]==8){
			d--;
			Create_Mh_NoiDung();
			set_Word(8,1);
			outtextxy(20,570,"Nhap ten file (Do dai ten file <=30): ")	;
			set_Word(8,4);
			updateChar(d,s);
			outtextxy(20,590,s  );	
			if(d==-1) d=0;
			continue;
		}
		else{
			longdz111:
			updateChar(d+1,s);
			outtextxy(20,590,s  );
		} 						
		d++;
	}
	kt_Save=true;
	working=true;
	Open_DoThi(tenfile);	
}
void clearMouse(){
	clearmouseclick(WM_LBUTTONDOWN);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Del_Node(int i){
	setcolor(15);
	setfillstyle(1,15);
	pieslice(dt.node[i].x,dt.node[i].y,0,360,20);
}
void draw_Node(int i,int color){
	setcolor(color);
	setfillstyle(1,color);
	pieslice(dt.node[i].x,dt.node[i].y,0,360,20);
	setbkcolor(color);
	set_Word(8,4);
	
	outtextxy(dt.node[i].x-11,dt.node[i].y-10,dt.node[i].name);
	setbkcolor(15);
	setcolor(1);
	circle(dt.node[i].x,dt.node[i].y,20);
}
void Show_Link(int i,int j){ //i->j
	if(dt.MT[i][j]!=0&&dt.MT[j][i]==0)          Create_Arrow(dt.node[i].x,dt.node[i].y,dt.node[j].x,dt.node[j].y,dt.MT[i][j],0);
	else if(dt.MT[i][j]!=0&&dt.MT[j][i]!=0&&i<=j)   	   Create_Arrow(dt.node[i].x,dt.node[i].y,dt.node[j].x,dt.node[j].y,dt.MT[i][j],0);
	else if(dt.MT[i][j]!=0&&dt.MT[j][i]!=0&&i>j) 	Create_CurvedLine(dt.node[i].x,dt.node[i].y,dt.node[j].x,dt.node[j].y,dt.MT[i][j],0);		
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DFS(int u){// O(n.n+max(n,m)) n so dinh m so canh																							DFS												
	if(dt.stt_Node==-1) return;
	///init
	// tao danh sach ke
	Queue ke[dt.stt_Node+1];
	FOR(i,0,dt.stt_Node)
		FOR(j,0,dt.stt_Node)
			if (dt.MT[i][j]>0)
				ke[i].push(j);
	//
	bool check[dt.stt_Node+1];
	Stack stack;
	//khoi tao gia tri cho check
	FOR(i,0,dt.stt_Node){
		check[i]=false;
	}	
	stack.push(u);
	check[u]=true;
	int d=1;
	////draw u
	Create_Mh_NoiDung();
	set_Word(8,1);
	outtextxy(20,570,"DFS :");
	set_Word(8,4);
	outtextxy(100,570,dt.node[u].name);
	Del_Node(u);
	draw_Node(u,14);
	delay(TIME);
	// dfs theo danh sach ke
	while(!stack.empty()){
		int s;
		stack.pop(s);

		while(!ke[s].empty()){ // neu ke[s] khac rong
			int i ; ke[s].pop(i);
			if(!check[i]){
				stack.push(s); // dua s vao lai stack
				stack.push(i); // dua i vao stack
				check[i]=true;
				// draw node
				set_Word(8,4);
				outtextxy(100+50*d,570,dt.node[i].name);
				d++;
				Show_Link(s,i);
				delay(TIME);
				Del_Node(i);
				draw_Node(i,14);
				delay(TIME);
				//
				break;
			}
		}
	}
	
}
void BFS(int u){								//																								BFS
	Queue queue;
	int *back= new int[NODE_MAX+2];
	bool check[dt.stt_Node+1];
	FOR(i,0,dt.stt_Node){
		check[i]=false;
	}	
	queue.push(u);
	check[u]=true;
	int d=0;
	Create_Mh_NoiDung();
	set_Word(8,1);
	outtextxy(20,570,"BFS :");
	while(!queue.empty()){
		int s;
		queue.pop(s);
		//////////// in ra man hinh
		set_Word(8,4);
		outtextxy(100+50*d,570,dt.node[s].name);
		d++;
		// ve dinh duyet
		if(s==u){
			Del_Node(u);
			draw_Node(u,14);
			delay(TIME);
		}else{
			Show_Link(back[s],s);
			delay(TIME);
			Del_Node(s);
			draw_Node(s,14);
			delay(TIME);
		}
		////////
		FOR(i,0,dt.stt_Node){
			if (!check[i]&&dt.MT[s][i]>0){
				queue.push(i);
				check[i]=true;
				back[i]=s;
			}
		}
	}
	delete[] back;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// init MT
int** init_tmp(){
	int **tmp= new int*[dt.stt_Node+1];
	FOR(i,0,dt.stt_Node)
		tmp[i]=new int[dt.stt_Node+1];
	return tmp;
}
/////copy MT
void Copy_MT(int **tmp){
	FOR(i,0,dt.stt_Node){
		FOR(j,0,dt.stt_Node){
			dt.MT[i][j]>0?tmp[i][j]=1:tmp[i][j]=0;
		}
	}
}
///////////////Co lap dinh
void Co_Lap_Dinh(int **tmp,int pos){
	//
	Copy_MT(tmp);
	FOR(i,0,dt.stt_Node){
		tmp[pos][i]=0;
		tmp[i][pos]=0;
	}
}
//xoa canh 
void Xoa_Canh(int **tmp,int u,int v){
	Copy_MT(tmp);
	tmp[u][v]=0;
}
////////////																																	LIEN THONG	
int *TPLT_Num,*TPLT_Low,cnt,TPLT_Count;
bool *TPLT_Connect;
Queue TPLT_a[NODE_MAX+2];
Stack st;
void TPLT_dfs(int u){
	TPLT_Low[u]=TPLT_Num[u]=cnt++;//gan thoi gian, dinh danh
	st.push(u);//
	TPLT_Connect[u]=true;
	while(!TPLT_a[u].empty()){
		int v;
		TPLT_a[u].pop(v);
		if (TPLT_Num[v]==-1) TPLT_dfs(v);// duyet dfs
		if (TPLT_Connect[v])// neu v con trong ngan xep -> cap nhap lai dinh danh TPLT_Low[u]
			TPLT_Low[u]=min(TPLT_Low[u],TPLT_Low[v]);
	}
	if (TPLT_Num[u]==TPLT_Low[u]){ // u la goc cua mot thanh phan lien thong manh chua u
		TPLT_Count++;
		// lay cac dinh la thanh phan lien thong manh trong ngan xep ra
		while(!st.empty()){
			int v;
			st.pop(v);
			TPLT_Connect[v]=false;
			if (u==v) break;
		}
	}
}
int TPLT(int **tmp,bool f=true){ 
	////init
	cnt=0;// thoi gian
	TPLT_Count=0; 
	TPLT_Num=new int[NODE_MAX+2];// TPLT_Num[u] danh dau thoi gian diem ma u duoc tham -> Dinh Danh
	TPLT_Low=new int[NODE_MAX+2];// TPLT_Low[u] dinh danh cua w bat ki. co duong di tu u -> w, w thuoc TPLT	
	TPLT_Connect=new bool[NODE_MAX+2];//TPLT_Connect[u] kiem tra dinh u con trong do thi hay khong
	bool check[NODE_MAX+2];
	// tao danh sach ke
	FOR(i,0,dt.stt_Node){
		FOR(j,0,dt.stt_Node){
			if (tmp[i][j]>0){
				TPLT_a[i].push(j);
			}
		}
	}
	// reset gia tri
	FOR(i,0,NODE_MAX+1){
		TPLT_Num[i]=-1;
		TPLT_Low[i]=0;
		TPLT_Connect[i]=false;
		check[i]=true;
	}
	///// run 
	FOR(i,0,dt.stt_Node){
		if (TPLT_Num[i]==-1) TPLT_dfs(i);
	}
	/////// In ra man hinh
	int d=-1;
	if (f){
		int Color[]={3,7,9,10,11,14,13,1,2,5,6,8,12,0};
		int sizeColor=sizeof(Color)/sizeof(Color[0]);
		int Color_name=0;
		FOR(i,0,TPLT_Count-1){
			set_Word(8,1);
			d++;
			outtextxy(30+30*d-15,590,"(");d--;
			FOR(j,0,dt.stt_Node){
				if (check[j]){
					FOR(k,j,dt.stt_Node){
						if (TPLT_Low[k]==TPLT_Low[j]){
							//////
							check[k]=false;
							if (TPLT_Count<=sizeColor&&Color_name<sizeColor){
								Del_Node(k);
								draw_Node(k,Color[Color_name]);
							}
							set_Word(8,4);
							d++;
							outtextxy(30+30*d,590,dt.node[k].name);
							/////
						}
					}
					break;
				}
			}
			Color_name++;
			set_Word(8,1);
			d++;
			outtextxy(30+30*d,590,")");
			//d++;
		}
		//Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"So thanh phan lien thong la : ");
		set_Word(8,4);
		char xau[10];
		itoa(TPLT_Count,xau,10);
		outtextxy(350,570,xau);
	}
	/////// clear
	delete[] TPLT_Num;
	delete[] TPLT_Low;
	delete[] TPLT_Connect;
	////
	return TPLT_Count;
}
//////////////																															
bool check_duongdi_LT(int u, int v, int **tmp,bool f=true){ // f=true => check duong di; f=false => check Lien Thong do thi vo huong
	//bfs
	Queue queue;
	bool check[dt.stt_Node+1];
	FOR(i,0,dt.stt_Node){
		check[i]=false;
	}	
	queue.push(u);
	check[u]=true;
	while(!queue.empty()){
		int s;
		queue.pop(s);
		////////
		FOR(i,0,dt.stt_Node){
			if (!check[i]&&tmp[s][i]>0){
				queue.push(i);
				check[i]=true;
				if (v==i&&f)	return true;
			}
		}
	}
	if (!f){
		FOR(i,0,dt.stt_Node)	if (!check[i]) return false;
		return true;
	}
	return false;
}
//																															DINH THAT
void Dinh_That(int u,int v){/// u dinh dau, v la dinh cuoi
///init
	int **tmp=init_tmp();
	int count=0;
	int t=0;
//////	
	Copy_MT(tmp);//copy MT
	if (!check_duongdi_LT(u,v,tmp)){
		//
		////////////delete 

		
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co dinh that giua 2 dinh "); outtextxy(390,570,"->");
		set_Word(8,4);
		outtextxy(360,570,dt.node[u].name);		outtextxy(420,570,dt.node[v].name);
		
		
		FOR(i,0,dt.stt_Node)	delete[] tmp[i];
		delete[] tmp;
		return;
	}
	FOR(i,0,dt.stt_Node){
		if (i!=u&&i!=v){
			Co_Lap_Dinh(tmp,i);
			if (!check_duongdi_LT(u,v,tmp)){
				count++;
				/// draw node
				Del_Node(i);
				draw_Node(i,14);////////////////////
				set_Word(8,4);
				outtextxy(20+50*t,590,dt.node[i].name);
				t++;
			}
		}
			
	}
	if (count == 0 ){
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co dinh that giua 2 dinh "); outtextxy(390,570,"->");
		set_Word(8,4);
		outtextxy(360,570,dt.node[u].name);		outtextxy(420,570,dt.node[v].name);
	}
	////////////delete
	FOR(i,0,dt.stt_Node)	delete[] tmp[i];
	
	delete[] tmp;
}
//////////																																DINH TRU
void Dinh_Tru(){
	//init
	int **tmp=init_tmp();
	Copy_MT(tmp);
	int Min = TPLT(tmp,false),count=0;
	Create_Mh_NoiDung();
	set_Word(8,1);
	/////
	FOR(i,0,dt.stt_Node){
		Co_Lap_Dinh(tmp,i);
		if(TPLT(tmp,false)-1>Min){
			count++;
			/// ve 
			Del_Node(i);
			draw_Node(i,YELLOW);
			set_Word(8,4);
			outtextxy(150+count*50,570,dt.node[i].name);
		}
	}
	//
	
	//
	if(count==0) {
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co dinh tru");
	}else{
		//Create_Mh_NoiDung();
		set_Word(8,4);
		char xau[10];
		itoa(count,xau,10);
		outtextxy(20,570,xau);
		set_Word(8,1);
		
		outtextxy(60,570,"dinh tru :");///////////////////////
	}
	//delete
	FOR(i,0,dt.stt_Node)	delete[] tmp[i];
	delete[] tmp;
}
///////																																				CANH CAU
void Canh_Cau(){
	///init
	int **tmp=init_tmp();
	Copy_MT(tmp);
	int Min=TPLT(tmp,false),count=0;
	///
	FOR(i,0,dt.stt_Node){
		FOR(j,0,dt.stt_Node){
			Xoa_Canh(tmp,i,j);
			if(TPLT(tmp,false)>Min){
				count++;
				Show_Link(i,j);
			}
		}
	}
	//
	if(count==0){
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co canh cau");
	}else{
		Create_Mh_NoiDung();
		set_Word(8,1);
		char s[10];
		itoa(count,s,10);
		outtextxy(20,570,"Do thi co "); set_Word(8,4);outtextxy(150,570,s); set_Word(8,1);outtextxy(200,570," canh cau");
	}
	//delete
	FOR(i,0,dt.stt_Node)	delete[] tmp[i];
	delete[] tmp;
}
////////////																																	HAMILTON
bool *check_Hamilton;
int *CT_Hamilton;
bool kt_ham;
void H_get(){
	Create_Mh_NoiDung();
	Load_Node();
	kt_ham=true;
	// ve ra man hinh nut dau
	set_Word(8,1);
	outtextxy(20,570,"Chu trinh hamilton:");
	set_Word(8,4);
	outtextxy(20,590,dt.node[CT_Hamilton[0]].name);
	Del_Node(CT_Hamilton[0]);
	draw_Node(CT_Hamilton[0],LIGHTGREEN);
	delay(TIME);
	//
	FOR(i,1,dt.stt_Node+1){
//		////draw line
		set_Word(8,1);
		outtextxy(20+i*50-25,590,"->");
		set_Word(8,4);
		outtextxy(20+i*50,590,dt.node[CT_Hamilton[i]].name);
		
		int Fi=CT_Hamilton[i-1],La=CT_Hamilton[i];
		Show_Link(Fi,La);
		delay(TIME/2);
		///draw node
		if (i!=dt.stt_Node+1){
			Del_Node(CT_Hamilton[i]);
			draw_Node(CT_Hamilton[i],YELLOW);
			delay(TIME);
		}
		////////////////
	}
}
void QL_Hamilton(int i){
	FOR(j,0,dt.stt_Node){
		if (dt.MT[CT_Hamilton[i-1]][j]>0&&!kt_ham){
			if (i==dt.stt_Node+1&&j==CT_Hamilton[0]){
				CT_Hamilton[i]=j;
				H_get();
				delay(TIME);
			}else if(check_Hamilton[j]==true){
				CT_Hamilton[i]=j;
				check_Hamilton[j]=false;
				QL_Hamilton(i+1);
				check_Hamilton[j]=true;
			}
		}
	}
}
void Hamilton(int u){
	//init
	check_Hamilton=new bool[dt.stt_Node+1];//
	CT_Hamilton=new int[dt.stt_Node+2];
	//
	kt_ham=false;				
	FOR(j,0,dt.stt_Node)	
		check_Hamilton[j]=true;	
	
	CT_Hamilton[0]=u;			
	check_Hamilton[u]=false;
	QL_Hamilton(1);
	if (!kt_ham) {
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co chu trinh Hamilton");
	}
	delete[] check_Hamilton;
	delete[] CT_Hamilton;
}
///////////////////																																	EULER
bool kiemtra_LT(int **tmp){
	Copy_MT(tmp);
	FOR(i,0,dt.stt_Node){
		FOR(j,0,dt.stt_Node){
			if (tmp[i][j]>0){
				tmp[i][j]=1;
				tmp[j][i]=1;
			}
		}
	}
	if (check_duongdi_LT(0,-1,tmp,false)) return true;
	return false;
	
}
bool kiemtra_deg(int **tmp){
	Copy_MT(tmp);
	int deg1=0,deg2=0;
	FOR(i,0,dt.stt_Node){
		deg1=0;deg2=0;
		FOR(j,0,dt.stt_Node){
			deg1+=tmp[i][j];
			deg2+=tmp[j][i];
		}
		if (deg1!=deg2)	return false;
	}
	return true;
}
void EulerCycle(int **tmp,int u){
	//init
	// tao danh sach ke
	Queue ke[dt.stt_Node+1];
	FOR(i,0,dt.stt_Node)FOR(j,0,dt.stt_Node)
		if (tmp[i][j]>0) ke[i].push(j);
	int back=u;
	///
	Stack stack,CE;
	stack.push(u);
	while(!stack.empty()){
		int s=stack.get();
		if (!ke[s].empty()){
			int t;
			ke[s].pop(t);// loai bo canh khoi E
			stack.push(t);
		}
		else{
			stack.pop(s);
			CE.push(s);
		}
	}
	int stt=0;

	while(!CE.empty()){
		int t;
		CE.pop(t);
		if (stt == 0){
			//draw
			Del_Node(t);
			draw_Node(t,YELLOW);
			//
			Create_Mh_NoiDung();
			set_Word(8,1);
			outtextxy(20,570,"Chu trinh EULER :");
			set_Word(8,4);
			outtextxy(20,590,dt.node[t].name);
		}
		else {	
			///// draw
			Show_Link(back,t);
			set_Word(8,4);
			outtextxy(20+50*stt,590,dt.node[t].name);
			set_Word(8,1);
			outtextxy(20+50*stt-25,590,"->");
			delay(TIME);
		}
		stt++;
		back=t;
	}
}
void Euler(int u){
	////init
	int **tmp=init_tmp();
	////kiem tra
	if (kiemtra_LT(tmp)&&kiemtra_deg(tmp)&&dt.stt_Node>0){
			Load_Node();
			Copy_MT(tmp);
			EulerCycle(tmp,u);
		
	}else {
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co chu trinh Euler");
	}
	/////delete tmp
	FOR(i,0,dt.stt_Node)	delete[] tmp[i];
	delete[] tmp;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 				TOPO
struct topo{
	Queue Q;
	int count;
};
void init_topo(topo G[]){
	///count: so cung toi dinh j
	FOR(j,0,dt.stt_Node){
		G[j].count=0;
		FOR(i,0,dt.stt_Node){
			if (dt.MT[i][j]>0)	G[j].count++;
		}
	}
	FOR(i,0,dt.stt_Node)
		FOR(j,0,dt.stt_Node)
			if (dt.MT[i][j]>0){
				G[i].Q.push(j);
			}
}
void Topo_Sort(){
	topo G[dt.stt_Node+1];
//	Stack run;
	Queue run;
	Queue kq;
	Create_Mh_NoiDung();
	set_Word(8,1);
	outtextxy(20,570,"Thu tu sap xep Topo : ");
	init_topo(G);
	// dua vao stack cac cung k di toi i
	FOR(i,0,dt.stt_Node)
		if(G[i].count==0)
			run.push(i);
	FOR(i,0,dt.stt_Node){
		if (run.empty()){
			Create_Mh_NoiDung();
			set_Word(8,1);
			outtextxy(20,570,"Do thi ton tai chu trinh");
			return;
		}
		int u;
		run.pop(u);
		kq.push(u);
		while(!G[u].Q.empty()){
			int k;
			G[u].Q.pop(k); // u -> k
			G[k].count--;
			if (G[k].count==0){
				run.push(k);
			}
		}
	}
	int t=-1;
	while(!kq.empty()){
		int s;
		t++;
		kq.pop(s);
		Del_Node(s);
		draw_Node(s,YELLOW);
		set_Word(8,4);
		outtextxy(20+50*t,590,dt.node[s].name);
		delay(TIME);
	}
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////					 DIJKSTRA

void Dijkstra(int v, int q){
	///init
	int Cost[dt.stt_Node+1][dt.stt_Node+1];
	int Do_Dai[dt.stt_Node+1];
	int duongdi[dt.stt_Node+1];
	
	bool S[dt.stt_Node+1];//Tap dinh S[i] =fasle: chua duyet, S[i]=true da duyet 
	FOR(i,0,dt.stt_Node) S[i]=false;
	S[v]=true;
	
	int k=1;// so luong s[i]=true
	Do_Dai[v]=0;
	//khoi tao Cost
	FOR(i,0,dt.stt_Node)FOR(j,0,dt.stt_Node)	
		Cost[i][j]=(dt.MT[i][j]>0)?dt.MT[i][j]:INT_MAX_N;
	//khoi tao Do_Dai, duongdi
	FOR(i,0,dt.stt_Node){
		if(!S[i]){
			Do_Dai[i]=Cost[v][i];
			duongdi[i]=v;
		}
	}
	//////run
	while(k<=dt.stt_Node+1){
		// tim u sao cho Do_Dai[u]= min(Do_Dai[index])
		int u=0,minn=INT_MAX_N;
		FOR(i,0,dt.stt_Node){
			if (!S[i]){
				if (minn>Do_Dai[i]){
					minn=Do_Dai[i];
					u=i;
				}
			}
		}

		if (u==q){
			break;
		}
		S[u]=true; 
		k++;
		// cap nhat lai Do_Dai va duongdi
		FOR(i,0,dt.stt_Node){
			if (!S[i]){
				if (Do_Dai[i]>Do_Dai[u]+Cost[u][i]){
					Do_Dai[i]=Do_Dai[u]+Cost[u][i];
					duongdi[i]=u;// u->i
				}
			}
		}
	}
	////In ra man hinh
	if (Do_Dai[q]<INT_MAX_N){
		//Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,610,"Tong trong so :");
		set_Word(8,4);
		char ss[10];
		itoa(Do_Dai[q],ss,10);
		outtextxy(200,610,ss);
	}else{
		Create_Mh_NoiDung();
		set_Word(8,1);
		outtextxy(20,570,"Khong co duong di tu ");  outtextxy(270,570,"->");
		set_Word(8,4);
		outtextxy(250,570,dt.node[v].name);	outtextxy(300,570,dt.node[q].name);
		return;
	}
	Stack st;
	int x=q;
	st.push(q);
	while(x!=v){
		x=duongdi[x];
		st.push(x);
	}
	int back;
	int d=0;// dem, 
	while(!st.empty()){
		int tmp;
		st.pop(tmp);
		/////
		if (d==0){
			back = tmp;
			
			set_Word(8,4);
			outtextxy(20+50*d,590,dt.node[tmp].name);
			Del_Node(tmp);
			draw_Node(tmp,YELLOW);
		}
		else{
			set_Word(8,4);
			outtextxy(20+50*d,590,dt.node[tmp].name);
			set_Word(8,1);
			outtextxy(20+50*d-25,590,"->");
			Show_Link(back,tmp);
			
			delay(TIME);
			
			Del_Node(tmp);
			if(st.empty())
				draw_Node(tmp,YELLOW);
			else 	
				draw_Node(tmp,LIGHTGREEN);

			back=tmp;
			delay(TIME);
		}
		d++;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Start(){
	dt.stt_Node=-1;
	Create_Mh_NoiDung();
	Create_Mh_Algo();
	Create_Mh_MaTran();
	Create_Mh_Work();
	FOR(i,0,50) tenfile[i]='\0';
	kt_Save=false;
	Load_Node();
	Load_MT();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{	
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
	setlinestyle(0, 0, 1);
	working=false;
	Create_Mh_Start();
	dt.stt_Node=-1;
	FOR(i,0,50) tenfile[i]='\0';
	kt_Save=false;
	while(true){
		
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(In_Rec(20,50,60,100,x,y)){//																	DFS
				Create_Mh_AlTo();
				Create_HL_DFS();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}
				
				set_TF(kt_DFS);
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570,"Click vao dinh bat ki de duyet DFS");				
			}
			if(In_Rec(60,50,100,100,x,y)){//																BFS
				Create_Mh_AlTo();
				Create_HL_BFS();
				//Load_MT();
				Load_Node();	
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}
					
				set_TF(kt_BFS);
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570,"Click vao dinh bat ki de duyet BFS");									
			}
			if(In_Rec(120,50,200,100,x,y)){//																DinhThat
				Create_Mh_AlTo();
				Create_HL_DinhThat();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi phai co it nhat 2 dinh");
						set_F();
						continue;
					}
				
				
				dem=0;
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570,"Click vao dinh bat ki de chon dinh bat dau");
				set_TF(kt_DThat);			
			}
			if(In_Rec(220,50,300,100,x,y)){//																				X-->Y
				Create_Mh_AlTo();
				Create_HL_XtoY();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi phai co it nhat 2 dinh");
						set_F();
						continue;
					}
						
				dem=0;
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570,"Click vao dinh bat ki de chon dinh bat dau");
				set_TF(kt_XY);			
			}
			if(In_Rec(20,190,100,240,x,y)){//																Dinh Tru
				Create_Mh_AlTo();
				Create_HL_DinhTru();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}	
				Dinh_Tru();	
				set_F();
			}
			if(In_Rec(220,190,300,240,x,y)){//																Canh Cau
				Create_Mh_AlTo();
				Create_HL_CanhCau();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi phai co it nhat 2 dinh");
						set_F();
						continue;
						}
				
				Create_Mh_NoiDung();
				Canh_Cau();	
				set_F();
			}
			if(In_Rec(120,120,200,170,x,y)){//																Lien Thong
				Create_Mh_AlTo();
				Create_HL_TPLT();	
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}
				
				Create_Mh_NoiDung();
				TPLT(dt.MT);
				set_F();
			}
			if(In_Rec(220,120,300,170,x,y)){//																Hamilton
				Create_Mh_AlTo();
				Create_HL_Hamilton();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}
				
				Create_Mh_NoiDung();
				set_TF(kt_Ham);		
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570,"Click vao dinh de chon dinh bat dau");
			}
			if(In_Rec(120,190,200,240,x,y)){//																				euler
				Create_Mh_AlTo();
				Create_HL_Euler();	
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}	
				
				Create_Mh_NoiDung();
				set_TF(kt_Eurle);		
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570,"Click vao dinh de chon dinh bat dau");
			}
			if(In_Rec(20,120,100,170,x,y)){//																				TopoSort
				Create_Mh_AlTo();
				Create_HL_TopoSort();
				//Load_MT();
				Load_Node();
				if(working==false){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
					continue;
				}	
				if(dt.stt_Node<0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi chua co dinh");
						set_F();
						continue;
					}
				Topo_Sort();	
				set_F();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(In_Circle(360,525,x,y)){//													NEW
				Create_Mh_AlTo();
				Create_HL_New();
				
				set_F();
				Start();					
				working=true;
				kt_Save=false;	
			}
			if(In_Circle(420,525,x,y)){//													Open
				Create_Mh_AlTo();
				Create_HL_Open();
				
				set_F();
				Start();	
				kt_Save=true;
				working=true;
				Open();
				Load_MT();
				Load_Node();
				Create_Mh_NoiDung();	
				Create_Mh_AlTo();			
			}
			if(In_Circle(480,525,x,y)){//													Save
				Create_Mh_AlTo();
				Create_HL_Save();
				Load_Node();
				
				set_F();
				if(working==false||dt.stt_Node==-1){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Chua co do thi")	;
					delay(TIME);
					Create_Mh_NoiDung();
				}else{
					if(kt_Save==false) Save();else Save2();
				}
				Create_Mh_AlTo();
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			if(In_Circle(560,525,x,y)){//											Add
				Load_Node();
				Create_Mh_AlTo();
				Create_HL_Add();
				if(dt.stt_Node>NODE_MAX-2){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Da du      dinh");
					char xau[10];
					itoa(NODE_MAX,xau,10);
					set_Word(8,4);
					outtextxy(100,570,xau);
					set_F();
					continue;
				}
				Create_Mh_NoiDung();
				
				set_Word(8,1);
				if(working){
					Create_Mh_NoiDung();
					set_TF(kt_Add);	
					set_Word(8,1);			
					outtextxy(20,570,"Click chuot trai vao khoang trong de tao dinh moi")	;
					outtextxy(20,590,"So dinh <=15")	;
				}else outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
			}
			if(In_Circle(620,525,x,y)){//											Del
				Create_Mh_NoiDung();
				Load_Node();
				Create_Mh_AlTo();
				Create_HL_Del();
				
				set_Word(8,1);				
				if(working){
					Create_Mh_NoiDung();
					set_TF(kt_Del);
					if(dt.stt_Node==-1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi khong co dinh");
						set_F();
						continue;
					}
					set_Word(8,1);
					outtextxy(20,570,"Click chuot trai vao dinh de xoa")	;
				}else outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;	
			}
			if(In_Circle(680,525,x,y)){//									Link
				Create_Mh_NoiDung();
				Load_Node();
				Create_Mh_AlTo();
				Create_HL_Link();
				
				set_Word(8,1);
				if(working){
					dem=0;
					if(dt.stt_Node<1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi phai co it nhat 2 dinh");
						set_F();
						continue;
					}
					Create_Mh_NoiDung();
					set_TF(kt_Link);
					set_Word(8,1);
					outtextxy(20,570,"Click chuot trai lan luot vao A va B de tao cung AB")	;
					outtextxy(20,590,"Neu cung AB da ton tai,click lan 2 de xoa hoac chinh sua")	;
				}else outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
				
			}
			if(In_Circle(740,525,x,y)){//								Move
				Create_Mh_NoiDung();
				Load_Node();
				Create_Mh_AlTo();
				Create_HL_Move();
				
				set_Word(8,1);
				if(working){
					dem=0;
					if(dt.stt_Node==-1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi khong co dinh");
						set_F();
						continue;
					}
					Create_Mh_NoiDung();
					set_TF(kt_Move);
					set_Word(8,1);
					outtextxy(20,570,"Click chuot trai lan 1 vao dinh de chon dinh")	;	
					outtextxy(20,590,"Click chuot trai lan 2 vao khoang trong de di chuyen dinh toi toa do moi")	;
				}else outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
				
			}
			if(In_Circle(800,525,x,y)){//							Rename
				Create_Mh_NoiDung();
				Load_Node();
				Create_Mh_AlTo();
				Create_HL_Rename();
				
				set_Word(8,1);
				if(working){
					if(dt.stt_Node==-1){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Do thi khong co dinh");
						set_F();
						continue;
					}
					Create_Mh_NoiDung();
					set_TF(kt_Rename);
					set_Word(8,1);
					outtextxy(20,570,"Click chuot trai vao dinh de doi ten")	;	
				}else outtextxy(20,570,"Ban phai mo do thi hoac tao do thi moi truoc")	;
				
			}
			
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(kt_Link&&dt.stt_Node>=1&&In_Rec(340,30,getmaxx()-30,480,x,y)){
				set_Word(8,1);
				if(dem==0){
					FOR(i,0,dt.stt_Node){
						if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=20) {
							dem=1;
							tam1=i;
							Create_Node(dt.node[tam1].x,dt.node[tam1].y,4);
							break;
						}
					}						
				}
				else if(dem==1){
					bool kt=false,kt2=false,kt3=false;//kt :B t?n tai
					FOR(i,0,dt.stt_Node)
						if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=20&&i!=tam1) {
							kt=true;tam2=i;
							Create_Node(dt.node[tam2].x,dt.node[tam2].y,4);
							break;
						}
					if(kt==false) continue;
					FOR(i,0,dt.stt_Node) FOR(j,0,dt.stt_Node) if(dt.MT[tam1][tam2]!=0) kt2=true;//kt2   : a-->b   ton tai
					FOR(i,0,dt.stt_Node) FOR(j,0,dt.stt_Node) if(dt.MT[tam2][tam1]!=0) kt3=true;//kt3   : b-->a   ton tai
					if(kt&&kt2==false&&kt3){		//a->b chua ton tai,b-->a ton tai				
						
						dem=0;
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Nhap trong so cung ")	;
						outtextxy(20,590,"0 < Trong so < 1000")	;
						
						set_Word(8,4);			outtextxy(250,570,dt.node[tam1].name)	;
						set_Word(8,1);			outtextxy(300,570,"->")	;
						set_Word(8,4);			outtextxy(350,570,dt.node[tam2].name)	;
						set_Word(8,1);			outtextxy(400,570,":");			
						char s[20];
						int d=0;
						setcolor(4);
						while(true){
							s[d]=getch();
							if(!(('0'<=s[d]&&s[d]<='9')||s[d]==13||s[d]==8)) continue;
							if(d==3){
								if(s[d]!=13&&s[d]!=8){
									s[2]=s[3];
									d--;
								} 
							}
							if(s[d]==13){	
								if(d==0) continue;
								else{
									settextstyle(0,0,1);
									char xau[d];
									FOR(i,0,d-1) xau[i]=s[i];xau[d]='\0';
									int t=atoi(xau);
									set_Word(8,4);	
									dt.MT[tam1][tam2]=t;
									Create_Mh_NoiDung();
									Load_Node();
									Load_MT();	
									break;
								}
							}
							else if(s[d]==8){
								setfillstyle(1,15);
								bar(500+20*(d-1),570,500+20*(d),590);
								d--;
								if(d==-1) d=0;
								continue;
							}else OutPut(500+20*d,570,s[d]);
							d++;
						}
					}
					if(kt&&kt2==false&&kt3==false){
						dem=0;
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Nhap trong so cung ")	;
						outtextxy(20,590,"0 < Trong so < 1000")	;
						set_Word(8,4);			outtextxy(250,570,dt.node[tam1].name)	;
						set_Word(8,1);			outtextxy(300,570,"->")	;
						set_Word(8,4);			outtextxy(350,570,dt.node[tam2].name)	;
						set_Word(8,1);			outtextxy(400,570,":");	
						setcolor(4);
						char s[20];
						int d=0;
						setcolor(4);
						fflush(stdin);
						while(true){
							s[d]=getch();
							if(!(('0'<=s[d]&&s[d]<='9')||s[d]==13||s[d]==8)) continue;
							if(d==3){
								if(s[d]!=13&&s[d]!=8){
									s[2]=s[3];
									d--;
								} 
							}
							if(s[d]==13){	
								if(d==0) continue;
								else{
									settextstyle(0,0,1);
									char xau[d];
									FOR(i,0,d-1) xau[i]=s[i];xau[d]='\0';
									int t=atoi(xau);
									set_Word(8,4);
									dt.MT[tam1][tam2]=t;
									Create_Mh_NoiDung();
									Load_Node();
									Load_MT();	
									break;
								}
							}
							else if(s[d]==8){
								setfillstyle(1,15);
								bar(500+20*(d-1),570,500+20*(d),590);
								d--;
								if(d==-1) d=0;
								continue;
							}else OutPut(500+20*d,570,s[d]);
							d++;
						}
						
					}
					bool kt_Change=false,kt_Remove=false,kt_Back=false;
					dem=0;
					if(kt&&kt2)	{		
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"0  Quay lai")	;
						outtextxy(20,590,"1  Xoa cung")	;
						outtextxy(20,610,"2  Chinh sua trong so")	;
						outtextxy(20,630,"nhap lua chon :")	;
						setcolor(4);
						int s[2];
						fflush(stdin);
						while(true){
							s[0]=getch();
							longdz:
							if(!(s[0]=='0'||s[0]=='1'||s[0]=='2')) continue;
							OutPut(300,630,s[0]);
							longdz2:	
							s[1]=getch();
							if(!(s[1]=='0'||s[1]=='1'||s[1]=='2'||s[1]==13)) goto longdz2;
							if(s[1]==13) {
								settextstyle(0,0,1);
								if(s[0]=='0')kt_Back=true;
								if(s[0]=='1')kt_Remove=true;
								if(s[0]=='2')kt_Change=true;
								break;	
							}else  {s[0]=s[1];	goto longdz;							}
							
							
						}

					}
					if(kt_Back) {
						Load_Node();
						Load_MT();
						Create_Mh_NoiDung();
					}
					if(kt_Remove){
						dt.MT[tam1][tam2]=0;
						Load_Node();	
						Load_MT();	
						Create_Mh_NoiDung();				
					}
					if(kt_Change){
						Create_Node(dt.node[tam1].x,dt.node[tam1].y,4);
						Create_Node(dt.node[tam2].x,dt.node[tam2].y,4);
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Nhap trong so cung ")	;
						outtextxy(20,590,"0 < Trong so < 1000")	;
						set_Word(8,4);			outtextxy(250,570,dt.node[tam1].name)	;
						set_Word(8,1);			outtextxy(300,570,"->")	;
						set_Word(8,4);			outtextxy(350,570,dt.node[tam2].name)	;
						set_Word(8,1);			outtextxy(400,570,":");		
						setcolor(4);
						char s[15];
						int d=0;
						fflush(stdin);
						while(true){
							s[d]=getch();
							if(!(('0'<=s[d]&&s[d]<='9')||s[d]==13||s[d]==8)) continue;
							if(d==3){
								if(s[d]!=13&&s[d]!=8){
									s[2]=s[3];
									d--;
								} 
							}
							if(s[d]==13){	
								if(d==0) continue;
								else{
									char xau[d];
									FOR(i,0,d-1) xau[i]=s[i];xau[d]='\0';
									int t=atoi(xau);
									set_Word(8,4);
									Create_Mh_NoiDung();
									dt.MT[tam1][tam2]=t;
									Load_Node();
									Load_MT();		
									break;
								}
							}
							else if(s[d]==8){
								setfillstyle(1,15);
								bar(500+20*(d-1),570,500+20*(d),590);
								d--;
								if(d==-1) d=0;
								continue;
							}else OutPut(500+20*d,570,s[d]);
							d++;
						}
						
					}
				}						
			}			
			if(kt_Add&&In_Rec(340,30,getmaxx()-30,480,x,y)){//														Them node
				if(dt.stt_Node>NODE_MAX-2){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Da du      dinh");
					char xau[10];
					itoa(NODE_MAX,xau,10);
					set_Word(8,4);
					outtextxy(100,570,xau);
					continue;
				}

				bool kt=false;
				FOR(i,0,dt.stt_Node) if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=45) {	kt=true;break;	}
				if(kt) continue;
				Create_Node(x,y,4);
				Create_Mh_NoiDung();
				set_Word(8,1);
				outtextxy(20,570," Nhap ten dinh :")	;
				outtextxy(20,590,"(Ten dinh theo dinh dang: 00->99 va khac ten da ton tai)")	;
				outtextxy(20,610,"So dinh <=15")	;
				setcolor(4);
				char s[2];
				FOR(i,0,2) s[i]='\0';
				int d=0;
				char xx;
				while(true){
					xx=getch();
					if(!(('0'<=xx&&xx<='9')||xx==13||xx==8)) continue;
					if(d==0){
						if('0'<=xx&&xx<='9') {s[0]=xx;d=1;}
					}else if(d==1){
						if('0'<=xx&&xx<='9') {s[1]=xx;d=2;}
						if(xx==8){
							FOR(i,0,2) s[i]='\0';
							d=0;
						} 
					}else if(d==2){
						if(xx==8){
							FOR(i,1,2) s[i]='\0';
							d=1;
						} 
						if('0'<=xx&&xx<='9'){
							s[1]=xx;
							d=2;
						}
						if(xx==13){
							bool kt2=true;
							FOR(i,0,dt.stt_Node) if(dt.node[i].name[0]==s[0]&&dt.node[i].name[1]==s[1]) kt2=false;
							if(kt2){
								set_Word(8,4);
								dt.stt_Node++;
								dt.init_Node(1,1);
								dt.init_MT(1,1);
								dt.node[dt.stt_Node].x=x;dt.node[dt.stt_Node].y=y;
								dt.node[dt.stt_Node].name[0]=s[0];dt.node[dt.stt_Node].name[1]=s[1];dt.node[dt.stt_Node].name[2]='\0';
								Load_Node();
								Load_MT();					
								Create_Mh_NoiDung();
									
								break;
							}
						}
					}
					
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570," Nhap ten dinh :")	;
					outtextxy(20,590,"(Ten dinh theo dinh dang: 00->99 va khac ten da ton tai)")	;
					outtextxy(20,610,"So dinh <=15")	;
					set_Word(8,4);
					outtextxy(400,570,s);
					

				}			
			}
			
			if(kt_Del&&In_Rec(320,10,getmaxx()-10,490,x,y)){///////////////////////////////////////////////////////////////	xoa node
				if(dt.stt_Node==-1){
					Create_Mh_NoiDung();
					set_Word(8,1);
					outtextxy(20,570,"Do thi khong co dinh");
					continue;
				}
				FOR(i,0,dt.stt_Node)		if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=20){						
					dt.stt_Node--;
					dt.init_MT(-1,i);
					dt.init_Node(-1,i);
					break;										
				}
				Load_Node();
				Load_MT();	
			}
			if(kt_Move&&In_Rec(340,30,getmaxx()-30,480,x,y)){//																move node	
				if(dem==0)	
					FOR(i,0,dt.stt_Node){
						if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=20) {
							dem=1;
							tam=i;
							Create_Node(dt.node[tam].x,dt.node[tam].y,4);
							break;
						}
					}						
				else if(dem==1){
					bool kt=true;
					FOR(i,0,dt.stt_Node)	if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=45) kt=false;
					if(kt){
						dem=0;
						dt.node[tam].x=x;dt.node[tam].y=y;
						Load_Node();
						//Load_MT();					
					}
				}
	
			}
			if(kt_Rename&&In_Rec(340,30,getmaxx()-30,480,x,y)){//											doi ten
				FOR(i,0,dt.stt_Node)
					if(Kc(x,y,dt.node[i].x,dt.node[i].y)<=20){
					 	Create_Mh_NoiDung();
					 	Create_Node(dt.node[i].x,dt.node[i].y,4);
						set_Word(8,1);
						outtextxy(20,570," Nhap ten dinh :")	;
						outtextxy(20,590,"(Ten dinh theo dinh dang: 00->99 va khac ten da ton tai)")	;
						outtextxy(20,610,"So dinh <=15")	;
						setcolor(4);
						char s[2];
						FOR(j,0,2) s[j]='\0';
						int d=0;
						char xx;
						while(true){
							xx=getch();
							if(!(('0'<=xx&&xx<='9')||xx==13||xx==8)) continue;
							if(d==0){
								if('0'<=xx&&xx<='9') {s[0]=xx;d=1;}
							}else if(d==1){
								if('0'<=xx&&xx<='9') {s[1]=xx;d=2;}
								if(xx==8){
									FOR(i,0,2) s[i]='\0';
									d=0;
								} 
							}else if(d==2){
								if(xx==8){
									FOR(i,1,2) s[i]='\0';
									d=1;
								} 
								if('0'<=xx&&xx<='9'){
									s[1]=xx;
									d=2;
								}
								if(xx==13){
									bool kt2=true;
									FOR(j,0,dt.stt_Node) if(dt.node[j].name[0]==s[0]&&dt.node[j].name[1]==s[1]) kt2=false;
									if(kt2){		
										dt.node[i].name[0]=s[0];dt.node[i].name[1]=s[1];dt.node[i].name[2]='\0';
										Load_Node();	
										Create_Mh_NoiDung();
										Load_MT();	
										break;
									}
								}
							}				
							Create_Mh_NoiDung();
							set_Word(8,1);
							outtextxy(20,570," Nhap ten dinh :")	;
							outtextxy(20,590,"(Ten dinh theo dinh dang: 00->99 va khac ten da ton tai)")	;
							outtextxy(20,610,"So dinh <=15")	;
							set_Word(8,4);
							outtextxy(400,570,s);
						}
						break;
					}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(kt_DFS&&In_Rec(340,30,getmaxx()-30,480,x,y)){//////								DFS
				int tam=-1;
				FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)) tam=i;
				
				if(tam!=-1){
					Load_Node();
					DFS(tam);
					
					kt_DFS=false;
				}
			}
			if(kt_BFS&&In_Rec(340,30,getmaxx()-30,480,x,y)){//								BFS
				int tam=-1;
				FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)) tam=i;
				
				if(tam!=-1){
					Load_Node();
					BFS(tam);
					kt_BFS=false;
				}
			}
			if(kt_DThat&&In_Rec(340,30,getmaxx()-30,480,x,y)){
				if(dem==0){
					FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)) {tam=i;dem=1;}	
					if(dem==1){
						Create_Node(dt.node[tam].x,dt.node[tam].y,4);
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Click vao dinh khac de chon dinh ket thuc");
					}		
				}else{
					int t;
					FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)&&i!=tam) {
						Create_Node(dt.node[i].x,dt.node[i].y,4);	
						dem=0;t=i;
					}	
					if(dem==0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Dinh that giua 2 dinh ");
						set_Word(8,4);
						outtextxy(270,570,dt.node[tam].name);	outtextxy(300,570,"-->");	outtextxy(350,570,dt.node[t].name);
						set_Word(8,1); 		outtextxy(390,570,":");
						Dinh_That(tam,t);
						kt_DThat=false;
					}
				}	
			}
			if(kt_XY&&In_Rec(340,30,getmaxx()-30,480,x,y)){//												X->Y
				if(dem==0){
					FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)) {tam=i;dem=1;}	
					if(dem==1){
						Create_Node(dt.node[tam].x,dt.node[tam].y,4);
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Click vao dinh khac de chon dinh ket thuc");
					}		
				}else{
					int t;
					FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)&&i!=tam) {
						Create_Node(dt.node[i].x,dt.node[i].y,4);	
						dem=0;t=i;
					}	
					if(dem==0){
						Create_Mh_NoiDung();
						set_Word(8,1);
						outtextxy(20,570,"Duong di ngan nhat tu ");
						set_Word(8,4);
						outtextxy(300,570,dt.node[tam].name);
						set_Word(8,1);
						outtextxy(325,570,"->");	outtextxy(380,570,":");
						set_Word(8,4);
						outtextxy(350,570,dt.node[t].name);
						
						Dijkstra(tam,t);
						kt_XY=false;
					}
				}	
			}
			
			if(kt_Ham&&In_Rec(340,30,getmaxx()-30,480,x,y)){
				FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)){
					Load_Node();
					Hamilton(i);
					break;	
				}
			}
			if(kt_Eurle&&In_Rec(340,30,getmaxx()-30,480,x,y)){
				FOR(i,0,dt.stt_Node) if(In_Circle(x,y,dt.node[i].x,dt.node[i].y)){
					Load_Node();
					Euler(i);
					break;	
				}
			}
			
		}
		clearMouse();

		while(kbhit()) {
			char s=getch();
			if(s==27) {
				dt.delete_Data();
				return 0;
			}
		}
		
        delay(0.0001);
		
	}
	return 0;
}
