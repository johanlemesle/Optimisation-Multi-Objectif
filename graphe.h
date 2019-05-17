#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        graphe ( graphe* base, std::vector<bool> sol );
        void pareto(std::vector<std::vector<bool>> x,Svgfile& svgout);
        ~graphe();
        graphe();
        ///void afficher() const;
        void dessiner(Svgfile& svgout);
        std::vector<Arete*> parcoursKruskal(int choixpoids);
        ///void parcoursKruskal();
        void setA(std::vector<Arete*> A);
        std::vector<Arete*> getAretes() const;
        std::vector<Sommet*> getSommets() const;
        std::vector<float> getPoidstotal() const;
        ///bool sortFunction(const Arete* i, const Arete *j);
        std::vector<std::vector<bool>> bruteForce();
        void dessinerPareto(std::vector<graphe*> non_domine, std::vector<graphe*> domine, Svgfile& svgout);
        void set_poidstotaux(std::vector<float> a);




    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::vector<Arete*> m_aretes;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::vector<float> m_poidstotaux;//

};

#endif // GRAPHE_H
