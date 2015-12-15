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
	glEnable(GL_CULL_FACE);

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
    
    meshList[GEO_BODY] = MeshBuilder::GenerateSphere("body", Color(0.969f, 0.953f, 0.522f), 40, 80);
	
    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36);
    
    meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 1, 1),36);
    
    meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 1, 1), 55);
    
    meshList[GEO_LEGJOINT] = MeshBuilder::GenerateCylinder("legjoint", Color(1.000f, 0.843f, 0.000f), 36);
    
    meshList[GEO_LEG] = MeshBuilder::GenerateCone("leg", Color(1.000f, 0.647f, 0.000f), 55);
    
    meshList[GEO_HORNJOINT] = MeshBuilder::GenerateCylinder("hornjoint", Color(1.000f, 0.843f, 0.000f), 36);
    
    meshList[GEO_HORN] = MeshBuilder::GenerateCone("horn", Color(1.000f, 0.647f, 0.000f), 55);
    
    meshList[GEO_WINGJOINT] = MeshBuilder::GenerateCylinder("wingjoint", Color(1.000f, 0.843f, 0.000f), 36);
    
    meshList[GEO_WING] = MeshBuilder::GenerateSphere("wing", Color(0.969f, 0.953f, 0.522f), 40, 80);
    
    meshList[GEO_TAIL] = MeshBuilder::GenerateCylinder("tail", Color(1.000f, 0.843f, 0.000f), 42);
    
    meshList[GEO_TAILTIP] = MeshBuilder::GenerateSphere("tailtip", Color(1.000f, 0.843f, 0.000f), 40,80);
    
    meshList[GEO_TREETRUNK] = MeshBuilder::GenerateCone("treetrunk", Color(0.627f, 0.322f, 0.176f), 55);
    
    meshList[GEO_TREELEAF] = MeshBuilder::GenerateCone("treetrunk", Color(0.133f, 0.545f, 0.133f), 55);



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

    /**************************************************************************/                //body
    modelStack.PushMatrix(); // body
    modelStack.Rotate(0, 0, 1, 0);
    modelStack.Translate(0, 10, 0);
    modelStack.Scale(7, 7, 7);
    RenderMesh(meshList[GEO_BODY], true);

    /**************************************************************************/                //legjoint1
    modelStack.PushMatrix();   // legjoint1
    modelStack.Rotate(130, 1, 0, 0);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    /**************************************************************************/                //leg1

    modelStack.PushMatrix();   // leg1
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(0.7f, 2, 0.7f);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix(); // pop leg1
    /**************************************************************************/                //leg1

    modelStack.PopMatrix(); // pop legjoint1
    /**************************************************************************/                //legjoint2

    modelStack.PushMatrix();   // legjoint2
    modelStack.Rotate(-130, 1, 0, 45);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    /**************************************************************************/                //leg2

    modelStack.PushMatrix();   // leg2
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(0.7f, 2, 0.7f);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix(); // pop leg2

    modelStack.PopMatrix(); // pop legjoint2

    /**************************************************************************/                //legjoint3

    modelStack.PushMatrix();   // legjoint3
    modelStack.Rotate(-130, 1, 0, -45);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_LEGJOINT], true);
    /**************************************************************************/                //leg3

    modelStack.PushMatrix();   // leg3
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(0.7f, 2, 0.7f);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix(); // pop leg3

    modelStack.PopMatrix(); // pop legjoint3


    modelStack.PushMatrix();   // legjoint4
    modelStack.Rotate(-130, 1, 0, 0);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_LEGJOINT], true);

    modelStack.PushMatrix();   // leg4
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(0.7f, 2, 0.7f);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix(); // pop leg4

    modelStack.PopMatrix(); // pop legjoint4


    modelStack.PushMatrix();   // hornjoint1
    modelStack.Rotate(50, 1, 0, 0);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_LEGJOINT], true);

    modelStack.PushMatrix();   // horn1
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(0.7f, 2, 0.7f);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix(); // pop horn1

    modelStack.PopMatrix(); // pop hornjoint1


    modelStack.PushMatrix();   // hornjoint2
    modelStack.Rotate(50, 1, 0, -90);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_LEGJOINT], true);

    modelStack.PushMatrix();   // horn2
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(0.7f, 2, 0.7f);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_LEG], true);
    modelStack.PopMatrix(); // pop horn2

    modelStack.PopMatrix(); // pop hornjoint2

    /**************************************************************************/                //left wing
    modelStack.PushMatrix();   // wingjoint1
    modelStack.Rotate(-50, 1, 0, 0);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_WINGJOINT], true);


    modelStack.PushMatrix();   // rotatejoint wingjoin && left wing
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 1, 0);

    //RenderMesh(meshList[GEO_WING], true);


    modelStack.PushMatrix();   // leftwing
    modelStack.Rotate(-45, 1, 0, 0);
    modelStack.Rotate(50, 1, 1, 0);
    modelStack.Scale(1, 5, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_WING], true);


    modelStack.PushMatrix();   // joint for leftwing1
    /*modelStack.Rotate(-45, 1, 0, 0);
    modelStack.Rotate(-30, 0, 0, 1);*/
    modelStack.Scale(0.7, 0.7, 0.7);
    modelStack.Translate(0, 4, 0);
    //RenderMesh(meshList[GEO_WING], true);

    modelStack.PushMatrix();   // leftwing1
    /*modelStack.Rotate(-45, 1, 0, 0);
    modelStack.Rotate(-30, 0, 0, 1);*/
    modelStack.Scale(1.6, 3, 1.6);
    modelStack.Translate(0, -1, 0);
    RenderMesh(meshList[GEO_WING], true);


    //modelStack.PushMatrix();   // leftwing2
    //modelStack.Rotate(45, 1, 0, 0);
    //modelStack.Scale(0.5, 2, 0.5);
    //modelStack.Translate(0, 1, 0);
    //RenderMesh(meshList[GEO_WING], true);


    //modelStack.PopMatrix(); // pop leftwing2

    modelStack.PopMatrix(); // pop joint for leftwing1

    modelStack.PopMatrix(); // pop leftwing1


    modelStack.PopMatrix(); // pop leftwing

    modelStack.PopMatrix(); // pop rotate joint

    modelStack.PopMatrix(); // pop wingjoint1
    /**************************************************************************/                //left wing


    /**************************************************************************/                //right wing

    modelStack.PushMatrix();   // wingjoint2
    modelStack.Rotate(-50, 1, 0, -90);
    modelStack.Scale(0.25f, 0.2f, 0.25f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_WINGJOINT], true);


    modelStack.PushMatrix();   // rightwing
    modelStack.Rotate(0, 1, 0, 0);
    modelStack.Scale(1, 4, 1);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_WING], true);


    modelStack.PushMatrix();   // rightwing1
    /*modelStack.Rotate(45, 1, 0, 0);
    modelStack.Rotate(30, 0, 0, 1);*/
    modelStack.Scale(1, 4, 1);
    modelStack.Translate(0, 1, 0);
    RenderMesh(meshList[GEO_WING], true);


    modelStack.PopMatrix(); // pop rightwing1

    modelStack.PopMatrix(); // pop rightwing

    modelStack.PopMatrix(); // pop wingjoint2

    /**************************************************************************/                //right wing


    modelStack.PushMatrix();   // tail
    modelStack.Rotate(-100, 1, 0, -1);
    modelStack.Scale(0.1f, 0.2f, 0.1f);
    modelStack.Translate(0, 4.2f, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail1
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail2
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail3
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail4
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail5
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix();   // tail6
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 1, 1);
    modelStack.Translate(0, 0.8, 0);
    RenderMesh(meshList[GEO_TAIL], true);


    modelStack.PushMatrix(); // tail tip
    modelStack.Rotate(4, 1, 0, 0);
    modelStack.Scale(1, 4, 1);
    modelStack.Translate(0, 0.5, 0);
    RenderMesh(meshList[GEO_TAILTIP], true);

    modelStack.PopMatrix(); // pop tail tip

    modelStack.PopMatrix(); // pop tail6


    modelStack.PopMatrix(); // pop tail5


    modelStack.PopMatrix(); // pop tail4


    modelStack.PopMatrix(); // pop tail3


    modelStack.PopMatrix(); // pop tail2


    modelStack.PopMatrix(); // pop tail1



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
        modelStack.Translate(0, 2, 0);
        modelStack.Scale(2.5, 2.5, 2.5);
        RenderMesh(meshList[GEO_TREELEAF], true);


        modelStack.PushMatrix();   // treeleaf1
        //modelStack.Rotate(0, 1, 0, 0);
        modelStack.Translate(0, 1, 0);
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