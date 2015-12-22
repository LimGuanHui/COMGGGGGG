#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	//glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.f;

	//Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	//variable to rotate geometry
    turn = 0;
    lighton = true;
    camlight = 1;
	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
    
    meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("quad", Color(0.f, 1.f, 0.498f));
    
    meshList[GEO_BODY] = MeshBuilder::GenerateSphere("body", Color(1.000f, 0.843f, 0.000f), 40, 80);
    meshList[GEO_BODY]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
    meshList[GEO_BODY]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
    meshList[GEO_BODY]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
    meshList[GEO_BODY]->material.kShininess = 1.f;

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36);
    
    meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 1, 1),36);
    
    meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 1, 1), 55); 
    
    meshList[GEO_LEGJOINT] = MeshBuilder::GenerateCylinder("legjoint", Color(1.000f, 0.843f, 0.000f), 36);
    
    meshList[GEO_LEG] = MeshBuilder::GenerateCone("leg", Color(1.000f, 0.647f, 0.000f), 55);
    
    meshList[GEO_HORNJOINT] = MeshBuilder::GenerateCylinder("hornjoint", Color(1.000f, 0.843f, 0.000f), 36);
    
    meshList[GEO_HORN] = MeshBuilder::GenerateCone("horn", Color(1.000f, 0.647f, 0.000f), 55);
    
    meshList[GEO_WINGJOINT] = MeshBuilder::GenerateCylinder("wingjoint", Color(1.000f, 0.843f, 0.000f), 36);
    
    meshList[GEO_WING] = MeshBuilder::GenerateSphere("wing", Color(1.000f, 0.843f, 0.000f), 40, 80);
    
    meshList[GEO_TAIL] = MeshBuilder::GenerateCylinder("tail", Color(1.000f, 0.843f, 0.000f), 48);
    
    meshList[GEO_TAILTIP] = MeshBuilder::GenerateSphere("tailtip", Color(1.000f, 0.843f, 0.000f), 40,80);
    
    meshList[GEO_TREETRUNK] = MeshBuilder::GenerateCone("treetrunk", Color(0.627f, 0.322f, 0.176f), 55);
    
    meshList[GEO_TREELEAF] = MeshBuilder::GenerateCone("treetrunk", Color(0.133f, 0.545f, 0.133f), 55);

    meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("toorus", Color(0.133f, 0.545f, 0.133f), 360, 360, 36, 20 );

    meshList[GEO_FACE] = MeshBuilder::GenerateFace("face", Color(0.969f, 0.953f, 0.522f));

    meshList[GEO_FILLFACE] = MeshBuilder::GenerateQuad("fillface", Color(1.000f, 0.843f, 0.000f));

    meshList[GEO_FILLTRI] = MeshBuilder::GenerateFlatTriangle("flatfilltriangle", Color(1.000f, 0.843f, 0.000f));

    meshList[GEO_HEMI] = MeshBuilder::GenerateHemisphere("hemi", Color(1.000f, 0.843f, 0.000f), 40, 80);

    meshList[GEO_TAILPOINT] = MeshBuilder::GenerateCone("cone", Color(1.000f, 0.843f, 0.000f), 55);


	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
static float LSPEED = 10.f;

void Assignment2::Update(double dt)
{
	camera.Update(dt);

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('I'))
	{
		light[0].position.z -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('K'))
	{
		light[0].position.z += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('J'))
	{
		light[0].position.x -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('L'))
	{
		light[0].position.x += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('O'))
	{
		light[0].position.y -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('P'))
	{
		light[0].position.y += (float)(LSPEED * dt);
	}
    if (Application::IsKeyPressed('Q'))
    {
        lighton = false;
    }
    if (Application::IsKeyPressed('E'))
    {
        lighton = true;
    }
    if (Application::IsKeyPressed('Z'))
    {
        camlight = 0.f;
    }
    if (Application::IsKeyPressed('X'))
    {
        camlight = 1.f;
    }


    turn += (float)(2 * dt);
}

