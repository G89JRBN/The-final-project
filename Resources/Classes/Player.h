/**
* �ڲ�����Sprite
* ����ͨ��ForeverMove��StandMove�����ƶ�
* ĿǰĬ�Ͻ�ɫ�������Ժ������ӽ�ɫѡ����
*/
#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"
#include"KeyBoard.h"
USING_NS_CC;

class Player :public Layer
{
public:
	virtual bool init();
	//������Զִ���������
	CC_SYNTHESIZE(Sprite*, player, Player);
	void ForeverMove(int code);
	void StandMove(int code);

	//ͨ���������ֵõ���Ӧ�Ķ���
	Animate* getAnimateByName(std::string animName, float delay, int animNum);
	Sprite* _player;  // ��Ҿ���
	CREATE_FUNC(Player);
private:
	
	//�����ҡ��ϡ��µľ�̬ͼƬ�������Ӧ�����ƶ�ʱ���ô���ͼ�����滻
	CCTexture2D *_player_texture_left;
	CCTexture2D *_player_texture_right;
	CCTexture2D *_player_texture_up;
	CCTexture2D *_player_texture_down;
};
#endif