/*
* SceneWin.h
*
*  Created on: 23.02.2016
*      Author: User
*/

#ifndef __SCENEWIN_SCENE_H__
#define __SCENEWIN_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneGame.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;


class SceneWin : public cocos2d::Layer
{
public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SceneWin);

protected:

	void _buttonTouch(cocos2d::Ref*, Widget::TouchEventType eventType);

};

#endif // __SCENEWIN_SCENE_H__
