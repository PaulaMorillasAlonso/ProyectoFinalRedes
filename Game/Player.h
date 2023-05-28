/*#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../SDL_Utils/GameObject.h"
#include "../GameClient.h"

class Player : public GameObject {

public:
    Player(GameClient* game);
    ~Player();

    void handleInput(const SDL_Event &event) override;
    void update() override;
    void render() override;

    void setKeys(SDL_Scancode left, SDL_Scancode right);

    void setVelX(float newVel) {
        vel_.setX(newVel);
    }

    void setVelY(float newVel) {
        vel_.setY(newVel);
    }

private:
    GameClient* app_;

    Vector2D vel_;
    float gravity_;
    float jumpVel_;

    MoodleJumpMessageClient::InputType key;
	SDL_Scancode left_, right_;
};
#endif*/