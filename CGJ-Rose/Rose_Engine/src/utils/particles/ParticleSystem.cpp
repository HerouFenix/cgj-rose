#include "../../headers/particles/ParticleSystem.h"

#include "../../headers/particles/Random.h"
#include "../../headers/matrices/Matrix4.h"

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/compatibility.hpp>

#define GLM_ENABLE_EXPERIMENTAL

ParticleSystem::ParticleSystem(int _numberOfParticles)
{
	size = 0;
	numberOfParticles = _numberOfParticles;
	m_ParticlePool.resize(numberOfParticles);
	m_PoolIndex = numberOfParticles - 1;
}

void ParticleSystem::OnUpdate(float time_per_frame)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= time_per_frame;
		particle.Position += particle.Velocity * time_per_frame;
		particle.Rotation += 0.01f * time_per_frame;
	}
}

void ParticleSystem::SetupParticleMesh(const std::string& path, float _meshScale, ArcBallCamera& camera) {
	Shader basic1("resources/shaders/particle.shader");
	particleMaterial = new Particle_Material(basic1);

	particleMesh.CreateMesh(path, (Material*)particleMaterial, camera.UBO_BP);
	meshScale = _meshScale;
}

void ParticleSystem::OnRender()
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles using GLM lerp
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 colorBegin(particle.ColorBegin.getX(), particle.ColorBegin.getY(), particle.ColorBegin.getZ(), particle.ColorBegin.getW());
		glm::vec4 colorEnd(particle.ColorEnd.getX(), particle.ColorEnd.getY(), particle.ColorEnd.getZ(), particle.ColorEnd.getW());
		glm::vec4 color = glm::lerp(colorEnd, colorBegin, life);

		particleMaterial->setColour(Vector4(color.x, color.y, color.z, color.w));

		// Resize particles so they get smaller overtime
		size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

		// New particle position
		Matrix4 transform = Matrix4::translation(particle.Position) * Matrix4::rotationZ(particle.Rotation) *
			Matrix4::scaling(size, size, size) * Matrix4::scaling(meshScale, meshScale, meshScale);

		particleMesh.setWorldTransform(transform);

		particleMesh.Draw();
	}
}

void ParticleSystem::Emit(ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position; // Initial Postion
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>(); // Random initial rotation

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.setX(particle.Velocity.getX() + particleProps.VelocityVariation.getX() * (Random::Float() - 0.5f));

	float randY = Random::Float();
	if (randY > 0.7) {
		particle.Velocity.setY(particle.Velocity.getY() + particleProps.VelocityVariation.getY() * (-randY));
	}
	else {
		particle.Velocity.setY(particle.Velocity.getY() + particleProps.VelocityVariation.getY() * (randY-0.5f));
	}
	particle.Velocity.setZ(particle.Velocity.getZ() + particleProps.VelocityVariation.getZ() * (Random::Float() - 0.5f));

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f); // Random initial size
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
