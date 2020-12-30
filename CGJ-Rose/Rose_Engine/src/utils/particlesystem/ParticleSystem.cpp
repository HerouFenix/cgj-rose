#include "../../headers/particlesystem/ParticleSystem.h"

#include "../../headers/particlesystem/Random.h"
#include "../../headers/matrices/Matrix4.h"
#include "../../headers/materials/Particle_Material.h"

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/compatibility.hpp>

#define GLM_ENABLE_EXPERIMENTAL

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(10);
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

void ParticleSystem::SetupParticleMesh(ArcBallCamera& camera) {
	Shader basic1("resources/shaders/particle.shader");
	Particle_Material* b1 = new Particle_Material(basic1);

	particleMesh.CreateMesh("resources/models/cube.obj", (Material*)b1, camera.UBO_BP);
}

void ParticleSystem::OnRender()
{
	/*if (!particleMesh.VaoID)
	{
		

		//m_ParticleShader = std::unique_ptr<Shader>(new Shader("resources/shaders/particle.shader"));
		//shader = Shader("resources/shaders/particle.shader");
		//shader.SetupShader(false, false);
		//shader.SetUniformBlock("SharedMatrices", camera.UBO_BP);
	}*/

	//shader.Bind();
	//glUniformMatrix4fv(m_ParticleShaderViewProj, 1, GL_FALSE, glm::value_ptr(camera.GetViewProjectionMatrix()));
	//shader.SetUniformBlock("SharedMatrices", camera.UBO_BP);

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 colorBegin(particle.ColorBegin.getX(), particle.ColorBegin.getY(), particle.ColorBegin.getZ(), particle.ColorBegin.getW());
		glm::vec4 colorEnd(particle.ColorEnd.getX(), particle.ColorEnd.getY(), particle.ColorEnd.getZ(), particle.ColorEnd.getW());
		glm::vec4 color = glm::lerp(colorEnd, colorBegin, life);


		Particle_Material* old_child = dynamic_cast<Particle_Material*>(particleMesh.material);
		old_child->setColour(Vector4(color.x, color.y, color.z, color.w));

		//color.a = color.a * life;

		size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

		// Render
		
		Matrix4 transform = Matrix4::translation(particle.Position) * Matrix4::rotationZ(particle.Rotation) *
			Matrix4::scaling(size, size, size) * Matrix4::scaling(0.25f,0.25f,0.25f);

		particleMesh.setWorldTransform(transform);

		particleMesh.Draw(false, false);
	}
}

void ParticleSystem::Emit(ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.setX(particle.Velocity.getX() + particleProps.VelocityVariation.getX() * (Random::Float() - 0.5f));
	particle.Velocity.setY(particle.Velocity.getY() + particleProps.VelocityVariation.getY() * (Random::Float() - 0.5f));
	particle.Velocity.setZ(particle.Velocity.getZ() + particleProps.VelocityVariation.getZ() * (Random::Float() - 0.5f));

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
