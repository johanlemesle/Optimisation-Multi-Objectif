#ifndef SOMMET_H
#define SOMMET_H
#include "svgfile.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(int,double,double);
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins()const;
        void setX (double x);
        void setY (double y);
        double getX() const
        {
            return m_x;
        }
        double getY() const
        {
            return m_y;
        }

        ///m�thode de parcours en largeur du graphe � partir du sommet
        ///renvoie les pr�d�cesseurs sous forme d'une map (cl�=id du sommet,valeur=id de son pr�d�cesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///m�thode de parcours en profondeur du graphe � partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///m�thode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC() const;
        ~Sommet();
        int getid() const;

        void dessinerSommet(Svgfile& T);

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;
        /// Donn�es sp�cifiques du sommet
       int m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
