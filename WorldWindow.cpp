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
#include <stdlib.h>
#include <time.h>

const double WorldWindow::FOV_X = 45.0;

WorldWindow::WorldWindow(int x, int y, int width, int height, char *label)
	: Fl_Gl_Window(x, y, width, height, label)
{
    button = -1;

	srand ( time(NULL) );

    // Initial viewing parameters.
    phi = 45.0f;
    theta = 0.0f;
    dist = 100.0f;
    x_at = 0.0f;
    y_at = 0.0f;

	worldObjects = new vector<WorldObject*>();

	this->signalGates = false;
}

// Destructor
WorldWindow::~WorldWindow(void)
{
	for(std::vector<WorldObject*>::iterator it = this->worldObjects->begin(); it != this->worldObjects->end(); ++it) {
		delete (*it);
	}
	//this->worldObjects->clear();
	delete worldObjects;
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
		Wall *wall = new Wall(50.0f,0.0f,0.0f,3.0f,100.0f,6.0f,EAST);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(-50.0f,0.0f,0.0f,3.0f,100.0f,6.0f,WEST);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(0.0f,50.0f,0.0f,100.0f,3.0f,6.0f,NORTH);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(30.0f,-50.0f,0.0f,40.0f,3.0f,6.0f,SOUTH);
		wall->Initialize();
		worldObjects->push_back(wall);

		wall = new Wall(-30.0f,-50.0f,0.0f,40.0f,3.0f,6.0f,SOUTH);
		wall->Initialize();
		worldObjects->push_back(wall);

		//Corner Towers/////////////////////////////////
		Tower *tower = new Tower(50.0f,50.0f,0,5.0f,5.0f,12.0f,20);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(-50.0f,50.0f,0,5.0f,5.0f,12.0f,20);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(50.0f,-50.0f,0,5.0f,5.0f,12.0f,20);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(-50.0f,-50.0f,0,5.0f,5.0f,12.0f,20);
		tower->Initialize();
		worldObjects->push_back(tower);
		/////////////////////////////////////////////

		//Gate
		tower = new Tower(10.0f,-50.0f,0,5.0f,5.0f,12.0f,20);
		tower->Initialize();
		worldObjects->push_back(tower);

		tower = new Tower(-10.0f,-50.0f,0,5.0f,5.0f,12.0f,20);
		tower->Initialize();
		worldObjects->push_back(tower);

		Gate *gate = new Gate(-3.8f,-50.0f,0.5f,7.5f,0.7f,5.0f,7.5f/2.0f,1);
		gate->Initialize();
		worldObjects->push_back(gate);

		gate = new Gate(3.8f,-50.0f,0.5f,7.5f,0.7f,5.0f,-7.5f/2.0f,-1);
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
								  treeArray->at(x).at(5),treeArray->at(x).at(6),treeArray->at(x).at(7),treeArray->at(x).at(8),treeArray->at(x).at(9));

			tree->Initialize();
			worldObjects->push_back(tree);
		}

		delete treeArray;
		
	
		Flag *flag = new Flag(0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f);
		flag->Initialize();
		worldObjects->push_back(flag);

    }

    // Stuff out here relies on a coordinate system or must be done on every
    // frame.

    // Clear the screen. Color and depth.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Set up the viewing transformation. The viewer is at a distance
    // dist from (x_at, y_ay, 2.0) in the direction (theta, phi) defined
    // by two angles. They are looking at (x_at, y_ay, 2.0) and z is up.
    eye[0] = x_at + dist * cos(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
    eye[1] = y_at + dist * sin(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
    eye[2] = 2.0 + dist * sin(phi * M_PI / 180.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, 2.0, 0.0, 0.0, 1.0);

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

	x_axis[0] = -(float)sin(theta * M_PI / 180.0);
	x_axis[1] = (float)cos(theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

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
      case FL_PUSH:
        button = Fl::event_button();
		x_last = x_down = Fl::event_x();
		y_last = y_down = Fl::event_y();
		phi_down = phi;
		theta_down = theta;
		dist_down = dist;
		x_at_down = x_at;
		y_at_down = y_at;
		return 1;
      case FL_DRAG:
		x_last = Fl::event_x();
		y_last = Fl::event_y();
		return 1;
      case FL_RELEASE:
		button = -1;
		return 1;
	  case FL_KEYUP:
		  if(Fl::event_key() == (int)'o')
			  signalGates = true;
    }

    // Pass any other event types on the superclass.
    return Fl_Gl_Window::handle(event);
}


