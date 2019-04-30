#include "../header/Rana.h"
#include <cmath>

extern int wGlobal;
extern int hGlobal;

void Rana::stampa(int mx, int my)
        {
            double stampaX=cx, stampaY=cy;

            stampaX= stampaX+(displayW-(wGlobal * scale2))/2 ;
            stampaY= stampaY+(displayH-(hGlobal * scale2))/2 ;

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