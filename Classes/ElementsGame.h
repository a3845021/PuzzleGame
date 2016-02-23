/*
 * ElementsGame.h
 *
 *  Created on: 23.02.2016
 *      Author: User
 */

#ifndef __ELEMENTSGAME_H__
#define __ELEMENTSGAME_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Template.h"


using namespace cocostudio::timeline;
USING_NS_CC;
using namespace ui;


class ElementsGame : public ImageView {

public:

	enum enumElementsGame
	{
		kElectricWireBattery = 1,
		kElectricWireChudik,
		kElectricWire1,
		kElectricWire2,
		kElectricWire3,

		kBatteryAnimationTag,
		kChudikAnimationTag,
	};

	ElementsGame();

	static ElementsGame *create(int elementTag);

	void setRotateElementClockwise();
	void setElementActive(bool active);
	bool isElementActive();

	int getElementOrientation();
	int getElementType();

	std::pair<int, int> getPosElementInArray();
	void setPosElementInArray(std::pair<int, int> posElementInArray);

	virtual ~ElementsGame();

protected:

	void _callbackRotate(CCNode * Node);
	void _addChudikAnimation();
	void _addBatteryAnimation();

	void _setElementOrientation(int orientation);
	void _setElementType(int elementType);

	bool lockTouch_;
	bool rotate_;
	bool elementActive_;
	int orientation_;
	int elementType_;
	std::pair<int, int> posElementInArray_;

};

#endif // __ELEMENTSGAME_H__