void Assignment2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && lighton)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void Assignment2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	modelStack.LoadIdentity();

    Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
    glUniform3fv(m_parameters[U_LIGHT0_POSITION], 0, &lightPosition_cameraspace.x);
    


	RenderMesh(meshList[GEO_AXES], false);


	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y + 4, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();   // floor
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix(); // pop floor

    //modelStack.PushMatrix(); // face
    //modelStack.Rotate(0, 0, 1, 0);
    //modelStack.Translate(0, 0, 1);
    //modelStack.Scale(7, 7, 7);
    //RenderMesh(meshList[GEO_FACE], true);
    //modelStack.PopMatrix();
    

    //modelStack.PushMatrix();   // fillface
    //modelStack.Translate(0, 0, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Scale(2, 2, 2);
    //RenderMesh(meshList[GEO_FILLFACE], true);
    //modelStack.PopMatrix(); // pop fillface

    //modelStack.PushMatrix();   // fillface1
    //modelStack.Translate(1.5, 0, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Scale(1, 1, 1);
    //RenderMesh(meshList[GEO_FILLFACE], true);
    //modelStack.PopMatrix(); // pop fillface1

    //modelStack.PushMatrix();   // fillface2
    //modelStack.Translate(-1.5, 0, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Scale(1, 1, 1);
    //RenderMesh(meshList[GEO_FILLFACE], true);
    //modelStack.PopMatrix(); // pop fillface2

    //modelStack.PushMatrix();   // fillface3
    //modelStack.Translate(0, 1.5, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Scale(1, 1, 1);
    //RenderMesh(meshList[GEO_FILLFACE], true);
    //modelStack.PopMatrix(); // pop fillface3

    //modelStack.PushMatrix();   // fillface4
    //modelStack.Translate(0, -1.5, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Scale(1, 1, 1);
    //RenderMesh(meshList[GEO_FILLFACE], true);
    //modelStack.PopMatrix(); // pop fillface4

    //modelStack.PushMatrix();   // filltri1
    //modelStack.Translate(0, 1, 0);
    //modelStack.Translate(-0.23, 0, 0);
    //modelStack.Rotate(24, 0, 0, 1);
    //modelStack.Scale(1, 1, 1);
    //RenderMesh(meshList[GEO_FILLTRI], true);
    //modelStack.PopMatrix(); // pop filltri1

    //modelStack.PushMatrix();   // fillface5
    //modelStack.Translate(0, 1.9, 0);
    //modelStack.Translate(-0.3, 0, 0);
    //modelStack.Rotate(90, 0, 0, 1);
    //modelStack.Scale(0.6, 0.6, 0.6);
    //RenderMesh(meshList[GEO_FILLTRI], true);
    //modelStack.PopMatrix(); // pop fillface5


    

    //modelStack.PushMatrix();   // hemishpere
    //modelStack.Translate(0, 0, 0);
    //modelStack.Scale(7, 7, 7);
    //RenderMesh(meshList[GEO_HEMI], true);
    //modelStack.PopMatrix(); // pop hemishpere


    /**************************************************************************/                //body
    modelStack.PushMatrix(); // body
    modelStack.Rotate(45, 0, 1, 0);
    modelStack.Translate(0, 10, 0);
    modelStack.Scale(7, 7, 7);
    RenderMesh(meshList[GEO_BODY], true);

    /**************************************************************************/                //face
    modelStack.PushMatrix(); // face
    modelStack.Rotate(45, 0, 1, 0);
    modelStack.Translate(0, 0, 1);
    modelStack.Scale(0.3, 0.3, 0.3);
    RenderMesh(meshList[GEO_FACE], true);
    modelStack.PopMatrix(); 

    /**************************************************************************/                // pop face

    /**************************************************************************/                //legjoint1
    modelStack.PushMatrix();   // legjoint1
    modelStack.Rotate(130, 1, 0, 0);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    modelStack.PopMatrix();
    /**************************************************************************/                //leg1

    modelStack.PushMatrix();   // leg1
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 0.4, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix(); // pop leg1
    /**************************************************************************/                //leg1

    modelStack.PopMatrix(); // pop legjoint1
    /**************************************************************************/                //legjoint2

    modelStack.PushMatrix();   // legjoint2
    modelStack.Rotate(-130, 1, 0, 45);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    modelStack.PopMatrix();
    /**************************************************************************/                //leg2

    modelStack.PushMatrix();   // leg2
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 0.4f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix(); // pop leg2

    modelStack.PopMatrix(); // pop legjoint2

    /**************************************************************************/                //legjoint3

    modelStack.PushMatrix();   // legjoint3
    modelStack.Rotate(-130, 1, 0, -45);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    modelStack.PopMatrix();
    /**************************************************************************/                //leg3

    modelStack.PushMatrix();   // leg3
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 0.4f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix(); // pop leg3

    modelStack.PopMatrix(); // pop legjoint3


    modelStack.PushMatrix();   // legjoint4
    modelStack.Rotate(-130, 1, 0, 0);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leg4
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 0.4f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix(); // pop leg4

    modelStack.PopMatrix(); // pop legjoint4


    modelStack.PushMatrix();   // hornjoint1
    modelStack.Rotate(50, 1, 0, 0);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_LEGJOINT], true);

    modelStack.PushMatrix();   // horn1
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 2.2f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.8f, 2.4f, 0.8f);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix(); // pop horn1

    modelStack.PopMatrix(); // pop hornjoint1


    modelStack.PushMatrix();   // hornjoint2
    modelStack.Rotate(50, 1, 0, -90);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // horn2
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 0.4f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.23f, 0.53f, 0.23f);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix(); // pop horn2

    modelStack.PopMatrix(); // pop hornjoint2

    /**************************************************************************/                //left wing



    modelStack.PushMatrix();   // wingjoint1
    modelStack.Rotate(-50, 1, 0, 0);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_WINGJOINT], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // rotatejoint wingjoin && left wing
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Translate(0, 0.1, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25, 0.25, 0.25);
    //RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // leftwing
    //modelStack.Translate(0, 4.3, 0);
    modelStack.Rotate(-45, 1, 0, 0);
    modelStack.Rotate(50, 1, 1, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwingfeather
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.4, 0.45, -0.2);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

   
    
    modelStack.PopMatrix(); // pop leftwingfeather
    

    modelStack.PushMatrix();   // leftwing2
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();
    

    modelStack.PushMatrix();   // leftwing3
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing4
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing5
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing6
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing7
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing8
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing9
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing10
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // end
    modelStack.Translate(0, 0.4f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.22f, 0.22f, 0.22f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // leftwingfeather10
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(1.1f, 0.45, -0.55);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.3f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing10
    modelStack.PopMatrix(); // pop leftwingfeather10


    modelStack.PushMatrix();   // leftwingfeather9
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(1.f, 0.45, -0.5);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.2f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing9
    modelStack.PopMatrix(); // pop leftwingfeather9


    modelStack.PushMatrix();   // leftwingfeather8
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.9f, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.1f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing8
    modelStack.PopMatrix(); // pop leftwingfeather8


    modelStack.PushMatrix();   // leftwingfeather7
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.8f, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing7
    modelStack.PopMatrix(); // pop leftwingfeather7


    modelStack.PushMatrix();   // leftwingfeather6
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.75, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.95f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing6
    modelStack.PopMatrix(); // pop leftwingfeather6


    modelStack.PushMatrix();   // leftwingfeather5
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.75, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.9f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing5
    modelStack.PopMatrix(); // pop leftwingfeather5


    modelStack.PushMatrix();   // leftwingfeather4
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.6, 0.45, -0.3);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.8f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing4
    modelStack.PopMatrix(); // pop leftwingfeather4


    modelStack.PushMatrix();   // leftwingfeather3
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.6, 0.45, -0.3);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.7f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing3
    modelStack.PopMatrix(); // pop leftwingfeather3


    modelStack.PushMatrix();   // leftwingfeather2
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.4, 0.45, -0.2);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.6f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();


    modelStack.PopMatrix(); // pop leftwingfeather2


    modelStack.PopMatrix(); // pop leftwing2 

    modelStack.PopMatrix(); // pop leftwing

    modelStack.PopMatrix(); // pop rotate joint

    modelStack.PopMatrix(); // pop wingjoint1
    /**************************************************************************/                //left wing


    /**************************************************************************/                //right wing

    modelStack.PushMatrix();   // wingjoint2
    modelStack.Rotate(-50, 1, 0, -90);
    modelStack.Rotate(20, 0, 1, 0);
    modelStack.Translate(0, 0.8f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    RenderMesh(meshList[GEO_WINGJOINT], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // rotatejoint wingjoin && left wing
    modelStack.Rotate(145, 0, 1, 0);

    modelStack.Translate(0, 0.1, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.25, 0.25, 0.25);
    //RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // leftwing
    //modelStack.Translate(0, 4.3, 0);
    modelStack.Rotate(-45, 1, 0, 0);
    modelStack.Rotate(50, 1, 1, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwingfeather
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.4, 0.45, -0.2);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();



    modelStack.PopMatrix(); // pop leftwingfeather


    modelStack.PushMatrix();   // leftwing2
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // leftwing3
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing4
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing5
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing6
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing7
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing8
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing9
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // leftwing10
    modelStack.Translate(0, 0.15f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.5f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();   // end
    modelStack.Translate(0, 0.4f, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.22f, 0.22f, 0.22f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix();


    modelStack.PushMatrix();   // leftwingfeather10
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(1.1f, 0.45, -0.55);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.3f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing10
    modelStack.PopMatrix(); // pop leftwingfeather10


    modelStack.PushMatrix();   // leftwingfeather9
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(1.f, 0.45, -0.5);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.2f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing9
    modelStack.PopMatrix(); // pop leftwingfeather9


    modelStack.PushMatrix();   // leftwingfeather8
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.9f, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.1f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing8
    modelStack.PopMatrix(); // pop leftwingfeather8


    modelStack.PushMatrix();   // leftwingfeather7
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.8f, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 1.f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing7
    modelStack.PopMatrix(); // pop leftwingfeather7


    modelStack.PushMatrix();   // leftwingfeather6
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.75, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.95f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing6
    modelStack.PopMatrix(); // pop leftwingfeather6


    modelStack.PushMatrix();   // leftwingfeather5
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.75, 0.45, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.9f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing5
    modelStack.PopMatrix(); // pop leftwingfeather5


    modelStack.PushMatrix();   // leftwingfeather4
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.6, 0.45, -0.3);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.8f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing4
    modelStack.PopMatrix(); // pop leftwingfeather4


    modelStack.PushMatrix();   // leftwingfeather3
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.6, 0.45, -0.3);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.7f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();

    modelStack.PopMatrix(); // pop leftwing3
    modelStack.PopMatrix(); // pop leftwingfeather3


    modelStack.PushMatrix();   // leftwingfeather2
    //modelStack.Rotate(90, 1, 0, 0);
    modelStack.Translate(0.4, 0.45, -0.2);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.PushMatrix();
    modelStack.Scale(0.2f, 0.6f, 0.2f);
    RenderMesh(meshList[GEO_WING], true);
    modelStack.PopMatrix();


    modelStack.PopMatrix(); // pop leftwingfeather2


    modelStack.PopMatrix(); // pop leftwing2 

    modelStack.PopMatrix(); // pop leftwing

    modelStack.PopMatrix(); // pop rotate joint

    modelStack.PopMatrix(); // pop wing joint

    /**************************************************************************/                //right wing


    modelStack.PushMatrix();   // tail
    modelStack.Rotate(-45, 0, 1, 0);
    modelStack.Translate(-0.9, 0, 0);
    modelStack.Rotate(25, 0, 0, 1);
    modelStack.Scale(0.08f, 0.08f, 0.08f);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup1
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup2
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup3
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup4
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup5
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup6
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup7
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup8
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup9
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup10
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup11
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup12
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup13
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup14
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup15
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup16
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup17
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup18
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup19
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup20
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup21
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup22
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup23
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup24
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup25
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup26
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup27
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup28
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup29
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup30
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup31
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup32
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup33
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup34
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup35
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup36
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup37
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup38
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup39
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup40
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tailup41
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(3, 0, 0, 1);
    modelStack.Scale(1, 1, 1);

    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail2
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);
    
    modelStack.PushMatrix();   // tai3
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail4
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail5
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail6
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail7
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail8
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail9
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail10
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail11
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail12
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail13
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail14
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail15
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail16
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail17
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail18
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail19
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail20
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail21
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail22
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail23
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail23
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail25
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail26
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail27
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail28
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail29
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail30
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail31
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail32
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail33
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail34
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail35
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail36
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail37
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail38
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail39
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail40
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail41
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail42
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail43
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail44
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail45
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail46
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail47
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail48
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail49
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail50
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail51
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail52
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail53
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail54
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail55
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail56
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail57
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail58
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail59
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail60
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail61
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail62
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail63
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail64
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail65
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail66
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail67
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail68
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail69
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail70
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail71
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail72
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail73
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail74
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail75
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail76
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail77
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail78
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail79
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail80
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail81
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);

    modelStack.PushMatrix();   // tail82
    modelStack.Translate(0, 1, 0);
    modelStack.Rotate(-2.7, 0, 0, 1);
    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tailtip
    modelStack.Translate(0, 0, 0);
    modelStack.Rotate(0, 0, 0, 1);
    modelStack.Scale(4, 8, 8);
    RenderMesh(meshList[GEO_TAILTIP], true);

    modelStack.PushMatrix();   // tailtip1
    modelStack.Translate(0, 0, 0);
    modelStack.Rotate(0, 0, 0, 1);
    modelStack.Scale(1.2, 0.6, 0.6);
    RenderMesh(meshList[GEO_TAILTIP], true);

    modelStack.PushMatrix();   // tailpoint
    modelStack.Rotate(0, 0, 0, 1);
    modelStack.Translate(0, 2, 0);
    modelStack.Scale(0.5f, 2.f, 0.8f);
    RenderMesh(meshList[GEO_TAILPOINT], true);



    modelStack.PopMatrix(); // pop tailpoint

    modelStack.PopMatrix(); // pop tailtip1



    modelStack.PopMatrix(); // pop tailtip




    modelStack.PopMatrix(); // pop tail82


    modelStack.PopMatrix(); // pop tail81


    modelStack.PopMatrix(); // pop tail80


    modelStack.PopMatrix(); // pop tail79


    modelStack.PopMatrix(); // pop tail78


    modelStack.PopMatrix(); // pop tail77


    modelStack.PopMatrix(); // pop tail76


    modelStack.PopMatrix(); // pop tail75


    modelStack.PopMatrix(); // pop tail74


    modelStack.PopMatrix(); // pop tail73


    modelStack.PopMatrix(); // pop tail72


    modelStack.PopMatrix(); // pop tail71


    modelStack.PopMatrix(); // pop tail70


    modelStack.PopMatrix(); // pop tail69


    modelStack.PopMatrix(); // pop tail68


    modelStack.PopMatrix(); // pop tail67


    modelStack.PopMatrix(); // pop tail66


    modelStack.PopMatrix(); // pop tail65


    modelStack.PopMatrix(); // pop tail64


    modelStack.PopMatrix(); // pop tail63


    modelStack.PopMatrix(); // pop tail62


    modelStack.PopMatrix(); // pop tail61


    modelStack.PopMatrix(); // pop tail60


    modelStack.PopMatrix(); // pop tail59


    modelStack.PopMatrix(); // pop tail58


    modelStack.PopMatrix(); // pop tail57


    modelStack.PopMatrix(); // pop tail56


    modelStack.PopMatrix(); // pop tail55


    modelStack.PopMatrix(); // pop tail54


    modelStack.PopMatrix(); // pop tail53


    modelStack.PopMatrix(); // pop tail52


    modelStack.PopMatrix(); // pop tail51


    modelStack.PopMatrix(); // pop tail50


    modelStack.PopMatrix(); // pop tail49


    modelStack.PopMatrix(); // pop tail48


    modelStack.PopMatrix(); // pop tail47


    modelStack.PopMatrix(); // pop tail46


    modelStack.PopMatrix(); // pop tail45


    modelStack.PopMatrix(); // pop tail44


    modelStack.PopMatrix(); // pop tail43


    modelStack.PopMatrix(); // pop tail42


    modelStack.PopMatrix(); // pop tail41


    modelStack.PopMatrix(); // pop tail40


    modelStack.PopMatrix(); // pop tail39


    modelStack.PopMatrix(); // pop tail38


    modelStack.PopMatrix(); // pop tail37


    modelStack.PopMatrix(); // pop tail36


    modelStack.PopMatrix(); // pop tail35


    modelStack.PopMatrix(); // pop tail34


    modelStack.PopMatrix(); // pop tail33


    modelStack.PopMatrix(); // pop tail32


    modelStack.PopMatrix(); // pop tail31


    modelStack.PopMatrix(); // pop tail30


    modelStack.PopMatrix(); // pop tail29


    modelStack.PopMatrix(); // pop tail28


    modelStack.PopMatrix(); // pop tail27


    modelStack.PopMatrix(); // pop tail26


    modelStack.PopMatrix(); // pop tail25


    modelStack.PopMatrix(); // pop tail24


    modelStack.PopMatrix(); // pop tail23


    modelStack.PopMatrix(); // pop tail22


    modelStack.PopMatrix(); // pop tail21


    modelStack.PopMatrix(); // pop tail20


    modelStack.PopMatrix(); // pop tail19


    modelStack.PopMatrix(); // pop tail18


    modelStack.PopMatrix(); // pop tail17


    modelStack.PopMatrix(); // pop tail16


    modelStack.PopMatrix(); // pop tail15


    modelStack.PopMatrix(); // pop tail14


    modelStack.PopMatrix(); // pop tail13


    modelStack.PopMatrix(); // pop tail12


    modelStack.PopMatrix(); // pop tail11


    modelStack.PopMatrix(); // pop tail10


    modelStack.PopMatrix(); // pop tail9


    modelStack.PopMatrix(); // pop tail8


    modelStack.PopMatrix(); // pop tail7


    modelStack.PopMatrix(); // pop tail6


    modelStack.PopMatrix(); // pop tail5


    modelStack.PopMatrix(); // pop tail4


    modelStack.PopMatrix(); // pop tail3


    modelStack.PopMatrix(); // pop tail2


    modelStack.PopMatrix(); // pop tailup1


    modelStack.PopMatrix(); // pop tailup2


    modelStack.PopMatrix(); // pop tailup3


    modelStack.PopMatrix(); // pop tailup4


    modelStack.PopMatrix(); // pop tailup5


    modelStack.PopMatrix(); // pop tailup6


    modelStack.PopMatrix(); // pop tailup7


    modelStack.PopMatrix(); // pop tailup8


    modelStack.PopMatrix(); // pop tailup9


    modelStack.PopMatrix(); // pop tailup10


    modelStack.PopMatrix(); // pop tailup11


    modelStack.PopMatrix(); // pop tailup12


    modelStack.PopMatrix(); // pop tailup13


    modelStack.PopMatrix(); // pop tailup14


    modelStack.PopMatrix(); // pop tailup15


    modelStack.PopMatrix(); // pop tailup16


    modelStack.PopMatrix(); // pop tailup17


    modelStack.PopMatrix(); // pop tailup18


    modelStack.PopMatrix(); // pop tailup19

    
    modelStack.PopMatrix(); // pop tailup20

    
    modelStack.PopMatrix(); // pop tailup21

    
    modelStack.PopMatrix(); // pop tailup22

    
    modelStack.PopMatrix(); // pop tailup23

    
    modelStack.PopMatrix(); // pop tailup24

    
    modelStack.PopMatrix(); // pop tailup25

    
    modelStack.PopMatrix(); // pop tailup26

    
    modelStack.PopMatrix(); // pop tailup27

    
    modelStack.PopMatrix(); // pop tailup28

    
    modelStack.PopMatrix(); // pop tailup29


    modelStack.PopMatrix(); // pop tailup30


    modelStack.PopMatrix(); // pop tailup31


    modelStack.PopMatrix(); // pop tailup32


    modelStack.PopMatrix(); // pop tailup33


    modelStack.PopMatrix(); // pop tailup34


    modelStack.PopMatrix(); // pop tailup35


    modelStack.PopMatrix(); // pop tailup36


    modelStack.PopMatrix(); // pop tailup37


    modelStack.PopMatrix(); // pop tailup38
    

    modelStack.PopMatrix(); // pop tailup39


    modelStack.PopMatrix(); // pop tailup40


    modelStack.PopMatrix(); // pop tailup41


    modelStack.PopMatrix(); // pop tail











    modelStack.PopMatrix(); // pop body
    /**************************************************************************/                //body



    /**************************************************************************************************************/        // environment trees
    for (int treecoord_x = -500; treecoord_x < 500; treecoord_x += 50)
    {

        modelStack.PushMatrix();   // treetrunk
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(treecoord_x, 7, 100);
        modelStack.Scale(10, 20, 10);
        RenderMesh(meshList[GEO_TREETRUNK], true);


        modelStack.PushMatrix();   // treeleaf
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 1.4, 0);
        modelStack.Scale(2.5, 2.5, 2.5);
        RenderMesh(meshList[GEO_TREELEAF], true);


        modelStack.PushMatrix();   // treeleaf1
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 0.6, 0);
        modelStack.Scale(0.8, 0.8, 0.8);
        RenderMesh(meshList[GEO_TREELEAF], true);

        modelStack.PushMatrix();   // treeleaf2
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 0.5, 0);
        modelStack.Scale(0.5, 0.5, 0.5);
        RenderMesh(meshList[GEO_TREELEAF], true);


        modelStack.PopMatrix(); // pop treeleaf2


        modelStack.PopMatrix(); // pop treeleaf1

        modelStack.PopMatrix(); // pop treeleaf

        modelStack.PopMatrix(); // pop treetrunk
    }


    for (int treecoord_x = -500; treecoord_x < 500; treecoord_x += 50)
    {

        modelStack.PushMatrix();   // treetrunk
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(treecoord_x, 7, -100);
        modelStack.Scale(10, 20, 10);
        RenderMesh(meshList[GEO_TREETRUNK], true);


        modelStack.PushMatrix();   // treeleaf
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 1, 0);
        modelStack.Scale(2, 2, 2);
        RenderMesh(meshList[GEO_TREELEAF], true);


        modelStack.PushMatrix();   // treeleaf1
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 0.5, 0);
        modelStack.Scale(0.8, 0.8, 0.8);
        RenderMesh(meshList[GEO_TREELEAF], true);

        modelStack.PushMatrix();   // treeleaf2
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 0.5, 0);
        modelStack.Scale(0.8, 0.8, 0.8);
        RenderMesh(meshList[GEO_TREELEAF], true);


        modelStack.PopMatrix(); // pop treeleaf2


        modelStack.PopMatrix(); // pop treeleaf1

        modelStack.PopMatrix(); // pop treeleaf

        modelStack.PopMatrix(); // pop treetrunk
    }
    /**************************************************************************************************************/        // environment trees

}

void Assignment2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}