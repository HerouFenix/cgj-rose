#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../vectors/Vector3.h"
#include "../vectors/Vector4.h"
#include "../drawing/Shader.h"
#include "../drawing/VertexArray.h"
#include "../drawing/Renderer.h"

# define M_PI           3.14159265358979323846  /* pi */

class Particle;

class ParticleMaster
{
public:
	GLuint vaoID;
	GLuint vboID;
	int particleCount = 0;
	std::vector<float> particles_vertices;
	std::vector<Particle> particles;
	
	Shader shader_program;

	float PARTICLE_GRAVITY = 0.0f;
	float PARTICLE_LIFE_LENGTH = 5.0f;
	float PARTICLE_SPEED = 0.2f;
	float MASTER_DIAMETER = 3.0f;
	Vector3 MASTER_POSITION = Vector3();
	Vector4 MASTER_COLOR = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	int MASTER_MAX_PARTICLES = 1000;
	int MASTER_PPS = 50;

	ParticleMaster();
	void Init(GLuint UBO_BP, 
	float gravity, float life_length, float speed,
	Vector3 position, float diameter, Vector4 color, int max_particles, int particles_per_second);
	void UpdateAndDraw(float sof);

	Vector3 generateRandomUnitVectorWithinSphere();

	float RandomFloat(float a, float b);

};

class Particle
{
public:
	Vector3 direction = Vector3(0, 0, 0);
	Vector3 position = Vector3(0, 0, 0);
	float life_left;
	ParticleMaster* particle_master;
	Particle(Vector3 direction, ParticleMaster* master);
	bool update(float sof, Shader* shader);
};
