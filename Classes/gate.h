#ifndef __GATE_H__
#define __GATE_H__

#include "cocos2d.h"
#include <string>
#include "DataSetting.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class gate
{
public:
	//letter image
	string imageLetter;

	gate();
	~gate();
	void setImage(string letterURI);
	
	//get sprite
	Sprite* getLetter();
	Layout* getBackGround();

	//create
	void createLetter();
	void createBackGr();

	//touch Event
	void addEvent();
	bool onTouchBegan(Touch *touch, Event *unused_event); // ���� ����
	void onTouchMoved(Touch *touch, Event *unused_event); // �巡��
	void onTouchEnded(Touch *touch, Event *unused_event); // �� ����
	void onTouchCancelled(Touch *touch, Event *unused_event); // ��ġ�� ��ҵ�

	//delete scheduler
	void deleteLayout();
	void removeLayout();
private:
	//letter sprite
	Sprite* spriteLetter;
	
	//background
	Layout* layoutBackGr;

	//positions
	Vec2 letterPos;	
};

#endif //__GATE_H__