#include "SceneManager.h"

// Scenes
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "OptionsPageScene.h"
#include "FacebookScene.h"

void SceneManager::Init()
{
    auto director = Director::getInstance();

    auto scene = MainMenu::createScene();
    //Scene* scene2 = HelloWorld::createScene();
    //
    //listOfScenes.insert(std::pair<string, Scene*>("MainMenu", scene));
    //listOfScenes.insert(std::pair<string, Scene*>("HelloWorld", scene2));

    // run
    director->runWithScene(scene);
}

void SceneManager::ChangeScene(string name)
{
    //CCDirector::getInstance()->replaceScene(
    //    TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));

    //Director::getInstance()->getEventDispatcher()->setEnabled(false);

    //map<string, Scene*>::iterator it;
    //it = listOfScenes.find(name);
    //
    //auto scene = it->second;

    CCDirector::getInstance()->pause();

    Scene* scene;
	if (name == "MainMenu") {
		scene = MainMenu::createScene();

		CCDirector::getInstance()->replaceScene(
			TransitionFade::create(0.f, scene, Color3B(0, 50, 50)));
	}
	else if (name == "HelloWorld") {
		scene = HelloWorld::createScene();

		CCDirector::getInstance()->replaceScene(
			TransitionFade::create(1.f, scene, Color3B(0, 50, 50)));
	}
	else if (name == "OptionsPage") {
		scene = OptionsPage::createScene();

		CCDirector::getInstance()->replaceScene(
			TransitionFade::create(0.f, scene, Color3B(0, 50, 50)));
	}
    else if (name == "FacebookScene") {
        scene = FacebookScene::createScene();

        CCDirector::getInstance()->replaceScene(
			TransitionFade::create(0.f, scene, Color3B(0, 50, 50)));
    }

    CCDirector::getInstance()->resume();
}