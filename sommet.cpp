#include <iostream>
#include <queue>
#include <stack>

#include "sommet.h"
#include "svgfile.h"

Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(const Sommet* voisin) {
    m_voisins.push_back(voisin);
}
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }
void Sommet::afficherVoisins()const{
    std::cout<<"voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
        std::cout<<std::endl;
    }
}

void Sommet::setX(double x)
{
    m_x = x;
}

void Sommet::setY(double y)
{
    m_y = y;
}

void Sommet::dessinerSommet(Svgfile& T)
{
    T.addText(m_x-10,m_y-10,m_id,"red");
    T.addCircle(m_x,m_y,4,2,"red");
}



Sommet::~Sommet()
{
    //dtor
}
