/*
 * ElementsGame.cpp
 *
 *  Created on: 23.02.2016
 *      Author: User
 */

#include "ElementsGame.h"

ElementsGame::ElementsGame() {
	// TODO Auto-generated constructor stub
	//log("ElementsGame()");
	lockTouch_ = false;
	rotate_ = true;
	elementActive_ = false;
	elementType_ = 0;
	orientation_ = 0;
}

ElementsGame::~ElementsGame() {
	// TODO Auto-generated destructor stub
	//log("~ElementsGame()");
	std::pair<int, int>().swap(posElementInArray_);
}


ElementsGame* ElementsGame::create(int elementTag) {

	ElementsGame* image = new ElementsGame();
	if (image && image->init())
    {
        image->autorelease();

		CCString *path;
		CCString *name;

		switch (elementTag)
		{
		case kElectricWireBattery:
			name = CCString::create("Picture/4-");
			image->_addBatteryAnimation();
			break;
		case kElectricWireChudik:
			name = CCString::create("Picture/4-");
			image->_addChudikAnimation();
			break;
		case kElectricWire1:
			name = CCString::create("Picture/5-");
			break;
		case kElectricWire2:
			name = CCString::create("Picture/6-");
			break;
		case kElectricWire3:
			name = CCString::create("Picture/7-");
			break;
		default:
			break;
		}

		path = CCString::createWithFormat("%s1.png", name->getCString());
		image->loadTexture(path->getCString(), UI_TEX_TYPE_PLIST);
		image->setTouchEnabled(true);
		image->setName(name->getCString());

		int orientation = 0;

		if (elementTag >= kElectricWire1)
			orientation = rand() % 4;

		image->setRotation(elementTemplates[elementTag][orientation].angle);
		image->_setElementOrientation(orientation);
		image->_setElementType(elementTag);

		return image;
    }
	CC_SAFE_DELETE(image);
    return NULL;
}

// функция поворачивает элемент на 0 градусов по часовой стрелке
void ElementsGame::setRotateElementClockwise() {

	if (lockTouch_ || !rotate_)	return;

	lockTouch_ = true;
	float duration = 0.2f;
	CCActionInterval *rotateElement = CCRotateBy::create(duration, 90.0f);

	CCSequence *sequenceElement = CCSequence::create(rotateElement, CallFuncN::create(CC_CALLBACK_1(ElementsGame::_callbackRotate, this)), nullptr);		// v3
	//CCSequence *sequenceElement = CCSequence::create(rotateElement, CCCallFuncN::create(this, callfuncN_selector(ElementsGame::_callbackRotate)), nullptr); // v2 + v3
	this->runAction(sequenceElement);

	orientation_++;
	if (orientation_ > 3)
		orientation_ = 0;
}

// ункция обратного вызова при развороте
void ElementsGame::_callbackRotate(CCNode * Node) {
	lockTouch_ = false;
}

// функция добавляет анимацию чудика
void ElementsGame::_addChudikAnimation() {
	cocostudio::Armature * armature = cocostudio::Armature::create("chudik");
	this->addChild(armature, 1, kChudikAnimationTag);
	armature->getAnimation()->playWithIndex(0);
	armature->setPosition(Vec2(armature->getContentSize().width/2, armature->getContentSize().height/2));
	rotate_ = false;
}

// функция добавляет анимацию аккумулятора
void ElementsGame::_addBatteryAnimation() {
	cocostudio::Armature *armature = cocostudio::Armature::create("battery");
	this->addChild(armature, 1, kBatteryAnimationTag);
	armature->getAnimation()->playWithIndex(0);
	armature->setPosition(Vec2(armature->getContentSize().width / 2, armature->getContentSize().height / 2));
	rotate_ = false;
}

// функция добавляет анимацию аккумулятора
void ElementsGame::setElementActive(bool active) {

	int activeTag = active ? 2 : 1;

	CCString *pathTexture = CCString::createWithFormat("%s%d.png", this->getName().c_str(), activeTag);
	this->loadTexture(pathTexture->getCString(), UI_TEX_TYPE_PLIST);

	if (this->getChildByTag(kChudikAnimationTag)) {
		cocostudio::Armature *armature = static_cast<cocostudio::Armature *>(this->getChildByTag(kChudikAnimationTag));
		armature->getAnimation()->playWithIndex(activeTag - 1);
	}

	elementActive_ = active;
}


bool ElementsGame::isElementActive() {
	return elementActive_;
}

void ElementsGame::_setElementOrientation(int orientation) {
	orientation_ = orientation;
}

void ElementsGame::_setElementType(int elementType) {
	elementType_ = elementType;
}

int ElementsGame::getElementOrientation() {
	return orientation_;
}

int ElementsGame::getElementType() {
	return elementType_;
}


std::pair<int, int> ElementsGame::getPosElementInArray() {
	return posElementInArray_;
}


void ElementsGame::setPosElementInArray(std::pair<int, int> posElementInArray2) {
	posElementInArray_ = posElementInArray2;
}