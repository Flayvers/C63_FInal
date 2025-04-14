#pragma once
#include <functional>
#include <memory>
#include <string>
#include "raylib.h"
#include "LoopEngine/GameObject/GOSimpleTexture.h"
#include "LoopEngine/TimerCallback.h"

namespace LE
{
	class GOParticleEmitter : public GOSimpleTexture
	{
		public:
			struct ParticleEmitterParam
			{
				//////////////////////////
				//Pour no 4)
				//Fixed value - particles
				Vector2 _RangeSize{50.f,70.f};
				Color _StartEndColor[2]{WHITE,BLANK};
				//////////////////////////

				//////////////////////////
				//Pour no 5)
				//Random - particles
				Vector2 _RangeInitialLinearVelocity[2] = {{-40.f,-150.f},{40.f,-200.f}};
				Vector2 _RangeDieTime{0.4f,0.7f};
				Vector2 _RangeInitialRotationVelocity{-360.f,360.f};
				//Fixed value - particles
				Vector2 _LinearAcceleration{0.f,-900.f};
				//////////////////////////

				//////////////////////////
				//Pour no 6)
				//Random - emitter
				int _RangeBurstQuantity[2]{ 30,50 };
				//////////////////////////

				//Pour no 7)
				//Fixed value - emitter
				bool _IsEmittingContinuously = false;
				Vector2 _RangeNextBurstTime{ 0.1f,0.3f };
				//Random - emitter
			};

		protected:
			struct ParticleState
			{
				float _LifeTime = 0.f;
				float _DieTime = 1.f;
				Vector2 _Position = { 0.f,0.f };

				float _Rotation = 0.f;
				float _RotationVelocity = 0.f;
				float _Size = 100.f;
				Vector2 _LinearVelocity = {100.f,0.f};
				Vector2 _LinearAcceleration = {0.f,1000.f};
				Color _Color = WHITE;
			};

			std::vector<ParticleState> _ParticleStates;
			TimerCallback _TimerContinuousEmission;

		public:
			GOParticleEmitter(const std::string& InImageFileName, const std::string& InEmitterName = "GOEmitter");
			ParticleEmitterParam _EmissionParameter;

			void EmitOne();
			void EmitBurst();
			void KillAll();
			void Play();
			void Stop();

			virtual void PreUpdate() override;
			virtual void Draw2D() override;

			struct ParticleEmitterParamSmoke : public LE::GOParticleEmitter::ParticleEmitterParam
			{
				ParticleEmitterParamSmoke()
				{
					_RangeBurstQuantity[0] = 30;
					_RangeBurstQuantity[1] = 50;
					_RangeInitialLinearVelocity[0] = { -40.f,-150.f };
					_RangeInitialLinearVelocity[1] = { 40.f,-200.f };
					_RangeSize = { 50.f,70.f };
					_RangeDieTime = { 0.4f,0.7f };
					_RangeInitialRotationVelocity = { -360.f,360.f };

					_LinearAcceleration = { 0.f,-900.f };
					_StartEndColor[0] = WHITE;
					_StartEndColor[1] = BLANK;

					_IsEmittingContinuously = true;
					_RangeNextBurstTime = { 0.01f,0.01f };
				}
			};

			struct ParticleEmitterParamDirt : public LE::GOParticleEmitter::ParticleEmitterParam
			{
				ParticleEmitterParamDirt()
				{
					_RangeBurstQuantity[0] = 30;
					_RangeBurstQuantity[1] = 40;
					constexpr float explosionVelocity = 500.f;
					_RangeInitialLinearVelocity[0] = { -explosionVelocity,-explosionVelocity };
					_RangeInitialLinearVelocity[1] = {  explosionVelocity, explosionVelocity };
					_RangeSize = { 10.f,80.f };
					_RangeDieTime = { 0.4f,0.6f };
					_RangeInitialRotationVelocity = { -250.f,250.f };

					_LinearAcceleration = { 0.f,900.f };
					_StartEndColor[0] = WHITE;
					_StartEndColor[1] = {255,255,255,0};

					_IsEmittingContinuously = false;
					_RangeNextBurstTime = { 0.0f,0.0f };
				}
			};

			struct ParticleEmitterParamRain : public LE::GOParticleEmitter::ParticleEmitterParam
			{
				ParticleEmitterParamRain()
				{
					///////////////////////////
					//8) Trouvez des paramètres adéquats afin de faire une averse de pluie (Émetteur Rain).
					//Inspirez-vous de ParticleEmitterParamSmoke pour débuter
					//Une chose est déja faite pour vous la boite de collision de l'émetteur de pluie est {1000,1}.
					_RangeBurstQuantity[0] = 4;
					_RangeBurstQuantity[1] = 8;

					_RangeInitialLinearVelocity[0] = { 300.f, 600.f };
					_RangeInitialLinearVelocity[1] = { 0.f, 0.f };
					_RangeSize = { 70.f, 70.f };
					_RangeDieTime = { 10.f, 10.f };
					_RangeInitialRotationVelocity = { 0.f, 0.f };

					_LinearAcceleration = { 100.f, 100.f };
					_StartEndColor[0] = WHITE;
					_StartEndColor[1] = BLANK;

					_IsEmittingContinuously = true;
					_RangeNextBurstTime = { 0.05f,0.1f };

					//Fin de l'exercice
					///////////////////////////
				}
			};

			
	};

}

