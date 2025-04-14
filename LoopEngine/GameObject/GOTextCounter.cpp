#include "LoopEngine/GameObject/GOText.h"
#include "LoopEngine/GameObject/GOTextCounter.h"

LE::GOTextCounter::GOTextCounter(int InX, int InY)
    :GOText(InX, InY, "X", 32)
{
    _Timer.SetDuration(1.f);
    _Timer.SetActive(true);
    _Timer.PlayOnce(false);
    ////////////////////////////////////
    //3) Faite que le texte par d�faut soit 0 et non X
    SetText("0");
    ////////////////////////////////////
    _Timer.SetCallback(
        [this]() {
            ////////////////////////////////////
            //4) Faite qu'� chaque fois que le timer d�passe sa dur�e,
            //Il incr�mente la valeur du compteur � et met � jour le texte.
            //Vous ne verrez aucun changement � ce stade, compl�tez 5) avant!
            SetText(std::to_string(++this->_Value));
            ////////////////////////////////////
        }
    );
}

LE::GOTextCounter::~GOTextCounter()
{}

void LE::GOTextCounter::SetActive(bool InIsActive)
{
    _Timer.SetActive(InIsActive);
}

void LE::GOTextCounter::Reset()
{
    _Timer.Reset();
}

void LE::GOTextCounter::SetDuration(float InDuration)
{
    _Timer.SetDuration(InDuration);
}

void LE::GOTextCounter::PreUpdate()
{
    ////////////////////////////////////
    //5) Mettez � jour le timer avec Uppdate. On doit passer la dur�e du frame et non le temps absolu.
    _Timer.Update(GetFrameTime());
    ////////////////////////////////////

}