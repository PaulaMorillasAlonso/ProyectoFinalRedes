#include "Player.h"


Player::Player(std::string nickname) : GameObject(), vel_(), gravity_(-9.8), jumpVel_(50.0) {

	nick_=nickname;
	setDimensions(50,50);
}

Player::~Player() {}

/*void Player::handleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN){
		key = MoodleJumpMessageClient::InputType::NONE;
		
		if (e.key.keysym.scancode == left_){
			key = MoodleJumpMessageClient::InputType::LEFT;
			// rotation = (rotation - 5.0f);
		}
		else if (e.key.keysym.scancode == right_){
			key = MoodleJumpMessageClient::InputType::RIGHT;
			// rotation = (rotation + 5.0f);
		}

		app_->sendGameMessage(key);
	}
}

void Player::update() {
    tr_.setX(tr_.getX() + vel_.getX());
    tr_.setY(tr_.getY() + vel_.getY());

    vel_.setY(vel_.getY() + gravity_);

	if (tr_.getX() > GameManager::instance()->getWindowSize().getX())
		tr_.setX(0);
	else if (tr_.getX() < 0)
		tr_.setX(GameManager::instance()->getWindowSize().getX());
}

void Player::render() {
	GameObject::render();
}

void Player::setKeys(SDL_Scancode left, SDL_Scancode right) {
	left_ = left;
	right_ = right;
}*/