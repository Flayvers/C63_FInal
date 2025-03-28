#pragma once
#include <functional>
#include <memory>
#include <string>
#include "raylib.h"
#include "BaseObject.h"

//Banque d'objets de jeu générique

namespace LE
{
	////////////////////////////////////////
	/// 2D objects
	////////////////////////////////////////
	class GameObject2D;
	//Informations de collision lorsque 2 objets se touches.
	struct CollisionEvent
	{
		Vector2 _Position;
		GameObject2D const* _MyObject;
		GameObject2D const* _OtherObject;

	};

	//Object générique avec une position 2D. Peut collisionner avec d'autres objets.
	//Peut optionnellement avoir un nom.
	class GameObject2D : public IBaseObject, public std::enable_shared_from_this<GameObject2D>
	{
	protected:
		Rectangle _CollisionBox = Rectangle{ 0.f,0.f,100.f,100.f };
		int _CollisionMaks = 0;
		std::string _Name = "Nameless";
		std::function<void(const CollisionEvent&)> _CallbackOnCollision = nullptr;

	public:
		GameObject2D(const std::string& InName = "GameObject2D");
		//Log WARNING: Objet nommé X a une boite de collision invalide (valeur négative). Collision désactivée (collision mask = 0).
		//Log WARNING: Un objet a un nom vide!
		GameObject2D(Vector2 InPosition, Vector2 InCollisionBox, int InCollisionMask, const std::string& InName = "GameObject2D");
		virtual ~GameObject2D();

		void SetCollisionMask(int InCollisionGroup);
		int GetCollisionMask() const;

		void SetPosition(Vector2 InPosition);
		const Vector2& GetPosition() const;

		//Log WARNING: Un objet a un nom vide!
		void SetName(const std::string& InName);
		const std::string& GetName() const;

		//Log WARNING: Objet nommé X a une boite de collision invalide (valeur négative). La boite n'est pas modifie.
		void  SetCollisionBox(const Vector2& InNewBoxSize);
		//Retourne la grosseur x et y de la boite de collision
		const Vector2& GetCollisionBox() const;
		//Retourne un rectangle placé à la position de l'objet et de la grosseur de la boîte de collision
		virtual const Rectangle& GetCollisionAtPosition() const;

		//*=*=*=*=*=*=*=*AVANCÉ=*=*=*=*=*=*=*=*=//
		//Dans la classe Scene, dans le PreUpdate, après avoir appelé PreUpdate sur les objets de jeu, on test les collisions entre tous les objets
		//de jeu, un peu comme dans l'exercice. Comme règle supplémentaire, on a les masques de collision comme expliqué plus haut.
		virtual void OnCollisionEvent(std::function<void(const CollisionEvent&)> InFunctionToCall);
		virtual bool CheckCollision(const std::weak_ptr<GameObject2D> InOtherGO, bool InNotify = false);
		//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=//

		//======DÉBUT======
		//GameObject2D ne fait rien ici, mais ça fourni un interface pour les classes qui en héritent
		//Vous n'avez rien à faire
		virtual void Load() {}
		virtual void Unload() {}

		virtual void PreUpdate() {}
		virtual void Draw3D() {}
		virtual void Draw2D() {}
		virtual void DrawDebug();
		virtual void LateUpdate() {}
		//======FIN======

		virtual void Destroy();
	};

	//Affiche une image à la position et le scale donné.
	class GameObjectSingleImage : public GameObject2D
	{
	protected:
		Image _Image;
		Texture _Texture;
		Color _Tint = WHITE;
		float _Rotation = 0.0f;
		float _Scale = 1.0f;
		std::string _FilePathToLoad;
		bool _IsLoaded = false;

	public:
		//Log ERROR: Objet nommé X a un nom de fichier vide.
		//Log WARNING: Objet nommé X réfère un fichier non-existant. Note: Il existe une fonction pour vérifier si un fichier existe dans Raylib!
		//Chemin valide pour accéder au fichier dans {racineVSProjet}/res/Test-Image.png:
		//string(GetWorkingDirectory()) + "\\res\\Test-Image.png"
		GameObjectSingleImage(const std::string& InImageFileName, const std::string& InName = "GameObjectSingleImage");
		//Attention, il faut vérifier si Image et Texture sont encore chargés!
		virtual ~GameObjectSingleImage();

		void SetScale(float InScale);
		float GetScale() const;

		void SetRotation(float InRotationInDegree);
		float GetRotation() const;

		void SetColorTint(const Color& InColorTint);
		const Color& GetColorTint() const;

		virtual const Rectangle& GetCollisionAtPosition() const;

		//L'Image et la Texture sont chargées au moment du load.
		//Log WARNING: Objet nommé X réfère un fichier non-existant. Note: Il existe une fonction pour vérifier si un fichier existe dans Raylib!
		//Log WARNING: Objet nommé X a déjà chargé son image et ne peut la recharger.
		virtual void Load();
		//L'Image et la Texture sont déchargées au moment du unload.
		//Log WARNING: Objet nommé X n'a pas d'image chargé et ne peut la décharger.
		virtual void Unload();

		//Returne l'objet Image
		const Image& GetImage() const;
		//Returne l'objet Texture
		const Texture& GetTexture() const;
		//Affiche la Texture à la position et la grosseur fournie
		//Si l'image n'est pas chargé, on affiche un carré de la couleur tentée (ColorTint) de la grosseur de la boite de collision
		virtual void Draw2D() override;

		//Note: les autres méthodes fournies par le parent (PreUpdate,Draw3D et LateUpdate) n'ont pas besoin d'être codée ici
		//car on en a pas besoin!
	};

	class GameObjectTile : public GameObjectSingleImage
	{
	protected:
		float _TextureScale = 1.0f;

	public:
		GameObjectTile(const std::string& InImageFileName, const Rectangle& InSceneRectangle);
		virtual void Draw2D() override;
	};
}

