#include "GameInputManager.h"
#include "Scenes/SceneManager.h"

void GameInputManager::Init()
{
    Input::Init();

    keyControls.insert(std::pair<string, KEYCODE>("MoveRight", KEY_RIGHT));
    keyControls.insert(std::pair<string, KEYCODE>("MoveLeft", KEY_LEFT));
    keyControls.insert(std::pair<string, KEYCODE>("MoveUp", KEY_UP));
    keyControls.insert(std::pair<string, KEYCODE>("MoveDown", KEY_DOWN));
    keyControls.insert(std::pair<string, KEYCODE>("Shoot", KEY_SPACE));
    keyControls.insert(std::pair<string, KEYCODE>("ResetScene", KEY_R));
}

void GameInputManager::WhenKeyPressed(KEYCODE keyCode, Player* player)
{
    Input::OnKeyPressed(keyCode);

    if (keyCode == keyControls["MoveRight"]) {
        player->AnimatePlayer(KEY_RIGHT);
        player->SetMoveCharX(1);
    }
    else if (keyCode == keyControls["MoveLeft"]) {
        player->AnimatePlayer(KEY_LEFT);
        player->SetMoveCharX(-1);
    }
    else if (keyCode == keyControls["MoveUp"]) {
        player->AnimatePlayer(KEY_UP);
        player->SetMoveCharY(1);
    }
    else if (keyCode == keyControls["MoveDown"]) {
        player->AnimatePlayer(KEY_DOWN);
        player->SetMoveCharY(-1);
    }
    else if (keyCode == keyControls["Shoot"]) {
        // player shoot here
    }
    else if (keyCode == keyControls["ResetScene"]) {
        Input::OnKeyPressed(KEY_R);
        //SceneManager::GetInstance()->ChangeScene("HelloWorld");
    }

}

void GameInputManager::WhenKeyReleased(KEYCODE keyCode, Player* player)
{
    Input::OnKeyReleased(keyCode);

    if (keyCode == keyControls["MoveRight"]) {
        if (Input::IsKeyHeld(KEY_LEFT))
            player->SetMoveCharX(-1);
        else
            player->SetMoveCharX(0);
        //	mainPlayer->setLeftOrRight(1, false);
        //RightPressed = false;
    }
    else if (keyCode == keyControls["MoveLeft"]) {
        if (Input::IsKeyHeld(KEY_RIGHT))
            player->SetMoveCharX(1);
        else
            player->SetMoveCharX(0);
        //	mainPlayer->setLeftOrRight(-1, false);//LeftPressed = false;
    }
    else if (keyCode == keyControls["MoveUp"]) {
        if (Input::IsKeyHeld(KEY_DOWN))
            player->SetMoveCharY(-1);
        else
            player->SetMoveCharY(0);
        //mainPlayer->setUpOrDown(1, false);
    }
    else if (keyCode == keyControls["MoveDown"]) {
        if (Input::IsKeyHeld(KEY_UP))
            player->SetMoveCharY(1);
        else
            player->SetMoveCharY(0);
        //mainPlayer->setUpOrDown(-1, false);
    }
    else if (keyCode == keyControls["Shoot"]) {
        // player shoot here
    }
    else if (keyCode == keyControls["ResetScene"]) {
        SceneManager::GetInstance()->ChangeScene("HelloWorld");
    }

}