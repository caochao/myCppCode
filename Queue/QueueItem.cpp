template < class Type >
class QueueItem
{
	// 私有类, 无public部分
	QueueItem( const Type &t ): item(t), next(0) {}
	Type item;					// 保存节点值
	QueueItem *next;			// 类模板作用域内部, 可以用它的非限定名字引用该类. 实际等价于QueueItem<Type> *next;
};