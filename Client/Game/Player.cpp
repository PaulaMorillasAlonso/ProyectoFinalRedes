#include "Player.h"
#include <iostream>
Player::Player(std::string nickname) : GameObject(), velY_(), gravity_(0.02), jumpVel_(-3) {

	nick_=nickname;
	setDimensions(50,50);
}

Player::~Player() {}

SDL_Scancode Player::handleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN){

		if (e.key.keysym.scancode == left_){

			return left_;
		}
		else if (e.key.keysym.scancode == right_){

			return right_;
		}
	}
	return SDL_SCANCODE_UNKNOWN;
}

void Player::setKeys(SDL_Scancode left, SDL_Scancode right) {
	left_ = left;
	right_ = right;
}