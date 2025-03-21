// CPPINTRO.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//Par défaut, <> signifient d'importer de la librarie standard (ISO)
//ou libraries systèmes (Windows, Linux, MacOS,etc).
#include <iostream>
#include <string>
#include <fstream>

//namespace LoopEngine {
//    class MonModele;
//}
//
//using namespace LoopEngine;
//MonModele m;

using namespace std;

int main()
{
    //////////////////
    // Entiers
    //////////////////
    int unEntier = 0;
    __int64 unEntierSur8Octets = 0xFFFFFFFFFF; // Possible d'assigner en notation hexadécimale
    unsigned int unEntierPositif = 0b0001101;  // Possible d'assigner en notation binaire

    //////////////////
    // Points flottants
    //////////////////
    float hp = 0.f; // Le f signifie float
    double magic = 0.; // Rien signifie double

    //////////////////
    // Caractères
    //////////////////
    char unCaractere = 'b';
    char maPhrase[20] = "Bonjour!\0";

    //////////////////
    // Booléen
    //////////////////
    bool porteOuverte = true;

    //////////////////
    // auto
    //////////////////
    // Généralement peu utilisé, sauf dans des cas spécifique avec des itérateurs dont les noms sont très longs.
    auto devineMonType = 0.f;

    //////////////////
    // Enum
    //////////////////
    enum NiveauEtudiant
    {
        eMeh = 0,
        eOk, // sera = 1
        eBien, // sera 2
        eSuper, // sera 3
        eExcellent, // sera 4

        eMax, // sera 5 pratique, vous devez toujours le faire.
    };
    NiveauEtudiant niveauC63 = NiveauEtudiant::eBien;
    bool estMeilleur = (int)NiveauEtudiant::eBien > (int)NiveauEtudiant::eExcellent;

    //////////////////
    //std::string
    //#include <string>
    //////////////////
    string maPhraseEnString = "Bonjour!!";
    const char* maPhraseEnChar = maPhraseEnString.c_str();

    //////////////////
    //std::cout
    //#include<iostream>
    //////////////////
    cout << "Hello World!\n";

    //////////////////
    // Conversions implicites
    //////////////////

    // int en float
    float nbPatate = 0;

    // double en float
    float nbSante = 0.01;

    // int en char
    char status = 3;

    //////////////////
    // Conversions génériques explicites
    // Essaie en ordre:
    // statique : pendant la compilation
    // dynamique : si les classes ont un ancètre commun ou une fonction de conversion
    // reinterpret : peu être n'importe quoi.
    //////////////////
    char power = (char)3;
    string message = string("oups");

    //////////////////
    // Écrire dans un stream
    //////////////////
    cout << "Un message dans la console!\n";

    ofstream myfile("example.txt");
    if (myfile.is_open())
    {
        myfile << "This is a line.\n";
        myfile << "This is another line.\n";
        myfile.close();
    }
    // JAMAIS omettre ses {} même si cpp le permet
    else { 
        cout << "Unable to open file";
    }

    //////////////////
    // Pointeurs
    //////////////////
    // Alloue de la mémoire sur la pile (mémoire "stack" qui est mieux optimisé mais moins flexible).
    // Appelé objet automatique.
    int stackInt = 5;

    // Alloue de la mémoire dynamique (flexible) dans la mémoire "heap".
    int* ptrInt = nullptr;
    ptrInt = new int(5);
    *ptrInt = 3;
    cout << "Mon pointeur de int: " << *ptrInt << endl;
    // Quand on utilise new, toujours appeler delete pour éviter les fuites mémoires.
    delete ptrInt;
    ptrInt = nullptr;
    // Validation de pointeur - toujours à faire avant d'utiliser un pointeur.
    if (ptrInt != nullptr)
    {
        cout << "Crash!" << *ptrInt << endl;
    }
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.