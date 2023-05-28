#include "GameObject.h"

#include <SDL2/SDL_image.h>
#include "SDLGame.h"
#include "../SDL_Utils/macros.h"

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
    int x = 570;  // X-coordinate of the position
    int y = 400;  // Y-coordinate of the position

    // Create a destination rectangle
    SDL_Rect destinationRect;
    destinationRect.x = x;            // Set the X-coordinate of the destination rectangle
    destinationRect.y = y;            // Set the Y-coordinate of the destination rectangle

    // Query the texture to get its width and height

    SDL_QueryTexture(text_, NULL, NULL, &w, &h);

    // Set the width and height of the destination rectangle to match the texture
    destinationRect.w = w;  // Set the width of the destination rectangle
    destinationRect.h = h; // Set the height of the destination rectangle

    // Render the texture to the specified position
    SDL_RenderCopy(game_->getRenderer(), text_, NULL, &destinationRect);
    //dim_.set(w, h);

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
    

    SDL_FreeSurface(surface);
}
SDL_Texture* GameObject::getTexture(){
    return text_;
}
void GameObject::render()
{
    assert(text_ != nullptr);
    /*assert(texture_rect_!=nullptr);
    SDL_RenderCopy(game_->getRenderer(), text_, NULL, texture_rect_); 
    SDL_RenderPresent(game_->getRenderer()); */
    //updates the renderer
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