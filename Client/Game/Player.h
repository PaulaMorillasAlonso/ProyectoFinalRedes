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

    void update() override {
        velY_ += gravity_;

        /*
        if (tr_.getX() > GameManager::instance()->getWindowSize().getX())
            tr_.setX(0);
        else if (tr_.getX() < 0)
            tr_.setX(GameManager::instance()->getWindowSize().getX());
        */

        tr_.setY(tr_.getY() + velY_);

        // std::cout << "Pos: (" << tr_.getX() << ", " << tr_.getY() << ") VelY: " << velY_ << "\n";
    }


    // void render() override;

    void setKeys(SDL_Scancode left, SDL_Scancode right);

    /*void setVelX(float newVel) {
        vel_.setX(newVel);
    }
    */

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
