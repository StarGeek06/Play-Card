#include <iostream>
#include <list>
#include <string>
#include <random>

using namespace std;

//Initialsion la classe des Cartes

class Carte
{
   //Des attributs privés
   private:

      int valeur; // La valeur de ma carte
      string couleur; // La couleur de ma carte


   public:

       // Constructeur(s)

       Carte(int v, string c) : valeur(v) , couleur(c) {}


       void display() const 
       {
          cout << "Valeur : " << valeur << endl;
          cout << "Couleur : " << couleur << endl;
          cout << "\n";
       }

};


//La classe des Joueurs

class Joueur
{
    private:

        list <Carte> main; 
        // Une liste qui regroupe toutes les cartes qu'un joueur a en sa possesion

    public:

        void addcard(const Carte& card)
        {
            main.push_back(card);
        }

        void showhand() const
        {
            cout << "Le joueur détient : " << main.size() << " cartes " << endl;
            cout << "\n";

            for(const Carte& card : main)
            {
               card.display();    //Afficher les cartes d'un joueur
            }

      
        }


};


class Partie
{

    public:
      
      list<Carte> paquetCartes;

      list<Joueur> Joueurs;

      string couleurs[4] = {"Coeur", "Carreau", "Trèfle", "Pique"};

    public:
        
        //Créer un paquer de 14*4 Cartes 

        void initialiserPaquet()
        {
           for(int valeur = 2; valeur <= 14; ++valeur)
           {

              for(const string& couleur : couleurs)
              {
                paquetCartes.push_back(Carte(valeur,couleur));  
              }

           }

           cout << "Le Paquet est prêt à être utilisé !!" << endl;
           cout << "\n";
        }

        void distribuercartes()
        {
            int nbreJoueurs;

            std::random_device rd;
            std::mt19937 generator(rd()); 

            std::uniform_int_distribution<int> distribution(1, paquetCartes.size());

            cout << "Combien de joueurs voulez-vous inscrire? ";

            cin >> nbreJoueurs;


            if(nbreJoueurs*4 > paquetCartes.size())
            {
                cout << "Ce jeu ne peut être possible !!" << endl;
            }

            else 
            {
                

               // int carteParJoueur = paquetCartes.size() / nbreJoueurs;

                for(int njouer = 0; njouer <= nbreJoueurs; ++njouer)
                {

                    Joueur joueur;

                    for(int i = 0; i < 4; ++i)
                    {
                        //Utiliser la distribution uniforme pour 
                        //partager 4cartes alétoirement à chaque Joueurs

                        int cartes = distribution(generator);

                        auto it = next(paquetCartes.begin(), cartes-1);

                        joueur.addcard(*it); // Ajouter la carte au joueur

                        it = paquetCartes.erase(it); // Supprimer la carte du paquet

                    }

                    Joueurs.push_back(joueur);
                }
            }

            


        }


};


int main()
{
   
    Partie partie;
    partie.initialiserPaquet();
    partie.distribuercartes();

    for (const Joueur &joueur : partie.Joueurs)
    {
        joueur.showhand();
    }

    return 0;
}

