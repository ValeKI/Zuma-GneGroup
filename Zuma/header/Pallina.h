#ifndef PALLINA_H
#define PALLINA_H
#include "HitBox.h"
#include <utility>
enum DIREZIONE{AVANTI = 0, DIETRO, FERMO};
class Pallina: public HitBox
{
        private:
        ALLEGRO_COLOR colore;
        bool  bonus;
        int posizione;
        DIREZIONE direzione;
        
        public:
        ALLEGRO_COLOR getColore() const
        {
            return colore;
        }

        bool getBonus() const
        {
            return bonus;
        }

        int getPosizione() const
        {
            return posizione;
        }

        DIREZIONE getDirezione() const
        {
            return direzione;
        }
        void setDirezione(DIREZIONE dir)
        {
            direzione = dir;
        }

        void movimento(const pair<int, int>& c)
        {
            if(direzione == 0 || direzione == 1)
            {
                this -> setX(c.first);
                this -> setY(c.second);
                 if (direzione == 0)posizione++;
                else posizione--;
            }
        }

        
};

#endif