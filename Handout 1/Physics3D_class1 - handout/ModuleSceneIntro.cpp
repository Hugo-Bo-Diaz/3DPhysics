#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// TODO 2: Place the camera one unit up in Y and one unit to the right
	// experiment with different camera placements, then use LookAt()
	// to make it look at the center
	vec2 offset_2d (0,1);
	vec3 offset(offset_2d,0);
	App->camera->Move(offset);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 1: Create a Plane primitive. This uses the plane formula
	// so you have to express the normal of the plane to create 
	// a plane centered around 0,0. Make that it draw the axis for reference

	Plane* plano = new Plane(0,1,0,0);
	plano->axis = true;
	plano->Render();
	// TODO 6: Draw a sphere of 0.5f radius around the center
	// Draw somewhere else a cube and a cylinder in wireframe
	Sphere* sfere = new Sphere(0.5f);
	sfere->SetPos(10.0f,0.0f,0.0f);
	sfere->Render();

	Cylinder* cilinder = new Cylinder(0.5f,3.0f);
	cilinder->SetPos(5.0f, 0.0f, 0.0f);
	cilinder->SetRotation(90.0f,vec3(0,0,1));
	cilinder->Render();

	Cube* fair_and_square = new Cube(5.0f, 10.0f, 3.0f);
	fair_and_square->SetPos(-5.0f,0.0f,0.0f);
	cilinder->SetRotation(90.0f, vec3(0, 1, 0));
	fair_and_square->Render();

	return UPDATE_CONTINUE;
}

