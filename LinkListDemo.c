typedef struct NODE
{
	int value;
	struct NODE* link;
} Node;

#include <stdlib.h>
#include <stdio.h>

Node* createNode( int value )
{
	Node* node = (Node*)malloc( sizeof( Node ) );
	node->value = value;
	node->link = NULL;
	return node;
}

void printLinkList( Node* linkList )
{
	Node* curr = linkList;
	while ( curr != NULL )
	{
		printf( "%d->", curr->value );
		curr = curr->link;
	}
	printf("\n------------------------\n");
}

// 反转链表
// @param linkList 链表头结点
Node* listReverse( Node* linkList )
{
	if ( linkList == NULL )
	{
		return NULL;
	}
	Node *prev;
	Node *curr = linkList;
	Node *next = curr->link;
	while ( curr != NULL )
	{
		curr->link = prev;
		prev = curr;
		curr = next;
		if ( next != NULL )
		{
			next = next->link;
		}
	}
	return prev;
}

// 在链表中搜索值为value的节点
Node* listSearch( Node* linkList, int value )
{
	while ( linkList != NULL && linkList->value != value )
	{
		linkList = linkList->link;
	}
	return linkList;
}

void disposeList( Node* linkList )
{
	Node* prev;
	while ( linkList != NULL )
	{
		prev = linkList;
		linkList = linkList->link;
		printf( "disposing node=%d\n", prev->value );
		free( prev );
	}
}

/*
1.链表头插入
2.非链表头插入
3.链表尾插入
4.在空链表中插入
*/
void listInsert( Node** linkList, int value )
{
	Node* curr = *linkList;
	Node* prev = NULL;

	while ( curr != NULL && curr->value < value )
	{
		prev = curr;
		curr = curr->link;
	}

	Node* newNode = createNode( value );
	newNode->link = curr;

	if ( prev == NULL )
	{
		*linkList = newNode;
	}
	else
	{
		prev->link = newNode;
	}
}

void listInsert2( Node** linkList, int value )
{
	Node* curr;
	while ( ( curr = *linkList ) != NULL && curr->value < value )
	{
		linkList = &curr->link;
	}

	Node* newNode = createNode( value );
	if ( newNode == NULL )
	{
		return;
	}

	newNode->link = curr;
	*linkList = newNode;	// 由于while循环中对linkList赋值导致其指向变化.所以这里修改*linkList指向不会导致传入的链表头结点改变
}

/*
1.删除第一个结点
2.删除最后一个结点
3.删除中间的结点
4.删除的结点不存在
*/
void listRemove( Node** linkList, int value )
{
	// 空链表直接返回
	if ( *linkList == NULL )
	{
		return;
	}

	Node* curr = *linkList;
	Node* prev = NULL;
	
	while ( curr != NULL && curr->value != value )
	{
		prev = curr;
		curr = curr->link;
	}

	if ( prev == NULL )
	{
		Node* deleteNode = *linkList;
		*linkList = (*linkList)->link;
		free( deleteNode );
		return;
	}

	if ( curr != NULL )
	{
		prev->link = curr->link;
		free( curr );
	}
}

void listRemove2( Node** linkList, int value )
{
	Node* curr;

	while ( ( curr = *linkList ) != NULL && curr->value != value )
	{
		linkList = &curr->link;
	}
	if ( curr != NULL )
	{
		*linkList = curr->link;
		free( curr );
	}
}

int main()
{
	//Node* linkList = createNode( 2 );
	Node* linkList = NULL;	// 注意! 空链表中也能插入

	// insert
	listInsert( &linkList, 1 );
	listInsert( &linkList, 3 );
	listInsert( &linkList, -1 );
	listInsert( &linkList, 4 );
	printLinkList( linkList );

	// reverse
	Node* reversed = listReverse( linkList );
	printLinkList( reversed );

	linkList = listReverse( reversed );
	printLinkList( linkList );

	// remove
	listRemove2( &linkList, 5 );
	printLinkList( linkList );

	listRemove2( &linkList, -1 );
	listRemove2( &linkList, 1 );
	printLinkList( linkList );

	listRemove2( &linkList, 2 );
	printLinkList( linkList );

	// don't forget to free memory
	disposeList( linkList );
	scanf( "press any key to quit..." );
	return 0;
}
