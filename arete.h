#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include "sommet.h"
#include <iostream>
#include "svgfile.h"

class Arete
{

public :
        Arete();
        Arete(int,int,int,std::vector<float>);
        ~Arete();
        int getids1();
        int getids2();
        int getida();
        std::vector<float> getpoids() const;
        void dessinerArete(std::vector<Sommet *> collec,Svgfile& T);

private :
    std::vector<float> m_poids;
    int m_ids1, m_ids2, m_ida;

};

#endif // ARETE_H_INCLUDED
