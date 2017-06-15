#ifndef __MENU_SWITCH_H__
#define __MENU_SWITCH_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "BeginScene.h"
#include "AudioControlScene.h"
#include "PauseScene.h"
#include "Select.h"
class MenuSwitch : public cocos2d::Layer
{
public:

	//ѡ���ͼ������
	void SelectMap(cocos2d::Object* pSender);
	//������Ϸ�˵�
	void ExitGame(cocos2d::Ref* pSender);
	//�������˵�
	void BackToLast(cocos2d::Ref* pSender);
	//��Ϸ����
	void GameSet(cocos2d::Ref* pSender);
	//������Ϸ
	void Continue(cocos2d::Ref* pSender);
	//��ͣ��Ϸ
	void Break(cocos2d::Ref* pSender);
	//�������˵�
	void BackToMenu(cocos2d::Ref* pSender);
};

#endif 