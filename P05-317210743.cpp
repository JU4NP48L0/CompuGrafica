/*
Práctica 5: Optimización y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Model Cuerpo;
Model Pata1;
Model Pata2;
Model Pata3;
Model Pata4;
Model Cabeza;
Model Mandibula;
Model llanta1;
Model llanta2;
Model llanta3;
Model llanta4;
Model cofre;
Model coche;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	Cuerpo = Model();
	Cuerpo.LoadModel("Models/Cuerpo.obj");
	Pata1 = Model();
	Pata1.LoadModel("Models/Pata1.obj");
	Pata2 = Model();
	Pata2.LoadModel("Models/Pata2.obj");
	Pata3 = Model();
	Pata3.LoadModel("Models/Pata3.obj");
	Pata4 = Model();
	Pata4.LoadModel("Models/Pata4.obj");
	Cabeza = Model();
	Cabeza.LoadModel("Models/Cabeza.obj");
	Mandibula = Model();
	Mandibula.LoadModel("Models/Mandibula.obj");

    //coche

    coche = Model();
    coche.LoadModel("Models/coche.obj");


    llanta1 = Model();
    llanta1.LoadModel("Models/llanta1.obj");

    llanta2 = Model();
    llanta2.LoadModel("Models/llanta2.obj");

    llanta3 = Model();
    llanta3.LoadModel("Models/llanta1.obj");

    llanta4 = Model();
    llanta4.LoadModel("Models/llanta2.obj");

    cofre = Model();
    cofre.LoadModel("Models/cofre.obj");



	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	glm::mat4 model(1.0);
	//glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        deltaTime += (now - lastTime) / limitFPS;
        lastTime = now;

        // Recibir eventos del usuario
        glfwPollEvents();
        camera.keyControl(mainWindow.getsKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        // Limpiar la ventana
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dibujar el Skybox
        skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformColor = shaderList[0].getColorLocation();

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

        // INICIA DIBUJO DEL PISO
        color = glm::vec3(0.5f, 0.5f, 0.5f); // Piso de color gris
        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        meshList[2]->RenderMesh();



        // INICIA DIBUJO COCHE
       // coche
       color = glm::vec3(1.0f, 1.0f, 1.0f);
       model = glm::mat4(1.0);
       model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
       model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
       model = glm::translate(model, glm::vec3(mainWindow.getcochepos(), 0.0f, 0.0f));
       glUniform3fv(uniformColor, 1, glm::value_ptr(color));
       glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
       coche.RenderModel();
       glm::mat4 modelCoche = model;



         //llanta1
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::mat4 modelllanta1 = modelCoche;
        modelllanta1 = glm::translate(modelllanta1, glm::vec3(-7.1f, 1.0f, -3.5f));
        modelllanta1 = glm::rotate(modelllanta1, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta1));
        llanta1.RenderModel();


        //llanta2
        color = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 modelllanta2 = modelCoche;
        modelllanta2 = glm::translate(modelllanta2, glm::vec3(-7.1f, 1.0f, 3.8f));
        modelllanta2 = glm::rotate(modelllanta2, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta2));
        llanta2.RenderModel();


        //llanta3
        color = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::mat4 modelllanta3 = modelCoche;
        modelllanta3 = glm::translate(modelllanta3, glm::vec3(5.5f, 1.0f, -3.5f));
        modelllanta3 = glm::rotate(modelllanta3, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta3));
        llanta3.RenderModel();


        //llanta4
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glm::mat4 modelllanta4 = modelCoche;
        modelllanta4 = glm::translate(modelllanta4, glm::vec3(5.5f, 1.0f, 3.8f));
        modelllanta4 = glm::rotate(modelllanta4, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta4));
        llanta4.RenderModel();


        //cofre
        color = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::mat4 modelcofre = modelCoche;
        modelcofre = glm::translate(modelcofre, glm::vec3(-5.0f, 4.2f, 0.0f));
        modelcofre = glm::rotate(modelcofre, glm::radians(mainWindow.getangulocofre()), glm::vec3(0.0f, 0.0f, -1.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelcofre));
        cofre.RenderModel();






        //// INICIA DIBUJO DE NUESTROS DEMÁS OBJETOS
        //// Cuerpo
        //color = glm::vec3(1.0f, 1.0f, 1.0f);
        //model = glm::mat4(1.0);
        //model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        //Cuerpo.RenderModel();
        //glm::mat4 modelCuerpo = model;

        //// Pata 1
        //color = glm::vec3(1.0f, 0.0f, 0.0f);
        //glm::mat4 modelpata1 = modelCuerpo;
        //modelpata1 = glm::translate(modelpata1, glm::vec3(1.0f, -0.4f, 0.7f));
        //modelpata1 = glm::rotate(modelpata1, glm::radians(mainWindow.getangulopata1()), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelpata1));
        //Pata1.RenderModel();

        //// Pata 2
        //color = glm::vec3(1.0f, 1.0f, 0.0f);
        //glm::mat4 modelpata2 = modelCuerpo;
        //modelpata2 = glm::translate(modelpata2, glm::vec3(1.0f, -0.4f, -0.7f));
        //modelpata2 = glm::rotate(modelpata2, glm::radians(mainWindow.getangulopata2()), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelpata2));
        //Pata2.RenderModel();

        //// Pata 3
        //color = glm::vec3(0.0f, 0.0f, 1.0f);
        //glm::mat4 modelpata3 = modelCuerpo;
        //modelpata3 = glm::translate(modelpata3, glm::vec3(-0.5f, -1.1f, 0.7f));
        //modelpata3 = glm::rotate(modelpata3, glm::radians(mainWindow.getangulopata3()), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelpata3));
        //Pata3.RenderModel();

        //// Pata 4
        //color = glm::vec3(0.0f, 1.0f, 0.0f);
        //glm::mat4 modelpata4 = modelCuerpo;
        //modelpata4 = glm::translate(modelpata4, glm::vec3(-0.5f, -1.1f, -0.7f));
        //modelpata4 = glm::rotate(modelpata4, glm::radians(mainWindow.getangulopata4()), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelpata4));
        //Pata4.RenderModel();

        //// Cabeza
        //color = glm::vec3(1.0f, 0.5f, 0.0f);
        //glm::mat4 modelcabeza = modelCuerpo;
        //modelcabeza = glm::translate(modelcabeza, glm::vec3(1.4f, 0.6f, 0.0f));
        //modelcabeza = glm::rotate(modelcabeza, glm::radians(mainWindow.getangulocabeza()), glm::vec3(0.0f, 1.0f, 0.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelcabeza));
        //Cabeza.RenderModel();

        //// Mandíbula
        //color = glm::vec3(0.0f, 1.0f, 0.0f);
        //glm::mat4 modelmandibula = modelcabeza;
        //modelmandibula = glm::translate(modelmandibula, glm::vec3(1.6f, 0.2f, 0.0f));
        //modelmandibula = glm::rotate(modelmandibula, glm::radians(mainWindow.getangulomandibula()), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        //glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelmandibula));
        //Mandibula.RenderModel();

        glUseProgram(0);
        mainWindow.swapBuffers();
    }


	return 0;
}
