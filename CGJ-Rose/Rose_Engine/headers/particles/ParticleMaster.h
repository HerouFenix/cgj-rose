#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../vectors/Vector3.h"
#include "../vectors/Vector4.h"
#include "../drawing/Shader.h"
#include "../drawing/VertexArray.h"
#include "../drawing/Renderer.h"

# define M_PI           3.14159265358979323846  /* pi */

class Particle
{
public:
	Vector3 velocity = Vector3(0, 0, 0);
	Vector3 position = Vector3(0, 0, 0);
	Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	Particle(Vector3 velocity);

	bool update(float sof, Shader* shader);

private:
	float PARTICLE_GRAVITY = 0.0f;
	float PARTICLE_LIFE_LENGTH = 5.0f;
	float PARTICLE_SPEED = 0.2f;
	float lifeLeft = PARTICLE_LIFE_LENGTH;

};

class ParticleMaster
{
public:
	GLuint vaoID;
	GLuint vboID;
	int particleCount = 0;
	std::vector<float> particles_vertices;
	std::vector<Particle> particles;
	Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	float diameter = 3.0f;
	Shader shader_program;

	ParticleMaster();
	void Init(GLuint UBO_BP, Vector4 color);
	void UpdateAndDraw(float sof);

	Vector3 generateRandomUnitVectorWithinCone(Vector3 coneDirection, float angle);

	Vector3 generateRandomUnitVectorWithinSphere();

	float RandomFloat(float a, float b);

private:
	int MAX_PARTICLES  = 1000;
	int PPS = 50;
};


