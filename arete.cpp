#include "arete.h"
#include "svgfile.h"

Arete::Arete()
{
}
Arete::Arete(int a,int b,int c, std::vector<float> d):m_ida{a},m_ids1{b},m_ids2{c},m_poids{d}
{
}
Arete::~Arete()
{
}

void Arete::dessinerArete(std::vector<Sommet *> collec, Svgfile& T)
{
    int x1,y1,x2,y2;

    x1 = collec[m_ids1]->getX();
    y1 = collec[m_ids1]->getY();
    x2 = collec[m_ids2]->getX();
    y2 = collec[m_ids2]->getY();

    T.addLine(x1,y1,x2,y2,"black");

    int distanceX = collec[m_ids2]->getX() - collec[m_ids1]->getX();

    int distanceY = collec[m_ids2]->getY() - collec[m_ids1]->getY();

    if(distanceX == 0)
    {
        T.addText(collec[m_ids2]->getX() - 22,  collec[m_ids1]->getY() + distanceY/2, m_poids[0],"black");

        T.addText(collec[m_ids2]->getX() - 13,  collec[m_ids1]->getY() +  distanceY/2,";","black");

        T.addText(collec[m_ids2]->getX() - 9, collec[m_ids1]->getY() + distanceY/2, m_poids[1],"black");
    }

    if(distanceY == 0)
    {
        T.addText(collec[m_ids1]->getX() + distanceX/2 - 10,collec[m_ids2]->getY() - 3,m_poids[0],"black");

        T.addText(collec[m_ids1]->getX() +  distanceX/2 - 3,collec[m_ids2]->getY() - 3 ,";","black");

        T.addText(collec[m_ids1]->getX()  + distanceX/2, collec[m_ids2]->getY() - 3,m_poids[1],"black");
    }

    if(distanceX != 0 && distanceY != 0)
    {
        T.addText(collec[m_ids1]->getX() + distanceX/2 - 10,collec[m_ids1]->getY() + distanceY/2,m_poids[0],"black");

        T.addText(collec[m_ids1]->getX() +  distanceX/2 - 3,collec[m_ids1]->getY() +  distanceY/2,";","black");

        T.addText(collec[m_ids1]->getX()  + distanceX/2, collec[m_ids1]->getY() +  distanceY/2,m_poids[1],"black");
    }

}
std::vector<float> Arete::getpoids() const
{
    ///std::cout << this << " get poids " << m_poids[0] << " " << m_poids[1] << "\n";
    return m_poids;
}

int Arete::getids1()
{
    return m_ids1;
}


int Arete::getids2()
{
    return m_ids2;
}

int Arete::getida()
{
    return m_ida;
}
