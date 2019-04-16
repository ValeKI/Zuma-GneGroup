#include "../header/Pallina.h"

extern int wGlobal;
extern int hGlobal;

void Pallina::movimento(const pair<int, int>& c)
{
    setX(c.first);
    setY(c.second);
   // cout << c.first << " " << ((displayW-(wGlobal * scale))/2 ) << endl;
}