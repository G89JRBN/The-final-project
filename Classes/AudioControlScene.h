#ifndef __AUDIO_CONTROL_SCENE__
#define __AUDIO_CONTROL_SCENE__


#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "BeginScene.h"
using namespace CocosDenshion;

// AudioControl���������ñ������ֺ�������Ч
class AudioControl : public cocos2d::Layer
{
public:
	//��̬����������Scene����
	static cocos2d::Scene* createScene();

// init��������ɳ�ʼ��������
	virtual bool init();

	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	
	CREATE_FUNC(AudioControl);
};
#endif