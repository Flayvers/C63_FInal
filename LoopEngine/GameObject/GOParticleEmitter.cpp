#include "LoopEngine/Global.h"
#include "LoopEngine/GameObject/GOParticleEmitter.h"
#include "raymath.h"

LE::GOParticleEmitter::GOParticleEmitter(const std::string& InImageFileName, const std::string& InEmitterName)
	:GOSimpleTexture(InImageFileName,InEmitterName)
{
	_TimerContinuousEmission.PlayOnce(false);
	_TimerContinuousEmission.SetActive(false);
	_TimerContinuousEmission.SetCallback([this]() {
		Play();
		});
}

void LE::GOParticleEmitter::Play()
{
	///////////////////////////
	//7) Appeler Play() (testable avec le bouton) émet TOUJOURS un burst.
	//Ce n'est pas tout: dans ParticleEmitterParam, repérer les paramètres pour le no 7).
	//Si _IsEmittingContinuously est à vrai, on démarre le timercallback (configuré en PlayOnce)
	//et le temps d'appel sera aléatoire selon _RangeNextBurstTime.
	//Testez la fumée après avec Play() et Stop()
	EmitBurst();
	if (_EmissionParameter._IsEmittingContinuously)
	{
		_TimerContinuousEmission.SetActive(true);
		_TimerContinuousEmission.SetDuration(GetRandomFloat(_EmissionParameter._RangeNextBurstTime));
	}

	//Rendez-vous dans LE::GOParticleEmitter::EmitOne()
	///////////////////////////
}

void LE::GOParticleEmitter::Stop()
{
	_TimerContinuousEmission.SetActive(false);
}

void LE::GOParticleEmitter::KillAll()
{
	_ParticleStates.clear();
}

void LE::GOParticleEmitter::EmitOne()
{
	ParticleState state;
	state._LifeTime = 0.f;
	state._Position = GetWorldPosition();

	///////////////////////////
	//5) Toutes les valeur de ParticleEmitterParam du no 5 donnent l'état initial des particules.
	// Utilisez GetRandomFloat et GetRandomVector dans Global.h
	// Vitesse linéaire
	// Durée de vie
	// Vitesse de rotation
	// Accélération linéaire (exception - valeur fixe non aléatoire)
	//Allez ensuite dans LE::GOParticleEmitter::EmitBurst()
	///////////////////////////
	state._LinearVelocity = GetRandomVector({_EmissionParameter._RangeInitialLinearVelocity[0].x, _EmissionParameter._RangeInitialLinearVelocity[0].y, _EmissionParameter._RangeInitialLinearVelocity[1].x, _EmissionParameter._RangeInitialLinearVelocity[1].y});
	state._DieTime = GetRandomFloat(_EmissionParameter._RangeDieTime);
	state._RotationVelocity = GetRandomFloat(_EmissionParameter._RangeInitialRotationVelocity);
	state._LinearAcceleration = _EmissionParameter._LinearAcceleration;

	///////////////////////////
	//8) La position de la particule doit être émise aléatoirement dans la boite de collision
	//Aidez-vous de GetRandomVector de Global.h pour initialiser sa position
	//Testez ensuite la fumée, elle sera émise dans un carré au lieu d'un point.
	//Rendez-vous dans ParticleEmitterParamRain()
	///////////////////////////
	state._Position = GetRandomVector(GetCollisionAtWorldPosition());



	_ParticleStates.emplace_back(state);
}


void LE::GOParticleEmitter::EmitBurst()
{
	///////////////////////////
	//6) Dans ParticleEmitterParam, section no6), utilisez le paramètre pour émettre un nombre de particule aléatoire.
	//Testez avec le bouton EmitBurst()
	int burstQuantity = GetRandomValue(_EmissionParameter._RangeBurstQuantity[0], _EmissionParameter._RangeBurstQuantity[1]);
	for (int i = 0; i < burstQuantity; ++i)
	{
		EmitOne();
	}

	//Allez dans LE::GOParticleEmitter::Play()
	///////////////////////////
}

void LE::GOParticleEmitter::PreUpdate()
{
	const float delta = GetFrameTime();
	_TimerContinuousEmission.Update(delta);

	//Efface les particules dont la durée de vie est terminée.
	_ParticleStates.erase(
		std::remove_if(_ParticleStates.begin(), _ParticleStates.end(), [](LE::GOParticleEmitter::ParticleState p) {
				return p._LifeTime > p._DieTime;
			}),
		_ParticleStates.end()
	);

	for (auto& p : _ParticleStates)
	{

		///////////////////////////
		//3) Bougez avec WASD et utilisez le bouton EmitOne() pour tester. Une petite particule devrait apparaître
		//Vous devez mettre à jour l'état de la particule ici. Le résultat final doit être comme le vidéo.
		//Liftetime:
		//Rotation:
		//Vitesse
		//Position
		///////////////////////////

		p._LifeTime += delta;
		p._Rotation += p._RotationVelocity * delta;
		p._Position.x += p._LinearVelocity.x * delta;
		p._Position.y += p._LinearVelocity.y * delta;
		p._LinearVelocity.x += p._LinearAcceleration.x * delta;
		p._LinearVelocity.y += p._LinearAcceleration.y * delta;

		///////////////////////////
		//4) Dans ParticleEmitterParam, les variable de no 4) vous donnerons les points de départ et d'arrivée de la grosseur et de la couleur.
		//Calculer à combien de % la vie de la particule est rendue avant.
		float lifePercentage = p._LifeTime / p._DieTime;
		p._Size = Lerp(_EmissionParameter._RangeSize.x, _EmissionParameter._RangeSize.y, lifePercentage);
		p._Color = ColorLerp(_EmissionParameter._StartEndColor[0], _EmissionParameter._StartEndColor[1], lifePercentage);

		//Grosseur - Utiliser la fonction Lerp de Raylib
		//Couleur - Utiliser ColorLerp de Raylib - 
		//Rendez-vous dans LE::GOParticleEmitter::EmitOne()
		///////////////////////////
	}
}

void LE::GOParticleEmitter::Draw2D()
{
	GameObject::Draw2D();
	for (auto& p : _ParticleStates)
	{
		Rectangle destination{p._Position.x,p._Position.y,p._Size,p._Size };
		const float center = p._Size * 0.5f;
		Vector2 origin{ center ,center };
		if (IsTextureValid(_Texture))
		{
			Rectangle source{0,0,_Texture.width,_Texture.height};
			DrawTexturePro(_Texture, source, destination, origin,p._Rotation, p._Color);
		}
		else
		{
			DrawRectanglePro(destination, origin, p._Rotation, p._Color);
		}
	}
}
