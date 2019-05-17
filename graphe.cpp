#include <fstream>
#include <iostream>
#include "graphe.h"
#include <algorithm>
#include <stdlib.h>


graphe::graphe ( std::string nomFichier1, std::string nomFichier2 )
{
    std::ifstream ifs1 { nomFichier1 };
    std::ifstream ifs2 { nomFichier2 };

    if ( !ifs1 )
        throw std::runtime_error ( "Impossible d'ouvrir en lecture " + nomFichier1 );
    if ( !ifs2 )
        throw std::runtime_error ( "Impossible d'ouvrir en lecture" + nomFichier2 );

    int ordre1;
    int taille1;
    int id1;
    double x1, y1;
    int id_a1, id_s1, id_s2;



    int taille2, id_a2, nb_poids2;

    ifs1 >> ordre1;
    if ( ifs1.fail ( ) )
        throw std::runtime_error ( "ordre1" );

    for ( int i = 0; i < ordre1; ++i )
    {
        ifs1 >> id1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "id1" );
        ifs1 >> x1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "x1" );
        ifs1 >> y1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "y1" );
        m_sommets.push_back ( new Sommet { id1,x1,y1 } );
    }


    ifs1 >> taille1;
    if ( ifs1.fail ( ) )
        throw std::runtime_error ( "taille1" );
    ifs2 >> taille2;
    if ( ifs2.fail ( ) )
        throw std::runtime_error ( "taille2" );
    ifs2 >> nb_poids2;
    if ( ifs2.fail ( ) )
        throw std::runtime_error ( "nb_poids2" );

    for ( int i = 0; i < taille2; i++ )
    {
        ifs1 >> id_a1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "id_a1" );
        ifs2 >> id_a2;
        if ( ifs2.fail ( ) )
            throw std::runtime_error ( "id_a2" );
        ifs1 >> id_s1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "id_s1" );
        ifs1 >> id_s2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "id_s2" );
        std::vector<float> poids;

        for ( int j = 0; j < nb_poids2; j++ )
        {
            float x;
            ifs2 >> x;
            if ( ifs2.fail ( ) )
                throw std::runtime_error ( "poids_courant" );

            poids.push_back ( x );
        }
        m_aretes.push_back ( new Arete { id_a1,id_s1,id_s2,poids } );
    }
}
std::vector<Arete*> graphe::getAretes() const
{
    return m_aretes;
}
std::vector<Sommet*> graphe::getSommets() const
{
    return m_sommets;
}
graphe::graphe ( graphe* base, std::vector<bool> sol )
{
    ///parcourir les aretes du graphe source, et les insérer dans le graphe que je construit si elle est true à la case i du vec bool
///    m_sommets=source.m_sommet
    for(size_t i = 0 ; i<base->getAretes().size() ; i++)
    {
        if(sol[i])
        {
            this->m_aretes.push_back(base->getAretes()[i]);
        }
    }
    this->m_sommets=base->getSommets();
}
bool myFunction0(Arete* i,Arete *j)
{
    ///std::cout << i << " " << j << std::endl;
    ///std::cout<< i->getpoids().at(0) << " " << j->getpoids().at(0) << std::endl;
    return i->getpoids().at(0) < j->getpoids().at(0);
}
bool myFunction1(Arete* i,Arete *j)
{
    ///std::cout << i << " " << j << std::endl;
    ///std::cout<< i->getpoids().at(0) << " " << j->getpoids().at(0) << std::endl;
    return i->getpoids().at(1) < j->getpoids().at(1);
}

