struct qNode{
	int data;
	qNode *next;
};
struct Queue{
	qNode *front;
	qNode *rear;
	Queue(){
		front=NULL;
		rear=NULL;
	}
	bool empty(){
		return (front==NULL);
	}
	void push(int value){
		qNode *p= new qNode;
		p->data=value;
		p->next=NULL;
		if (front==NULL){
			front = p;
		}else {
			rear->next = p;
		}
		rear = p;
	}
	int pop(int &tmp){
		if (empty()) return -1;
		//delete p=front
		qNode *p = front;
		tmp = front->data;
		front = front->next;
		delete p;
		return 1;
	}
	// giai phong bo nho
	~Queue()
	{
		while (front != NULL)
		{
			qNode *tmp;
			tmp = front;
			front = front->next;
			delete tmp;
		}
	}
	
};
