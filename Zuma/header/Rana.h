#ifndef RANA_H
#define RANA_H
#include "Pallina.h"
#include <cmath>
class Rana: public HitBox
{
    private:
        int cx;
        int cy;
        double scale;
        Pallina* pallina;
        
        
    public:
        Rana(int a = 0,int b = 0):HitBox("../image/Rana.png", a, b, 1 ), scale(0.5)
        {
            cx = a; 
            cy = b;
            setX(a-getLunghezza()/2);
            setY(b-getAltezza()/2);
        }

        

        void stampa(int mx, int my)
        {
            double stampaX=cx, stampaY=cy;

            stampaX= (stampaX+(displayW-(wGlobal * scale2))/2 );
            stampaY= (stampaY+((displayH-(hGlobal * scale2))/2 ));
            //stampaL= stampaL*( (wGlobal*scale2)/1024.);
            //stampaA= stampaA*( (hGlobal*scale2)/768.);
      
            if ((stampaY -my) != 0)
             al_draw_scaled_rotated_bitmap
            (
                load,
                146, 132,
                stampaX, stampaY,
                ( (wGlobal*scale2)/1024.)*scale,
                ( (hGlobal*scale2)/768.)*scale,
                atan((stampaX-mx)/(stampaY-my))*180./M_PI,
                0
            );
        }
        
};

#endif