std::vector<Arete*> graphe::parcoursKruskal(int choixpoids)
{
    std::vector<Arete*> vec (m_aretes);

    ///Trier
    if(choixpoids==0)
    {
        std::sort(vec.begin(),vec.end(),myFunction0);
    }
    if(choixpoids==1)
    {
        std::sort(vec.begin(),vec.end(),myFunction1);
    }


    ///Parcourir
    ///std::vector<Arete*> arbre;


    std::vector<Arete*> solution;
    std::vector<int>cc;

    ///Initialiser composantes connexes
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        ///on initialise avec 1,2,3,...
        cc.push_back(i);
    }

    ///Parcours des arètes sélectionnées
    int i =0;
    int buffer=0;
    while(solution.size()!=(m_sommets.size()-1))
    {
        if(cc[vec[i]->getids1()]!=cc[vec[i]->getids2()])
        {
            ///1 - On sélectionne l'arète
            solution.push_back(vec[i]);

            ///2 - On met à jour le vecteur de connexité en attribuant le même numéro aux deux sommets
            buffer=cc[vec[i]->getids2()];
            ///std::cout<<"Buffer : "<< buffer <<std::endl;

            cc[vec[i]->getids2()] =  cc[vec[i]->getids1()];

            for(size_t j=0; j<cc.size(); j++)
            {
                if(cc[j]==buffer)
                {
                    cc[j]=cc[vec[i]->getids1()];
                    ///std::cout<<"changement connexite"<<std::endl;
                }

            }
        }

        i++;
    }
    return solution;
}
void graphe::setA(std::vector<Arete*> A)
{
    m_aretes=A;
}

void graphe::dessiner(Svgfile& svgout)
{
    ///std::cout<<m_aretes.size();
    for (size_t i = 0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessinerSommet(svgout);

    }

    for (size_t i = 0; i<m_aretes.size(); i++)

    {
        m_aretes[i]->dessinerArete(m_sommets,svgout);
        ///std::cout << "dessine aretes ";
        ///std::cout << i;
    }

}
graphe::~graphe()
{
    //dtor
}
graphe::graphe()
{
    //dtor
}
std::vector<std::vector<bool>> graphe::bruteForce()
{
    ///N bool dans le vecteur de bool /// 2^N bool dans le vecteur de vecteurs de bool
    std::vector<std::vector<bool>> vecvecbool;
    unsigned int NbArete;
    int Nb;
    ///std::cout << " NbAretes " << m_aretes.size() <<std::endl;
    ///std::cout << " Bruteforce " <<std::endl;
    ///Construction de l'ensemble des solutions possibles
    for(int i=0; i<pow(2, m_aretes.size()); i++)
    {
        ///initialiser vecbool avec m_aretes.size() elements, tous à 0
        std::vector<bool> vecbool(m_aretes.size(), false);
        //std::cout << " Boucle 1 " <<std::endl;
        //std::cout << " NbAretes " << m_aretes.size() <<std::endl;
        Nb=i;
        NbArete=0;

        for (int j = m_aretes.size()-1; j>=0; j--)
        {
            if(Nb-pow(2,j)>=0)
            {
                ///std::cout << "1";
                vecbool[j]=true;
                Nb=Nb-pow(2,j);
                NbArete++;
            }
            else
            {
                ///std::cout << "0" ;
                vecbool[j]=false;

            }


        }
        ///std::cout << " " << std::endl;
        ///ON conserve uniquement les solutions à Ordre-1 aretes
        if (NbArete==m_sommets.size()-1)
        {
            vecvecbool.push_back(vecbool);
        }

    }
    ///std::cout << " nb vecteurs gardes " << vecvecbool.size() << std::endl;
    ///Associer variables booléennes aux x arêtes du graphe

    ///On ne garde que les solutions non cycliques
    std::vector<int>cc;
    unsigned int n=0;

    ///Parcours des vecteurs d'arètes sélectionnées
    while(n<vecvecbool.size())
    {
        ///std::cout<<"Etude du vecteurs de sommet "<< n <<std::endl;

        ///Initialiser composantes connexes
        cc.clear();
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            ///on initialise avec 1,2,3,...
            cc.push_back(i);
        }
        int buffer=0;
        bool cycle=false;

        /// On parcours les vecteurs d'aretes
        for (size_t i=0; i<vecvecbool[n].size(); i++)
        {

            if (vecvecbool[n][i])
            {
                ///std::cout<<"Arete "<< i <<std::endl;

                if(cc[m_aretes[i]->getids1()]!=cc[m_aretes[i]->getids2()])
                {
                    /// On met à jour le vecteur de connexité en attribuant le même numéro aux deux sommets
                    buffer=cc[m_aretes[i]->getids2()];
                    //std::cout<<"Buffer : "<< buffer <<std::endl;

                    cc[m_aretes[i]->getids2()] =  cc[m_aretes[i]->getids1()];

                    for(size_t j=0; j<cc.size(); j++)
                    {
                        if(cc[j]==buffer)
                        {
                            cc[j]=cc[m_aretes[i]->getids1()];
                            //std::cout<<"changement connexite"<<std::endl;
                        }
                    }
                }
                else
                {
                    cycle=true;
                }

                /*for(size_t j=0; j<cc.size(); j++)
                {
                    std::cout<<"-" << cc[j]<<std::endl;
                }
                std::cout<<"------------------------" <<std::endl;*/
            }
        }
        if (cycle)
        {
            vecvecbool.erase(vecvecbool.begin()+n);
            ///std::cout<<"Retrait du vecteur : " << n <<std::endl;

        }
        else
            n++;

    }
    ///std::cout<< "" << std::endl;
    ///std::cout << " nb vecteurs gardes " << vecvecbool.size() << std::endl;
    return vecvecbool;
}

