#ifndef __BEGIN_SCENE_H__
#define __BEGIN_SCENE_H__

#include "cocos2d.h"

class BeginScene : public cocos2d::Layer
{
public:
	//��������
	static cocos2d::Scene* createScene();
	//������ʼ��init���������ɹ�����������ʱ�򷵻�true
	virtual bool init();
	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	CREATE_FUNC(BeginScene);
};

#endif 

