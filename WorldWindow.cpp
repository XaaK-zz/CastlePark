/*
 * CS559 Maze Project
 *
 * Class file for the WorldWindow class.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

#include "WorldWindow.h"
#include <Fl/math.h>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include "Tower.h"
#include "Gate.h"
#include "Tree.h"
#include "Flag.h"
#include "Bench.h"
#include <stdlib.h>
#include <time.h>
#include "dragon.h"

const double WorldWindow::FOV_X = 45.0;

WorldWindow::WorldWindow(int x, int y, int width, int height, char *label)
	: Fl_Gl_Window(x, y, width, height, label)
{
    button = -1;

	srand ( time(NULL) );

    // Initial viewing parameters.
    phi = 45.0f;
    theta = -90.0f;
    dist = 25.0f;
    x_at = 0.0f;
    y_at = 00.0f;

	fps_phi = 0;
	fps_theta = -90.0;
	fps_dist = 5.0f;
	fps_x_at = 0.0f;
	fps_y_at = -50.0f;

	worldObjects = new vector<WorldObject*>();
	
	this->viewingMode = VIEWMODE_NORMAL;
	this->signalGates = false;
	this->textureManager = new TextureManager();

	//fixed camera locations
	this->fixedCamera = new FixedCamera();
	this->fixedCamera->AddCameraPos(125.0f,-125.0f,100.0f,27.0f,-45.0f);
	this->fixedCamera->AddCameraPos(50.5f,50.5f,15.5f,15.0f,45.0f);
	this->fixedCamera->AddCameraPos(40.5f,-40.5f,2.0f,0.0f,-45.0f);
}

// Destructor
WorldWindow::~WorldWindow(void)
{
	for(std::vector<WorldObject*>::iterator it = this->worldObjects->begin(); it != this->worldObjects->end(); ++it) {
		delete (*it);
	}
	//this->worldObjects->clear();
	delete worldObjects;
	delete this->textureManager;
	delete this->fixedCamera;
}




void
WorldWindow::draw(void)
{
    double  eye[3];
    float   color[4], dir[4];

    if ( ! valid() )
    {
		// Stuff in here doesn't change from frame to frame, and does not
		// rely on any coordinate system. It only has to be done if the
		// GL context is damaged.

		double	fov_y;

		// Sets the clear color to sky blue.
		glClearColor(0.53f, 0.81f, 0.92f, 1.0);

		// Turn on depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Turn on back face culling. Faces with normals away from the viewer
		// will not be drawn.
		glEnable(GL_CULL_FACE);

		// Enable lighting with one light.
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		// Ambient and diffuse lighting track the current color.
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		// Turn on normal vector normalization. You don't have to give unit
		// normal vector, and you can scale objects.
		glEnable(GL_NORMALIZE);

		// Set up the viewport.
		glViewport(0, 0, w(), h());

		// Set up the persepctive transformation.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		fov_y = 360.0f / M_PI * atan(h() * tan(FOV_X * M_PI / 360.0) / w());
		gluPerspective(fov_y, w() / (float)h(), 1.0, 1000.0);

		// Do some light stuff. Diffuse color, and zero specular color
		// turns off specular lighting.
		color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
		color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
		glLightfv(GL_LIGHT0, GL_SPECULAR, color);

		// Initialize all the objects.
		ground.Initialize();
		traintrack.Initialize();
		Wall *wall = new Wall(50.0f,0.0f,0.0f,3.0f,100.0f,6.0f,EAST,this->textureManager);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(-50.0f,0.0f,0.0f,3.0f,100.0f,6.0f,WEST,this->textureManager);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(0.0f,50.0f,0.0f,100.0f,3.0f,6.0f,NORTH,this->textureManager);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(30.0f,-50.0f,0.0f,40.0f,3.0f,6.0f,SOUTH,this->textureManager);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(-30.0f,-50.0f,0.0f,40.0f,3.0f,6.0f,SOUTH,this->textureManager);
		wall->Initialize();
		worldObjects->push_back(wall);

		//Corner Towers/////////////////////////////////
		Tower *tower = new Tower(50.0f,50.0f,0,5.0f,5.0f,12.0f,20,this->textureManager);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(-50.0f,50.0f,0,5.0f,5.0f,12.0f,20,this->textureManager);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(50.0f,-50.0f,0,5.0f,5.0f,12.0f,20,this->textureManager);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(-50.0f,-50.0f,0,5.0f,5.0f,12.0f,20,this->textureManager);
		tower->Initialize();
		worldObjects->push_back(tower);
		/////////////////////////////////////////////

		//Gate
		tower = new Tower(10.0f,-50.0f,0,5.0f,5.0f,12.0f,20,this->textureManager);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(-10.0f,-50.0f,0,5.0f,5.0f,12.0f,20,this->textureManager);
		tower->Initialize();
		worldObjects->push_back(tower);

		Gate *gate = new Gate(-3.8f,-50.0f,0.5f,7.5f,0.7f,5.0f,7.5f/2.0f,1,this->textureManager);
		gate->Initialize();
		worldObjects->push_back(gate);

		gate = new Gate(3.8f,-50.0f,0.5f,7.5f,0.7f,5.0f,-7.5f/2.0f,-1,this->textureManager);
		gate->Initialize();
		worldObjects->push_back(gate);

		int numTrees = 25;
		vector<vector<float>> *treeArray = new vector<vector<float>>();
		for(int treeNum=0;treeNum<numTrees;treeNum++) {
			vector<float> treeSettings;// = {37.5f + (rand() % 12) - 25.0f,
									  //37.5f + (rand() % 12) - 25.0f,
									  //0.0f,1.0f,1.0f,1.0f,0.5f,2.0f,3.0f,1.0f};
			treeSettings.push_back(37.5f + (rand() % 25) - 25.0f);
			treeSettings.push_back(37.5f + (rand() % 25) - 25.0f);
			treeSettings.push_back(0.0f);
			treeSettings.push_back(1.0f);
			treeSettings.push_back(1.0f);
			treeSettings.push_back(1.0f);
			float widthTemp = ((float)(rand() % 100)+1)/100.0f;
			treeSettings.push_back(widthTemp);//width
			treeSettings.push_back((rand() % 8)+1);//height
			treeSettings.push_back((rand() % 5)+1);//top
			treeSettings.push_back(widthTemp + (rand() % 3)+1);//tree height

			//treeSettings[0] = 37.5f + (rand() % 12) - 25.0f;
			//treeSettings[1] = 37.5f + (rand() % 12) - 25.0f;
			treeArray->push_back(treeSettings);
		}

		//Trees
		for(int x=0;x<numTrees;x++) {
			//Tree *tree = new Tree(25.0f,25.0f,0.0f,1.0f,1.0f,1.0f,0.5f,2.0f,3.0f,1.0f);
			Tree *tree = new Tree(treeArray->at(x).at(0),treeArray->at(x).at(1),treeArray->at(x).at(2),treeArray->at(x).at(3),treeArray->at(x).at(4),
								  treeArray->at(x).at(5),treeArray->at(x).at(6),treeArray->at(x).at(7),treeArray->at(x).at(8),treeArray->at(x).at(9),this->textureManager);

			tree->Initialize();
			worldObjects->push_back(tree);
		}

		delete treeArray;
		
	
		Flag *flag = new Flag(50.0f,50.0f,14.0f,1.0f,1.0f,1.0f,2.0f,0.2f,0.2f,1.0f, 0.0f, 0.0f, 1, 0.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(-50.0f,50.0f,14.0f,1.0f,1.0f,1.0f,2.0f,0.2f,0.2f,1.0f, 0.0f, 0.0f, 1, 0.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(50.0f,-50.0f,14.0f,1.0f,1.0f,1.0f,2.0f,0.2f,0.2f,1.0f, 0.0f, 0.0f, 1, 0.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(-50.0f,-50.0f,14.0f,1.0f,1.0f,1.0f,2.0f,0.2f,0.2f,1.0f, 0.0f, 0.0f, 1, 0.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		//big flags
		flag = new Flag(10.0f,-50.0f,14.0f,1.0f,1.0f,1.0f,3.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f, 1, 0.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(-10.0f,-50.0f,14.0f,1.0f,1.0f,1.0f,3.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f, 1, 0.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		//stage flags
		flag = new Flag(33.0f,-47.0f,0.0f,1.0f,1.0f,1.0f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(35.0f,-47.0f,0.0f,1.0f,1.0f,1.2f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(37.0f,-47.0f,0.0f,1.0f,1.0f,1.4f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(39.0f,-47.0f,0.0f,1.0f,1.0f,1.6f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(41.0f,-47.0f,0.0f,1.0f,1.0f,1.8f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(43.0f,-47.0f,0.0f,1.0f,1.0f,2.0f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(45.0f,-47.0f,0.0f,1.0f,1.0f,2.2f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-47.0f,0.0f,1.0f,1.0f,2.4f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-33.0f,0.0f,1.0f,1.0f,1.0f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-35.0f,0.0f,1.0f,1.0f,1.2f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-37.0f,0.0f,1.0f,1.0f,1.4f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-39.0f,0.0f,1.0f,1.0f,1.6f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-41.0f,0.0f,1.0f,1.0f,1.8f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-43.0f,0.0f,1.0f,1.0f,2.0f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		flag = new Flag(47.0f,-45.0f,0.0f,1.0f,1.0f,2.2f,3.0f,2.0f,1.0f,0.69f, 0.13f, 0.13f, 2, 35.0f,this->textureManager);
		flag->Initialize();
		worldObjects->push_back(flag);

		/////////////////////////////////////////////////////////////////////////////////////////
		//benches
		//First - "Stage"
		Bench *bench = new Bench(40.0f,-40.0f,-0.8f,15.0f,15.0f,1.0f,0.0f,1, this->textureManager);
		bench->HideLegs();
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(31.0f,-31.0f,0.0f,1.5f,0.5f,0.5f,45.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(33.0f,-30.0f,0.0f,1.0f,0.5f,0.5f,-5.0f,2, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(36.0f,-30.0f,0.0f,2.0f,0.5f,0.5f,3.0f,2, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(39.0f,-30.0f,0.0f,1.0f,0.5f,0.5f,0.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(42.0f,-30.0f,0.0f,1.2f,0.5f,0.5f,2.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(45.0f,-30.0f,0.0f,2.0f,0.5f,0.5f,1.0f,2, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-33.0f,0.0f,1.0f,0.5f,0.5f,90.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-35.0f,0.0f,1.5f,0.5f,0.5f,92.0f,2, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-38.0f,0.0f,2.5f,0.5f,0.5f,88.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-41.0f,0.0f,1.0f,0.5f,0.5f,90.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-43.0f,0.0f,1.0f,0.5f,0.5f,92.0f,2, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-45.0f,0.0f,1.5f,0.5f,0.5f,89.0f,2, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		bench = new Bench(30.0f,-47.0f,0.0f,1.0f,0.5f,0.5f,90.0f,1, this->textureManager);
		bench->Initialize();
		worldObjects->push_back(bench);

		Dragon *dragon = new Dragon(0,0,0,1.0f,1.0f,1.0f,this->textureManager);
		dragon->Initialize();
		worldObjects->push_back(dragon);

		//////////////////////////////////////////////////////////////////////////////////
    }

    // Stuff out here relies on a coordinate system or must be done on every
    // frame.

    // Clear the screen. Color and depth.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Set up the viewing transformation. The viewer is at a distance
    // dist from (x_at, y_ay, 2.0) in the direction (theta, phi) defined
    // by two angles. They are looking at (x_at, y_ay, 2.0) and z is up.
	if(this->viewingMode == VIEWMODE_NORMAL) {
		eye[0] = x_at + dist * cos(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
		eye[1] = y_at + dist * sin(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
		eye[2] = 2.0 + dist * sin(phi * M_PI / 180.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, 2.0, 0.0, 0.0, 1.0);
	}
	else if(this->viewingMode == VIEWMODE_FPS) {
		
		fps_phi = 90.0f - (90.0f * (((float)h()-fps_mouseY)/((float)h()/2.0f)));
		fps_theta = 360.0f - (360.0f * (fps_mouseX/((float)w()/2.0f)));

		while ( fps_theta >= 360.0f )
			fps_theta -= 360.0f;
		while ( fps_theta < 0.0f )
			fps_theta += 360.0f;

		if ( fps_phi > 55.0f )
			fps_phi = 55.0f;
		if ( fps_phi < -35.0f )
			fps_phi = -35.0f;

		eye[0] = fps_x_at + fps_dist * cos(fps_theta * M_PI / 180.0) * cos(fps_phi * M_PI / 180.0);
		eye[1] = fps_y_at + fps_dist * sin(fps_theta * M_PI / 180.0) * cos(fps_phi * M_PI / 180.0);
		eye[2] = 2.0 + fps_dist * sin(fps_phi * M_PI / 180.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye[0], eye[1], eye[2], fps_x_at, fps_y_at, 2.0, 0.0, 0.0, 1.0);
	}
	else if(this->viewingMode == VIEWMODE_FIXED) {

		CameraPos pos = this->fixedCamera->GetCurrentPos();
		float dist_fixed = 5.0f;

		eye[0] = pos.xPos - dist_fixed * cos(pos.theta * M_PI / 180.0) * cos(pos.phi* M_PI / 180.0);
		eye[1] = pos.yPos - dist_fixed * sin(pos.theta * M_PI / 180.0) * cos(pos.phi * M_PI / 180.0);
		eye[2] = pos.zPos - dist_fixed * sin(pos.phi* M_PI / 180.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pos.xPos, pos.yPos, pos.zPos, eye[0], eye[1], eye[2], 0.0, 0.0, 1.0);
	}
	else if(this->viewingMode == VIEWMODE_COASTER) {

		CameraPos pos = this->traintrack.GetCameraPos();
		float dist_fixed = 5.0f;

		eye[0] = pos.xPos - dist_fixed * cos(pos.theta * M_PI / 180.0) * cos(pos.phi* M_PI / 180.0);
		eye[1] = pos.yPos - dist_fixed * sin(pos.theta * M_PI / 180.0) * cos(pos.phi * M_PI / 180.0);
		eye[2] = pos.zPos - dist_fixed * sin(pos.phi* M_PI / 180.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pos.xPos, pos.yPos, pos.zPos, eye[0], eye[1], eye[2], 0.0, 0.0, 1.0);
	}

    // Position the light source. This has to happen after the viewing
    // transformation is set up, so that the light stays fixed in world
    // space. This is a directional light - note the 0 in the w component.
    dir[0] = 1.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, dir);

    // Draw stuff. Everything.
    ground.Draw();
    traintrack.Draw();

	for(std::vector<WorldObject*>::iterator it = this->worldObjects->begin(); it != this->worldObjects->end(); ++it) {
		(*it)->Draw();
	}
	
}


void
WorldWindow::Drag(float dt)
{
    int	    dx = x_down - x_last;
    int     dy = y_down - y_last;

    switch ( button )
    {
      case FL_LEFT_MOUSE:
	// Left button changes the direction the viewer is looking from.
	theta = theta_down + 360.0f * dx / (float)w();
	while ( theta >= 360.0f )
	    theta -= 360.0f;
	while ( theta < 0.0f )
	    theta += 360.0f;
	phi = phi_down + 90.0f * dy / (float)h();
	if ( phi > 89.0f )
	    phi = 89.0f;
	if ( phi < -5.0f )
	    phi = -5.0f;
	break;
      case FL_MIDDLE_MOUSE:
	// Middle button moves the viewer in or out.
	dist = dist_down - ( 0.5f * dist_down * dy / (float)h() );
	if ( dist < 1.0f )
	    dist = 1.0f;
	break;
      case FL_RIGHT_MOUSE: {
	// Right mouse button moves the look-at point around, so the world
	// appears to move under the viewer.
	float	x_axis[2];
	float	y_axis[2];
	//cout << "Right Mouse Drag: x_at: " << x_at << " y_at: " << y_at
	//	 << " theta: " << theta << endl;

	x_axis[0] = -(float)sin(theta * M_PI / 180.0);
	x_axis[1] = (float)cos(theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

	//cout << "	x_axis[0]: " << x_axis[0] << " x_axis[1]: " << x_axis[1] << endl 
	//	 << "	y_axis[0]: " << y_axis[0] << " y_axis[1]: " << y_axis[1] << endl; 

	//cout << "	dx: " << dx << " dy: " << dy << " x_at_down: " << x_at_down 
	//	 << "	y_at_down: " << y_at_down << endl;

	//cout << "	x_axis[0] * dx / (float)w(): " <<  x_axis[0] * dx / (float)w() << endl
	//	<< "	y_axis[0] * dy / (float)h(): " << y_axis[0] * dy / (float)h() << endl; 

	x_at = x_at_down + 100.0f * ( x_axis[0] * dx / (float)w()
				    + y_axis[0] * dy / (float)h() );
	y_at = y_at_down + 100.0f * ( x_axis[1] * dx / (float)w()
				    + y_axis[1] * dy / (float)h() );


	} break;
      default:;
    }
}


bool
WorldWindow::Update(float dt)
{
    // Update the view. This gets called once per frame before doing the
    // drawing.

    if ( button != -1 ) // Only do anything if the mouse button is down.
	Drag(dt);

    // Animate the train.
    traintrack.Update(dt);

	for(std::vector<WorldObject*>::iterator it = this->worldObjects->begin(); it != this->worldObjects->end(); ++it) {
		if(signalGates) {
			Gate *temp = dynamic_cast<Gate*>(*it);
			if(temp != NULL) {
				temp->ChangeGateState();
			}
		}
		(*it)->Update(dt);
	}

	signalGates = false;
    return true;
}


int
WorldWindow::handle(int event)
{
	//cout << "event: " << event << endl;
	
    // Event handling routine. Only looks at mouse events.
    // Stores a bunch of values when the mouse goes down and keeps track
    // of where the mouse is and what mouse button is down, if any.
	switch ( event )
    {
		case FL_MOVE:
			if(this->viewingMode == VIEWMODE_FPS) {
				fps_mouseX = Fl::event_x();
				fps_mouseY = Fl::event_y();
			}
			return 1;
		case FL_PUSH:
			if(this->viewingMode == VIEWMODE_NORMAL) {
				button = Fl::event_button();
				x_last = x_down = Fl::event_x();
				y_last = y_down = Fl::event_y();
				phi_down = phi;
				theta_down = theta;
				dist_down = dist;
				x_at_down = x_at;
				y_at_down = y_at;
			}
			return 1;
		case FL_DRAG:
			if(this->viewingMode == VIEWMODE_NORMAL) {
				x_last = Fl::event_x();
				y_last = Fl::event_y();
			}
			return 1;
		case FL_RELEASE:
			if(this->viewingMode == VIEWMODE_NORMAL) {
				button = -1;
			}
			return 1;
		case FL_KEYDOWN:
			if(this->viewingMode == VIEWMODE_FPS) {
				if(Fl::event_key() == (int)'w') {
					this->Move(-2.0,0);
				}
				else if(Fl::event_key() == (int)'s') {
					this->Move(2.0,0);
				}
				else if(Fl::event_key() == (int)'a') {
					this->Move(0,-2.0);
				}
				else if(Fl::event_key() == (int)'d') {
					this->Move(0,2.0);
				}
			}
			break;
		case FL_KEYUP:
			if(Fl::event_key() == (int)'o')
				signalGates = true;
			if(Fl::event_key() == (int)'v') {
				this->ChangeViewmode();
			}
			if(Fl::event_key() == (int)'.' && this->viewingMode == VIEWMODE_FIXED) {
				this->fixedCamera->NextPosition();
			}
			break;
    }

    // Pass any other event types on the superclass.
    return Fl_Gl_Window::handle(event);
}

void WorldWindow::Move(float yDir, float xDir) {

	//cout << "MoveForward. theta: " << theta << endl;

	float	x_axis[2];
	float	y_axis[2];
	float dx = 0.0f;
	float dy = -5.0f;
	//float walkDistance = -5.0f;

	x_axis[0] = -(float)sin(fps_theta * M_PI / 180.0);
	x_axis[1] = (float)cos(fps_theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

	float moveX = (yDir * (float)cos(fps_theta * M_PI / 180.0)) + (xDir * x_axis[0]);
	float moveY = (yDir * (float)sin(fps_theta * M_PI / 180.0)) + (xDir * x_axis[1]);;

	fps_x_at += moveX;
	fps_y_at += moveY;
	//x_at = x_at + 100.0f * ( x_axis[0] * dx / (float)w() + y_axis[0] * dy / (float)h() );
	//y_at = y_at + 100.0f * ( x_axis[1] * dx / (float)w() + y_axis[1] * dy / (float)h() );
}





void WorldWindow::ChangeViewmode() {
	if(this->viewingMode == VIEWMODE_NORMAL) {
		this->viewingMode = VIEWMODE_FPS;
	}
	else if(this->viewingMode == VIEWMODE_FPS) {
		this->viewingMode = VIEWMODE_FIXED;
	}
	else if(this->viewingMode == VIEWMODE_FIXED) {
		this->viewingMode = VIEWMODE_COASTER;
	}
	else if(this->viewingMode == VIEWMODE_COASTER) {
		this->viewingMode = VIEWMODE_NORMAL;
	}
}