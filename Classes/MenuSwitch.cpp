#include "MenuSwitch.h"

USING_NS_CC;
void MenuSwitch::StartGame(cocos2d::Object* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionSplitRows::create(0.5, GameScene::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);//ת����Ϸ����
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
	auto transition = TransitionFadeTR::create(0.5, AudioControl::createScene());///��������ת��
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
	auto transition = TransitionProgressInOut::create(0.5,PauseScene::createScene());///��������ת��
	Director::getInstance()->pushScene(transition);
}
void MenuSwitch::BackToMenu(cocos2d::Ref* pSender) {
	SimpleAudioEngine::getInstance()->playEffect("lay.wav");
	auto transition = TransitionFadeTR::create(0.5, BeginScene::createScene());///��������ת��
	Director::getInstance()->replaceScene(transition);
}

