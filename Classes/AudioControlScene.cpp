#include "AudioControlScene.h"
#include "ui/CocosGUI.h"
#include "MenuSwitch.h"
USING_NS_CC;
using namespace ui;

Scene* AudioControl::createScene() {
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();
	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = AudioControl::create();
	// ��GameSet����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool AudioControl::init() {
	// ���ø����init����
	if (!Layer::init()) {
		return false;
	}
	// ����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/***********************�������ֱ�ǩ�ͻ��������**************************/
	// �������������֡��ı������Ϊ��ǰ����ӽڵ�
	auto music_text = Label::createWithTTF("Music", "fonts/Marker Felt.ttf", 36);
	music_text->enableShadow(Color4B::GREEN, Size(5, 5));
	music_text->enableOutline(Color4B::RED, 3);
	
	music_text->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.7));
	this->addChild(music_text,1);

	// ����һ��������
	auto music_slider = Slider::create();
	// ���û�����������
	music_slider->loadBarTexture("sliderTrack.png");
	// ���û������Ĺ�������
	music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	// ���ô��������Ľ���������
	music_slider->loadProgressBarTexture("sliderProgress.png");
	// ��ȡ֮ǰ���õı�����������
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");
	// ����ǵ�һ�ν������ó��������ñ������ֻ�����Ĭ�ϳ�ʼֵΪ100
	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}
	// ���ñ������ֻ������ĳ�ʼֵ
	music_slider->setPercent(musicPercent);
	music_slider->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.7));
	// ����¼�������,����������������
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		// ������İٷֱȷ����仯ʱ
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			// ��û������ٷֱ�
			int percent = music_slider->getPercent();
			// ���ñ�������ֵΪ�������ٷֱ�/100����ΪSlider�İٷֱ���1-100����MusicVolume��ȡֵ��0.0-1.0
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent) / 100);
			// �洢���õı�������ֵ
			UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	this->addChild(music_slider,1);

	/***********************��Ч������ǩ�ͻ��������**************************/
	// ��������Ч�������ı������Ϊ��ǰ����ӽڵ�
	auto sound_text = Label::createWithTTF("Sound Effect", "fonts/Marker Felt.ttf", 36);
	sound_text->enableGlow(Color4B::GREEN);
	sound_text->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.5));
	this->addChild(sound_text,1);

	// ����һ��������
	auto effects_slider = Slider::create();
	// ���û�����������
	effects_slider->loadBarTexture("sliderTrack.png");
	// ���û������Ĺ�������
	effects_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	// ���ô��������Ľ���������
	effects_slider->loadProgressBarTexture("sliderProgress.png");
	// ��ȡ֮ǰ���õ���Ч����
	float effectPercent = UserDefault::getInstance()->getFloatForKey("effectPercent");
	// ����ǵ�һ�ν������ó�����������Ч������Ĭ�ϳ�ʼֵΪ100
	if (effectPercent == 0.0f) {
		effectPercent = 100.0f;
	}
	// ������Ч�������ĳ�ʼֵ
	effects_slider->setPercent(effectPercent);
	effects_slider->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.5));
	// ����¼�������,������Ч����
	effects_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		// ������İٷֱȷ����仯ʱ
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			// ��û������ٷֱ�
			int percent = effects_slider->getPercent();
			// ���ñ�����Чֵ
			SimpleAudioEngine::getInstance()->setEffectsVolume(float(percent) / 100);
			// �洢���õı�������ֵ
			UserDefault::getInstance()->setFloatForKey("effectPercent", percent);
		}
	});
	this->addChild(effects_slider,1);

	auto* background = Sprite::create("BeginScene.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //����λ��
	background->setScale(1.5f);//��С
	addChild(background, 0); //��ӵ�����
							 //�������˵���ť
	auto* pSet = MenuItemImage::create("button4.1.png",
		"button4.2.png",
		this,
		menu_selector(MenuSwitch::BackToLast));
	auto* Set = Menu::create(pSet, NULL);
	Set->setAnchorPoint(Vec2(0, 0));
	Set->setPosition(850, visibleSize.height / 2 - 250);
	Set->setScale(0.9f);
	addChild(Set);
	return true;
}