// ����TQueue��Ա����

template < class Type > void TQueue<Type>::destroy()
{
	while ( !empty() )
	{
		pop();
	}
}

// ��������ͷԪ��
template < class Type > void TQueue<Type>::pop()
{
	if ( empty() ) return;
	TQueueItem<Type> *p = head;
	head = head->next;
	delete p;
}

// ��β���Ԫ��
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

// �Ӷ���q����Ԫ�ص���ǰ����
template < class Type > void TQueue<Type>::copy_elems( const TQueue& q )
{
	for ( TQueueItem<Type> *pt = q.head; pt; pt = pt->next )
	{
		push( pt->item );
	}
}