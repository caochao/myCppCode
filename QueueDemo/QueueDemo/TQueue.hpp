#ifndef TQUEUE_H
#define TQUEUE_H
#include <fstream>
using namespace std;

// ���Ͷ�����
// author:c++ primer
// editor:cc

template < class Type > class TQueue;
template < class T > ostream& operator<<( ostream&, const TQueue<T>& );

// class TQueueItem
template < class Type > class TQueueItem
{
	// ��Ԫ����
	friend class TQueue<Type>;
	friend ostream& operator<<<Type>( ostream&, const TQueue<Type>& );

	// ˽�г�Ա
	TQueueItem( const Type &t ): item(t), next(0) {}
	Type item;
	TQueueItem *next;
};

// class TQueue
template < class Type > class TQueue
{
	// ��Ԫ����
	friend ostream& operator<<<Type>( ostream&, const TQueue<Type>& );

public:
	// ���캯��, �ն���
	TQueue(): head(0), tail(0) {}

	// ��һ�Ե�����ָ����������Χ�ڴ�������
	template < class It >
	TQueue( It beg, It end ): head(0), tail(0) { copy_elems( beg, end ); }

	// ���ƹ��캯��
	TQueue( const TQueue &q ): head(0), tail(0) { copy_elems(q); }

	// �������ظ�ֵ������
	TQueue& operator=( const TQueue& );

	~TQueue() { destroy(); }

	// ����ģ������. ��һ�Ե�����ָ���ķ�Χ�ڵ������滻��ǰ����
	template < class Iter > void assign( Iter, Iter );

	// ���ض���ͷ��Ԫ��. δ���ն���
	Type& front() { return head->item; }
	const Type& front const { return head->item; }
	void push( const Type& );
	void pop();
	bool empty() const { return head == 0; }
private:
	TQueueItem<Type> *head;		// ָ����е�һ��TQueueItem<Type>
	TQueueItem<Type> *tail;		// ָ����еں�һ��TQueueItem<Type>

	void destroy();
	void copy_elems( const TQueue& );
	template < class Iter > copy_elems( Iter, Iter );
};

#include "TQueue.cpp"		// ����ģ��ʵ���ļ�

#endif