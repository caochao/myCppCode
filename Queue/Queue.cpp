template < class Type > class Queue
{
public:
	// 默认构造函数. 这里实际等价于Queue<Type>(), 下同
	Queue(): head(0), tail(0) {}

	// 复制构造函数
	Queue( const Queue &q ): head(0), tail(0) { copy_elems(q); }

	// 重载赋值操作符
	Queue& operator=( const Queue& );

	~Queue() { destroy(); }

	// 返回队头元素, 不检查空队列
	Type& front() { return head->item; }

	const Type& front() const { return head->item; }

	void push( const Type& );	// 队尾添加元素

	void pop();					// 队头移除元素

	bool empty() const { return head == 0; }
private:
	QueueItem<Type> *head;		// 队头, 指向头节点的指针. 这里不能写成QueueItem *head
	QueueItem<Type> *tail;
	void destroy();
	void copy_elems( const Queue& );
};