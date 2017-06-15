#include "PassTheGame.h"
#include "MenuSwitch.h"
USING_NS_CC;
Scene* PassTheGame::createScene()
{
	// ����һ����������
	auto scene = Scene::create();
	// ���������
	auto layer = PassTheGame::create();
	// ��BeginScene����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool PassTheGame::init()
{
	// ���ø����init����
	if (!Layer::init())
	{
		return false;
	}
	// ����豸�ɼ���ͼ��С
	Size size = Director::getInstance()->getVisibleSize();
	//�������ԭ��
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//��Ϸ��ʼ����
	auto* background = Sprite::create("BeginScene.png");
	background->setPosition(size.width / 2, size.height / 2);  //����λ��
	background->setScale(1.5f);//��С
	addChild(background, 0); //��ӵ�����

							 //�������˵���ť
	auto* pBack = MenuItemImage::create("backtomenu1.png",
		"backtomenu2.png",
		this,
		menu_selector(MenuSwitch::BackToMenu));
	auto* Back = Menu::create(pBack, NULL);
	Back->setAnchorPoint(Vec2(0, 0));
	Back->setPosition(850, size.height / 2 - 70);
	Back->setScale(0.9f);
	addChild(Back);

	SimpleAudioEngine::getInstance()->playBackgroundMusic("Village.mp3", true);
	return true;
}