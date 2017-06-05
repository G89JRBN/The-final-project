/**
* �ڲ���TMXTiledMap������ͨ��getMap����
* Ŀǰֻ֧��Ĭ�ϵ�ͼ������������ӵ�ͼѡ����
* ͨ��boom����ʵ�����ݱ�ը���ͼ�Ľ���
* judge_collide�����ж��ض�λ���Ƿ����ϰ���
* create_BlockVector���������ϰ�������
*/
#ifndef _MAP_LAYER_
#define _MAP_LAYER

#include "cocos2d.h"

USING_NS_CC;


class MapLayer :public Layer
{
public:
	virtual bool init();
	TMXTiledMap* getMap() { return _map; }
	bool boom(Vec2 _BubblePosition[]);
	bool judge_collide(Vec2 position);
	//�󷽸����������  
	Vec2 centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord);
	//��breakable��block�Ϸ�һ������ �����Ϳ��Է�����ײ
	void create_BlockVector(Vector<Sprite*> &_breakableBlockVector);
	CREATE_FUNC(MapLayer);
private:
	TMXTiledMap* _map;  // ��ͼ
	TMXLayer* _collidable;  // �ϰ���
	TMXLayer* _boxbottom;//�ײ�
	Vector<TMXLayer*> _layerNames;//������
};
#endif
