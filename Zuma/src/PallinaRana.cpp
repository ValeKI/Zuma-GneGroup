#include "../header/PallinaRana.h"

PallinaRana::PallinaRana(COLORE c):Pallina(c){}

void PallinaRana::spara(int a, int b, int mx, int my)
{
    posizione++;
    vx = mx - a;
    vy = my - b;
    int scalare = MODULO/sqrt(pow(vx, 2) + pow(vy, 2));
    vx *= scalare;
    vy *= scalare;
    punto.first = a;
    punto.second = b;
}

void PallinaRana::movimento()
{
    posizione++;
    Pallina::movimento(pair<int,int> (vx * posizione + punto.first, vy * posizione + punto.second));
}