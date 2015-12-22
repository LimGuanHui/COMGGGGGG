#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//top
	v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	//left
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	//back
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	//bottom
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	//front
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	//right
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);


	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float CircleX(float theta)
{
	return cos(Math::DegreeToRadian(theta));
}
float CircleZ(float theta)
{
	return sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		float theta = i * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	v.pos.Set(0, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		index_buffer_data.push_back(i);
		index_buffer_data.push_back(numSlices + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		float theta = i * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerRadius * CircleX(theta), 0, innerRadius * CircleZ(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		index_buffer_data.push_back(2 * i);
		index_buffer_data.push_back(2 * i + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float SphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}
float SphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}
float SphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(0, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	float anglePerStack = 180.f / numSlices;
	float anglePerSlice = 360.f / numSlices;
	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90 + stack * anglePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			v.color = color;
			v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 360.f / numSlices;

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice *anglePerSlice;
        v.pos.Set(CircleX(theta), 0, CircleZ(theta));
        v.color = color;
        v.normal.Set(CircleX(theta), 0, CircleZ(theta));
        vertex_buffer_data.push_back(v);

        v.pos.Set(CircleX(theta), 1, CircleZ(theta));
        v.color = color;
        v.normal.Set(CircleX(theta), 0, CircleZ(theta));
        vertex_buffer_data.push_back(v);
    }

    v.pos.Set(0, 0, 0);
    v.color = color;
    v.normal.Set(0, -1, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, 1, 0);
    v.color = color;
    v.normal.Set(0, 1, 0);
    vertex_buffer_data.push_back(v);

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        index_buffer_data.push_back(2 * slice);
        index_buffer_data.push_back(2 * slice + 1);
    }

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        index_buffer_data.push_back(2 * (numSlices + 1));
        index_buffer_data.push_back(2 * slice);

    }

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        index_buffer_data.push_back(2 * slice + 1);
        index_buffer_data.push_back(2 * (numSlices + 1) + 1);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlices)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 360.f / numSlices;

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice *anglePerSlice;
        v.pos.Set(CircleX(theta), -0.5f, CircleZ(theta));
        v.color = color;
        v.normal.Set(CircleX(theta), 1, CircleZ(theta));
        v.normal.Normalized();
        vertex_buffer_data.push_back(v);

        v.pos.Set(0, 0.5f, 0);
        v.color = color;
        v.normal.Set(CircleX(theta), 1, CircleZ(theta));
        v.normal.Normalized();
        vertex_buffer_data.push_back(v);
    }

    v.pos.Set(0, -0.5f, 0);
    v.color = color;
    v.normal.Set(0, -1, 0);
    vertex_buffer_data.push_back(v);


    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        index_buffer_data.push_back(2 * (numSlices + 1));
        index_buffer_data.push_back(2 * slice);
    }

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        index_buffer_data.push_back(2 * slice);
        index_buffer_data.push_back(2 * slice + 1);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}

//Mesh* MeshBuilder::GenerateUniqueFace(const std::string &meshName, Color color, unsigned numSlices)
//{
//    std::vector<Vertex> vertex_buffer_data;
//    std::vector<GLuint> index_buffer_data;
//    Vertex v;
//
//
//    float anglePerSlice = 360.f / numSlices;
//
//
//
//    Mesh *mesh = new Mesh(meshName);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
//
//
//    mesh->indexSize = index_buffer_data.size();
//    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
//
//    return mesh;
//}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color , 
    unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    /*v.pos.Set(0, 0, 0);
    v.color = color;
    vertex_buffer_data.push_back(v);*/

    float degreePerStack = Math::DegreeToRadian(360.f / numStack); 
    float degreePerSlice = Math::DegreeToRadian(360.f / numStack);
    float x1, z1; //y1 is always zero 
    float x2, y2, z2; 
    for(unsigned stack = 0; stack < numStack + 1; stack++) 
    { 
        for(unsigned slice = 0; slice < numSlice + 1; slice++) 
        { 
            z1 = outerR * cos(stack * degreePerStack); 
            x1 = outerR * sin(stack * degreePerStack); 
            z2 = (outerR + innerR * cos(slice * degreePerSlice)) * cos(stack * degreePerStack); 
            y2 = innerR * sin(slice * degreePerSlice); 
            x2 = (outerR + innerR * cos(slice * degreePerSlice)) * sin(stack * degreePerStack); 
            v.pos.Set(x2, y2, z2); 
            v.normal.Set(x2 - x1, y2, z2 - z1); 
            v.color = color;
            vertex_buffer_data.push_back(v);
        } 
    }
    for(unsigned stack = 0; stack < numStack; stack++) 
    { 
        for(unsigned slice = 0; slice < numSlice + 1; slice++) 
        { 
            index_buffer_data.push_back((numSlice + 1) * stack + slice + 0); 
            index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0); 
        } 
    } 

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}

