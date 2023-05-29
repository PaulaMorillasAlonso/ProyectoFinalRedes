#include "GameObject.h"

#include <SDL2/SDL_image.h>
#include "SDLGame.h"
#include "../SDL_Utils/macros.h"
int GameObject::numObjects=0;

GameObject::GameObject() : tr_(), dim_(), rotation(0), text_(nullptr), textDim_() {
		enabled_ = true;
		game_=SDLGame::GetInstance();
		numObjects++;
}
GameObject::GameObject(std::string name) : tr_(), dim_(), rotation(0), text_(nullptr), textDim_() {
		enabled_ = true;
		game_=SDLGame::GetInstance();
		name_=name;
		numObjects++;
}
GameObject::~GameObject() {
    if(text_ != nullptr)
        SDL_DestroyTexture(text_);
    game_=nullptr;
}

void GameObject::setTransform(const int x, const int y) {
    tr_.set(x, y);
}

void GameObject::setTransform(Vector2D tr) {
    tr_.set(tr);
}

void GameObject::setRotation(const float rot) {
    rotation = rot;
}

void GameObject::setDimensions(int w, int h) {
    
    dim_.set(w, h);

}

Vector2D GameObject::getDimensions() const {
    return dim_;
}

Vector2D GameObject::getTransform() const {
    return tr_;
}

void GameObject::setTexture(const std::string &path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
        throw "Couldn't load image: " + path;

    text_ = SDL_CreateTextureFromSurface(game_->getRenderer(), surface);
    if (text_ == nullptr) {
        SDL_FreeSurface(surface);
        throw "Couldn't load image: " + path;
    }
    if(name_==""){
        name_=path+std::to_string(numObjects);
    }

    SDL_FreeSurface(surface);
}
SDL_Texture* GameObject::getTexture(){
    return text_;
}
void GameObject::render()
{
    assert(text_ != nullptr);

    SDL_Rect src = build_sdlrect(0, 0, textDim_.getX(), textDim_.getY());
    SDL_Rect dest = build_sdlrect(tr_, dim_.getX(), dim_.getY());
    render(src, dest);
}

void GameObject::render(const SDL_Rect &src, const SDL_Rect &dest,
                const SDL_Point *p, SDL_RendererFlip flip)
{
    game_->GetInstance();
    SDL_RenderCopyEx(game_->getRenderer(), text_, &src, &dest, rotation, p, flip);
}
std::string GameObject::getName(){
    return name_;
}