
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "../headers/matrices/Matrix4.h"
//#include "../headers/camera/Camera.h"
//#include "../headers/camera/ArcBallCamera.h"
//#include "../headers/drawing/Obj_Loader.h"
//
//int window_width;
//int window_height;
//float cursorX, cursorY;
//float xOffset, yOffset;
//
//Camera camera(Vector3(5, 5, 5), Vector3(0, 0, 0), Vector3(0, 1, 0));
//ArcBallCamera arcBall(5);
//
//float view[16];
//float proj[16];
//bool ortho = false;
//bool projChanged;
//
//bool quaternionRotation = false;
//
//// KEY PRESSED FLAGS
//bool forwardKeyPressed = false;
//bool backwardKeyPressed = false;
//bool lockMouse = true;
//bool firstMouse = true;
//bool mouseMoved = false;
//
//bool keyRotationX = false;
//bool keyRotationY = false;
//bool keyRotationZ = false;
//bool mouseRotating = true;
//bool downMoved, upMoved = false;
//
//bool cameraReset = false;
//bool stopRotating = false;
//bool automaticRotating = false;
//
//Obj_Loader obj_loader;
//
///////////////////////////////////////////////////////////////////////// SCENE
//
//void move_camera() {
///*
//	// FPS CAMERA
//
//	if (forwardKeyPressed) {
//		camera.moveCameraForward(0.05f);
//	}
//	if (backwardKeyPressed) {
//		camera.moveCameraBackward(0.05f);
//	}
//
//	// ROTATE CAMERA //
//
//	if (!stopRotating) {
//		if (!quaternionRotation) {
//			if (automaticRotating) {
//				camera.rotateCameraAround(1, Vector3(0.0f, 1.0f, 0.0f));
//			}
//			else
//
//				if (mouseMoved) {
//					camera.rotateCameraAround(xOffset, Vector3(0.0f, 1.0f, 0.0f));
//					//camera.rotateCameraAround(yOffset, Vector3(1.0f, 0.0f, 0.0f));
//					mouseMoved = false;
//				}
//		}
//		else {
//			if (automaticRotating) {
//				camera.rotateCameraAroundQuaternion(1, Vector3(0.0f, 1.0f, 0.0f));
//			}
//			else
//				if (mouseMoved) {
//					camera.rotateCameraAroundQuaternion(xOffset, Vector3(0.0f, 1.0f, 0.0f));
//					//camera.rotateCameraAroundQuaternion(yOffset, Vector3(1.0f, 0.0f, 0.0f));
//					mouseMoved = false;
//				}
//		}
//	}
//	// Get the updated view matrix
//	Matrix4 viewM = camera.getViewMatrix();
//	viewM.getRowMajor(view);
//	cameraReset = false;
//	*/
//
//	
//	// ARCBALL CAMERA //
//
//	if (forwardKeyPressed) {
//		arcBall.incrementRadius(-0.05f);
//	}
//	if (backwardKeyPressed) {
//		arcBall.incrementRadius(0.05f);
//	}
//
//	if (!stopRotating) {
//		if (!quaternionRotation) {
//			//std::cout << "EULER ROTATION \n";
//			if (keyRotationX) {
//				if (downMoved) {
//					arcBall.rotateCameraAroundVertical(-1);
//				}
//				else if (upMoved) {
//					arcBall.rotateCameraAroundVertical(1);
//				}
//			}
//			else if (keyRotationY) {
//				if (downMoved) {
//					arcBall.rotateCameraAroundHorizontal(-1);
//				}
//				else if (upMoved) {
//					arcBall.rotateCameraAroundHorizontal(1);
//				}
//			}
//			else if (keyRotationZ) {
//				if (downMoved) {
//					arcBall.rotateCameraAroundZ(-1);
//				}
//				else if (upMoved) {
//					arcBall.rotateCameraAroundZ(1);
//				}
//			}
//			else if (mouseRotating)
//				if (mouseMoved) {
//					arcBall.rotateCameraAroundHorizontal(xOffset);
//					arcBall.rotateCameraAroundVertical(yOffset);
//					mouseMoved = false;
//				}
//		}
//
//		else {
//			//std::cout << "QUATERNION ROTATION \n";
//			if (keyRotationX) {
//				if (downMoved) {
//					arcBall.rotateCameraAroundQuaternionVertical(-1);
//				}
//				else if (upMoved) {
//					arcBall.rotateCameraAroundQuaternionVertical(1);
//				}
//			}
//			else if (keyRotationY) {
//				if (downMoved) {
//					arcBall.rotateCameraAroundQuaternionHorizontal(-1);
//				}
//				else if (upMoved) {
//					arcBall.rotateCameraAroundQuaternionHorizontal(1);
//				}
//			}
//			else if (keyRotationZ) {
//				if (downMoved) {
//					arcBall.rotateCameraAroundQuaternionZ(-1);
//				}
//				else if (upMoved) {
//					arcBall.rotateCameraAroundQuaternionZ(1);
//				}
//			}
//			else if (mouseRotating)
//				if (mouseMoved) {
//					arcBall.rotateCameraAroundQuaternionHorizontal(xOffset);
//					arcBall.rotateCameraAroundQuaternionVertical(yOffset);
//					mouseMoved = false;
//				}
//		
//	}
//
//	///////////////////////////////////////////////////////////////////////
//	// Get the updated view matrix
//	Matrix4 viewM = arcBall.getViewMatrix();
//	viewM.getRowMajor(view);
//	cameraReset = false;
//	}
//}
//
//void set_view_proj() {
//	Matrix4 viewM = arcBall.getViewMatrix();
//	//Matrix4 viewM = camera.getViewMatrix();
//	viewM.getColMajor(view);
//
//	Matrix4 projM;
//	if (ortho) {
//		projM = arcBall.getOrthProj();
//		//projM = camera.getOrthProj();
//	}
//	else {
//		projM = arcBall.getPerspProj();
//		//projM = camera.getPerspProj();
//	}
//	projM.getRowMajor(proj);
//}
//
//void setupCamera() {
//	// CAMERA SETUP //
//	arcBall.setOrthoProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
//	arcBall.setPrespProjectionMatrix(30, ((GLfloat)window_width / (GLfloat)window_height), 1.0f, 10.0f);
//	//camera.setOrthoProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
//	//camera.setPrespProjectionMatrix(30, ((GLfloat)window_width / (GLfloat)window_height), 1.0f, 10.0f);
//
//	//Set initial cursor position to be the middle of the screen
//	cursorX = (float)window_width / 2;
//	cursorY = (float)window_height / 2;
//}
//
//void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
//{
//	// Key Presses
//	if (action == GLFW_PRESS) {
//		switch (key) {
//		case GLFW_KEY_P:
//			ortho = !ortho;
//			projChanged = true;
//			break;
//		case GLFW_KEY_X:
//			keyRotationX = true;
//			keyRotationY = false;
//			keyRotationZ = false;
//			mouseRotating = false;
//			break;
//		case GLFW_KEY_Y:
//			keyRotationX = false;
//			keyRotationY = true;
//			keyRotationZ = false;
//			mouseRotating = false;
//			break;
//		case GLFW_KEY_Z:
//			keyRotationX = false;
//			keyRotationY = false;
//			keyRotationZ = true;
//			mouseRotating = false;
//			break;
//		case GLFW_KEY_M:
//			keyRotationX = false;
//			keyRotationY = false;
//			keyRotationZ = false;
//			mouseRotating = true;
//			break;
//		case GLFW_KEY_ESCAPE:
//			glfwSetWindowShouldClose(win, GLFW_TRUE);
//			break;
//		case GLFW_KEY_W:
//			forwardKeyPressed = true;
//			break;
//		case GLFW_KEY_S:
//			backwardKeyPressed = true;
//			break;
//		case GLFW_KEY_R:
//			//camera.resetCamera();
//			arcBall.resetCamera();
//			cameraReset = true;
//			break;
//		case GLFW_KEY_G:
//			quaternionRotation = !quaternionRotation;
//			break;
//		case GLFW_KEY_F:
//			lockMouse = !lockMouse;
//			if (lockMouse) {
//				firstMouse = true;
//			}
//			break;
//		case GLFW_KEY_SPACE:
//			stopRotating = !stopRotating;
//			break;
//		case GLFW_KEY_UP:
//			upMoved = true;
//			break;
//		case GLFW_KEY_DOWN:
//			downMoved = true;
//			break;
//
//		}
//	}
//	else if (action == GLFW_RELEASE) {
//		switch (key) {
//		case GLFW_KEY_W:
//			forwardKeyPressed = false;
//			break;
//		case GLFW_KEY_S:
//			backwardKeyPressed = false;
//			break;
//		case GLFW_KEY_UP:
//			upMoved = false;
//			break;
//		case GLFW_KEY_DOWN:
//			downMoved = false;
//			break;
//		}
//	}
//}
//
//void mouse_callback(GLFWwindow* win, double xPos, double yPos) {
//	/*
//		1. Calculate the mouse's offset since the last frame.
//		2. Add the offset values to the camera's yaw and pitch values.
//		3. Add some constraints to the minimum/maximum pitch values.
//		4. Calculate the direction vector.
//	*/
//
//	if (firstMouse) // initially set to true
//	{
//		cursorX = (float)xPos;
//		cursorY = (float)yPos;
//		firstMouse = false;
//	}
//
//	xOffset = (float)xPos - cursorX;
//	yOffset = cursorY - (float)yPos; // reversed since y-coordinates range from bottom to top
//
//	cursorX = (float)xPos;
//	cursorY = (float)yPos;
//
//	mouseMoved = true;
//}
//
//void setupCallbacks(GLFWwindow* win)
//{
//	glfwSetKeyCallback(win, key_callback);
//	glfwSetCursorPosCallback(win, mouse_callback);
//}
//
/////////////////////////////////////////////////////////////////////// CALLBACKS
//
//void window_close_callback(GLFWwindow* win)
//{
//	obj_loader.destroyShaderProgram();
//	obj_loader.destroyBufferObjects();
//}
//
//void window_size_callback(GLFWwindow* win, int winx, int winy)
//{
//	window_width = winx;
//	window_height = winy;
//	glViewport(0, 0, winx, winy);
//	// Change projection matrices to maintain aspect ratio
//}
//
/////////////////////////////////////////////////////////////////////////// SETUP
//
//void glfw_error_callback(int error, const char* description)
//{
//	std::cerr << "GLFW Error: " << description << std::endl;
//}
//
//GLFWwindow* setupWindow(int winx, int winy, const char* title,
//	int is_fullscreen, int is_vsync)
//{
//	window_width = winx;
//	window_height = winy;
//	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
//	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
//	if (!win)
//	{
//		glfwTerminate();
//		exit(EXIT_FAILURE);
//	}
//	glfwMakeContextCurrent(win);
//	glfwSwapInterval(is_vsync);
//	return win;
//}
//
//GLFWwindow* setupGLFW(int gl_major, int gl_minor,
//	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
//{
//	glfwSetErrorCallback(glfw_error_callback);
//	if (!glfwInit())
//	{
//		exit(EXIT_FAILURE);
//	}
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
//
//	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
//
//#if _DEBUG
//	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
//#endif
//	return win;
//}
//
//void setupGLEW()
//{
//	glewExperimental = GL_TRUE;
//	// Allow extension entry points to be loaded even if the extension isn't 
//	// present in the driver's extensions string.
//	GLenum result = glewInit();
//	if (result != GLEW_OK)
//	{
//		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	GLenum err_code = glGetError();
//	// You might get GL_INVALID_ENUM when loading GLEW.
//}
//
//void checkOpenGLInfo()
//{
//	const GLubyte* renderer = glGetString(GL_RENDERER);
//	const GLubyte* vendor = glGetString(GL_VENDOR);
//	const GLubyte* version = glGetString(GL_VERSION);
//	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
//	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
//	std::cerr << "OpenGL version " << version << std::endl;
//	std::cerr << "GLSL version " << glslVersion << std::endl;
//}
//
//void setupOpenGL(int winx, int winy)
//{
//#if _DEBUG
//	checkOpenGLInfo();
//#endif
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);
//	glDepthMask(GL_TRUE);
//	glDepthRange(0.0, 1.0);
//	glClearDepth(1.0);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//	glFrontFace(GL_CCW);
//	glViewport(0, 0, winx, winy);
//}
//
//GLFWwindow* setup(int major, int minor,
//	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
//{
//	GLFWwindow* win =
//		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
//	setupGLEW();
//	setupOpenGL(winx, winy);
//
//	setupCallbacks(win);
//	setupCamera();
//
//	obj_loader.setup("resources/models/cube.obj", "resources/shaders/cube_vs.glsl", "resources/shaders/cube_fs.glsl");
//
//	return win;
//}
//
//////////////////////////////////////////////////////////////////////////// RUN
//
//void display(GLFWwindow* win, double elapsed_sec)
//{
//	GLfloat model[16];
//	Matrix4 model_M = Matrix4::identity();
//	model_M.getColMajor(model);
//	obj_loader.drawObj(model, view, proj, Vector4(1.0f, 0.0f, 0.0f, 0.0f));
//
//	model_M *= Matrix4::translation(2.2f, 0.0f, 0.0f);
//	model_M.getColMajor(model);
//	obj_loader.drawObj(model, view, proj, Vector4(0.0f, 1.0f, 0.0f, 0.0f));
//
//	model_M *= Matrix4::translation(2.2f, 0.0f, 0.0f);
//	model_M.getColMajor(model);
//	obj_loader.drawObj(model, view, proj, Vector4(0.0f, 0.0f, 1.0f, 0.0f));
//
//	model_M *= Matrix4::translation(-4.4f, 2.2f, 0.0f);
//	model_M.getColMajor(model);
//	obj_loader.drawObj(model, view, proj, Vector4(1.0f, 1.0f, 1.0f, 0.0f));
//}
//
//void run(GLFWwindow* win)
//{
//	double last_time = glfwGetTime();
//	while (!glfwWindowShouldClose(win))
//	{
//		double time = glfwGetTime();
//		double elapsed_time = time - last_time;
//		last_time = time;
//
//		move_camera();
//
//		set_view_proj();
//
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		display(win, elapsed_time);
//		glfwSwapBuffers(win);
//		glfwPollEvents();
//	}
//	glfwDestroyWindow(win);
//	glfwTerminate();
//}
//
//////////////////////////////////////////////////////////////////////////// MAIN
//
//int main(int argc, char* argv[])
//{
//	int gl_major = 4, gl_minor = 3;
//	int is_fullscreen = 0;
//	int is_vsync = 1;
//	GLFWwindow* win = setup(gl_major, gl_minor,
//		920, 920, "3D Tetrominos", is_fullscreen, is_vsync);
//	glEnable(GL_CULL_FACE);
//	glFrontFace(GL_CCW);
//
//	if (lockMouse) {
//		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Tell GLFW that it should hide the cursorand capture it.Capturing a cursor means that, once the application has focus, the mouse cursor stays within the center of the window(unless the application loses focus or quits)
//	}
//	else {
//		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//	}
//	run(win);
//	exit(EXIT_SUCCESS);
//
//}
//
/////////////////////////////////////////////////////////////////////////////////
//