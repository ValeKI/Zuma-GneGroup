#include "../header/Livello.h"

extern int wGlobal;
extern int hGlobal;



void Livello::caricaCoordinate()
{
    ifstream in;
    string line;
    in.open("../Percorso/Percorso_0.txt");
    int ml=0;
    int i=0,n1,n2;

    ALLEGRO_DISPLAY* display=al_get_current_display();
    int displayW= al_get_display_width(display);
    int displayH= al_get_display_height(display);
    int sx = displayW/wGlobal;
    int sy = displayH/hGlobal;
    int scale = min(sx,sy);


    while(getline(in,line))
    {
        if(ml%1==0)
        {
            string n;
            i=0;

            while(line[i]!='-')
            {
                n+=line[i++];
            }
            n1=atoi(n.c_str())*( (wGlobal*scale)/1024.);
            n="";
            i++;
                   while(line[i]!='\0')
                    {
                        n+=line[i++];
                    }
                    n2=atoi(n.c_str())*( (hGlobal*scale)/768.);
                    n="";

                    coordinate.push_back(new pair<int,int>(n1,n2));
                }

                ml++;
            }

            in.close();
}