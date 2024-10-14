#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;

	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	articulacion8 = 0.0f;
	articulacion9 = 0.0f;
	articulacion10 = 0.0f;
	articulacion11 = 0.0f;


	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica09:Animacion Basica, Gomez Vazquez Juan Pablo - 317210743", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

//GLboolean Window::getarrancar()
//{
//	return arrancar;
//}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0;
	}
	if (key == GLFW_KEY_F)//COCHE
	{
		theWindow->articulacion1 += 10.0;
	}

	if (key == GLFW_KEY_G)//llanta1
	{
		theWindow->articulacion2 += 10.0;
	}
	if (key == GLFW_KEY_H)//llanta1
	{
		theWindow->articulacion2 -= 10.0;
	}

	if (key == GLFW_KEY_J)//llanta2
	{
		theWindow->articulacion3 += 10.0;
	}

	if (key == GLFW_KEY_K)//llanta2
	{
		theWindow->articulacion3 -= 10.0;
	}

	if (key == GLFW_KEY_L)//llanta3
	{
		theWindow->articulacion4 += 10.0;
	}

	if (key == GLFW_KEY_Z)//llanta3
	{
		theWindow->articulacion4 -= 10.0;
	}

	if (key == GLFW_KEY_X)//llanta4
	{
		theWindow->articulacion5 += 10.0;
	}

	if (key == GLFW_KEY_C)//llanta4
	{
		theWindow->articulacion5 -= 10.0;
	}

	if (key == GLFW_KEY_V) //cofre
	{
		if (theWindow->angulocofre > 50.0)
		{
		}
		else {
			theWindow->angulocofre += 50.0f;
		}
	}

	if (key == GLFW_KEY_B) //cofre
	{
		if (theWindow->angulocofre < 10.0)
		{
		}
		else {
			theWindow->angulocofre -= 50.0f;
		}
	}

	if (key == GLFW_KEY_3) {
		theWindow->cochepos += 2.0f;
	}
	if (key == GLFW_KEY_4) {
		theWindow->cochepos -= 2.0f;
	}

	if (key == GLFW_KEY_5) {
		theWindow->helicopteropos += 2.0f;
	}
	if (key == GLFW_KEY_6) {
		theWindow->helicopteropos -= 2.0f;
	}

	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		theWindow->LuzLampara = !theWindow->LuzLampara;
	}


	if (key == GLFW_KEY_8 && action == GLFW_PRESS)
	{
		theWindow->LuzCofre = !theWindow->LuzCofre;
	}

	//Moto
	if (key == GLFW_KEY_1)
	{
		theWindow->arrancar = true;
	}

	//Dado
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		if (theWindow->contador == 0) {
		
			theWindow->contador++;
			theWindow->caer = true;
		}
		else if (theWindow->contador == 1) {

			theWindow->contador--;
			theWindow->caer = false;
		}
	}





	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
