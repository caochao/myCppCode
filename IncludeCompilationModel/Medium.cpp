// Medium.cpp
// 定义medium函数模板的实现文件( 源文件 )
template < typename T >
bool medium( const vector<T>& c, T& m )
{
	// 构造temp为c的副本
	vector<T> temp( c );

	// 如果容器中包含偶数个元素, 则没有中间值, 返回false
	if ( temp.size() % 2 == 0 )
	{
		return false;
	}

	// 将元素排序
	sort( temp.begin(), temp.end() );

	// 判断中间点元素是否为中间值, 是则返回true, 并用m记录. 否则返回false
	typename vector<T>::size_type index = temp.size() / 2;
	if ( temp[ index ] > temp[ index - 1 ] && temp[ index ] < temp[ index + 1 ] )
	{
		m = temp[ index ];
		return true;
	}
	else
	{
		return false;
	}
}