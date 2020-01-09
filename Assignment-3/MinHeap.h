typedef Process Data; 

typedef struct PriorityQueue{
	int capacity;
	int size;
	Data* arr;
}PriorityQueue;

typedef PriorityQueue* PQueue;

int isFull(PQueue Q){
	return Q -> size == Q -> capacity;
}

int isEmpty(PQueue Q){
	return Q -> size == 0;
}


PQueue createPQueue(const int maxsize){
	PQueue tmp = (PQueue)malloc(sizeof(PriorityQueue));

	tmp -> capacity = maxsize;
	tmp -> size = 0;
	tmp -> arr = (Data*)malloc(sizeof(Data) * maxsize);

	tmp -> arr[0].rt = -1; 
	return tmp;
}

void enqueue(PQueue q,const Data d){
	if(isFull(q)){
		printf("Queue Full!\n");
		return;
	}	
	int i = ++q -> size;
	for(; q -> arr[i/2].rt > d.rt ; i /= 2)
		q -> arr[i] = q -> arr[i/2];
	
	q -> arr[i] = d; 

}

Data dequeue(PQueue q){
	if(isEmpty(q)){
		printf("Queue Empty!\n");
		return q -> arr[0]; 
	}
	int i,child;
	Data min,last;

	min = q -> arr[1];
	last = q -> arr[q -> size--];

	for(i = 1; i * 2 <= q -> size ; i = child){
		child = i * 2;

		if(child != q -> size && q -> arr[child + 1].rt < q -> arr[child].rt)
			child ++;
		if(last.rt > q -> arr[child].rt)
			q -> arr[i] = q -> arr[child];
		else
			break;
	}

	q -> arr[i] = last;
	return min;
}

void display(PQueue Q){
	for(int i = 1 ; i <= Q -> size ; i++)
		printf("PID :%d RT: %4.2f\n",Q -> arr[i].pid,Q -> arr[i].rt);
}