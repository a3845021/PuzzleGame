/*
* SceneWin.cpp
*
*  Created on: 23.02.2016
*      Author: User
*/

#include "SceneWin.h"

Scene* SceneWin::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneWin::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneWin::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SceneWin::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "SceneWin" splash screen"
    auto sprite = Sprite::create("SceneWin.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("SceneWin.csb");
	static_cast<ImageView *>(rootNode->getChildByName("ImageButton"))->addTouchEventListener(CC_CALLBACK_2(SceneWin::_buttonTouch, this));

    this->addChild(rootNode);

	ActionTimeline *action = CSLoader::createTimeline("SceneWin.csb");
	rootNode->runAction(action);

    return true;
}


// функция обрабатывает нажатие на кнопку
void SceneWin::_buttonTouch(Ref* pSender, Widget::TouchEventType type)
{
	float scalePersent = 1.1f;

	if (type == Widget::TouchEventType::BEGAN) {
		ImageView *button = (ImageView *)pSender;
		button->setScale(button->getScale()*scalePersent);
	}

	if (type == Widget::TouchEventType::ENDED) {
		ImageView *button = (ImageView *)pSender;
		button->setScale(button->getScale() / scalePersent);

		// показать экран игры
		if (1002 == button->getTag()) {

			CCScene *scene = SceneGame::createScene();
			CCScene* transition = TransitionFade::create(0.1f, scene);
			if (transition) {
				Director::getInstance()->replaceScene(transition);				// v 3
				//CCDirector::sharedDirector()->replaceScene(transition);		// v 2
			}
		}
	}

	if (type == Widget::TouchEventType::CANCELED) {
		ImageView *button = (ImageView *)pSender;
		button->setScale(button->getScale() / scalePersent);
	}

}