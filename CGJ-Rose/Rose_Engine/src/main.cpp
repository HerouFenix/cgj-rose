
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <typeinfo>


#include "../headers/matrices/Matrix4.h"

#include "../headers/camera/Camera.h"
#include "../headers/camera/ArcBallCamera.h"

#include "../headers/drawing/Shader.h"
#include "../headers/drawing/Mesh.h"

#include "../headers/drawing/Skybox.h"

#include "../headers/scene/SceneGraph.h"
#include "../headers/scene/Scene.h"

#include "../headers/particles/ParticleSystem.h"

#include <ctime>
#include <ratio>
#include <chrono>
#include "../headers/materials/Basic_Material.h"
#include "../headers/materials/Rose_Material.h"
#include "../headers/materials/Marble_Material.h"
#include "../headers/materials/Glass_Material.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../headers/materials/stb_image.h"
#include "../headers/materials/Wood_Material.h"
#include "../headers/materials/Stem_Material.h"

// TODO - Shadows ; Better Marble ; Make light correspond to actual position and equal to all materials instead of hardcoded...

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

GLuint ProgramId;
std::vector <Vertex> Vertices;
std::vector <Texcoord> Texcoords;
std::vector <Normal> Normals;

Skybox skybox;

Mesh meshes[6];

int window_width;
int window_height;
float cursorX, cursorY;
float xOffset, yOffset;

const float Threshold = (float)1.0e-5;

Scene scene;

const GLuint UBO_BP = 0;

bool ortho = false;
bool projChanged;

// KEY PRESSED FLAGS
bool forwardKeyPressed = false;
bool backwardKeyPressed = false;
bool lockMouse = false;
bool firstMouse = true;
bool mouseMoved = false;

bool moveForward = false;
bool moveBackward = false;
bool moveLeft = false;
bool moveRight = false;

bool mouseRotating = true;
bool downMoved, upMoved = false;

bool cameraReset = false;
bool mouseHeld = false;
bool automaticRotating = false;

ParticleProps particle;
ParticleSystem particleSystem(1000);
int spawnCounter = 25;


unsigned int depthMapFBO;
unsigned int depthMap;
const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
const unsigned int WIN_HEIGHT = 920, WIN_WIDTH = 920;


Shader lightDepthShader;
Vector3 lightPosition(-4.0f, 0.0f, 0.0f);

/////////////////////////////////////////////////////////////////////// SCENE
void moveCamera() {
	// ARCBALL CAMERA //

	if (forwardKeyPressed) {
		scene.GetSceneGraphs()[0]->camera.incrementRadius(-0.05f);
	}
	if (backwardKeyPressed) {
		scene.GetSceneGraphs()[0]->camera.incrementRadius(0.05f);
	}

	if (mouseMoved) {
		if (mouseHeld) {
			scene.GetSceneGraphs()[0]->camera.rotateCameraAroundQuaternionHorizontal(xOffset);
			scene.GetSceneGraphs()[0]->camera.rotateCameraAroundQuaternionVertical(-yOffset);
			mouseMoved = false;
		}
		else if (lockMouse) {
			scene.GetSceneGraphs()[0]->camera.rotateCameraAroundQuaternionHorizontal(-xOffset);
			scene.GetSceneGraphs()[0]->camera.rotateCameraAroundQuaternionVertical(yOffset);
			mouseMoved = false;
		}
	}

	///////////////////////////////////////////////////////////////////////

	cameraReset = false;
	if (projChanged)
		!projChanged;
}

void moveFloor() {
	if (moveForward) {
		scene.GetSceneGraphs()[0]->GetRoot()->position += Vector3(0, 0, -0.05);
	}
	if (moveBackward) {
		scene.GetSceneGraphs()[0]->GetRoot()->position += Vector3(0, 0, 0.05);
	}
	if (moveLeft) {
		scene.GetSceneGraphs()[0]->GetRoot()->position += Vector3(-0.05, 0, 0);
	}
	if (moveRight) {
		scene.GetSceneGraphs()[0]->GetRoot()->position += Vector3(0.05, 0, 0);
	}
}

void drawScene()
{
	// Movements
	bool cameraMoved = (mouseMoved || projChanged || cameraReset || forwardKeyPressed || backwardKeyPressed);

	if (cameraMoved)
		moveCamera();

	bool floorMoved = (moveForward || moveBackward || moveLeft || moveRight);
	if (floorMoved) {
		moveFloor();
	}
	////////////////

	// Render to Depth Map
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	scene.DrawSceneGraphsDepth(&lightDepthShader, lightPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// Render as normal with shadow mapping (using depth map)
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, depthMap);


	// Emit Particles
	/*
	if (spawnCounter < 25) {
		particleSystem.Emit(particle);
	}

	if (spawnCounter <= 0) {
		spawnCounter = 100;
	}
	else {
		spawnCounter--;
	}

	particleSystem.OnUpdate(0.005f);
	particleSystem.OnRender();
	*/

	scene.DrawSceneGraphs(ortho);

	// Draw skybox
	skybox.Draw();
}


