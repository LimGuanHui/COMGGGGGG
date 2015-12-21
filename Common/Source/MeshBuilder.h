#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
    static Mesh* GenerateFace(const std::string &meshName, Color color);
	static Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlices = 36);
	static Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices = 36);
	static Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numSlices = 18, unsigned numStacks = 36);
    static Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices);
    static Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlices);
    static Mesh* MeshBuilder::GenerateUniqueFace(const std::string &meshName, Color color, unsigned numSlices);
    static Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
    static Mesh* MeshBuilder::GenerateHalfTorus(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
    static Mesh* MeshBuilder::GenerateFlatTriangle(const std::string &meshName, Color color);
    static Mesh* MeshBuilder::GeneratePrism(const std::string &meshName, Color color);
    static Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks);
};

#endif