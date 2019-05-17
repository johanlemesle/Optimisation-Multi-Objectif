#include <iostream>
#include "graphe.h"
#include <stdlib.h>


std::string choixNumFichier()
{
            std::string choixNum;

            std::cout << "\n\nQUEL  NUMERO DE FICHIER VOULEZ VOUS OUVRIR ?\n";
            std::cout << "  \n  1)- weights_0\n";
            std::cout << "  \n  2)- weights_1\n";
            std::cout << "  \n  3)- weights_2\n";

            std::cin >> choixNum;

            if(choixNum == "1")
            {
                return "0";
            }

            if(choixNum == "2")
            {
                return "1";
            }

            if(choixNum == "3")
            {
                return "2";
            }
            return 0;
}


int main()
{
    int choix=0;
    int choixPgm=0;
    int choixPoids;
    int a=0;
    std::string Fichier1 ;
    std::string Fichier2 ;
    system("CLS");

    while(a!=1)
    {
        std::cout<<" \n             QUEL FICHIER VOULEZ VOUS OUVRIR ?"<<std::endl;
        std::cout<<"\n    1)- BROADWAY"<<std::endl;
        std::cout<<"    2)- CUBETOWN"<<std::endl;
        std::cout<<"    3)- TRIVILLE"<<std::endl;
        std::cout<<"    4)- QUITTER"<<std::endl;

        std::cin >> choix ;

        system("CLS");
        if(choix==1)
        {
            Fichier1="broadway.txt";
            Fichier2="broadway_weights_" + choixNumFichier() + ".txt";

        }

        if(choix==2)
        {
            Fichier1="cubetown.txt";
            Fichier2="cubetown_weights_" + choixNumFichier() + ".txt";
        }

        if(choix==3)
        {
            Fichier1="triville.txt";
            Fichier2="triville_weights_" + choixNumFichier() + ".txt";
        }

        if(choix==4)
        {
            exit(1);
        }


        ///system("CLS");
        std::cout<<" \n             QUEL PROGRAMME VOULEZ VOUS EXECUTER ?"<<std::endl;

        std::cout<<"\n          1)- KRUSKAL"<<std::endl;
        std::cout<<"\n          2)- OPTMUM DE PARETO"<<std::endl;

        std::cin >> choixPgm;
        system("CLS");

        if(choixPgm == 1)
        {

            std::cout <<"\n\n        SELON QUEL POIDS VOULEZ VOUS OPTIMISER LE GRAPHE ?\n\n";

            std::cout<<"\n          0)- POIDS/COUT 1"<<std::endl;
            std::cout<<"\n          1)- POIDS/COUT 2"<<std::endl;
            do
            {
                std::cin >> choixPoids;
            }while(choixPoids>1 || choixPoids<0);

            if(choixPoids == 0)
            {
                Svgfile output;
                graphe g(Fichier1,Fichier2);
                graphe g2(Fichier1,Fichier2);
                g2.setA(g.parcoursKruskal(0));
                g2.dessiner(output);
                std::cout << "\n\n KRUSKAL A BIEN ETE EXEXUTE, VEUILLEZ OUVRIR LE FICHIER SVG\n";
            }


            if(choixPoids == 1)
            {
                Svgfile output;
                graphe g(Fichier1,Fichier2);
                graphe g2(Fichier1,Fichier2);
                g2.setA(g.parcoursKruskal(1));
                g2.dessiner(output);
                std::cout << "\n\n KRUSKAL A BIEN ETE EXEXUTE, VEUILLEZ OUVRIR LE FICHIER SVG\n";
            }
        }

        if(choixPgm == 2)
        {
            Svgfile output;
            graphe g(Fichier1,Fichier2);
            g.pareto(g.bruteForce(),output);

            std::cout << "\n\n LES OPTIMUMS DE PARETO ONT BIEN ETE EXEXUTES, VEUILLEZ OUVRIR LE FICHIER SVG\n";
        }


    }
    return 0;
}
