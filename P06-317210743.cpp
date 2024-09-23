/*
Pr�ctica 6: Texturizado
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
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;


Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture dadoTexture;
Texture decaedroTexture;
Texture logofiTexture;

Model Kitt_M;
Model Llanta_M;
Model Dado_M;
Model Decaedro_M;
Model coche;
Model llanta1;
Model llanta2;
Model llanta3;
Model llanta4;

//COCHE EJ 3
Model coche_text;
Model cofre_text;
Model parabrisas_text;


Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_texture.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_texture.frag";




//c�lculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}



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

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);


	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.26f,  0.34f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.49f,	0.34f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.49f,	0.66f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.26f,	0.66f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.51f,  0.34f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.74f,	0.34f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.74f,	0.66f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.51f,	0.66f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	1.0f,  0.34f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.76f,	0.34f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.76f,	0.66f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	1.0f,	0.66f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.34f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.24f,	0.34f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.24f,	0.66f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.66f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.51f,  0.01f,		0.0f,	1.0f,	0.0f,//2
		0.5f,  -0.5f,  0.5f,	0.51f,	0.32f,		0.0f,	1.0f,	0.0f,//3
		 0.5f,  -0.5f,  -0.5f,	0.74f,	0.32f,		0.0f,	1.0f,	0.0f,//4
		-0.5f, -0.5f,  -0.5f,	0.74f,	0.01f,		0.0f,	1.0f,	0.0f,//1

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.51f,  0.99f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.51f,	0.67f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.74f,	0.67f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.74f,	0.99f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}


void CrearDecaedro()
{
	unsigned int decaedro_indices[] = {
		// 1 .
		0, 1, 2,

		// 2 .
		3, 4, 5,

		// 3 .
		6, 7, 8,

		// 4 .
		9, 10, 11,

		// 9 .
		12, 13, 14,

		// 10 .
		15, 16, 17,

		// 7 .
		18, 19, 20,

		// 8 .
		21, 22, 23,

		// 5 .
		24, 25, 26,

		// 6 .
		27, 28, 29,


	};

	GLfloat decaedro_vertices[] = {
		//// 1 .
		//x			y			z			S			T			NX		NY		NZ
		-1.618f,	-0.013f ,	-1.176f,    0.24f,	    0.9f,		0.0f,	0.0f,	-1.0f,	//0
		0.0f,		 1.987f,	0.0f,		0.125f,	    1.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.618f,		 -0.013f,	-1.902f,	0.0f,	    0.9f,		0.0f,	0.0f,	-1.0f,	//2

		//// 2 .
		//x			y			z			S			T			NX		NY		NZ
		-1.618f,	 -0.013f ,	-1.176f,    0.62f,	    1.0f,		0.0f,	0.0f,	-1.0f,	//3
		0.618f,		 -0.013f,	-1.902f,	0.38f,	    1.0f,		0.0f,	0.0f,	-1.0f,	//4
		0.0f,		  -2.013f,   0.0f,		0.5f,	    0.87f,		0.0f,	0.0f,	-1.0f,	//5

		//// 3 .
		//x			y			z			S			T			NX		NY		NZ
		0.618f,		 -0.013f,	 -1.902f,	1.0f,	    0.9f,		0.0f,	0.0f,	-1.0f,	//6
		0.0f,		 1.987f,	 0.0f,		0.88f,	    1.0f,		0.0f,	0.0f,	-1.0f,	//7
		2.0f,		 -0.013f,	 0.0f,		0.76f,	    0.9f,		0.0f,	0.0f,	1.0f,	//8

		//// 4 .
		//x			y			z			S			T			NX		NY		NZ
		0.618f,		-0.013f,	 -1.902f,	0.24f,	    0.64f,		0.0f,	0.0f,	-1.0f,	//9
		0.0f,		-2.013f,	  0.0f,		0.125f,	    0.54f,		1.0f,	0.0f,	0.0f,	//10
		2.0f,		 -0.013f,	 0.0f,		0.0f,	    0.64f,		0.0f,	0.0f,	1.0f,	//11

		//// 9 .
		//x			y			z			S			T			NX		NY		NZ
		-1.618f,	 -0.013f ,	-1.176f,    0.76f,	    0.23f,		0.0f,	0.0f,	-1.0f,	//12
		0.0f,		 1.987f,	0.0f,		0.88f,	    0.35f,		0.0f,	0.0f,	-1.0f,	//13
		-1.618f,	 -0.013f ,	1.176f,     1.0f,	    0.23f,		0.0f,	0.0f,	-1.0f,	//14

		//// 10 .
		//x			y			z			S			T			NX		NY		NZ
		-1.618f,	 -0.013f ,	-1.176f,    0.35f,	    0.08f,		0.0f,	0.0f,	-1.0f,	//15
		0.0f,		-2.013f,	  0.0f,		0.5f,	    0.0f,		1.0f,	0.0f,	0.0f,	//16
		-1.618f,	 -0.013f ,	1.176f,     0.65f,	    0.08f,		0.0f,	0.0f,	-1.0f,	//17

		//// 7 .
		//x			y			z			S			T			NX		NY		NZ
		-1.618f,    -0.013f ,	1.176f,    0.0f,	    0.23f,		0.0f,	0.0f,	-1.0f,	//18
		0.0f,		 1.987f,	0.0f,	   0.125f,	    0.35f,		0.0f,	0.0f,	-1.0f,	//19
		0.618f,		-0.013f ,	1.902f,    0.24f,	    0.23f,		0.0f,	0.0f,	-1.0f,	//20

		//// 8 .
		//x			y			z			S			T			NX		NY		NZ
		-1.618f,    -0.013f ,	1.176f,    0.38f,	    0.35f,		0.0f,	0.0f,	-1.0f,	//21
		0.0f,		-2.013f,	  0.0f,	   0.5f,	    0.23f,		1.0f,	0.0f,	0.0f,	//22
		0.618f,		-0.013f ,	1.902f,    0.62f,	    0.35f,		0.0f,	0.0f,	-1.0f,	//23

		//// 5 .
		//x			y			z			S			T			NX		NY		NZ
		0.618f,		-0.013f ,	1.902f,    0.38f,	    0.55f,		0.0f,	0.0f,	-1.0f,	//24
		0.0f,		 1.987f,	0.0f,	   0.5f,	    0.65f,		0.0f,	0.0f,	-1.0f,	//25
		2.0f,		 -0.013f,	 0.0f,	   0.62f,	    0.55f,		0.0f,	0.0f,	1.0f,	//26

		//// 6 .
		//x			y			z			S			T			NX		NY		NZ
		0.618f,		-0.013f ,	1.902f,    0.76f,	    0.64f,		0.0f,	0.0f,	-1.0f,	//27
		0.0f,		-2.013f,	  0.0f,	   0.88f,	    0.54f,		1.0f,	0.0f,	0.0f,	//28
		2.0f,		 -0.013f,	 0.0f,	   1.0f,	    0.64f,		0.0f,	0.0f,	1.0f,	//29


	};

	Mesh* decaedro = new Mesh();
	decaedro->CreateMesh(decaedro_vertices, decaedro_indices, 240, 30);
	meshList.push_back(decaedro);

}







int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CrearDecaedro();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado_animales.tga");
	dadoTexture.LoadTextureA();
	logofiTexture = Texture("Textures/dado_animales.obj");
	logofiTexture.LoadTextureA();
	logofiTexture = Texture("Textures/escudo_fi_color.tga");
	logofiTexture.LoadTextureA();
	decaedroTexture = Texture("Textures/numeros.tga");
	decaedroTexture.LoadTextureA();

	
	
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Dado_M = Model();
	Dado_M.LoadModel("Textures/dado_animales.obj");

	//coche
	coche = Model();
	coche.LoadModel("Models/coche.obj");

	llanta1 = Model();
	llanta1.LoadModel("Models/llanta1.obj");
	llanta2 = Model();
	llanta2.LoadModel("Models/llanta2.obj");
	llanta3 = Model();
	llanta3.LoadModel("Models/llanta3.obj");
	llanta4 = Model();
	llanta4.LoadModel("Models/llanta4.obj");

	//coche ejercicio 3
	coche_text = Model();
	coche_text.LoadModel("Models/coche_parabrisas_cofre.obj");
	
	parabrisas_text = Model();
	parabrisas_text.LoadModel("Models/parabrisas_textura.obj");

	cofre_text = Model();
	cofre_text.LoadModel("Models/cofre_textura.obj");




	
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
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		color = glm::vec3(1.0f, 1.0f, 1.0f);//color blanco, multiplica a la informaci�n de color de la textura

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();


		//Decaedro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		decaedroTexture.UseTexture();
		meshList[5]->RenderMesh();


		////Dado de Opengl
		////Ejercicio 1: Texturizar su cubo con la imagen dado_animales ya optimizada por ustedes
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//dadoTexture.UseTexture();
		//meshList[4]->RenderMesh();
		//
		////Ejercicio 2:Importar el cubo texturizado en el programa de modelado con 
		////la imagen dado_animales ya optimizada por ustedes
		//
		////Dado importado
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-3.0f, 3.0f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Dado_M.RenderModel();
		

		 // INICIA DIBUJO COCHE
	    // coche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -1.5f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(mainWindow.getcochepos(), 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		coche_text.RenderModel();
		glm::mat4 modelCoche = model;

		//llanta4
		glm::mat4 modelllanta1 = modelCoche;
		modelllanta1 = glm::translate(modelllanta1, glm::vec3(-6.5f, 1.0f, -4.2f));
		//modelllanta1 = glm::rotate(modelllanta1, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta1));
		llanta4.RenderModel();


		//llanta2
		glm::mat4 modelllanta2 = modelCoche;
		modelllanta2 = glm::translate(modelllanta2, glm::vec3(-7.0f, 1.0f, 3.4f));
		//modelllanta2 = glm::rotate(modelllanta2, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta2));
		llanta2.RenderModel();


		//llanta3
		glm::mat4 modelllanta3 = modelCoche;
		modelllanta3 = glm::translate(modelllanta3, glm::vec3(5.5f, 1.0f, -4.2f));
		//modelllanta3 = glm::rotate(modelllanta3, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta3));
		llanta3.RenderModel();


		//llanta1
		glm::mat4 modelllanta4 = modelCoche;
		modelllanta4 = glm::translate(modelllanta4, glm::vec3(5.5f, 1.0f, 3.4f));
		//modelllanta4 = glm::rotate(modelllanta4, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelllanta4));
		llanta1.RenderModel();

		//cofre
		glm::mat4 modelcofre = modelCoche;
		modelcofre = glm::translate(modelcofre, glm::vec3(-4.75f, 3.65f, -0.5f));
		//modelllanta4 = glm::rotate(modelllanta4, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelcofre));
		cofre_text.RenderModel();


		//parabrisas
		glm::mat4 modelparabrisas = modelCoche;
		modelparabrisas = glm::translate(modelparabrisas, glm::vec3(-3.1f, 4.8f, -0.3f));
		//modelllanta4 = glm::rotate(modelllanta4, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelparabrisas));
		parabrisas_text.RenderModel();

		////profe
		////Llanta trasera derecha
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Llanta_M.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
/*
//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		logofiTexture.UseTexture(); //textura con transparencia o traslucidez
		FIGURA A RENDERIZAR de OpenGL, si es modelo importado no se declara UseTexture
		glDisable(GL_BLEND);
*/