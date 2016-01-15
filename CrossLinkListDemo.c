/*
***************************************************************************************
************十字链表, 横向链表用作索引, 每个横向链表结点指向有序的单词节点链表*********
***************************************************************************************
*/

// 单词节点
typedef struct NODE
{
	char* value;			// 存储单词
	struct NODE* next;		// 指向下一个单词节点
} Node;

// 交叉节点
typedef struct CROSSNODE
{
	char* value;				// 存储索引用的单词首字母
	struct CROSSNODE* hNext;	// 横向指向下一个交叉结点
	struct NODE* vNext;			// 纵向指向有序的单词结点链表
} CrossNode;


#include <stdlib.h>
#include <stdio.h>
#include "StringDemo.cpp"

CrossNode* createCrossNode( char* value )
{
	 CrossNode* node = ( CrossNode* )malloc( sizeof( CrossNode ) );
	 node->value = value;
	 node->hNext = NULL;
	 node->vNext = NULL;
	 printf("createCrossNode:%s\n", value);
	 return node;
}

Node* createNode( char* value )
{
	Node* node = ( Node* )malloc( sizeof( Node ) );
	node->value = value;
	node->next = NULL;
	printf("createNode:%s\n", value);
	return node;
}

void printCrossList( CrossNode* root )
{
	Node* vNode;
	while ( root != NULL )
	{
		printf( "%s->", root->value );
		vNode = root->vNext;
		while ( vNode != NULL )
		{
			printf( "%s->", vNode->value );
			vNode= vNode->next;
		}
		root = root->hNext;
		printf("\n");
	}
	printf("\n----------------------------------------\n");
}

// 在交叉节点链表中搜索结果返回值类型
typedef enum { FOUNDED, NOTFOUNDED } RetType;
typedef struct
{
	RetType retType;
	union
	{
		void* foundedRet;
		struct 
		{
			void* prev;
			void* next;
		} notFoundedRet;
	} value;
} SearchRet;

// 在单词节点链表中搜索节点, 如没找到则找返回拟插入的新节点的前指针和后指针
SearchRet searchNode( Node** root, char* value )
{
	Node* curr;
	SearchRet ret;

	// 寻找第一个值与大于或等于value的交叉节点
	while ( ( curr = *root ) != NULL && strcmp( curr->value, value ) < 0 )
	{
		root = &curr->next;
	}

	// 找到了单词节点
	if ( curr != NULL && strcmp( curr->value, value ) == 0 )
	{
		ret.retType = FOUNDED;
		ret.value.foundedRet = curr;
	}
	else
	{
		ret.retType = NOTFOUNDED;
		ret.value.notFoundedRet.prev = root;
		ret.value.notFoundedRet.next = curr;
	}
	return ret;
}

// 寻找值等于value的交叉节点, 如没找到则找返回拟插入的新节点的前指针和后指针
SearchRet searchCrossNode( CrossNode** cl, char* value )
{
	CrossNode* curr;
	char* c = substr( value, 0, 1 );
	SearchRet ret;

	// 寻找第一个值与大于或等于value的交叉节点
	while ( ( curr = *cl ) != NULL && strcmp( curr->value, c ) < 0 )
	{
		cl = &curr->hNext;
	}

	// 找到了交叉节点
	if ( curr != NULL && strcmp( curr->value, c ) == 0 )
	{
		ret.retType = FOUNDED;
		ret.value.foundedRet = curr;
	}
	else
	{
		ret.retType = NOTFOUNDED;
		ret.value.notFoundedRet.prev = cl;
		ret.value.notFoundedRet.next = curr;
	}
	return ret;
}

// 释放所有单词节点
void disposeNodeList( Node** root )
{
	Node* prev;
	Node* curr = *root;
	*root = NULL;
	while ( curr != NULL )
	{
		prev = curr;
		curr = curr->next;
		printf( "disposing Node=%s\n", prev->value );
		free( prev );
	}
}