void graphe::set_poidstotaux(std::vector<float> a)
{
    m_poidstotaux=a;
}
///void graphe::

std::vector<float> graphe::getPoidstotal() const
{
    return m_poidstotaux;
}


///fonction qui retourne vecteur de poids totaux
void graphe::pareto(std::vector<std::vector<bool>> x, Svgfile& svgout)
{
    std::vector<graphe*>sol; /// vecteur d'ensemble de sol en graphe
    std::vector<graphe*>opti;
    for(size_t m = 0 ; m<x.size() ; m++)
    {
        sol.push_back(new graphe(this,x[m]));
    }
    std::vector<std::vector<float>> vecp_ensemble;
    std::vector<float> vecp_graphe;
/// std::map<graphe*,std::vector<float>> graphe_ensemble;

/// std::vector<std::vector<graphe>> vecp_ensemble;
/// std::vector<graphe> vecp_graphe;
    float p=0;
    for(size_t i=0; i<x.size() ; i++)
    {
        vecp_graphe.clear();
        for(size_t k=0 ; k<m_aretes[0]->getpoids().size(); k++)
        {
            p=0;
            for(size_t j=0 ; j<x[i].size() ; j++)
            {
                if(x[i][j])
                {
                    p=p+m_aretes[j]->getpoids().at(k);
                }
            }
            ///vec_p va obtenir dans chaque case le poids total du cout k
            vecp_graphe.push_back(p); /// on push le p total du cout k
        }
        vecp_ensemble.push_back(vecp_graphe);
    }

    for(size_t w = 0 ; w < vecp_ensemble.size() ; w++)
    {
        sol[w]->m_poidstotaux=vecp_ensemble[w]; ///on attribue à m_poidstotaux : les poids totaux de chaque graphe
    }
    ///std::cout << "sol size de base : " << sol.size() << std::endl;*/


    ///CONSTITUTION DE LA FRONTIERE DE PARETO
    //std::vector<std::vector<float>> optimum_pareto;
    ///COMPARER LES COUTS TOTAUX 1 DE CHAQUE GRAPHE
    float p1_min = 3000;
    float p2_min = 3000;
    float p1_max=0;

    for(size_t s = 0 ; s < sol.size() ; s++)
    {
        if(sol[s]->m_poidstotaux[0]>p1_max)
        {
            p1_max = sol[s]->m_poidstotaux[0];
        }
    }


///1 ere etape
///----------------------------------------------------------------------------------------------------------------------------------

    for(size_t i = 0 ; i < sol.size() ; i++)
    {
        if(sol[i]->m_poidstotaux[0]<p1_min)
        {
            p1_min = sol[i]->m_poidstotaux[0];
        }
    }

    for(size_t d = 0 ; d < sol.size() ; d++)
    {
        if(p1_min==sol[d]->m_poidstotaux[0])
        {
            if(sol[d]->m_poidstotaux[1]<p2_min)
            {
                p2_min = sol[d]->m_poidstotaux[1];
            }
        }
    }
    ///std::cout << p1_min << p2_min << std::endl;
    ///std::cout << sol[5]->m_poidstotaux[0] << "xxx" << sol[5]->m_poidstotaux[1] << std::endl;
    ///std::cout << sol.size() << std::endl;

    for(size_t k =0 ; k < sol.size() ; k++)
    {
        ///std::cout << sol[k]->m_poidstotaux.size() << std::endl;

        if(((sol[k]->m_poidstotaux[0])==p1_min)&&((sol[k]->m_poidstotaux[1])==p2_min))
        {
            ///std::cout << "prout" << std::endl;
            opti.push_back(sol[k]);
            sol.erase(sol.begin()+k);

        }


    }


///----------------------------------------------------------------------------------------------------------------------------------

///2 ème étape
    bool pn_sup=false;
    bool cond=false;
    float buffer1 = p1_min;
    float buffer2 = p2_min;
    float push1, push2;
    float i=1.0;
    /// on doit retirer ceux qu'on compare
    ///while((pn_sup==false)&&(cond2==false))

    while(cond==false)
    {
        for(size_t j =0 ; j<sol.size() ; j++)
        {
            if(buffer1+i == sol[j]->m_poidstotaux[0])
            {
                pn_sup=true;
                push1=sol[j]->m_poidstotaux[0];
                push2=sol[j]->m_poidstotaux[1];
                for(size_t d = 0; d<sol.size(); d++)
                {
                    if(sol[j]->m_poidstotaux[0]==sol[d]->m_poidstotaux[0])
                    {
                        if(sol[d]->m_poidstotaux[1]<push2)
                        {
                            push2 = sol[d]->m_poidstotaux[1];///on en veut qu'un !!!
                        }
                    }
                }
            }
            if((pn_sup==true) && (push2<buffer2))
            {
                for(size_t k =0 ; k < sol.size() ; k++)
                {
                    ///std::cout << sol[k]->m_poidstotaux.size() << std::endl;

                    if(((sol[k]->m_poidstotaux[0])==push1)&&((sol[k]->m_poidstotaux[1])==push2))
                    {
                        ///std::cout << "prout" << std::endl;
                        opti.push_back(sol[k]); /// je vais avoir deux pointeurs qui pointent sur le même objet
                        sol.erase(sol.begin()+k);
                        k=sol.size();

                    }


                }

                buffer1=push1;
                buffer2=push2;

                j=0;
                i=0;
            }
            if(buffer1+i>p1_max)
            {
                cond=true;
            }
        }
        i=i+1.0;
    }

    std::cout << "sol size d'arrivée : " << sol.size() << std::endl;



    for(size_t i = 0 ; i < opti.size() ; i++)
    {
        ///std::cout << "bobby" << std::endl;
        std::cout << opti[i]->m_poidstotaux[0] << " 88888888888888888888 " << opti[i]->m_poidstotaux[1] << std::endl;
    }
    dessinerPareto(opti,sol,svgout);

}
float mapp(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void graphe::dessinerPareto(std::vector<graphe*> non_domine, std::vector<graphe*> domine, Svgfile& svgout)
{
    unsigned int indice;
    svgout.addLine(500,10,1000,10,"black");
    svgout.addText(1010,10,"Cout 1","black");
    svgout.addLine(500,10,500,510,"black");
    svgout.addText(487,522,"Cout 2", "black");
    for(size_t j = 0 ; j < domine.size() ; j++)
    {
        svgout.addCircle((domine[j]->m_poidstotaux[0])*10+425,(domine[j]->m_poidstotaux[1])*10,1,2,"red");
    }
    for(size_t i = 0 ; i < non_domine.size() ; i++)
    {
        svgout.addCircle((non_domine[i]->m_poidstotaux[0])*10+425,(non_domine[i]->m_poidstotaux[1])*10,1,2,"green");
    }
    std::cout << "Il y a " << non_domine.size() << " optimums de pareto" << std::endl;
    std::cout << "Choisissez quel graphe optimum vous voulez afficher !" << std::endl;
    do
    {
        std::cout << "Choisissez un indice entre 1 et " << non_domine.size() << std::endl;
        std::cin >> indice;
        system("cls");
        indice--;
    }
    while((indice < 1) || (indice > non_domine.size()-1));
    svgout.addText(25,25,"VOICI LE GRAPHE CORRESPONDANT A VOTRE INDICE","black");
    non_domine[indice]->dessiner(svgout);

}

