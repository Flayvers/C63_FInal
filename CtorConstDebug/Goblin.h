#pragma onc
#include <string>

using namespace std;

class Goblin
{
public:
	//Constructeur - toujours appelé automatiquement lors de la construction.
	Goblin();
	//Overload du constructeur possible
	//TOUJOURS: Passer un const & pour toutes les non primitives
	//Si on passe string ou const string, la string sera copiée.
	Goblin(const string& InName);
	//Destructeur - toujours appelé lors de la destruction.
	~Goblin();


	//const string&: retourne une RÉFÉRENCE (et non une copie) de la string. La string ne peut pas être modifiée
	// grâce au const. Autrement, ça reviendrait à modifier la string de l'instance de l'extérieur ce qui n'est
	//pas idéal
	//GetName() const: L'instance courrante (le this) n'est pas modifié.
	const string&  GetName() const;


	//GetLife() const: L'instance courrante (le this) n'est pas modifié.
	int GetLife() const;
	//Ici, on modifie le membre _Life donc on ne peut pas faire void SetLife(int InLife) const;
	void SetLife(int InLife);

private:
	//Une constante initialisée dans la déclaration de classe.
	const string _Name = "GoblinNoName";
	int _Life = 10;
};

