// 定义TQueue成员函数

template < class Type > void TQueue<Type>::destroy()
{
	while ( !empty() )
	{
		pop();
	}
}

// 弹出队列头元素
template < class Type > void TQueue<Type>::pop()
{
	if ( empty() ) return;
	TQueueItem<Type> *p = head;
	head = head->next;
	delete p;
}

// 队尾添加元素
template < class Type > void TQueue<Type>::push( const Type& val )
{
	TQueueItem<Type> *item = new TQueueItem<Type>( val );
	if ( empty() == 0 )
	{
		head = tail = item;
		return;
	}
	tail->next = item;
	tail = item;
}

// 从队列q复制元素到当前队列
template < class Type > void TQueue<Type>::copy_elems( const TQueue& q )
{
	for ( TQueueItem<Type> *pt = q.head; pt; pt = pt->next )
	{
		push( pt->item );
	}
}