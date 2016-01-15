#ifndef TQUEUE_H
#define TQUEUE_H
#include <fstream>
using namespace std;

// 泛型队列类
// author:c++ primer
// editor:cc

template < class Type > class TQueue;
template < class T > ostream& operator<<( ostream&, const TQueue<T>& );

// class TQueueItem
template < class Type > class TQueueItem
{
	// 友元声明
	friend class TQueue<Type>;
	friend ostream& operator<<<Type>( ostream&, const TQueue<Type>& );

	// 私有成员
	TQueueItem( const Type &t ): item(t), next(0) {}
	Type item;
	TQueueItem *next;
};

// class TQueue
template < class Type > class TQueue
{
	// 友元声明
	friend ostream& operator<<<Type>( ostream&, const TQueue<Type>& );

public:
	// 构造函数, 空队列
	TQueue(): head(0), tail(0) {}

	// 从一对迭代器指定的容器范围内创建队列
	template < class It >
	TQueue( It beg, It end ): head(0), tail(0) { copy_elems( beg, end ); }

	// 复制构造函数
	TQueue( const TQueue &q ): head(0), tail(0) { copy_elems(q); }

	// 声明重载赋值操作符
	TQueue& operator=( const TQueue& );

	~TQueue() { destroy(); }

	// 函数模板声明. 用一对迭代器指定的范围内的内容替换当前队列
	template < class Iter > void assign( Iter, Iter );

	// 返回队列头的元素. 未检查空队列
	Type& front() { return head->item; }
	const Type& front const { return head->item; }
	void push( const Type& );
	void pop();
	bool empty() const { return head == 0; }
private:
	TQueueItem<Type> *head;		// 指向队列第一个TQueueItem<Type>
	TQueueItem<Type> *tail;		// 指向队列第后一个TQueueItem<Type>

	void destroy();
	void copy_elems( const TQueue& );
	template < class Iter > copy_elems( Iter, Iter );
};

#include "TQueue.cpp"		// 引入模板实现文件

#endif