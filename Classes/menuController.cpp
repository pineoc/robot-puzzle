#include "menuController.h"

menuController::menuController(int _sceneNum)
{
	sceneNum = _sceneNum;

	//base layout create & setup
	baseLayout = Layout::create();
	baseLayout->setAnchorPoint(Vec2(0.5, 0.5));
	baseLayout->setPosition(Vec2());//will change
	baseLayout->setSize(Size(1080, 260));

	//background sprite setup
	layoutBackgroundSpr = Sprite::create("menu1.png");
	layoutBackgroundSpr->setAnchorPoint(Vec2());
	layoutBackgroundSpr->setPosition(Vec2());
	//TODO: animation
	baseLayout->addChild(layoutBackgroundSpr, 0);

	//scrollview setup
	scrollview = ScrollView::create();
	scrollview->setAnchorPoint(Vec2());
	scrollview->setPosition(Vec2(250, 50));
	scrollview->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollview->setSize(Size(700, 190));
	scrollview->setInnerContainerSize(Size(1400, 190));
	//for test
	scrollview->addEventListener(CC_CALLBACK_2(menuController::scrollEvent, this));
	baseLayout->addChild(scrollview, 1);

	//scrollview set percent with scene number
	setScrollViewPosition();

	//arrow btns setup
	//left arrow btn setup
	leftBtn = Button::create("left_arrow.png", "left_arrow_s.png");
	leftBtn->setPosition(Vec2(180, 130));
	leftBtn->setTag(10);
	leftBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	baseLayout->addChild(leftBtn, 2);

	//right arrow btn setup
	rightBtn = Button::create("right_arrow.png", "right_arrow_s.png");
	rightBtn->setPosition(Vec2(900, 130));
	rightBtn->setTag(11);
	rightBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	baseLayout->addChild(rightBtn, 2);

	//btns setup
	btn1 = Button::create("menu_1.png", "menu_1_s.png");
	btn1->setPosition(Vec2(100, 190.0 / 2));
	btn1->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn1->setTag(1);
	scrollview->addChild(btn1, 1);

	btn2 = Button::create("menu_2.png", "menu_2_s.png");
	btn2->setPosition(Vec2(300, 190.0 / 2));
	btn2->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn2->setTag(2);
	scrollview->addChild(btn2, 1);

	btn3 = Button::create("menu_3.png", "menu_3_s.png");
	btn3->setPosition(Vec2(500, 190.0 / 2));
	btn3->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn3->setTag(3);
	scrollview->addChild(btn3, 1);

	btn4 = Button::create("menu_4.png", "menu_4_s.png");
	btn4->setPosition(Vec2(700, 190.0 / 2));
	btn4->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn4->setTag(4);
	scrollview->addChild(btn4, 1);

	btn5 = Button::create("menu_5.png", "menu_5_s.png");
	btn5->setPosition(Vec2(900, 190.0 / 2));
	btn5->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn5->setTag(5);
	scrollview->addChild(btn5, 1);

	btn6 = Button::create("menu_6.png", "menu_6_s.png");
	btn6->setPosition(Vec2(1100, 190.0 / 2));
	btn6->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn6->setTag(6);
	scrollview->addChild(btn6, 1);
}

menuController::~menuController()
{
	baseLayout->autorelease();
}

Layout* menuController::getMenuLayout()
{
	if (baseLayout)
		return baseLayout;
}

void menuController::setScrollViewPosition()
{
	switch (sceneNum)
	{
	case 1:
		scrollview->jumpToPercentHorizontal(0.0f);//will change
		break;
	case 2:
		scrollview->jumpToPercentHorizontal(0.0f);//will change
		break;
	case 3:
		scrollview->jumpToPercentHorizontal(0.0f);//will change
		break;
	case 4:
		scrollview->jumpToPercentHorizontal(0.0f);//will change
		break;
	case 5:
		scrollview->jumpToPercentHorizontal(0.0f);//will change
		break;
	case 6:
		scrollview->jumpToPercentHorizontal(0.0f);//will change
		break;
	default:
		break;
	}
}

void menuController::setMenuLayoutPosition(float x, float y)
{
	baseLayout->setPosition(Vec2(x, y));
}

void menuController::btnsListener(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{
		Button* btn = (Button*)pSender;
		int tag = btn->getTag();
		switch (tag)
		{
		case 1://goto bone scene
			//TODO: scrollview move to 0.0
			scrollview->jumpToPercentHorizontal(0.0);
			//TODO: btn set selected
			break;
		case 2://goto moter scene
			//TODO: scrollview move to 25.0
			scrollview->jumpToPercentHorizontal(25.0);
			//TODO: btn set selected
			break;
		case 3://goto power scene
			//TODO: scrollview move to 45.0
			scrollview->jumpToPercentHorizontal(45.0);
			//TODO: btn set selected
			break;
		case 4://goto hand scene
			//TODO: scrollview move to 65.0
			scrollview->jumpToPercentHorizontal(65.0);
			//TODO: btn set selected
			break;
		case 5://goto head scene
			//TODO: scrollview move to 85.0
			scrollview->jumpToPercentHorizontal(85.0);
			//TODO: btn set selected
			break;
		case 6://goto armor scene
			//TODO: scrollview move to 100.0
			scrollview->jumpToPercentHorizontal(100.0);
			//TODO: btn set selected
			break;
		case 10://left arrow, slide position to left

			break;
		case 11://right arrow, slide position to right

			break;
		default:
			break;
		}
	}
}

void menuController::scrollEvent(Ref* pSender, ScrollView::EventType type)
{
	CCLOG("scroll percent : %f", scrollview->getPositionPercent().x);
}
