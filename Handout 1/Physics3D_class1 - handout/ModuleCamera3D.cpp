#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update()
{
	// OnKeys WASD keys -----------------------------------

	// TODO 3: Make the camera go up/down when pressing R (up) F(down)
	if (App->input->GetKey(SDL_SCANCODE_R)==KEY_REPEAT)
		App->camera->Move(vec3(0,  0.4, 0));
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
		App->camera->Move(vec3(0, -0.4, 0));

	// TODO 4: Make the camera go forward (w) and backward with (s)
	// Note that the vectors X/Y/Z contain the current axis of the camera
	// you can read them to modify Position
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		Position += -Z;
		Reference += -Z;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		Position += Z;
		Reference += -Z;
	}

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	{
		angle -= 0.1f;
		
		App->camera->Look(Position,vec3(Position.x+cos(angle),Position.y,Position.z+sin(angle)));
	}
	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
	{
		angle += 0.1f;

		App->camera->Look(Position, vec3(Position.x + cos(angle), Position.y, Position.z + sin(angle)));
	}

	// TODO 5: Make the camera go left (a) and right with (d)
	// Note that the vectors X/Y/Z contain the current axis of the camera
	// you can read them to modify Position
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		App->camera->Move(-X);
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		App->camera->Move(X);
	// Mouse motion ----------------
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		SDL_WarpMouseInWindow(App->window->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		//int dx = -App->input->GetMouseXMotion();
		//int dy = -App->input->GetMouseYMotion();
		int dx = -App->input->GetMouseX() + SCREEN_WIDTH/2;
		int dy = -App->input->GetMouseY() + SCREEN_HEIGHT/2;
		angle -= dx * 3.14/180;
		if (angle > 2*3.14)
		{
			angle -= 2 * 3.14;
		}
		if (angle < 0)
		{
			angle += 2 * 3.14;
		}
		angle_y += dy* 3.14 / 180;
		
		App->camera->Look(Position, vec3(Position.x + cos(angle), Position.y+sin(angle_y), Position.z + sin(angle)),true);
		LOG("%f %f",angle,angle_y);
		SDL_WarpMouseInWindow(App->window->window,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
		// TODO (Homework): Rotate the camera with the mouse
	}

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}