Mesh* MeshBuilder::GenerateFace(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    //v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //top segment
    v.pos.Set(1.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    //northwest curve
    v.pos.Set(-1.f, 2.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    
    v.pos.Set(-0.85f, 1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);



    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.f, 1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, 0.85f, 0.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    


    v.pos.Set(-1.8f, 0.85f, 0.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //left segment
    v.pos.Set(-2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, -1.f, 0.f); v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    //southwest curve
    v.pos.Set(-2.f, -1.f, 0.f); v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    
    v.pos.Set(-1.5f, -0.8f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.5f, -0.8f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.2f, -0.85f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.2f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.85f, -1.2f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.85f, -1.2f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-0.8f, -1.5f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    
    v.pos.Set(-0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);



    //bottom segment
    v.pos.Set(-1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    //southeast curve
    v.pos.Set(1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.85f, -1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, -0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.2f, -0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.2f, -0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //right segment
    v.pos.Set(2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //northeast curve
    v.pos.Set(2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, 0.85f, 0.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    
    v.pos.Set(1.8f, 0.85f, 0.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    
    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    
    v.pos.Set(1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 1.f, 0.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    
    v.pos.Set(1.f, 1.f, 0.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    
    v.pos.Set(0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, 0.f);   v.color = color;     v.normal.Set(0, 0, 1);  	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    
    v.pos.Set(0.85f, 1.8f, 0.f);   v.color = color;     v.normal.Set(0, 0, 1);  	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);




    //3d
    //top segment
    v.pos.Set(1.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.f, 2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.f, 3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.f, 3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, -1.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.f, 3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, -1.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //northwest curve
    v.pos.Set(-1.f, 2.f, -1.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 2.f, -1.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    
    v.pos.Set(-0.85f, 1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.85f, 1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, 1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-1.f, 1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, 0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(-1.2f, 0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, 0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.5f, 0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, 0.85f, 0.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, 0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, 0.85f, -1.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, 0.85f, 0.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.8f, 0.85f, -1.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, 0.85f, 0.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, 0.85f, -1.f);     v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    //left segment
    v.pos.Set(-2.f, 1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, 1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-3.f, 0.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-3.f, 0.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-3.f, 0.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, -1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //southwest curve
    v.pos.Set(-2.f, -1.f, -1.f); v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, -1.f, 0.f); v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-2.f, -1.f, -1.f); v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, -0.85f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.8f, -0.85f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.8f, -0.85f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.5f, -0.8f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.5f, -0.8f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.2f, -0.85f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.2f, -0.85f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-1.f, -1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.2f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.2f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.2f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.85f, -1.2f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.2f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.2f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.8f, -1.5f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, 0.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.8f, -1.5f, -1.f);	  v.color = color;	  v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.85f, -1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.85f, -1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    //bottom segment
    v.pos.Set(-1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.f, -3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -3.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, -3.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //southeast curve
    v.pos.Set(1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.85f, -1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.8f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.8f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.8f, -1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, -1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.85f, -1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, -1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.f, -1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, -0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -1.f, 0.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, -1.f, -1.f);       v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, -0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, -0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.2f, -0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, -0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, -0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.5f, -0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, -0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, -0.85f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.8f, -0.85f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, -0.85f, 0.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, -0.85f, -1.f);    v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, -1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);



    //right segment
    v.pos.Set(2.f, -1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, -1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, -1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(3.f, 0.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(3.f, 0.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(3.f, 0.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(3.f, 0.f, -2.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    //northeast curve
    v.pos.Set(2.f, 1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, 0.85f, 0.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(2.f, 1.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, 0.85f, -1.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, 0.85f, 0.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.8f, 0.85f, -1.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, 0.85f, 0.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.8f, 0.85f, -1.f);   v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, 0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.5f, 0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, 0.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.5f, 0.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.2f, 0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 1.f, 0.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.2f, 0.85f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 1.f, -1.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 1.f, 0.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(1.f, 1.f, -1.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 1.f, 0.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 1.f, -1.f);      v.color = color;    v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.85f, 1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.2f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.2f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, 0.f);   v.color = color;     v.normal.Set(0, 0, 1);  	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.8f, 1.5f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);


    v.pos.Set(0.85f, 1.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, 0.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.85f, 1.8f, -1.f);	 v.color = color;	 v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 2.f, -1.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(1.f, 2.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);



    for (unsigned i = 0; i < vertex_buffer_data.size(); ++i)
    {
        index_buffer_data.push_back(i);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}


Mesh* MeshBuilder::GenerateFlatTriangle(const std::string &meshName, Color color)
{

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;


    //top segment
    v.pos.Set(1.f, 0.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 1.f, 0.f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-1.f, 0.f, 0.f);  v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    


    for (unsigned i = 0; i < 54; ++i)
    {
        index_buffer_data.push_back(i);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}

Mesh* MeshBuilder::GeneratePrism(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    //4 sides
    v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.5f, 0.f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.5f, 0.f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.5f, 0.f, -0.5f); v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.5f, 0.f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.5f, 0.f, -0.5f); v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.f, 0.5f, 0.f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

    //botttom part
    v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);

    v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);

    for (size_t num = 0; num < vertex_buffer_data.size(); ++num)
    {
        index_buffer_data.push_back(num);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}


Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerStack = 180.f / numStacks;
    float anglePerSlice = 180.f / numSlices;
    for (unsigned stack = 0; stack < numStacks + 1; ++stack)
    {
        float phi = -90.f + stack * anglePerStack;
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            float theta = slice *anglePerSlice;
            v.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            v.color = color;
            v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            v.normal.Normalize();
            vertex_buffer_data.push_back(v);
        }
    }

    for (unsigned stack = 0; stack < numStacks; ++stack)
    {
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
        }
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}