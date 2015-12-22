#ifndef ASSIGNMENT_2_H
#define ASSIGNMENT_2_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_FLOOR,
        GEO_CYLINDER,
        GEO_CONE,
        GEO_BODY,
        GEO_LEGJOINT,
        GEO_LEG,
        GEO_HORNJOINT,
        GEO_HORN,
        GEO_WINGJOINT,
        GEO_WING,
        GEO_TAIL,
        GEO_TAILTIP,
        GEO_TREETRUNK,
        GEO_TREELEAF,
		GEO_LIGHTBALL,
        GEO_FACE,
        GEO_FILLTRI,
        GEO_HEMI,
        GEO_TAILPOINT,
        GEO_CORE,
        GEO_MASTERBALL,
        GEO_M,
        GEO_INNERBUTTON,
        GEO_OUTERBUTTON,
        GEO_OUTERBALL,
        GEO_LETTERM,
		NUM_GEOMETRY,

	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
    bool lighton;
    float camlight;

    float turn;
    float flapwing;

	Camera2 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[1];
};

#endif