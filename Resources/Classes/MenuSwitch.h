#ifndef __MENU_SWITCH_H__
#define __MENU_SWITCH_H__

#include "cocos2d.h"

class MenuSwitch : public cocos2d::Layer
{
public:
	//��ʼ��Ϸ�˵�
	void StartGame(cocos2d::Object* pSender);
	//������Ϸ�˵�
	void ExitGame(cocos2d::Ref* pSender);
	//�������˵�
	void BackToMenu(cocos2d::Ref* pSender);
	//��Ϸ����
	void GameSet(cocos2d::Ref* pSender);
};

#endif 