// 从单词节点链表中删除值为value的节点
void removeFromNodeList( Node** root, char* value )
{
	Node* curr;
	while ( ( curr = *root ) != NULL && strcmp( curr->value, value ) != 0 )
	{
		root = &curr->next;
	}

	if ( curr != NULL )
	{
		*root = curr->next;
		printf( "disposing Node=%s\n", curr->value );
		free( curr );
	}
}

// 插入新节点到单词链表
void insertNodeList( Node** root, char* value )
{
	printf("insertNodeList:root=%s, value=%s\n", (*root?(*root)->value:"null"), value );
	Node* curr;

	// 寻找第一个值与大于或等于value的单词节点
	while ( ( curr = *root ) != NULL && strcmp( curr->value, value ) < 0 )
	{
		root = &curr->next;
	}

	// 没找到单词节点, 或找到的结点值大于value, 则新建一个单词节点并插入到适当位置
	if ( curr == NULL || strcmp( curr->value, value ) > 0 )
	{
		Node* vNode = createNode( value );
		vNode->next = curr;
		*root = vNode;
	}
}

// 插入新节点到交叉链表
void insertCrossList( CrossNode** cl, char* value )
{
	CrossNode* curr;
	char* c = substr( value, 0, 1 );

	// 寻找第一个值与大于或等于value的交叉节点
	while ( ( curr = *cl ) != NULL && strcmp( curr->value, c ) < 0 )
	{
		cl = &curr->hNext;
	}

	// 没找到交叉节点, 或找到的结点值大于value, 则新建一个交叉节点并插入到适当位置
	CrossNode* hNode = curr;
	if ( curr == NULL || strcmp( curr->value, c ) > 0 )
	{
		hNode = createCrossNode( c );
		hNode->hNext = curr;
		*cl = hNode;
	}

	// 新建一个单词节点并插入到以cl为表头的单词链表的适当位置
	insertNodeList( &hNode->vNext, value );
}

// 从交叉节点链表中删除值为value的节点, 相应的删除其所指向的单词链表
void removeFromCrossList( CrossNode** cl, char* value, bool deleteAllVnode = false )
{
	CrossNode* curr;
	while ( ( curr = *cl ) != NULL && strncmp( curr->value, value, 1 ) != 0 )
	{
		cl = &curr->hNext;
	}
	if ( curr != NULL )
	{
		// 是否删除纵向单词节点链表?
		if ( deleteAllVnode )
		{
			disposeNodeList( &curr->vNext );
			return;
		}
		removeFromNodeList( &curr->vNext, value );
	}
}

// 释放十字链表
void disposeCrossList( CrossNode** cl )
{
	CrossNode *prev;
	CrossNode *curr = *cl;
	*cl = NULL;
	while ( curr != NULL )
	{
		prev = curr;
		curr = curr->hNext;
		printf( "disposing CrossNode=%s\n", prev->value );
		disposeNodeList( &prev->vNext );	// 释放其指向的单词节点链表
		free( prev->value );				// CrossNode value由malloc而来, 也要释放
		free( prev );
	}
}

int main()
{
	CrossNode* root = NULL;

	// test insert
	insertCrossList( &root, "alpha" );
	insertCrossList( &root, "alice" );
	insertCrossList( &root, "beta" );
	insertCrossList( &root, "foo" );
	insertCrossList( &root, "bar" );
	insertCrossList( &root, "apple" );
	insertCrossList( &root, "caochao" );
	insertCrossList( &root, "fun" );
	insertCrossList( &root, "wish" );
	insertCrossList( &root, "warn" );
	printCrossList( root );

	// remove test
	removeFromCrossList( &root, "alice", true );
	removeFromCrossList( &root, "alpha" );
	removeFromCrossList( &root, "apple" );
	insertCrossList( &root, "apple" );
	printCrossList( root );	

	// dispose all
	disposeCrossList( &root );
	printCrossList( root );	

	scanf( "press any key to quit..." );
	return 0;
}