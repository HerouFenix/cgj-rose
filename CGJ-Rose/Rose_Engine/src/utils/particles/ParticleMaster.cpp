#include "../../headers/particles/ParticleMaster.h"
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>

ParticleMaster::ParticleMaster()
{
	
}

void ParticleMaster::Init(GLuint UBO_BP, Vector4 color) {

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

	this->color = color;

	GLCall(glGenVertexArrays(1, &vaoID));
	GLCall(glBindVertexArray(vaoID));
	GLCall(glGenBuffers(1, &vboID));
	glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_DYNAMIC_DRAW);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
}


void ParticleMaster::UpdateAndDraw(float sof)
{

	int particlesToCreate = PPS * sof;
	int count = (int)floor(particlesToCreate);

	for (int i = 0; i < count; i++) {
		//Particle part = (generateRandomUnitVectorWithinCone(Vector3(0, 1, 0), 30));
		Particle part = (generateRandomUnitVectorWithinSphere());
		part.position += Vector3(0.0f, 0.2f, 0.0f);
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

		//std::cout << "Id: " << i << " ; Pos: " << pos << std::endl;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	glBufferData(GL_ARRAY_BUFFER, particles_vertices.size() * sizeof(float), 0, GL_DYNAMIC_DRAW);
	if(particles_vertices.size() > 0)
		glBufferSubData(GL_ARRAY_BUFFER, 0, particles_vertices.size() * sizeof(float), &particles_vertices[0]);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	shader_program.Bind();
	shader_program.SetUniform4fvec("u_Color", new float[] {color.getX(), color.getY(), color.getZ(), color.getW()});
	GLCall(glBindVertexArray(vaoID));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glDrawArrays(GL_POINTS, 0, particles.size()));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindVertexArray(0));
	shader_program.UnBind();
}

Vector3 ParticleMaster::generateRandomUnitVectorWithinCone(Vector3 coneDirection, float angle) {
	float cosAngle = (float)cos(angle);
	float theta = (float)(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f * M_PI);
	float z = cosAngle + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (1 - cosAngle));
	float rootOneMinusZSquared = (float)sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));

	Vector4 direction (x, y, z, 1);
	if (coneDirection.getX() != 0 || coneDirection.getY() != 0 || (coneDirection.getZ() != 1 && coneDirection.getZ() != -1)) {
		Vector3 rotateAxis = coneDirection.crossProd(Vector3(0, 0, 1));
		rotateAxis.normalize();
		float rotateAngle = (float)acos(coneDirection.dotProd(Vector3(0, 0, 1)));
		Matrix4 rotationMatrix = Matrix4::rotation(rotateAxis, -rotateAngle);
		direction = rotationMatrix * direction;
	}
	else if (coneDirection.getZ() == -1) {
		direction.setZ(direction.getZ() * -1);
	}
	return direction;
}

Vector3 ParticleMaster::generateRandomUnitVectorWithinSphere() {
	float low = -(diameter / 2);
	float high = diameter / 2;
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


Particle::Particle(Vector3 velocity) {
	this->velocity = velocity;
}

bool Particle::update(float sof, Shader* shader) {

	velocity.setY(velocity.getY() - (PARTICLE_GRAVITY * sof));
	Vector3 change(velocity);
	change *= (sof * PARTICLE_SPEED);
	position += change;
	float perc = lifeLeft / PARTICLE_LIFE_LENGTH;
	lifeLeft -= sof;
	return lifeLeft > 0;

}
