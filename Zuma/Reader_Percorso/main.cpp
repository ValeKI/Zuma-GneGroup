#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

void ReadImage(const char fname[], int**& fimage, int& M, int& N, int& Q);
bool criterio(pair<int,int> prec, pair<int,int> x, pair<int,int> succ);
void ordina(vector<pair<int,int> >& v);


// prima il nuovo file che voglio creare, dopo dove trovo l'immagine pgm
int main(int arg, char** str)
{
    int righe, colonne, lunghezza_num;
    int** matriceMisteriosa;
    vector<pair<int,int> > coordinate;
    pair<int,int> var;

    ReadImage(str[2] ,matriceMisteriosa, colonne, righe, lunghezza_num);


    //riempie coordinate e primaC e ultima C
    for(int i=0; i<righe; i++)
        for(int j=0; j<colonne; j++)
            if(matriceMisteriosa[i][j]!=217)
            {    
                var.second=i;
                var.first=j;
                if(matriceMisteriosa[i][j]==255)
                    coordinate.insert(coordinate.begin(),var);
                else
                    coordinate.push_back(var);
                
            }
    ordina(coordinate);
  
    for(int i=0; i<righe; i++)
        delete[] matriceMisteriosa[i];
    delete[] matriceMisteriosa;

    /*
        CREARE IL FILE NEL QUALE SARA' SCRITTO IL VECTOR COORDINATE
    */
    ofstream in;
    string filename=str[1];
    
    in.open( (filename+".txt").c_str() );
    
    for(int i=0; i<coordinate.size(); i++)
    {
        in << coordinate[i].first << "-" << coordinate[i].second << endl;
    }
    
    
    in.close();

    return 0;
}

void ReadImage(const char fname[], int**& fimage, int& M, int& N, int& Q)
{
    int i, j;
    unsigned char *image;
    char header [100], *ptr;

    ifstream ifp;
    ifp.open(fname, ios::in); 
    if (!ifp) 
    {
        cout << "Can't read image: " << fname << endl;
        exit(1);
    }

    // read header

    ifp.getline(header,100,'\n');
    if ( (header[0]!=80) ||	/* 'P' */ (header[1]!=53) ) 
    {   /* '5' */
	    cout << "Image " << fname << " is not PGM" << endl;
	    exit(1);
    }

    ifp.getline(header,100,'\n');
    while(header[0]=='#')
        ifp.getline(header,100,'\n');

    M=strtol(header,&ptr,0);
    N=atoi(ptr);

    ifp.getline(header,100,'\n');

    Q=strtol(header,&ptr,0);

    image = (unsigned char *) new unsigned char [M*N];

    fimage = new int* [N];
    for(i=0; i<N; i++)
        fimage[i] = new int[M];

    ifp.read( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

    if (ifp.fail()) 
    {
        cout << "Image " << fname << " has wrong size" << endl;
        exit(1);
    }

    ifp.close();

 //
 // Convert the unsigned characters to integers
 //

    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
	        fimage[i][j]=(int)image[i*M+j];

    delete[] image;
}

/* 
    * * *
    * x *
    * * *
*/

bool criterio(pair<int,int> prec, pair<int,int> x, pair<int,int> succ)
{
    return (prec.first!=succ.first || prec.second!=succ.second) 
        && 
            (x.first!=succ.first || x.second!=succ.second) 
        &&
        (abs(succ.first-x.first)<=1 && abs(succ.second-x.second)<=1 );
}


void ordina(vector<pair<int,int> >& v)
{
    //cerca il secondo
    for(int i=1; i<v.size()-1; i++)
    {
        pair<int,int> fake(-1,-1);
        if(criterio(fake,v[0],v[i]))
            swap(v[i],v[1]);
    } 

    // ordina tutti
    int many=0;
    for(int i=1; i<v.size()-2; i++)
        for(int j=i+1; j<v.size(); j++)
            if( criterio(v[i-1],v[i],v[j])==true)
                swap(v[i+1],v[j]);
}
