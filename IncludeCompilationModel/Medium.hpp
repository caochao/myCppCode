// Medium.hpp
// 定义medium函数模板的头文件
// medium函数模板在保存未知类型的vector中查找中间值
// 中间值是指, 一半元素比它大, 一半元素比它小
#ifndef MEDIUM_H
#define MEDIUM_H
#include <vector>
#include <algorithm>
using std::vector;

// 如果vector中有中间值, 则返回true, 并将中间值记录在第2个参数中
// 否则, 返回false
template < typename T >
bool medium( const vector<T>&, T& );

#include "Medium.cpp"	// 引入函数模板的实现文件

#endif