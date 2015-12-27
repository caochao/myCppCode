// josephCycle.cpp : Defines the entry point for the console application.
//
/*
约瑟夫环是一个数学的应用问题：已知n个人(以编号1，2，3...n分别表示)围坐在一张圆桌周围。
编号为k的人开始从1报数，数到m的那个人出列;他的下一个人又从1开始报数，
数到m的那个人又出列;依此规律重复下去，直到圆桌周围的人全部出列。
*/

#include <stdio.h>
#include <stdlib.h>

#define COUNT_INIT 1   // 计数起点

typedef struct LINKNODE
{
    int value;
    struct LINKNODE* next;
}LinkNode, *LinkNodePtr;

// 创建结点
LinkNodePtr createNode( int value )
{
    LinkNodePtr node = ( LinkNodePtr )malloc( sizeof( LinkNode ) );
    node->value = value;
    return node;
}

// 创建循环单链表
LinkNodePtr createCycle( int total )
{
    int index = 1;
    LinkNodePtr head = NULL, curr = NULL, prev = NULL;
    head = createNode( index );
    prev = head;

    while( --total > 0 )
    {
        curr = createNode( ++index );
        prev->next = curr;
        prev = curr;
    }
    curr->next = head;  // 链表尾结点指向头结点, 构成循环链表
    return head;
}

// 数到m, 节点出列, 下一个节点继续从1开始数. m不可与COUNT_INIT同值
void run( int total, int m )
{
    LinkNodePtr node = createCycle( total );
    LinkNodePtr prev = NULL;
    int index = COUNT_INIT;

    while( node && node->next )
    {
        if( index == m )    
        {
            printf( "pop:%d\n", node->value );
            prev->next = node->next;
            node->next = NULL;
            free( node );
            node = prev->next;
            index = COUNT_INIT;
        }
        else
        {
            prev = node;
            node = node->next;
            index++;
        }
    }
}

// JosephCycleDemo.exe -o -c test
// JosephCycleDemo -o -c test
// argc为4, argv是有4个char*元素的数组
void parseArgs( int argc, char** argv )
{
    for( char** p = argv; p < argv + argc; p++ )
    {
        printf("%s\n", *p);
    }
}

int main( int argc, char** argv )
{
    run( 5, 5 );
    parseArgs( argc, argv );

    scanf( "press any key to quit..." );
    return 0;
}