#pragma once
#include <string>
#include <memory>
#include <vector>
#include "BaseObject.h"
#include "GameObject.h"

namespace LE
{
	class Scene : public IBaseObject
	{
		public:
			//Log ERROR: Nom de scène vide.
			Scene(const std::string& InName);
			virtual ~Scene();

			//Retourne le nom de la scène.
			const std::string& GetName() const;

			//Ajoute un GameObject2D de la collection
			//Si la scène est active, on appel Load sur l'objet ajouté
			//Log WARNING: Objet nommé X déjà dans la scène, l'objet n'est pas ajouté.
			void AddGameObject2D(std::shared_ptr<GameObject2D> InNewGameObject);

			//Enlève un GameObject2D
			//Si la scène est active, on appel Unload sur l'objet ajouté
			//Log WARNING: Objet nommé X n'est pas dans dans la scène, l'objet n'est pas enlevé.
			void RemoveGameObject2D(std::shared_ptr<GameObject2D> InRemovedGameObject);
			bool HasGameObject2D(std::shared_ptr<GameObject2D> InGameObject);

			//Appel Load sur les GameObject2D
			//Log WARNING: Scène déjà loadé, la scène ne reloadera pas.
			void Load();
			//Appel Unload sur les GameObject2D
			//Log WARNING: Scène n'est pas loadée, la scène ne déloadera pas.
			virtual void Unload();

			//Les méthodes suivantes sont appelées dans l'ordre dans le while à chaque image affichée.
			//Effectue les test de collisions, puis appelle PreUpdate sur les GameObject2D
			virtual void PreUpdate();
			//Appel Draw3D sur les GameObject2D
			virtual void Draw3D();
			//Appel Draw2D sur les GameObject2D
			virtual void Draw2D();
			//Compare tous les objets entre eux pour voir s'ils collisionnent et appel le fonction de callback au besoin
			//Filtre selon les masque de collision
			virtual void CheckAndNotifyCollision();
			//Appel LateUpdate sur les GameObject2D
			virtual void LateUpdate();
	private:
		std::string _Name;
		std::vector<std::shared_ptr<GameObject2D>> _GameObjects;
		bool _IsLoaded;
	};
}