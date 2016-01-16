// 定义重载的泛型输出操作符
template < class Type > ostream& operator<<( ostream& os, const TQueue<Type>& q )
{
	os << "< ";
	for ( TQueueItem<Type> *p = q.head; p; p = p->next )
	{
		os << p->item << " ";
	}
	os << ">";
	return os;
}

// 定义TQueue成员函数
template < class Type > 
TQueue<Type>& TQueue<Type>::operator=( const TQueue& q )
{
	head = tail = 0;
	copy_elems( q );
	return *this;
}

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
	if ( empty() )
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

// 定义成员模板
template < class Type > template < class Iter > 
void TQueue<Type>::assign( Iter beg, Iter end )
{
	destroy();
	copy_elems( beg, end );
}

template < class Type > template < class Iter > 
void TQueue<Type>::copy_elems( Iter beg, Iter end )
{
	while ( beg != end )
	{
		push( *beg );
		++beg;
	}
}