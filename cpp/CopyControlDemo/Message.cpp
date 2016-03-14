#include <set>
#include <string>
#include <iostream>
using namespace std;

class Message
{
public:
	// folders隐式初始化为空集合
	Message( const string& str = "" ): contents( str ) {}

	// 复制控制成员
	Message( const Message& );
	Message& operator=( const Message& );
	~Message();

	// 在指定Folder的消息集中增加/删除该消息
	void save( Folder& );
	void remove( Folder& );

	// 在包含该消息的目录集中增加/删除指定Folder
	void addFldr( Folder* );
	void remFldr( Folder* );
private:
	string contents;		// 消息内容
	set<Folder*> folders;	// 包含该消息的目录

	// 复制构造函数, 赋值操作符, 析构函数所使用的实用函数
	// 将消息加到形参所指的目录集中
	void put_Msg_in_Folders( const set<Folder*>& );

	// 从消息所在的所有目录中删除该消息
	void remove_Msg_from_Folders();
};

Message::Message( const Message& m ): contents( m.contents ), folders( m.folders )
{
	// 将该消息加到指向m的每个目录中
	put_Msg_in_Folders( folders );
}

// 将该消息加到rhs所指的目录集中
void Message::put_Msg_in_Folders( const set<Folder*>& rhs )
{
	for ( set<Folder*>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++beg )
	{
		(*beg)->addMsg( this );
	}
}

Message& Message::operator=( const Message& rhs )
{
	if ( &rhs != this )
	{
		remove_Msg_from_Folders();			// 更新现有目录
		contents = rhs.contents;			// 从rhs复制消息内容
		folders = rhs.folders;				// 从rhs复制目录指针集
		put_Msg_in_Folders( rhs.folders );	// 将该消息加到rhs中的每个目录中
	}
	return *this;
}

// 从对应目录中删除该消息
void Message::remove_Msg_from_Folders()
{
	for ( set<Folder*>::const_iterator beg = folders.begin();
			beg != folders.end(); ++beg )
	{
		(*beg)->remMsg( this );
	}
}

// contents, folders被合成析构函数释放
Message::~Message()
{
	remove_Msg_from_Folders();
}

void Message::save( Folder& fldr )
{
	addFldr( &fldr );
	fldr.addMsg( this );
}

void Message::remove( Folder& fldr )
{
	remFldr( &fldr );
	fldr.remMsg( this );
}

void Message::addFldr( Folder* fldr )
{
	folders.insert( fldr );
}

void Message::remFldr( Folder* fldr )
{
	folders.erase( fldr );
}