#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include"Player.h"
#include"MapLayer.h"
#include "SpriteGift.h"
#include"KeyBoard.h"
#include "AudioControlScene.h"
#include "MenuSwitch.h"
#include "pop.h"
#include "Fail.h"
#include "PassTheGame.h"

USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:
	//����Scene����
	static cocos2d::Scene* createScene();
	//init��������ɳ�ʼ������
	virtual bool init();
	//���̰��º������
	void keyPressedDuration(float delta);
	/**
	*��player�ŵ�����Ϊê�㣬����������Ϊԭ��
	*�����˸����㣬ÿ�δ�����Ҫʹ�õĵ�
	*���м�⣬�����һ��Ҫ�����ϰ����ֹͣ������1���أ���ֹ��ס��
	*/
	void rightMove(int Move,int flag1,int flag2,int flag3);
	// �ص����º������ú���ÿһ֡�������
	void update(float delta);
	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	CREATE_FUNC(GameScene);
	//�ж��Ƿ�������ϰ���
	bool collide(Vec2 position,int type);
	//�ж��Ƿ���������
	void giftcollide(float delta);
	void playAnimate();
	void collisionDetection(float delta);
	void Fail();
	void Pass();
private:

	//���̰�����¼
	KeyBoard *key;
	MapLayer * map;  // ��ͼ
	Player* _player;  // ��Ҿ���
	Vector<Pop*> _popVector;//���ݲ�
	Vector<Sprite*> _breakableBlockVector;//�ɱ�ը������
	Vector<SpriteGift*> _giftVector;//��������
	Vector<Sprite*>_pop;
	int power = 1;//��������
	int popMax = 1;//�����������
	double addSpeed = 0;//��Ь�Ӻ����ӵ��ٶ�
	bool on_pop=false;
	int record=-1;
	//��¼�ϴ��ж�������������
	bool moveRecord[4] = { false,false,false,false };
	double move[4][2] = { { -1.5,0 },{ 1.5,0 },{ 0,1.5 },{ 0,-1.5 } };
	bool a = false;
};

#endif
