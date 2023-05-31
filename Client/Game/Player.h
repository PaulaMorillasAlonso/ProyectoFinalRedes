#include "../../NetUtils/GameObject.h"
#include <string>

class GameClient;


class Player : public GameObject {

public:

    Player(std::string nickname);
    ~Player();

    std::string getNick(){
        return nick_;
    };

    /*
    void handleInput(const SDL_Event &event) override;
    void update() override;
    void render() override;

    void setKeys(SDL_Scancode up,SDL_Scancode left, SDL_Scancode right);

    void setVelX(float newVel) {
        vel_.setX(newVel);
    }

    void setVelY(float newVel) {
        vel_.setY(newVel);
    }
    */

private:

    GameClient *client_;

    Vector2D vel_;
    float gravity_;
    float jumpVel_;

    std::string nick_;
    //MoodleJumpMessageClient::InputType key;
	SDL_Scancode left_, right_,up_;
};
