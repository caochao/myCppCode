#include <cstdlib>

/*
 * 模仿cocos2d-x 3.9 PoolManager构造单例
 */
class PoolMgr
{
public:
	PoolMgr() {}
	static PoolMgr* getInst();
	static void destroyInst();
private:
	static PoolMgr *_inst;
};

PoolMgr* PoolMgr::_inst = NULL;

PoolMgr* PoolMgr::getInst()
{
	if ( _inst == NULL )
	{
		_inst = new PoolMgr();
	}
	return _inst;
}

void PoolMgr::destroyInst()
{
	delete _inst;
	_inst = NULL;
}

int main(int argc, char const *argv[])
{
	PoolMgr *pm = PoolMgr::getInst();
	PoolMgr::destroyInst();
	return 0;
}