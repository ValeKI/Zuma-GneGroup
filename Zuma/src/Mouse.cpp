#include "../header/Mouse.h"

extern int wGlobal;
extern int hGlobal;

Mouse::Mouse():x(0),y(0)
{
  
}

void Mouse::setY(const int& _y) 
{ 
    y=_y;
}

void Mouse::setX(const int& _x) 
{ 
    x=_x;  
}

int Mouse::getY() const
{
    return y;
}

int Mouse::getX() const
{
    return x;
}

bool Mouse::collisione(HitBox* obj)
{
    return ((y >= obj->getStampaY() && y <= (obj->getStampaY() + obj->getStampaA() ) ) &&
            (x >= obj->getStampaX() && x <= (obj->getStampaX() + obj->getStampaL() ) )   );            
}