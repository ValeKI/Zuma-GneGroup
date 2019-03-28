#include "../header/Mouse.h"

extern int wGlobal;
extern int hGlobal;

Mouse::Mouse():x(0),y(0)
{
    ALLEGRO_DISPLAY* display=al_get_current_display();
    displayW= al_get_display_width(display);
    displayH= al_get_display_height(display);
    int sx = displayW/wGlobal;
    int sy = displayH/hGlobal;
    scale = min(sx,sy);
    
}

void Mouse::setY(int _y) 
{ 
    y=_y-((displayH-(hGlobal * scale))/2 );
}
void Mouse::setX(int _x) 
{ 
    x=_x-((displayW-(wGlobal * scale))/2 );  
}
int Mouse::getY() {return y;}
int Mouse::getX() {return x;}



bool Mouse::collisione(HitBox* obj)
{
    return ((y >= obj->getY() && y <= (obj->getY() + obj->getAltezza()   ) ) &&
            (x >= obj->getX() && x <= (obj->getX() + obj->getLunghezza() ) )   );
            
}