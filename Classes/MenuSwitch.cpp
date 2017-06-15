#include "MenuSwitch.h"

USING_NS_CC;


void MenuSwitch::SelectMap(cocos2d::Object * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionSplitRows::create(1.0, Select::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);
}

void MenuSwitch::ExitGame(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	Director::getInstance()->end();//������Ϸ
}
void MenuSwitch::BackToLast(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	Director::getInstance()->popScene();
}
void MenuSwitch::GameSet(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionFadeTR::create(1.0, AudioControl::createScene());///��������ת��
	Director::getInstance()->pushScene(transition);
}
void MenuSwitch::Continue(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	Director::getInstance()->popScene();
}
void MenuSwitch::Break(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionProgressInOut::create(1.0,PauseScene::createScene());///��������ת��
	Director::getInstance()->pushScene(transition);
}
void MenuSwitch::BackToMenu(cocos2d::Ref* pSender) {
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionFadeTR::create(0.5, BeginScene::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);
}

