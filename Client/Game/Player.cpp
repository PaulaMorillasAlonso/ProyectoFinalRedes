#include "Player.h"
#include <iostream>
Player::Player(std::string nickname) : GameObject(), velY_(), gravity_(0.02), jumpVel_(-5) {

	nick_=nickname;
	setDimensions(50,50);
}

Player::~Player() {}

SDL_Scancode Player::handleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN){

		if (e.key.keysym.scancode == left_){

			setTransform(getTransform().getX()-PLAYER_MOVEMENT_,getTransform().getY());
			return left_;
		}
		else if (e.key.keysym.scancode == right_){

			setTransform(getTransform().getX()+PLAYER_MOVEMENT_,getTransform().getY());
			return right_;
		}
	}
	return SDL_SCANCODE_UNKNOWN;
}

/*
void Player::update() {
	velY_ += gravity_;

	/*
	if (tr_.getX() > GameManager::instance()->getWindowSize().getX())
		tr_.setX(0);
	else if (tr_.getX() < 0)
		tr_.setX(GameManager::instance()->getWindowSize().getX());
	*/

/*
	tr_.setY(tr_.getY() + velY_);
}
*/

/*
void Player::render() {
	GameObject::render();
}
*/

void Player::setKeys(SDL_Scancode left, SDL_Scancode right) {
	left_ = left;
	right_ = right;
}