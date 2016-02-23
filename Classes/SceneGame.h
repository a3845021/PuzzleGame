/*
* SceneGame.h
*
*  Created on: 23.02.2016
*      Author: User
*/

#ifndef __SCENEGAME_SCENE_H__
#define __SCENEGAME_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "ElementsGame.h"
#include "SceneWin.h"


USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;
using namespace std;



class SceneGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SceneGame);

	virtual ~SceneGame();

protected:

	enum enumSceneGame
	{
		kElementMapCount = 5,
		kElementTag = 100,
		kBlankArea = 9999,
	};

	void _elementTouch(cocos2d::Ref*, Widget::TouchEventType eventType);
	void _updateGame(float dt);
	void _switchSceneWin(float dt);

	void _setActivateWire(std::vector<std::pair<int, int> > path);

	void _setClearGameMap();
	void _setUpdateGameMap();

	void _checkWaveAlgorithm(std::pair<int, int> startPos, std::pair<int, int> endPos);
	std::vector<std::pair<int, int> >_getPathInWaveAlgorithm(std::pair<int, int> startPos, std::pair<int, int> endPos);



	int map_[kElementMapCount][kElementMapCount];
	int gameMap_[kElementMapCount*GRID_LENGTH + 2][kElementMapCount*GRID_LENGTH + 2];

	Vector<ElementsGame *> element_;
	std::vector<std::pair<int, int> > wave_;

};

#endif // __SCENEGAME_SCENE_H__
