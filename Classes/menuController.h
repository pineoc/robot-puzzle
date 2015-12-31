#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class menuController
{
private:
	//scene number
	int sceneNum;
	
	//base Layout
	Layout* baseLayout;

	//layout background
	Sprite* layoutBackgroundSpr;

	//Scroll view
	ScrollView* scrollview;

	//menu btns
	Button* btn1;//bone
	Button* btn2;//moter
	Button* btn3;//power
	Button* btn4;//hand
	Button* btn5;//head
	Button* btn6;//armor

	//arrow btns
	Button* leftBtn;
	Button* rightBtn;

public:
	//make menu layout
	menuController(int _sceneNum);
	//delete menu layout
	~menuController();

	//get menuLayout
	Layout* getMenuLayout();

	//set menuLayout - scrollView position
	void setScrollViewPosition();

	//set menulayout - position
	void setMenuLayoutPosition(float x, float y);

	//menu button items listener
	void btnsListener(Ref* pSender, Widget::TouchEventType type);
	//scrollEvent
	void scrollEvent(Ref* pSender, ScrollView::EventType type);

};

