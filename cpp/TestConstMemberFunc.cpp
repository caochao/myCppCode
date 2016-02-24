class X;	// incomplete class, 声明而不定义类
class Y;	// 只能定义指向不完全类型的指针或引用, 或用于声明(而非定义)使用不完全类型作为函数形参类型或返回类型的函数

class X
{
	Y *y;
};

class Y
{
	X x;	
};

class TestConst
{
public:
	TestConst(): num(0) {};
	const TestConst& getRef() const { return *this; }
	TestConst& getRef() { return *this; }
	void changeNum() { num++; }
public:
	//int num;
	mutable int num;
};

int main()
{
	TestConst tc;
	tc.getRef().changeNum();
	//tc.num = 0;						// 可以修改非const对象的数据成员

	const TestConst ctc;
	//ctc.getRef().changeNum();		// 不用用const对象调用非const成员函数, 因为非const成员函数this指针指向非const对象
	ctc.num = 0;					// 不能修改const对象的数据成员. 但可修改用mutable声明的成员

	return 0;
}