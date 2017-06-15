#ifndef __SELECT_H__
#define __SELECT_H__

#include "cocos2d.h"
USING_NS_CC;
class Select : public cocos2d::Layer
{
private:
	int _selectMap = 1;
	int _selectPlayer = 1;
	Vector<Sprite*> _tagVector;
	Vector<Sprite*> _mapVector;
public:
	//��������
	static cocos2d::Scene* createScene();
	//������ʼ��init���������ɹ�����������ʱ�򷵻�true
	virtual bool init();
	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	CREATE_FUNC(Select);

};

#endif 
