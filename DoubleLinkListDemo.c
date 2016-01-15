typedef struct DOUBLELINKNODE
{
	int value;
	struct DOUBLELINKNODE* next;
	struct DOUBLELINKNODE* prev;
} DoubleLinkNode;

/*
***************************************************************************************
************双向链表头结点的prev指向链表尾结点, 头结点的next指向链表头结点*************
************头结点的prev和next都为NULL表示指向的是空链表*************
***************************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>

#define FAILURE	0
#define SUCCESS 1
#define ROOT_NODE_VALUE	-999

DoubleLinkNode* createNode( int value )
{
	DoubleLinkNode* node = ( DoubleLinkNode* )malloc( sizeof( DoubleLinkNode ) );
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void printLinkList( DoubleLinkNode* dll, bool reversed = false )
{
	DoubleLinkNode* curr = reversed ? dll->prev : dll->next;
	while ( curr != NULL && curr->value != ROOT_NODE_VALUE )
	{
		printf( "%d->", curr->value );
		curr = reversed ? curr->prev : curr->next;
	}
	printf("\n------------------------\n");
}

void disposeList( DoubleLinkNode* dll )
{
	DoubleLinkNode* curr = dll;
	DoubleLinkNode* prev;
	while ( curr != NULL )
	{
		prev = curr;
		curr = curr->next;
		printf( "disposing node=%d\n", prev->value );
		free( prev );
	}
}

/*
1.链表头插入
2.非链表头插入
3.链表尾插入
4.插入到空链表中
*/
int insertNode( DoubleLinkNode* ddl, int value )
{
	// 空链表直接返回
	if ( ddl->prev == NULL && ddl->next == NULL )
	{
		return;
	}

	DoubleLinkNode *curr, *next;

	// 寻找新节点的插入位置. 找到插入位置或直到链表尾都没找到则结束循环
	for ( curr = ddl; ( next = curr->next ) != NULL; curr = next )
	{
		// 如果链表中已有相同值的节点则不插入
		if ( next->value == value )
		{
			return FAILURE;
		}
		if ( next->value > value )
		{
			break;
		}
	}

	DoubleLinkNode* newNode = createNode( value );
	if ( newNode == NULL )
	{
		return FAILURE;
	}

	// 找到插入位置
	if ( next != NULL )
	{
		// 在表头插入
		if ( curr == ddl )
		{
			newNode->prev = curr;
			newNode->next = next;
			next->prev = newNode;
			ddl->next = newNode;
		}
		else	// 非表头插入
		{
			newNode->prev = curr;
			newNode->next = next;
			curr->next = newNode;
			next->prev = newNode;
		}
	}
	else	// 没找到插入位置
	{
		if ( curr == ddl )	// 在空表中插入
		{
			newNode->prev = NULL;
			newNode->next = NULL;
			ddl->prev = newNode;
			ddl->next = newNode;
		}
		else	// 在表尾插入
		{
			newNode->prev = curr;
			newNode->next = NULL;
			curr->next = newNode;
			ddl->prev = newNode;
		}
	}
	return SUCCESS;
}

/*
1.删除第一个结点
2.删除最后一个结点
3.删除中间的结点
4.删除的结点不存在
*/
void removeNode( DoubleLinkNode* ddl, int value )
{
	// 空链表直接返回
	if ( ddl->prev == NULL && ddl->next == NULL )
	{
		return;
	}
	
	DoubleLinkNode* curr = ddl->next;
	DoubleLinkNode* prev = NULL;

	while ( curr != NULL && curr->value != value )
	{
		prev = curr;
		curr = curr->next;
	}

	if ( prev == NULL )
	{
		DoubleLinkNode* deleteNode = ddl->next;

		// 根节点next指向新的链表头结点
		ddl->next = deleteNode->next;

		// 删除结点之后变为空链表, 需要改变头结点prev指向
		if ( ddl->next == NULL )
		{
			ddl->prev = NULL;
		}

		free( deleteNode ) ;
		return;
	}

	if ( curr != NULL )
	{
		prev->next = curr->next;

		// 删除最后一个节点
		if ( curr->next == NULL )
		{
			ddl->prev = prev;
		}

		free( curr );
	}
}

int main()
{
	// 头结点, 设置一个特殊值
	DoubleLinkNode* ddl = createNode( ROOT_NODE_VALUE );
	removeNode( ddl, 5 );
	
	// insert
	insertNode( ddl, -1 );
	insertNode( ddl, -3 );
	insertNode( ddl, -2 );
	insertNode( ddl, 4 );
	insertNode( ddl, 4 );
	insertNode( ddl, 7 );
	insertNode( ddl, -77 );
	printLinkList( ddl );
	printLinkList( ddl, true );

	// remove
	removeNode( ddl, 5 );
	removeNode( ddl, -1 );
	removeNode( ddl, -3 );
	removeNode( ddl, -2 );
	removeNode( ddl, 4 );
	removeNode( ddl, 4 );
	removeNode( ddl, 7 );
	removeNode( ddl, -77 );
	printLinkList( ddl );

	// don't forget to free memory
	disposeList( ddl );
	scanf( "press any key to quit..." );
	return 0;
}