#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// ����һ����������
	auto scene = Scene::create();
	// ���������
	auto layer = GameScene::create();
	// ������Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool GameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	// ��ôӴ��ڴ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��ʾ��ͼ
	  map = TMXTiledMap::create("cnm.tmx");
	  // �ѵ�ͼ��ê���λ�ö�����Ϊԭ�㣬��������ʹ��ͼ�����½�����Ļ�����½Ƕ���
	//���õ�ͼ��ê��
	map->setAnchorPoint(Vec2::ZERO);
	//���õ�ͼλ��
	map->setPosition(0, 0);
	map->setScale(1.6f);
    addChild(map, 0);

	// ��ȡ�ϰ��㣬�������ϰ��㲻�ɼ�
	_collidable = map->getLayer("collidable");
	_collidable->setVisible(false);

	// �ٻ�ȡ����֡����ĵ������󣬲���ȡanimation.plist�ļ�������֡������ӵ�����֡���浱��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player.plist");
	//һ�����
	_player = Sprite::create("player_down_1.png");
	// ����λ�ò����Ϊ��ͼ���ӽڵ�
	_player->setPosition(50, visibleSize.height / 2 );
	//�ڵ�Ч��ʵ�ֽ�������Ҫ������ڵ��������zOrderֵ�����ó�<2��������ҵ�zOrder��Ƴ�2���Ϳ���ʵ���ڵ�Ч���ˡ�											  
	map->addChild(_player, 2);
	// ���������¼�������
	auto keyBoardListener = EventListenerKeyboard::create();
	//���������£�map���������ֵ����Ϊtrue
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = true;
	};
	//�������ɿ���map���������ֵ����Ϊfalse
	keyBoardListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = false;
	};
	// ��Ӧ�����¼�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	// ��Ϸ��ѭ��,ÿ֡�����õĺ���
	this->scheduleUpdate();
	return true;
}



