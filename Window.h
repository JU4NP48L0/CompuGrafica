#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getarticulacion5() { return articulacion5; }
	GLfloat getarticulacion6() { return articulacion6; }
	GLfloat getarticulacion7() { return articulacion7; }
	GLfloat getarticulacion8() { return articulacion8; }
	GLfloat getarticulacion9() { return articulacion9; }
	GLfloat getarticulacion10() { return articulacion10; }
	GLfloat getarticulacion11() { return articulacion11; }
	GLfloat getangulocofre() { return angulocofre; }
	GLfloat getcochepos() { return cochepos; }
	GLfloat gethelicopteropos() { return helicopteropos; }
	bool getLuzLampara() { return LuzLampara; }
	bool getLuzCofre() { return LuzCofre; }
	bool getfuegoActivo() { return fuegoActivo; }
	bool gettruenoActivo() { return truenoActivo; }
	bool getgasActivo() { return gasActivo; }
	bool gethieloActivo() { return hieloActivo; }
	bool getarenaActivo() { return arenaActivo; }
	GLboolean getarrancar() { return arrancar; }
	GLint getcontador() { return contador; }
	void incrementarcontador() { contador++; }
	bool getcaer() { return caer; }
	void setcaer(bool valor) { caer = valor; }

	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat articulacion1, articulacion2, articulacion3, articulacion4, articulacion5, articulacion6, articulacion7, articulacion8, articulacion9, articulacion10, articulacion11;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat cochepos = 0.0f;
	GLfloat helicopteropos = 0.0f;
	GLfloat angulocofre = 0.0f;
	bool LuzLampara = false;
	bool LuzCofre = false;
	bool mouseFirstMoved;
	bool arrancar;
	bool caer = false;
	bool fuegoActivo = false;
	bool truenoActivo = false;
	bool gasActivo = false;
	bool hieloActivo = false;
	bool arenaActivo = false;

	GLint contador = 0;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

