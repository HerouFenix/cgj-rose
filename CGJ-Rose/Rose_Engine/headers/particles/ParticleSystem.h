#pragma once
#include "../vectors/Vector3.h"
#include "../vectors/Vector4.h"
#include "../vectors/Vector4.h"

#include "../drawing/Mesh.h"

#include "../camera/ArcBallCamera.h"
#include "../drawing/Shader.h"

#include "../../headers/materials/Particle_Material.h"

#include <chrono>
#include <vector>

typedef std::chrono::milliseconds ms;

struct ParticleProps
{
	Vector3 Position;
	Vector3 Velocity, VelocityVariation;
	Vector4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(int _numberOfParticles);

	void OnUpdate(float time_per_frame);
	void SetupParticleMesh(const std::string& path, float _meshScale, ArcBallCamera& camera);
	void OnRender();

	void Emit(ParticleProps& particleProps);

	Mesh particleMesh;
private:
	struct Particle
	{
		Vector3 Position;
		Vector3 Velocity;
		Vector4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 0;

	Shader shader;
	Particle_Material* particleMaterial;

	float size;
	int numberOfParticles;
	float meshScale;
};