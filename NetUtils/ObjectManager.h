
//#include "GameObject.h"
class GameObject;
#include <map>
#include <string>

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