#include "../header/PallinaRana.h"

extern int wGlobal;
extern int hGlobal;

PallinaRana::PallinaRana(COLORE c):Pallina(c,0)
{
    setVelocita(10);
}

PallinaRana::PallinaRana(const PallinaRana& p):
Pallina(p.getColore(),p.getPosizione()),vx(p.getVx()),vy(p.getVy()),scalare(p.getScalare()),punto(p.getPunto())
{
    setStampaX(p.getStampaX());
    setStampaY(p.getStampaY());
    setVelocita(10);
}

// e' calcolata la posizione della pallina, che dipende dalle coordinate del mouse
void PallinaRana::direziona(int a, int b, int mx, int my)
{
    posizione = 1;
    vx = mx - a;
    vy = my - b;
    float scalare = MODULO/sqrt(pow(vx, 2) + pow(vy, 2));
    vx = float(vx*scalare);
    vy = float(vy*scalare);
    punto.first = a;
    punto.second = b;
}

void PallinaRana::setStampaX(int a)
{
    HitBox::setStampaX(a-lunghezza/2);
}
        
void PallinaRana::setStampaY(int a)
{
    HitBox::setStampaY(a-altezza/2);
}

void PallinaRana::movimento()
{
    posizione+=velocita;
    // la pallina si muove velocita interi per volta, per questo viene diviso per MODULO
    setStampaX( (vx * posizione/MODULO) + punto.first);
    setStampaY( (vy * posizione/MODULO) + punto.second);   
}

float PallinaRana::getVx() const
{
    return vx;
}

float PallinaRana::getVy() const
{
    return vy;
}

float PallinaRana::getScalare() const
{
    return scalare;
}

pair<int,int> PallinaRana::getPunto() const
{
    return punto;
}