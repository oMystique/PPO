#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

static const std::string BACKGROUND_MENU_IMAGE_PATH = "background_menu.png";
static const std::string PLAYERS_BUTTON_NONCLICKED_IMAGE_PATH = "2players_nonclicked.png";
static const std::string PLAYERS_BUTTON_CLICKED_IMAGE_PATH = "2players_clicked.png";


Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create(BACKGROUND_MENU_IMAGE_PATH);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//backgroundSprite->setScale(BACKGROUND_SPRITE_SCALE);
	this->addChild(backgroundSprite);

	auto playItem = MenuItemImage::create(PLAYERS_BUTTON_NONCLICKED_IMAGE_PATH, PLAYERS_BUTTON_CLICKED_IMAGE_PATH, 
		CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	return true;
}


void MainMenuScene::goToGameScene(cocos2d::Ref *sender)
{
	auto scene = CMainScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}