//�жϼ����Ƿ�ס
bool GameScene::isKeyPressed(EventKeyboard::KeyCode code) {
	return keys[code];
}
//�������λ��
void GameScene::UpdatePosition(float delta) {
	//�ĸ������
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	//���·����������ƶ�
	if (isKeyPressed(leftArrow)) {
		keyPressedDuration(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedDuration(rightArrow);
	}
	else if (isKeyPressed(upArrow)) {
		keyPressedDuration(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedDuration(downArrow);
	}
}


//ÿ֡����������������»���
void GameScene::update(float delta) {
	//�������λ��
	UpdatePosition(delta);
}


//���̰��º������
void GameScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX += 2;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY += 2;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY -= 2;
		break;
	default:
		break;
	}
	if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] == true) {
		// ��ʹ�þ���֡�����еľ��鴴��һ������������������
		auto animation = Animation::create();
		// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
		for (int i = 1; i <= 6; i++) {
			std::string szName = StringUtils::format("player_left_%d.png", i);
			// ������ͼƬ���Ϊ����֡��������֡��
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
		}
		// ���ö������ŵ����ԣ�3��/15֡
		animation->setDelayPerUnit(1.0f / 6.0f);

		// ���ö���֡����AnimationCache�������ж����Ͷ���֡
		AnimationCache::getInstance()->addAnimation(animation, "walk");
		// �޴Ӷ���֡����AnimationCache�л�ȡ֮ǰ����Ķ���
		auto walk = AnimationCache::getInstance()->getAnimation("walk");
		// �ߴ�����������
		auto animate = Animate::create(walk);
		// �ྫ��ִ�ж���
		_player->runAction(animate);
		auto moveTo = MoveTo::create(0.06, _player->getPosition() + Vec2(offsetX, offsetY));
		_player->runAction(moveTo);
	}
	else if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] == true) {
		// ��ʹ�þ���֡�����еľ��鴴��һ������������������
		auto animation = Animation::create();
		// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
		for (int i = 1; i <= 6; i++) {
			std::string szName = StringUtils::format("player_right_%d.png", i);
			// ������ͼƬ���Ϊ����֡��������֡��
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
		}
		// ���ö������ŵ����ԣ�3��/15֡
		animation->setDelayPerUnit(1.0f / 6.0f);

		// ���ö���֡����AnimationCache�������ж����Ͷ���֡
		AnimationCache::getInstance()->addAnimation(animation, "walk");
		// �޴Ӷ���֡����AnimationCache�л�ȡ֮ǰ����Ķ���
		auto walk = AnimationCache::getInstance()->getAnimation("walk");
		// �ߴ�����������
		auto animate = Animate::create(walk);
		// �ྫ��ִ�ж���
		_player->runAction(animate);
		auto moveTo = MoveTo::create(0.06, _player->getPosition() + Vec2(offsetX, offsetY));
		_player->runAction(moveTo);
	}
	else if (keys[EventKeyboard::KeyCode::KEY_UP_ARROW] == true) {
		// ��ʹ�þ���֡�����еľ��鴴��һ������������������
		auto animation = Animation::create();
		// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
		for (int i = 1; i <= 6; i++) {
			std::string szName = StringUtils::format("player_up_%d.png", i);
			// ������ͼƬ���Ϊ����֡��������֡��
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
		}
		// ���ö������ŵ����ԣ�3��/15֡
		animation->setDelayPerUnit(1.0f / 6.0f);

		// ���ö���֡����AnimationCache�������ж����Ͷ���֡
		AnimationCache::getInstance()->addAnimation(animation, "walk");
		// �޴Ӷ���֡����AnimationCache�л�ȡ֮ǰ����Ķ���
		auto walk = AnimationCache::getInstance()->getAnimation("walk");
		// �ߴ�����������
		auto animate = Animate::create(walk);
		// �ྫ��ִ�ж���
		_player->runAction(animate);
		auto moveTo = MoveTo::create(0.06, _player->getPosition() + Vec2(offsetX, offsetY));
		_player->runAction(moveTo);
	}
	else if (keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] == true) {
		// ��ʹ�þ���֡�����еľ��鴴��һ������������������
		auto animation = Animation::create();
		// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
		for (int i = 1; i <= 6; i++) {
			std::string szName = StringUtils::format("player_down_%d.png", i);
			// ������ͼƬ���Ϊ����֡��������֡��
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
		}
		// ���ö������ŵ����ԣ�3��/15֡
		animation->setDelayPerUnit(1.0f / 6.0f);

		// ���ö���֡����AnimationCache�������ж����Ͷ���֡
		AnimationCache::getInstance()->addAnimation(animation, "walk");
		// �޴Ӷ���֡����AnimationCache�л�ȡ֮ǰ����Ķ���
		auto walk = AnimationCache::getInstance()->getAnimation("walk");
		// �ߴ�����������
		auto animate = Animate::create(walk);
		// �ྫ��ִ�ж���
		_player->runAction(animate);
		auto moveTo = MoveTo::create(0.06, _player->getPosition() + Vec2(offsetX, offsetY));
		_player->runAction(moveTo);
	}
}
// ����Ļ����ת��ΪTileMap���꣬��ʱû��
Vec2 GameScene::tileCoordForPosition(Vec2 position)
{// CC_CONTENT_SCALE_FACTOR Retina����2�����򷵻�1
 // ���λ�õ�x���Ե�ͼ�Ŀ��õ����ǵ�ͼ����ĵڼ������ӣ�tile��
 // ��ͼ����㣺26[����] * 64[ͼ��Ŀ�] = 1680[��ͼ��]
 // ���羫���ڵ�x������640���������ڵ�ͼ�ĸ��Ӽ��㣺640[����λ��] / 64[ͼ��Ŀ�] = 10 [����]
	int x = (int)(position.x / (map->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	// ���λ�õ�y���Ե�ͼ�ĸߣ��õ����ǵ�ͼ����ڼ������ӣ�tile����
	// ������Ϊcocos2d-x��y�ᣨ���½ǣ���TileMap��y�ᣨ���Ͻǣ����෴������ʹ�õ�ͼ�ĸ߶ȼ�ȥ���λ�õ�y
	float pointHeight = map->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((map->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x,y);
}

