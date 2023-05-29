#include "ObjectManager.h"
#include "GameObject.h"
void ObjectManager::addObject(GameObject* obj){

allObjects_.insert( std::pair<std::string,GameObject*>(obj->getName(),obj));

}
std::map<std::string,GameObject*> ObjectManager::getObjects(){
    return allObjects_;
}
void ObjectManager::removeObject(){

}