#include <iostream>
#include <windows.h> //Pour SetConsoleOutputCP
#include "Goblin.h"

//Déclaration de fonctions globales pour tantôt
void PresentationGoblinTresMalFait(Goblin InGoblin);
void PresentationGoblinMalFait(Goblin InGoblin);
void PresentationGoblinBienFait(Goblin InGoblin);

int main()
{
    //Pour voir les accents comme il faut.
    SetConsoleOutputCP(1252);

    cout << endl << "Durée de vie d'un objet automatique" << endl;
    {
        //Construit ici
        Goblin goblinAutomatique;
    } //Détruit ici

    cout << endl << "Durée de vie d'un objet automatique: dans un if" << endl;
    if (true)
    {
        //Construit ici
        Goblin goblinAutomatiqueDansUnIf("IffyGoblin");
    } //Détruit ici


    cout << endl << "Durée de vie d'un objet créé avec new" << endl;
    //Construit ici
    Goblin* ptrGoblin = new Goblin("PeterLeGoblin");
    const string& nomDeptrGoblin = ptrGoblin->GetName();
    cout << "Je suis " << nomDeptrGoblin << endl;
    //Détruit ici
    delete ptrGoblin;
    ptrGoblin = nullptr;

    cout << endl << "Passage par paramètre" << endl;

    Goblin goblinPresentateur("GoblinPresentateur");
    PresentationGoblinTresMalFait(goblinPresentateur);
    cout << endl;
    PresentationGoblinMalFait(goblinPresentateur);
    cout << endl;
    PresentationGoblinBienFait(goblinPresentateur);

}


//Implémentation
void PresentationGoblinTresMalFait(Goblin InGoblin)
{
    cout << "Présentation très mal faite du goblin " << InGoblin.GetName() << endl;
}

void PresentationGoblinMalFait(const Goblin InGoblin)
{
    cout << "Présentation mal faite du goblin " << InGoblin.GetName() << endl;
}

void PresentationGoblinBienFait(const Goblin InGoblin)
{
    cout << "Présentation bien fait du goblin " << InGoblin.GetName() << endl;
}
