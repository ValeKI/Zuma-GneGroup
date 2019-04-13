#ifndef PALLINA_H
#define PALLINA_H
#include "HitBox.h"
#include <utility>
#include <string>
enum DIREZIONE{AVANTI = 0, DIETRO, FERMO};
enum COLORE{ROSSO=0,BLU,VERDE,ARANCIONE,VIOLA,GIALLO};
class Pallina: public HitBox
{
        private:
        COLORE colore;
        bool  bonus;
        int posizione;
        DIREZIONE direzione;
        int displayW;    
        int displayH;
        int scale;

        public:
        Pallina(COLORE c, int pos):colore(c),bonus(false),posizione(pos),direzione(AVANTI), HitBox("../image/Ball.png", 0, 0, 0.026)
        {
            

            string imm;
            
            switch(colore)
            {
                case(ROSSO):
                    imm="Ball.png";
                break;

                case(BLU):
                    imm="Ballblue.png";
                break;


                case(VERDE):
                    imm="Ballgreen.png";
                break;


                case(ARANCIONE):
                    imm="Ballorange.png";
                break;

                case(GIALLO):
                    imm="Ballyellow.png";
                break;

                case(VIOLA):
                    imm="Ballviolet.png";
                break;

            }

            //cout << "Imm e' " << imm << endl;

            distruggiLoad();
            setImmagine("../image/" + imm);
            ricreaLoad();
        }

        COLORE getColore() const
        {
            return colore;
        }

        bool getBonus() const
        {
            return bonus;
        }

        int getPosizione() const
        {
            return this->posizione;
        }

        DIREZIONE getDirezione() const
        {
            return direzione;
        }
        void setDirezione(DIREZIONE dir)
        {
            direzione = dir;
        }

        void stop()
        {
            direzione = FERMO;
        }

        void inverti()
        {

            if(direzione == AVANTI)
                direzione = DIETRO;
            else if(direzione == DIETRO)
                direzione = AVANTI;
        }

        void avanza()
        {
            if(direzione==AVANTI)
                posizione++;
            if(direzione==DIETRO)
                posizione--;
            // altrimenti FERMO
        }

        void movimento(const pair<int, int>& c);

        ~Pallina(){}     
};

#endif