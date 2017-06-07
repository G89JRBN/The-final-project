#include "PauseScene.h"
#include "GameScene.h"
#include "MenuSwitch.h"
USING_NS_CC;
Scene* PauseScene::createScene()
{
	// ����һ����������
	auto scene = Scene::create();
	// ���������
	auto layer = PauseScene::create();
	// ��BeginScene����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool PauseScene::init()
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

							 //���¿�ʼ��Ϸ��ť
	auto* pStart = MenuItemImage::create("button1.1.png",
		"button2.2.png",
		this,
		menu_selector(MenuSwitch::StartGame));
	auto* Start = Menu::create(pStart, NULL);
	Start->setAnchorPoint(Vec2(0, 0));
	Start->setPosition(850, size.height / 5);
	Start->setScale(0.9f);
	addChild(Start);
	//������Ϸ��ť
	auto* pExit = MenuItemImage::create("button1.2.png",
		"button2.3.png",
		this,
		menu_selector(MenuSwitch::ExitGame));
	auto* Exit = Menu::create(pExit, NULL);
	Exit->setAnchorPoint(Vec2(0, 0));
	Exit->setPosition(850, size.height * 2 / 5);
	Exit->setScale(0.9f);
	addChild(Exit);

	//��Ϸ���ð�ť
	auto* pSet = MenuItemImage::create("button3.1.png",
		"button3.2.png",
		this,
		menu_selector(MenuSwitch::GameSet));
	auto* Set = Menu::create(pSet, NULL);
	Set->setAnchorPoint(Vec2(0, 0));
	Set->setPosition(850, size.height * 3 / 5);
	Set->setScale(0.9f);
	addChild(Set);

	//������Ϸ
	auto* pGoOn = MenuItemImage::create("����.png",
		"����.png",
		this,
		menu_selector(MenuSwitch::Continue));
	auto* GoOn = Menu::create(pGoOn, NULL);
	GoOn->setAnchorPoint(Vec2(0, 0));
	GoOn->setPosition(850, size.height * 4 / 5);
	GoOn->setScale(0.9f);
	addChild(GoOn);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Village.mp3", true);
	return true;
}