///////////////////////////////////////////////////////////////////// CALLBACKS

void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	glViewport(0, 0, winx, winy);
}

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void destroyBufferObjects()
{
	for (Mesh m : meshes)
	{
		glBindVertexArray(m.VaoID);
		glDisableVertexAttribArray(VERTICES);
		glDisableVertexAttribArray(TEXCOORDS);
		glDisableVertexAttribArray(NORMALS);
		glDeleteVertexArrays(1, &(m.VaoID));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void window_close_callback(GLFWwindow* win)
{
	destroyBufferObjects();
	std::cout << "Bye bye!" << std::endl;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	//std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;

	// Key Presses
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_P:
			ortho = !ortho;
			projChanged = true;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			window_close_callback(win);
			break;
		case GLFW_KEY_UP:
			forwardKeyPressed = true;
			break;
		case GLFW_KEY_DOWN:
			backwardKeyPressed = true;
			break;
		case GLFW_KEY_W:
			moveForward = true;
			break;
		case GLFW_KEY_S:
			moveBackward = true;
			break;
		case GLFW_KEY_A:
			moveLeft = true;
			break;
		case GLFW_KEY_D:
			moveRight = true;
			break;
		case GLFW_KEY_R:
			scene.GetSceneGraphs()[0]->camera.resetCamera(); // Reset camera
			//scene.GetSceneGraphs()[0]->GetRoot()->ResetToDefaultPosition(); // Reset objects
			cameraReset = true;
			break;
		case GLFW_KEY_F:
			lockMouse = !lockMouse;
			if (lockMouse) {
				firstMouse = true;
			}
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_UP:
			forwardKeyPressed = false;
			break;
		case GLFW_KEY_DOWN:
			backwardKeyPressed = false;
			break;
		case GLFW_KEY_W:
			moveForward = false;
			break;
		case GLFW_KEY_S:
			moveBackward = false;
			break;
		case GLFW_KEY_A:
			moveLeft = false;
			break;
		case GLFW_KEY_D:
			moveRight = false;
			break;
		}
	}

}


void mouse_callback(GLFWwindow* win, double xPos, double yPos) {
	if (firstMouse) // initially set to true
	{
		cursorX = (float)xPos;
		cursorY = (float)yPos;
		firstMouse = false;
	}

	xOffset = (float)xPos - cursorX;
	yOffset = cursorY - (float)yPos; // reversed since y-coordinates range from bottom to top

	cursorX = (float)xPos;
	cursorY = (float)yPos;

	mouseMoved = true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS)
			mouseHeld = true;
		else
			mouseHeld = false;
	}
}


void setupCallbacks(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
}

///////////////////////////////////////////////////////////////////////// SETUP

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync)
{
	window_width = winx;
	window_height = winy;

	cursorX = (float)window_width / 2;
	cursorY = (float)window_height / 2;

	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);

	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);

	return win;
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW()
{
	glewExperimental = GL_TRUE;
	// Allow extension entry points to be loaded even if the extension isn't 
	// present in the driver's extensions string.
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	// You might get GL_INVALID_ENUM when loading GLEW.
}

void checkOpenGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy)
{
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}

void setupShaderProgram() {
	// TODO - CHANGE THIS TO NUMBER OF MESHES BEING DRAWN
	for (int i = 0; i < 6; i++) {
		meshes[i].setupShader(UBO_BP);
	}
	lightDepthShader.SetupShader(false, false);
}

void setupBufferObjects() {
	// TODO - CHANGE THIS TO NUMBER OF MESHES BEING DRAWN
	for (int i = 0; i < 6; i++) {
		meshes[i].setupBufferObjects();
	}
}

void setupSkybox() {
	std::string faces[6] = { "resources/images/right.jpg","resources/images/left.jpg" ,"resources/images/top.jpg" ,"resources/images/bottom.jpg" ,"resources/images/front.jpg" ,"resources/images/back.jpg" };
	//std::string faces[6] = { "resources/images/back.png","resources/images/bottom.png" ,"resources/images/front.png" ,"resources/images/left.png" ,"resources/images/right.png" ,"resources/images/top.png" };

	skybox.SetTextures(faces);
	skybox.SetShader(Shader("resources/shaders/Skybox.shader"));
	skybox.SetupSkybox(10.0f);
}

