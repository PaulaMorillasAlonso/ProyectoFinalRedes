#pragma once
#include "../../NetUtils/GameObject.h"
#include "Platform.h"
#include <string>
#include <iostream>
//class GameClient;
class Player : public GameObject {

public:

    Player(std::string nickname);
    ~Player();

    std::string getNick(){
        return nick_;
    };
    SDL_Scancode handleInput(const SDL_Event &event) override;

    void setKeys(SDL_Scancode left, SDL_Scancode right);
    void setVelY(float newVel) {
        velY_ = newVel;
    }

    float getVelY() {
        return velY_;
    }

    float getJumpVel(){
        return jumpVel_;
    }
    

	void onPlatformCollision(Platform* other) {};
	void onReachBottom() {};

private:

    float velY_;
    float gravity_;
    float jumpVel_;
    const float PLAYER_MOVEMENT_=5;
    std::string nick_;

	SDL_Scancode left_, right_;//,up_;
};
