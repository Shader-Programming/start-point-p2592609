#include "WindowManager.h"
#include "Properties.h"
#include "Scene.h" 

/*
Entry point for App
Creates a window with an input handler
Creates instances of a scene
Runs game loop
*/

void main() {

	WindowManager windowMan("IMAT3906 Labs", SCR_WIDTH, SCR_HEIGHT, true);  // name, width, height, vSync,
	Scene scene(windowMan.getWindow(), windowMan.getHandler()); // pass GLFWwindow and Input Handler to scene

	while (!glfwWindowShouldClose(windowMan.getWindow())) {


		windowMan.startFrame();
		scene.update(windowMan.getDeltaTime());
		windowMan.endFrame();

	}
	windowMan.shutDown();

}

