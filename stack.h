struct sNode{
	int data;
	sNode *next;
};
struct Stack{
	sNode *top;
	Stack(){
		top=NULL;
	}
	bool empty(){
		return(top==NULL);
	}
	void push(int value){
		sNode *p = new sNode;
		p->data=value;
		p->next=top;
		top=p;
	}
	int pop(int &tmp){
		if (empty())	return -1;
		sNode *p = top;
		tmp=top->data;
		top=top->next;
		delete p;
		return 1;
	}
	int get()
	{
		if (empty()) return INT_MIN;
		return top->data;
	}
	// giai phong bo nho
	~Stack(){
		while(top!=NULL){
			sNode *tmp ;
			tmp=top;
			top=top->next;
			delete tmp;
		}
	}
};
