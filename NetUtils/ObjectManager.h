
#include "GameObject.h"

#include <map>

class ObjectManager{

public:
ObjectManager(){};
~ObjectManager(){};
void addObject(GameObject* obj);
void removeObject();

std::map<std::string,GameObject*> getObjects();
private:

 std::map<std::string,GameObject*> allObjects_;

};