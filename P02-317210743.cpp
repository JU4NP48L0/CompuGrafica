//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�
static const char* vShaderRojo = "shaders/shaderrojo.vert";
static const char* fShaderRojo = "shaders/shadercolor.frag";
static const char* vShaderAzul = "shaders/shaderazul.vert";
static const char* fShaderAzul = "shaders/shadercolor.frag";
static const char* vShaderVerde = "shaders/shaderverde.vert";
static const char* fShaderVerde = "shaders/shadercolor.frag";
static const char* vShaderCafe = "shaders/shadercafe.vert";
static const char* fShaderCafe = "shaders/shadercolor.frag";
static const char* vShaderVerdeOscuro = "shaders/shaderverdeoscuro.vert";
static const char* fShaderVerdeOscuro = "shaders/shadercolor.frag";

float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {

		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras_j[] = {	//J INDICE 0
			//X			Y			Z			R		G		B
			-0.7f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.7f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.6f,	-0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	-0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.6f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	-0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.7f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	-0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.9f,	-0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.7f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.9f,	-0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.9f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.7f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.7f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.7f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.7f,	0.6f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.8f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
								
			-0.7f,	0.6f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.8f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.8f,	0.6f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.5f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.6f,	0.6f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.6f,	0.6f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.5f,	0.7f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.5f,	0.6f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.9f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.8f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.8f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,

			-0.9f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.8f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
			-0.9f,	0.2f,		0.0f,			0.0f,	0.0f,	1.0f,
	};
	MeshColor *letrasj = new MeshColor();
	letrasj->CreateMeshColor(vertices_letras_j,252);
	meshColorList.push_back(letrasj);

	GLfloat vertices_letras_p[] = {	//P INDICE 1
		//X			Y			Z			R		G		B
		-0.4f,	0.7f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.1f,	0.7f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.4f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.4f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.1f,	0.7f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.1f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.4f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.4f,	-0.1f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	-0.1f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.3f,	-0.1f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.4f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.1f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.1f,	0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.1f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.6f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.2f,	0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.5f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f	,0.5f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.3f,	0.5f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

	};
	MeshColor* letrasp = new MeshColor();
	letrasp->CreateMeshColor(vertices_letras_p, 252);
	meshColorList.push_back(letrasp);


	GLfloat vertices_letras_g[] = {	//G INDICE 2
		//X			Y			Z			R		G		B
		0.0f,	0.7f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,	0.7f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,	0.6f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.0f,	0.7f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,	0.6f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.0f,	0.6f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.0f,	0.6f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.1f,	-0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.1f,	0.6f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.0f,	-0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.0f,	0.6f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.1f,	-0.1f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.4f,	-0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.1f,	-0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.1f,	0.0f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.1f,   0.0f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.4f,   -0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.4f,   0.0f,	    0.0f,			1.0f,	0.0f,	0.0f,

		0.4f,   0.0f,       0.0f,			1.0f,	0.0f,	0.0f,
		0.4f,   0.3f,	    0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,	0.0f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.4f,   0.3f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,   0.0f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,   0.3f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.3f,   0.3f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,   0.2f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.2f,   0.2f,		0.0f,			1.0f,	0.0f,	0.0f,

		0.2f,   0.2f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.2f,   0.3f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.3f,   0.3f,	    0.0f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* letrasg = new MeshColor();
	letrasg->CreateMeshColor(vertices_letras_g, 252);
	meshColorList.push_back(letrasg);

	GLfloat vertices_triangulorojo[] = { //INDICE 1
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.0f,			1.0f,	0.0f,	0.0f,

		-0.5f,	0.5f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.5f,   0.5f,		0.0f,			1.0f,	0.0f,	0.0f
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 36);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_trianguloverde[] = { //INDICE 2
		//X			Y			Z			R		G		B
		-0.55f,	-0.3f,		0.0f,			0.0f,	0.5f,	0.0f,
		-0.75f,	-0.3f,		0.0f,			0.0f,	0.5f,	0.0f,
		-0.75f,	0.2f,		0.0f,			0.0f,	0.5f,	0.0f,

		-0.75f,	-0.3f,		0.0f,			0.0f,	0.5f,	0.0f,
		-0.75f,	0.2f,		0.0f,			0.0f,	0.5f,	0.0f,
		-0.95f, -0.3f,		0.0f,			0.0f,	0.5f,	0.0f,



	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 36);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_trianguloazul[] = { //INDICE 3
		//X			Y			Z			R		G		B
		-0.6f,	0.5f,		0.0f,			0.0f,	0.0f,	1.0f,
		0.0f,	0.5f,		0.0f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.0f,			0.0f,	0.0f,	1.0f,

		0.0f,	0.5f,		0.0f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.5f,		0.0f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 36);
	meshColorList.push_back(trianguloazul);




	GLfloat vertices_cuadradoverde[] = { //INDICE 4
		//X			Y			Z			R		G		B
		-0.15f,	-0.2f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.15f,	-0.5f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.15f,	-0.2f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.15f,	-0.2f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.15f,	-0.5f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.15f,	-0.5f,		0.0f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_cuadradocafe[] = { //INDICE 5
		//X			Y			Z			R		G		B
		-0.65f,	-0.5f,		0.0f,			0.478f,	0.255f,	0.067f,
		-0.65f,	-0.3f,		0.0f,			0.478f,	0.255f,	0.067f,
		-0.85f,	-0.5f,		0.0f,			0.478f,	0.255f,	0.067f,
		-0.65f,	-0.3f,		0.0f,			0.478f,	0.255f,	0.067f,
		-0.85f,	-0.5f,		0.0f,			0.478f,	0.255f,	0.067f,
		-0.85f,	-0.3f,		0.0f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);

	GLfloat vertices_cuadradorojo[] = { //INDICE 6
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);


}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();//shader para usar color como parte del VAO: letras 
	shader3->CreateFromFiles(vShaderRojo, fShaderRojo);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();//shader para usar color como parte del VAO: letras 
	shader4->CreateFromFiles(vShaderAzul, fShaderAzul);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();//shader para usar color como parte del VAO: letras 
	shader5->CreateFromFiles(vShaderVerde, fShaderVerde);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();//shader para usar color como parte del VAO: letras 
	shader6->CreateFromFiles(vShaderCafe, fShaderCafe);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader();//shader para usar color como parte del VAO: letras 
	shader7->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro);
	shaderList.push_back(*shader7);

}


int main()
{
	mainWindow = Window(900, 900);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
													
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		////Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		//// //INDICE 3
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[3]->RenderMeshColor();
		////INDICE 4
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();
		////INDICE 4
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.3f, 0.6f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();
		////INDICE 4
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.3f, 0.6f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();
		////INDICE 5
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();
		////INDICE 5
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(1.5f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();
		////INDICE 2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();
		////INDICE 2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(1.5f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();
		////INDICE 1
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[1]->RenderMeshColor();


		////Letras J
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		////Letras P
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[1]->RenderMeshColor();

		////Letras G
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();


		//Creacion de la casa con shaders
		//Rectangulo Verde Puerta
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.35f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Rectangulo Verde Ventana1
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, 0.25f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Rectangulo Verde Ventana2
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, 0.25f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Rectangulo piramide azul
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.75f, -3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//Rectangulo Rojo
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Rectangulo cafe1
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f,-0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Rectangulo cafe2
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Arbol Verde 1
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.1f, -3.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//Arbol Verde 2
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.1f, -3.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();








		////Para el cubo y la pir�mide se usa el primer set de shaders con �ndice 0 en ShaderList
		//shaderList[0].useShader(); 
		//uniformModel = shaderList[0].getModelLocation();
		//uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01;
		////Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/