#include"Player.h"

bool Player::init1(int a)
{
	_setPlayer = a;
	if (_setPlayer == 1)
	{
		_player = Sprite::create("player_down_1.png");
		_player->setAnchorPoint(_player->getAnchorPoint() + Vec2(0, -0.5));
		_player_texture_left = CCTextureCache::sharedTextureCache()->addImage("player_left_1.png");
		_player_texture_right = CCTextureCache::sharedTextureCache()->addImage("player_right_1.png");
		_player_texture_up = CCTextureCache::sharedTextureCache()->addImage("player_up_1.png");
		_player_texture_down = CCTextureCache::sharedTextureCache()->addImage("player_down_1.png");
		this->addChild(_player);
	}
	else if (_setPlayer == 2)
	{
		_player = Sprite::create("player2_down_1.png");
		_player->setAnchorPoint(_player->getAnchorPoint() + Vec2(0, -0.5));
		_player_texture_left = CCTextureCache::sharedTextureCache()->addImage("player2_left_1.png");
		_player_texture_right = CCTextureCache::sharedTextureCache()->addImage("player2_right_1.png");
		_player_texture_up = CCTextureCache::sharedTextureCache()->addImage("player2_up_1.png");
		_player_texture_down = CCTextureCache::sharedTextureCache()->addImage("player2_down_1.png");
		this->addChild(_player);
	}
	
	return true;
}
void Player::ForeverMove(int code) {

	Animate* animate;
	std::string Name = "player";
	if(_setPlayer == 2)
		Name = "player2";
	_player->stopAllActions();
	switch (code) {
	case keyBoard_left:
		animate = getAnimateByName(Name + "_left_", 0.1f, 6);
		break;
	case keyBoard_right:
		animate = getAnimateByName(Name + "_right_", 0.1f, 6);
		break;
	case keyBoard_up:
		animate = getAnimateByName(Name + "_up_", 0.05f, 6);
		break;
	case keyBoard_down:
		animate = getAnimateByName(Name + "_down_", 0.1f, 6);
		break;
	}
	//����һ������ �ظ�ִ�ж���
	auto repeatAnimate = RepeatForever::create(animate);
	_player->runAction(repeatAnimate);
}
void Player::StandMove(int code)
{
	_player->stopAllActions();
	if (keyBoard_left == code) {
		_player->setTexture(_player_texture_left);
	}
	else if (keyBoard_right == code) {
		_player->setTexture(_player_texture_right);
	}
	else if (keyBoard_up == code) {
		_player->setTexture(_player_texture_up);
	}
	else if (keyBoard_down == code) {
		_player->setTexture(_player_texture_down);
	}
}
Animate * Player::getAnimateByName(std::string animName, float delay, int animNum)
{
	// ����һ������
	Animation* animation = Animation::create();
	// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
	for (unsigned int i = 1; i <= animNum; i++) {
		std::string frameName = animName;

		//�ڶ���֡���ƺ�������
		frameName.append(StringUtils::format("%d", i)).append(".png");
		animation->addSpriteFrameWithFile(frameName.c_str());
	}
	//���ö�����ʱ
	animation->setDelayPerUnit(delay);

	//�ڲ����궯��ʱ�ָ�����ʼ֡
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);

	return animate;
}

Animate * Player::die()
{
	auto animation = Animation::create();
	if (_setPlayer == 1)
	{
		for (int i = 1; i <= 11; i++) {
				animation->addSpriteFrameWithFileName(StringUtils::format("player_die_%d.png", i));
			}
	}
	else if (_setPlayer == 2)
	{
		for (int i = 1; i <= 11; i++) {
			animation->addSpriteFrameWithFileName(StringUtils::format("player2_die_%d.png", i));
		}
	}
	// ���ö������ŵ����ԣ�3��/15֡
	animation->setDelayPerUnit(1.0f / 3.0f);
	// �þ�������ڶ���ִ�����ָ������״̬
	animation->setRestoreOriginalFrame(false);
	auto action = Animate::create(animation);
	return action;
}

void Player::setdie()
{
	isalive = false;
}

bool Player::getisalive()
{
	return isalive;
}




