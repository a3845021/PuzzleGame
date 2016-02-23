/*
* SceneGame.cpp
*
*  Created on: 23.02.2016
*      Author: User
*/

#include "SceneGame.h"

Scene* SceneGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool SceneGame::init()
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
                                           CC_CALLBACK_1(SceneGame::menuCloseCallback, this));
    
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

    // add "SceneGame" splash screen"
    auto sprite = Sprite::create("SceneGame.png");

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
    
	srand(time(NULL));
	element_.clear();

    auto rootNode = CSLoader::createNode("SceneGame.csb");
    this->addChild(rootNode);

	ActionTimeline *action = CSLoader::createTimeline("SceneGame.csb");
	rootNode->runAction(action);

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Plist.plist");
	//cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("Chudik/chudik.ExportJson");
	//cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("Battery/battery.ExportJson");

	int map[kElementMapCount][kElementMapCount] = { 0, 4, 3, 0, 0,
													4, 3, 5, 3, 5,
													1, 4, 3, 3, 2,
													0, 5, 3, 0, 0,
													0, 0, 2, 0, 0 };
	int elementTag = kElementTag;
	for (int i = 0; i < kElementMapCount; i++) {
		for (int j = 0; j < kElementMapCount; j++) {
			map_[i][j] = map[i][j];
			if (map[i][j]) {
				ElementsGame *element = ElementsGame::create(map[i][j]);
				element->setPosition(ccp(205.0 + 90 * j, 390.0 + 90 * (kElementMapCount - i)));
				element->addTouchEventListener(CC_CALLBACK_2(SceneGame::_elementTouch, this));
				rootNode->addChild(element, 10, kElementTag);
				elementTag++;
				element->setPosElementInArray(std::pair<int, int>(i, j));
				element_.pushBack(element);
			}
		}

	}

	this->schedule(schedule_selector(SceneGame::_updateGame), 1);

    return true;
}


SceneGame::~SceneGame() {
	element_.~Vector();
	wave_.clear();
	std::vector<std::pair<int, int> >().swap(wave_);
}


// функция обрабатывает нажатия на элементы
void SceneGame::_elementTouch(Ref* pSender, Widget::TouchEventType type)
{
	float scalePersent = 1.1f;

	if (type == Widget::TouchEventType::BEGAN) {
		ElementsGame *element = static_cast<ElementsGame *>(pSender);
		element->setScale(element->getScale()*scalePersent);
	}

	if (type == Widget::TouchEventType::ENDED) {
		ElementsGame *element = static_cast<ElementsGame *>(pSender);
		element->setScale(element->getScale() / scalePersent);

		element->setRotateElementClockwise();
	}

	if (type == Widget::TouchEventType::CANCELED) {
		ElementsGame *element = static_cast<ElementsGame *>(pSender);
		element->setScale(element->getScale() / scalePersent);
	}

}


void SceneGame::_updateGame(float dt) {

	// найти акукумулятор и чудиков
	ElementsGame *elementBattery = nullptr;
	Vector<ElementsGame *>elementChudik;
	int count = element_.size();
	for (int e = 0; e < count; e++) {

		ElementsGame *elementTemp = element_.at(e);

		if (ElementsGame::kElectricWireBattery == elementTemp->getElementType()) {
			elementBattery = elementTemp;
		}

		if (ElementsGame::kElectricWireChudik == elementTemp->getElementType()) {
			elementChudik.pushBack(elementTemp);
		}
		// сделать все элементы неактивными (отключить ток)
		elementTemp->setElementActive(false);
	
	}

	// проверить всех чудиков
	for (unsigned int i = 0; i < elementChudik.size(); i++)
	{
		// очистить массив
		this->_setClearGameMap();
		// обновить данные массива
		this->_setUpdateGameMap();
		// получить путь
		std::vector<std::pair<int, int> > path = this->_getPathInWaveAlgorithm(elementBattery->getPosElementInArray(), elementChudik.at(i)->getPosElementInArray());
		//активировать элементы 
		this->_setActivateWire(path);

	}

	// проверить игру на выигрыш
	bool gameWin = true;
	for (unsigned int i = 0; i < elementChudik.size(); i++)
	{
		if (!elementChudik.at(i)->isElementActive())
			gameWin = false;
	}

	elementChudik.clear();

	if (gameWin) {
		this->unschedule(schedule_selector(SceneGame::_updateGame));
		this->schedule(schedule_selector(SceneGame::_switchSceneWin), 1);
	}
}



