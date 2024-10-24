/*
Semestre 2024-1
Animaci�n:
Sesi�n 1:
Simple o b�sica:Por banderas y condicionales (m�s de 1 transforomaci�n geom�trica se ve modificada
Sesi�n 2
Compleja: Por medio de funciones y algoritmos.
Adicional.- ,Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <cstdlib> 
#include <ctime> 
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
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animaci�n
float movCocheZ;
float movCocheX;
float movOffset;
float movOffsetDado;
float rotllanta;
float rotllantaOffset;
//bool avanza;

//letrero
float movLetrero = 0.0f;
bool avanzaletrero = true;
bool avanzamotoZ = true;
bool avanzamotoX = false;
float arrancar = 0.0f;
float delayTime = 0.0f;
bool enEspera = false;

//Dado
float movDado = 0.0f;
float rotacionDado = 0.0f;

//Moto
float rotacion = 0.0f;
float rotacionmoto = 0.0f;

//GLfloat arrancar;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;


//Arco
Model Arco;
Model Letrero;

//Moto
Model Moto;
Model llanta1;
Model llanta2;

//tablero
Model Tablero;
Texture Monopoly;
Model Dado;
Texture Numeros;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci�n de calculo de normales por promedio de v�rtices 
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

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();
	srand(static_cast<unsigned int>(time(0)));

	CreateObjects();
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
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	//arco
	Arco = Model();
	Arco.LoadModel("Models/arco.obj");
	Letrero = Model();
	Letrero.LoadModel("Models/letrero.obj");

	//moto
	Moto = Model();
	Moto.LoadModel("Models/moto.obj");
	llanta1 = Model();
	llanta1.LoadModel("Models/llanta1moto.obj");
	llanta2 = Model();
	llanta2.LoadModel("Models/llanta2moto.obj");

	//tablero
	Tablero = Model();
	Tablero.LoadModel("Models/tablero.obj");
	Monopoly = Texture("Textures/Monopoly.png");
	Monopoly.LoadTextureA();
	Dado = Model();
	Dado.LoadModel("Models/decaedro.obj");
	Numeros = Texture("Textures/numeros.tga");
	Numeros.LoadTextureA();

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	movCocheZ, movCocheX = 0.0f;
	movOffset = 0.2f;
	movOffsetDado = 1.0f;
	rotllanta = 0.0f;
	rotllantaOffset = 5.0f;
	avanzaletrero = true;
	int estadoMoto = 0;


	float randomRotationX = 0.0f;
	float randomRotationY = 0.0f;
	float randomRotationZ = 0.0f;

	bool DadoRot = true;
	float tope = 0.01;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		arrancar += deltaTime;

		arrancar = glfwGetTime();
		//printf("arrancar %f \n", arrancar);

		//moto tablero
		if (mainWindow.getarrancar() == true) {

			// Movimiento hacia adelante en Z
			if (estadoMoto == 0) { //avanzar
				if (movCocheZ >= -190.0f) {
					movCocheZ -= movOffset * deltaTime * 2;
					printf("avanza Z %f \n", movCocheZ);
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					rotacionmoto = -90.0f;
					estadoMoto = 1;
				}
			}

			if (estadoMoto == 1) { // avanzar derecha
				if (movCocheX < 190.0f) {
					movCocheX += movOffset * deltaTime * 2;
					printf("avanza X %f \n", movCocheX);
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					rotacionmoto = -180.0f;
					estadoMoto = 2;
				}
			}

			if (estadoMoto == 2) { //avanzar abajo
				if (movCocheZ < 0.0f) {
					movCocheZ += movOffset * deltaTime * 2;
					printf("retrocede Z %f \n", movCocheZ);
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					rotacionmoto = -270.0f;
					estadoMoto = 3;
				}
			}

			if (estadoMoto == 3) {// avanzar izquierda
				if (movCocheX >= 0.0f) {
					movCocheX -= movOffset * deltaTime * 2;
					printf("retrocede X %f \n", movCocheX);
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					rotacionmoto = -360.0f;
					estadoMoto = 0;
				}
			}
		}


		//Dado
		int contador = mainWindow.getcontador();
		if (mainWindow.getcaer() == true && DadoRot == true && contador == 1) {
			movDado -= movOffsetDado * deltaTime;
			randomRotationX = static_cast<float>(rand() % 360);
			randomRotationY = static_cast<float>(rand() % 360);
			randomRotationZ = static_cast<float>(rand() % 360);

			if (movDado <= -52.0f) {
				movDado = -52.0f;
				DadoRot = false;
				mainWindow.setcaer(false);
			}
		}
		if (mainWindow.getcaer() == false && DadoRot == false && contador == 0) {
			movDado += movOffsetDado * deltaTime;
			if (movDado < tope) {
				movDado = 0.0f;
				DadoRot = true;
				mainWindow.setcaer(true);

				randomRotationX = 0.0f;
				randomRotationY = 0.0f;
				randomRotationZ = 0.0f;
			}
		}




		//letrero
		if (!enEspera && arrancar > 2) {
			if (avanzaletrero) {
				// Movimiento hacia abajo
				if (movLetrero > -7.0f) {
					movLetrero -= movOffset * deltaTime;  // Baja el objeto
				}
				else {
					// Cuando llega al punto m�s bajo, espera de 2 segundos
					avanzaletrero = false;
					enEspera = true;
					delayTime = now;  // Marca el tiempo de inicio de la espera
				}
			}
			else {
				// Movimiento hacia arriba
				if (movLetrero < 11.0f) {
					movLetrero += movOffset * deltaTime;  // Sube el objeto
				}
				else {
					// Cuando llega al punto m�s alto, espera de 2 segundos
					avanzaletrero = true;
					enEspera = true;
					delayTime = now;  // Marca el tiempo de inicio de la espera
				}
			}
		}
		else {
			// Fase de espera (2 segundos)
			if (now - delayTime >= 2.0f) {
				enEspera = false;  // Despu�s de 2 segundos, reanuda el movimiento
			}
		}

		// Rotaci�n del letrero cuando est� en la parte superior o inferior
		if (movLetrero >= 11.0f || movLetrero <= -7.0f) {
			rotacion += 2.0f * deltaTime;  // Rtotacion velocidad
		}


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
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		//sirve para que en tiempo de ejecuci�n (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux1(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		////Instancia del coche 
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(movCoche, 0.5f, -3.0f));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Kitt_M.RenderModel();

		////Llanta delantera izquierda
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Llanta_M.RenderModel();

		////Llanta trasera izquierda
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Llanta_M.RenderModel();

		////Llanta delantera derecha
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Llanta_M.RenderModel();

		////Llanta trasera derecha
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Llanta_M.RenderModel();

		////Heicoptero
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Blackhawk_M.RenderModel();

		// Arco
		glm::mat4 modelArco = modelaux;
		modelArco = glm::translate(modelArco, glm::vec3(-96.2f, -1.0f, 83.0f));
		modelArco = glm::rotate(modelArco, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelArco = glm::scale(modelArco, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelArco));
		Arco.RenderModel();

		// Letrero
		glm::mat4 modelLetrero = modelaux;
		modelLetrero = glm::translate(modelLetrero, glm::vec3(-96.2f, movLetrero + 8.0f, 83.0f));
		modelLetrero = glm::rotate(modelLetrero, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelLetrero = glm::scale(modelLetrero, glm::vec3(1.0f, 1.0f, 1.0f));
		if (movLetrero >= 11.0f || movLetrero <= -7.0f) {
			modelLetrero = glm::rotate(modelLetrero, glm::radians(rotacion), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotar sobre el eje X
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelLetrero));
		Letrero.RenderModel();

		// Moto
		glm::mat4 modelMoto = modelaux;
		modelMoto = glm::translate(modelMoto, glm::vec3(movCocheX - 96.2f, 1.7f, movCocheZ + 98.0f));
		modelMoto = glm::rotate(modelMoto, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelMoto = glm::scale(modelMoto, glm::vec3(5.0f, 5.0f, 5.0f));
		if (!avanzamotoX || !avanzamotoZ) {
			modelMoto = glm::rotate(modelMoto, glm::radians(rotacionmoto), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar sobre el eje X
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMoto));
		Moto.RenderModel();

		// Llanta 1 (Anclada a la moto)
		glm::mat4 llanta1Model = modelMoto;  // Usar la transformaci�n de la moto
		llanta1Model = glm::translate(llanta1Model, glm::vec3(0.0f, -0.2f, 0.85f));  // Trasladar relativo a la moto
		llanta1Model = glm::rotate(llanta1Model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));  // Rotaci�n de la rueda
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(llanta1Model));
		llanta1.RenderModel();

		// Llanta 2 (Anclada a la moto)
		glm::mat4 llanta2Model = modelMoto;  // Usar la transformaci�n de la moto
		llanta2Model = glm::translate(llanta2Model, glm::vec3(0.0f, -0.2f, -0.6f));  // Trasladar relativo a la moto
		llanta2Model = glm::rotate(llanta2Model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));  // Rotaci�n de la rueda
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(llanta2Model));
		llanta2.RenderModel();

		//Tablero
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tablero.RenderModel();

		//Dado
		glm::mat4 modelDado = modelaux1;
		modelDado = glm::translate(modelDado, glm::vec3(0.0f, movDado + 55.0f, 0.0f));
		modelDado = glm::scale(modelDado, glm::vec3(3.0f, 3.0f, 3.0f));
		if (mainWindow.getcaer() == true || movDado <= -52.0f) {
			modelDado = glm::rotate(modelDado, glm::radians(randomRotationX), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotaci�n en eje X
			modelDado = glm::rotate(modelDado, glm::radians(randomRotationY), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotaci�n en eje Y
			modelDado = glm::rotate(modelDado, glm::radians(randomRotationZ), glm::vec3(0.0f, 0.0f, 1.0f));  // Rotaci�n en eje Z
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelDado));
		Dado.RenderModel();



		////Agave �qu� sucede si lo renderizan antes del coche y el helic�ptero?
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//
		////blending: transparencia o traslucidez
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//AgaveTexture.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[3]->RenderMesh();
		//glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}


	return 0;
}