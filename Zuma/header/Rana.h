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
        double seno;
        double coseno;
        Pallina* pallina;
        
        
    public:
        Rana(int a = 0,int b = 0):HitBox("../image/Rana.png", a, b, 1 ), scale(0.3)
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
            seno = stampaY - my;
            if ((stampaX-mx) != 0)
            coseno = stampaX - mx;
            double segno = M_PI/2;
            if(seno <= 0 && coseno < 0 ||
                coseno < 0 && seno >= 0)
            {
                segno = M_PI/2 + M_PI;
            }

             al_draw_scaled_rotated_bitmap
            (
                load,
                146, 58,
                stampaX, stampaY,
                ( (wGlobal*scale2)/1024.)*scale,
                ( (hGlobal*scale2)/768.)*scale,
                (atan(seno/coseno) + segno)    ,
                0
            );
        }
        
};

#endif