#include <iostream>
#include "Patate.h"
//On evite une erreur de compilation grace au #pragma once
#include "Patate.h"


//
//#include : copie-colle le contenue entier d'un fichier
//en pratique sert à importer la declaration de symboles

int main()
{
    Patate p;

    #include "NeFaitPasCa.h"
    std::cout << "Hello World!\n";
    std::cout << PI << std::endl;
    std::cout << "Circonference de 4.0f : " << FORMULE_CIRCONFERENC(4.0f) << std::endl;
    //std::cout << "Circonference de Coucou :  : " << FORMULE_CIRCONFERENC("Coucou") << std::endl;
    std::cout << "addition 4+2 : " << ADDITION(4,2) << std::endl;

    std::cout << "fichier :" << __FILE__ << std::endl << "ligne : " << __LINE__ << std::endl;;


#undef GAME_RELEASE

#ifdef GAME_RELEASE
    std::cout << "is defined : " << std::endl;
#else
    std::cout << "is not defined : " << std::endl;
#endif


#ifndef STEAM_VERSION
    std::cout << "not on steam" << std::endl;

#endif
}
