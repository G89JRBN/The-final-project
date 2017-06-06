#include "MenuSwitch.h"
#include "GameScene.h"
#include "BeginScene.h"
#include "AudioControlScene.h"
USING_NS_CC;
void MenuSwitch::StartGame(cocos2d::Object* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionSlideInL::create(0.5, GameScene::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);//ת����Ϸ����
}

void MenuSwitch::ExitGame(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	Director::getInstance()->end();//������Ϸ
}
void MenuSwitch::BackToMenu(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionSlideInL::create(0.5, BeginScene::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);
}
void MenuSwitch::GameSet(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionSlideInL::create(0.5, AudioControl::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);
}