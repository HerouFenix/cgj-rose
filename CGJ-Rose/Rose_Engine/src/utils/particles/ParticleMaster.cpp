#include "../../headers/particles/ParticleMaster.h"
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>

class Particle;

ParticleMaster::ParticleMaster()
{
	
}

void ParticleMaster::Init(
	GLuint UBO_BP, 
	float gravity, float life_length, float speed,
	Vector3 position, float diameter, Vector4 color, int max_particles, int particles_per_second) {

	this->PARTICLE_GRAVITY = gravity;
	this->PARTICLE_LIFE_LENGTH = life_length;
	this->PARTICLE_SPEED = speed;
	this->MASTER_POSITION = position;
	this->MASTER_DIAMETER = diameter;
	this->MASTER_COLOR = color;
	this->MASTER_MAX_PARTICLES = max_particles;
	this->MASTER_PPS = particles_per_second;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glPointSize(2);

	shader_program = Shader("resources/shaders/ParticleMaster.shader");
	shader_program.SetupShader_VsFsGs(false, false);
	shader_program.Bind();
	shader_program.SetUniformBlock("SharedMatrices", UBO_BP);

	GLCall(glGenVertexArrays(1, &vaoID));
	GLCall(glBindVertexArray(vaoID));
	GLCall(glGenBuffers(1, &vboID));
	glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_DYNAMIC_DRAW);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
}


void ParticleMaster::UpdateAndDraw(float sof)
{

	int particlesToCreate = MASTER_PPS * sof;
	int count = (int)floor(particlesToCreate);

	for (int i = 0; i < count; i++) {
		Particle part = Particle(generateRandomUnitVectorWithinSphere(), this);
		particles.push_back(part);
	}

	for (std::size_t i = 0; i < particles.size(); i++) {
		if (!particles[i].update(sof, &shader_program)) {
			particles.erase(particles.begin()+i);
		}
	}

	particles_vertices.clear();
	for (Particle p : particles) {
		particles_vertices.push_back(p.position.getX());
		particles_vertices.push_back(p.position.getY());
		particles_vertices.push_back(p.position.getZ());
	}

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	glBufferData(GL_ARRAY_BUFFER, particles_vertices.size() * sizeof(float), 0, GL_DYNAMIC_DRAW);
	if(particles_vertices.size() > 0)
		glBufferSubData(GL_ARRAY_BUFFER, 0, particles_vertices.size() * sizeof(float), &particles_vertices[0]);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	shader_program.Bind();
	shader_program.SetUniform4fvec("u_Color", new float[] {MASTER_COLOR.getX(), MASTER_COLOR.getY(), MASTER_COLOR.getZ(), MASTER_COLOR.getW()});
	GLCall(glBindVertexArray(vaoID));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glDrawArrays(GL_POINTS, 0, particles.size()));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindVertexArray(0));
	shader_program.UnBind();
}

Vector3 ParticleMaster::generateRandomUnitVectorWithinSphere() {
	float low = -(MASTER_DIAMETER / 2);
	float high = MASTER_DIAMETER / 2;
	float theta = RandomFloat(0, 2 * M_PI);
	float z = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	return Vector3(sqrt(1.0f - (z * z)) * cos(theta), sqrt(1.0f - (z * z)) * sin(theta), z);
}

float ParticleMaster::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Particle::Particle(Vector3 direction, ParticleMaster* particle_master)
{
	this->direction = direction;
	this->position = particle_master->MASTER_POSITION;
	this->particle_master = particle_master;
	this->life_left = particle_master->PARTICLE_LIFE_LENGTH;
}


bool Particle::update(float sof, Shader* shader) {

	direction.setY(direction.getY() - (particle_master->PARTICLE_GRAVITY * sof));
	Vector3 change(direction);
	change *= (sof * particle_master->PARTICLE_SPEED);
	position += change;
	life_left -= sof;
	return life_left > 0;

}