void setupParticleSystem() {
	// Init here
	particle.ColorBegin = { 202.0f / 255.0f, 44.0f / 255.0f, 146.0f / 255.0f, 1.0f };
	particle.ColorEnd = { 242.0f / 255.0f, 198.0f / 255.0f, 226.0f / 255.0f, 1.0f };
	particle.SizeBegin = 0.5f, particle.SizeVariation = 0.3f, particle.SizeEnd = 0.0f;
	particle.LifeTime = 1.25f;
	particle.Velocity = Vector3();
	particle.VelocityVariation = Vector3(1.0f, 1.2f, 1.0f);
	particle.Position = Vector3(0.05f, 0.6f, 0.0f);

	particleSystem.SetupParticleMesh("resources/models/rose12.obj", 0.1f, scene.GetSceneGraphs()[0]->camera);
}

void setupCamera() {
	// ARC BALL CAMERA SETUP //
	ArcBallCamera c(5);

	c.setOrthoProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
	c.setPrespProjectionMatrix(50, ((GLfloat)window_width / (GLfloat)window_height), 1.0f, 25.0f);

	//Set initial cursor position to be the middle of the screen
	cursorX = (float)window_width / 2;
	cursorY = (float)window_height / 2;

	scene.GetSceneGraphs()[0]->SetCamera(c);
	scene.GetSceneGraphs()[0]->camera.SetupCamera(UBO_BP);
	scene.GetSceneGraphs()[0]->camera.RenderCamera(ortho);

	projChanged = false;
}

void setupScene() {
	scene.SetupSceneGraph(scene.GetSceneGraphs()[0], meshes);
}

void setupDepthMap() {
	lightDepthShader = Shader("resources/shaders/LightDepth.shader");

	glGenFramebuffers(1, &depthMapFBO);

	// Generate Depth Texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Attach it as the framebuffer's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);

#ifdef ERROR_CALLBACK
	setupErrorCallback();
#endif

	setupSkybox();
	setupCamera();
	setupParticleSystem();
	setupDepthMap();

	// SET MATERIALS ////////////////////////////////////////////
	Shader basic1("resources/shaders/Rose.shader");
	Rose_Material* b1 = new Rose_Material(basic1);

	Shader basic2("resources/shaders/Stem_Shader.shader");
	Stem_Material* b2 = new Stem_Material(basic2);
	b2->setColour(Vector4(0.4f, 0.6f, 0.2f, 1.0f));

	Shader basic3("resources/shaders/Marble.shader");
	Marble_Material* b3 = new Marble_Material(basic3);
	b3->setColour(Vector4(0.4f, 0.2f, 0.1f, 1.0f));

	Shader basic4("resources/shaders/Wood_Shader.shader");
	Wood_Material* b4 = new Wood_Material(basic4);
	b4->setColour(Vector4(0.4f, 0.2f, 0.1f, 1.0f));

	Glass_Material* b5 = new Glass_Material();
	b5->setColour(Vector4(0.776f, 0.886f, 0.890f, 0.15f));

	Shader basic5("resources/shaders/lightSource.shader"); // Light Source
	Basic_Material* b6 = new Basic_Material(basic5);

	Shader basic7("resources/shaders/Basic3D.shader");
	Basic_Material* b7 = new Basic_Material(basic7);
	b7->setColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	// SET MESHSES //////////////////////////////////////////////

	Mesh rose, stem, dome, base, handle, light, cube;

	rose.CreateMesh("resources/models/rose12.obj", (Material*)b1, UBO_BP);

	stem.CreateMesh("resources/models/stem.obj", (Material*)b2, UBO_BP);

	base.CreateMesh("resources/models/base.obj", (Material*)b3, UBO_BP);

	handle.CreateMesh("resources/models/handle.obj", (Material*)b4, UBO_BP);

	//dome.CreateMesh("resources/models/dome_quarter.obj", (Material*)b5, UBO_BP);
	//dome.CreateMesh("resources/models/dome.obj", (Material*)b5, UBO_BP);
	dome.CreateMesh("resources/models/dome_2.obj", (Material*)b5, UBO_BP);

	light.CreateMesh("resources/models/cube.obj", (Material*)b6, UBO_BP);
	cube.CreateMesh("resources/models/cube.obj", (Material*)b7, UBO_BP);

	meshes[0] = rose;
	meshes[1] = stem;
	meshes[2] = dome;
	meshes[3] = base;
	//meshes[4] = handle;
	meshes[4] = cube;
	meshes[5] = light;

	setupBufferObjects();
	setupShaderProgram();
	setupScene();
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		// Double Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (lockMouse) {
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Tell GLFW that it should hide the cursorand capture it.Capturing a cursor means that, once the application has focus, the mouse cursor stays within the center of the window(unless the application loses focus or quits)
		}
		else {
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		drawScene();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwTerminate();
}


////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{
	// DRAW SCENE //
	scene.CreateSceneGraph();
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		WIN_WIDTH, WIN_HEIGHT, "The Enchanted Rose", is_fullscreen, is_vsync);
	run(win);

	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END