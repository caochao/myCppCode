#include <set>
#include <string>
#include <iostream>
using namespace std;

class Message;
class Folder
{
public:
	Folder() { cout << "Folder()" << endl; }
	// 复制控制成员
	Folder( const Folder& );
	Folder& operator=( const Folder& );
	~Folder();

	// 在指定Message的目录集中增加/删除该目录
	void save( Message& );
	void remove( Message& );

	//在该目录的消息集中增加/删除指定Message
	void addMsg( Message* );
	void remMsg( Message* );
private:
	set<Message*> messages;	//该目录中的消息集

	// 复制控制成员所使用的实用函数
	// 将目录加到形参所指的消息集中
	void put_Fldr_in_Messages( const set<Message*>& );

	// 从目录所指的所有消息中删除该目录
	void remove_Fldr_from_Messages();
};

Folder::Folder( const Folder& f ): messages( f.messages )
{
	// 将该目录加到f所指向的每个消息中
	put_Fldr_in_Messages( messages );
}

// 将该目录加到rhs所指的消息集中
void Folder::put_Fldr_in_Messages( const set<Message*>& rhs )
{
	for ( set<Message*>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++beg )
	{
		(*beg)->addFldr( this );	// *beg指向Message
	}
}

Folder& Folder::operator=( const Folder& rhs )
{
	if ( &rhs != this )
	{
		remove_Fldr_from_Messages();			// 更新现有消息
		messages = rhs.messages;				// 从rhs复制消息指针集
		put_Fldr_in_Messages( rhs.messages );	// 将该目录加到rhs中的每个消息中
	}
	return *this;
}

// 从对应消息中删除该目录
void Folder::remove_Fldr_from_Messages()
{
	for ( set<Message*>::const_iterator beg = messages.begin();
			beg != messages.end(); ++beg )
	{
		(*beg)->remFldr( this );
	}
}

// set<Message*> messages被合成的析构函数释放
Folder::~Folder()
{
	remove_Fldr_from_Messages();
}

void Folder::save( Message& msg )
{
	addMsg( &msg );
	msg.addFldr( this );
}

void Folder::remove( Message& msg )
{
	remMsg( &msg );
	msg.remFldr( this );
}

void Folder::addMsg( Message* msg )
{
	messages.insert( msg );
}

void Folder::remMsg( Message* msg )
{
	messages.erase( msg );
}