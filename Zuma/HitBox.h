#ifndef HITBOX_H
#define HITBOX_H
#include <string>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

using namespace std;



class HitBox
{
    private:
        int x;
        int y;
        int altezza;
        int lunghezza;
        
        protected:  
        string immagine;
        ALLEGRO_BITMAP *load;

    public:

    HitBox(string _immagine, int _x, int _y, float scale):x(_x), y(_y), immagine(_immagine), load(nullptr) 
    {
        ricreaLoad();
        if(load!=nullptr)
        {
            altezza   = al_get_bitmap_height(load)*scale;//*(hGlobal/1024.);
            lunghezza = al_get_bitmap_width (load)*scale;//*(wGlobal/1024.);
            //x         = x*(wGlobal/1024.);
            //y         = y*(hGlobal/1024.);
        }
    }


    ~HitBox()
    {
        distruggiLoad();
    }

    


   virtual void stampa()
    {
       // cout << endl << immagine << x << " " << y << " " << altezza << " " << lunghezza << endl;

        al_draw_scaled_bitmap
        (
            load,
            0, 0,                                // source origin
            al_get_bitmap_width(load),           // source width
            al_get_bitmap_height(load),          // source height
            x, y,                                // target origin
            lunghezza,
            altezza,    // target dimensions
            0                                    // flags
        );
    }


    void distruggiLoad(){if(load!=nullptr) {al_destroy_bitmap(load); load=nullptr;}}
    void ricreaLoad()
    {
        if((load==nullptr) && !(load=al_load_bitmap(immagine.c_str())   ))
        {
            cerr << "Error to load an image - 62";
        }
    }
    void setImmagine(string immagine) { this->immagine = immagine;  }
    void setLunghezza(int lunghezza) { this->lunghezza = lunghezza;  }
    void setAltezza(int altezza) {this->altezza = altezza;}
    void setY(int y) { this->y = y;}
    void setX(int x) { this->x = x;}

    string getImmagine() {return immagine;}
    int getLunghezza() { return lunghezza;}
    int getAltezza() { return altezza;}
    int getY() {return y;}
    int getX() {return x;}
    ALLEGRO_BITMAP* getLoad() {return load;}
};

#endif