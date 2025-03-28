#include "GameObjectText.h"
#include "GameObjectTextCounter.h"


LE::GameObjectTextCounter::GameObjectTextCounter(int InX, int InY)
    :GameObjectText(InX, InY, "X", 32)
{
    _Timer.SetDuration(1.f);
    _Timer.SetActive(true);
    _Timer.PlayOnce(false);
    ////////////////////////////////////
    //3) Faite que le texte par défaut soit 0 et non X
    SetText("0");
    ////////////////////////////////////
    _Timer.SetCallback(
        [this]() {
            ////////////////////////////////////
            //4) Faite qu'à chaque fois que le timer dépasse sa durée,
            //Il incrémente la valeur du compteur à et met à jour le texte.
            //Vous ne verrez aucun changement à ce stade, complétez 5) avant!
            this->SetText(std::to_string(++this->_Value));
            ////////////////////////////////////
        }
    );
}

LE::GameObjectTextCounter::~GameObjectTextCounter()
{}

void LE::GameObjectTextCounter::SetActive(bool InIsActive)
{
    _Timer.SetActive(InIsActive);
}

void LE::GameObjectTextCounter::Reset()
{
    _Timer.Reset();
}

void LE::GameObjectTextCounter::SetDuration(float InDuration)
{
    _Timer.SetDuration(InDuration);
}

void LE::GameObjectTextCounter::PreUpdate()
{
    ////////////////////////////////////
    //5) Mettez à jour le timer avec Uppdate. On doit passer la durée du frame et non le temps absolu.
    //Le compteur devrait fonctionner maintenant! Retournez dans main.cpp
    _Timer.Update(GetFrameTime());
    ////////////////////////////////////
}