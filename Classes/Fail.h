#ifndef __FAIL_THE_GAME_H__
#define ___FAIL_THE_GAME_H__

#include "cocos2d.h"

class  FailTheGame : public cocos2d::Layer
{
public:
	//��������
	static cocos2d::Scene* createScene();
	//������ʼ��init���������ɹ�����������ʱ�򷵻�true
	virtual bool init();
	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	CREATE_FUNC(FailTheGame);
};

#endif 