// функция активирует провода, показывает что по ним проходит ток
void SceneGame::_setActivateWire(std::vector<std::pair<int, int> > path) {

	int count = element_.size();
	for (int e = 0; e < count; e++) {

		ElementsGame *elementTemp = element_.at(e);

		pair<int, int> posInMap = elementTemp->getPosElementInArray();
		int pos1 = posInMap.first * GRID_LENGTH + 2;
		int pos2 = posInMap.second * GRID_LENGTH + 2;

		for (vector<pair<int, int> >::iterator i = path.begin(); i != path.end(); ++i) {
			if (pos1 == i->first && pos2 == i->second) {
				elementTemp->setElementActive(true);
			}
		}
	}
}


// функция очищеает игровой массив
void SceneGame::_setClearGameMap() {
	for (int i = 0; i < kElementMapCount*GRID_LENGTH + 2; i++) {
		for (int j = 0; j < kElementMapCount*GRID_LENGTH + 2; j++) {
			gameMap_[i][j] = kBlankArea;
		}
	}
}

// функция обновляет данные в игровом массиве
void SceneGame::_setUpdateGameMap() {

	int count = element_.size();
	for (int e = 0; e < count; e++) {

		ElementsGame *elementTemp = element_.at(e);
		int i = elementTemp->getPosElementInArray().first;
		int j = elementTemp->getPosElementInArray().second;

		for (int ig = 0; ig < GRID_LENGTH; ig++) {

			for (int jg = 0; jg < GRID_LENGTH; jg++) {

				int value = elementTemplates[elementTemp->getElementType()][elementTemp->getElementOrientation()].grid[ig][jg] == 'X' ? -1 : kBlankArea;
				gameMap_[i*GRID_LENGTH + 1 + ig][j*GRID_LENGTH + 1 + jg] = value;
			}
		}
	}
}


// функция получает путь от начальной точки до конечной при помощи волнового алгоритма
std::vector<std::pair<int, int> >SceneGame::_getPathInWaveAlgorithm(std::pair<int, int> startPos, std::pair<int, int> endPos) {

	std::vector<std::pair<int, int> > oldwave;
	std::vector<std::pair<int, int> > wave;

	int start1 = startPos.first * GRID_LENGTH + 2;
	int start2 = startPos.second * GRID_LENGTH + 2;

	int end1 = endPos.first * GRID_LENGTH + 2;
	int end2 = endPos.second * GRID_LENGTH + 2;

	oldwave.push_back(std::pair<int, int>(start1, start2));

	int nstep = 0;
	gameMap_[start1][start2] = nstep;
	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	bool pathFind = false;
	
	// волновой проход
	while (oldwave.size() > 0 && !pathFind) {
		++nstep;
		wave.clear();
		for (vector<pair<int, int> >::iterator i = oldwave.begin(); i != oldwave.end(); ++i)
		{
			for (int d = 0; d < 4; ++d)
			{
				int nx = i->first + dx[d];
				int ny = i->second + dy[d];
				if (gameMap_[nx][ny] == -1) {
					wave.push_back(pair<int, int>(nx, ny));
					gameMap_[nx][ny] = nstep;

					// если удалось дойти до цели
					if (nx == end1 && ny == end2)
						pathFind = true;
				}
			}
		}
		oldwave = wave;
	}

	// обратный проход
	if (pathFind) {
		int x = end1;
		int y = end2;
		wave.clear();
		wave.push_back(pair<int, int>(x, y));
		while (gameMap_[x][y] != 0)
		{
			for (int d = 0; d < 4; ++d)
			{
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (gameMap_[x][y] - 1 == gameMap_[nx][ny]) {
					x = nx;
					y = ny;
					wave.push_back(pair<int, int>(x, y));
					break;
				}

			}
		}
	}

	return wave;
}

// функция переключает сцену
void SceneGame::_switchSceneWin(float dt) {
	CCScene *scene = SceneWin::createScene();
	CCScene* transition = TransitionFade::create(0.1f, scene);
	if (transition) {
		Director::getInstance()->replaceScene(transition);				// v 3
		//CCDirector::sharedDirector()->replaceScene(transition);		// v 2
	}
}