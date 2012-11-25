/*
 * Track.cpp: A class that draws the train and its track.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Track.h"
#include <stdio.h>
#include <FL/math.h>


// The control points for the track spline.
const int   Track::TRACK_NUM_CONTROLS = 4;
const float Track::TRACK_CONTROLS[TRACK_NUM_CONTROLS][3] =
		{ { -20.0, -20.0, -18.0 }, { 20.0, -20.0, 40.0 },
		  { 20.0, 20.0, -18.0 }, { -20.0, 20.0, 40.0 } };

// The carriage energy and mass
const float Track::TRAIN_ENERGY = 250.0f;


// Normalize a 3d vector.
static void
Normalize_3(float v[3])
{
    double  l = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if ( l == 0.0 )
	return;

    v[0] /= (float)l;
    v[1] /= (float)l;
    v[2] /= (float)l;
}


// Destructor
Track::~Track(void)
{
    if ( initialized )
    {
		glDeleteLists(track_list, 1);
		for(std::vector<Vertex*>::iterator it = this->vertexList->begin(); it != this->vertexList->end(); ++it) {
			delete (*it);
		}
		delete vertexList;
    }
}


// Initializer. Would return false if anything could go wrong.
bool Track::Initialize(void) {
    CubicBspline    refined(3, true);
    int		    n_refined;
    float	    p[3];
	float	    prev[3];
    int		    i;

	this->dragon = new Dragon(0.0f,0,0,1.0f,1.0f,1.0f,0);
	dragon->Initialize();

	vertexList = new vector<Vertex*>();

    // Create the track spline.
    track = new CubicBspline(3, true);
    for ( i = 0 ; i < TRACK_NUM_CONTROLS ; i++ )
		track->Append_Control(TRACK_CONTROLS[i]);

    // Refine it down to a fixed tolerance. This means that any point on
    // the track that is drawn will be less than 0.1 units from its true
    // location. In fact, it's even closer than that.
    track->Refine_Tolerance(refined, 0.1f);
    n_refined = refined.N();

	refined.Evaluate_Point(0.0f, prev);

	for ( i = 1 ; i <= n_refined ; i++ ) {
		refined.Evaluate_Point((float)i, p);
		float *temp = dragon->computeNormal(p[0],p[1],p[2],prev[0],prev[1],prev[2],p[0],p[1],p[2]+1.0f);
		Vertex *vert = new Vertex();
		vert->x = p[0] + temp[0];
		vert->y = p[1] + temp[1];
		vert->z = p[2] + temp[2];
		this->vertexList->push_back(vert);
		vert = new Vertex();
		vert->x = p[0] + temp[0];
		vert->y = p[1] + temp[1];
		vert->z = p[2] + temp[2]-0.2f;
		this->vertexList->push_back(vert);
		vert = new Vertex();
		vert->x = p[0] + temp[0] * 0.8f;
		vert->y = p[1] + temp[1] * 0.8f;
		vert->z = p[2] + temp[2]-0.2f;
		this->vertexList->push_back(vert);
		vert = new Vertex();
		vert->x = p[0] + temp[0] * 0.8f;
		vert->y = p[1] + temp[1] * 0.8f;
		vert->z = p[2] + temp[2];
		this->vertexList->push_back(vert);

		//right side
		vert = new Vertex();
		vert->x = p[0] + (-1.0f * temp[0]);
		vert->y = p[1] + (-1.0f * temp[1]);
		vert->z = p[2] + temp[2];
		this->vertexList->push_back(vert);
		vert = new Vertex();
		vert->x = p[0] + (-1.0f * temp[0] * 0.8f);
		vert->y = p[1] + (-1.0f * temp[1] * 0.8f);
		vert->z = p[2] + temp[2];
		this->vertexList->push_back(vert);
		vert = new Vertex();
		vert->x = p[0] + (-1.0f * temp[0] * 0.8f);
		vert->y = p[1] + (-1.0f * temp[1] * 0.8f);
		vert->z = p[2] + temp[2]-0.2f;
		this->vertexList->push_back(vert);
		vert = new Vertex();
		vert->x = p[0] + (-1.0f * temp[0]);
		vert->y = p[1] + (-1.0f * temp[1]);
		vert->z = p[2] + temp[2]-0.2f;
		this->vertexList->push_back(vert);
		
		

		delete [] temp;

		prev[0] = p[0];
		prev[1] = p[1];
		prev[2] = p[2];
	}

    // Create the display list for the track - just a set of line segments
    // We just use curve evaluated at integer paramer values, because the
    // subdivision has made sure that these are good enough.
    track_list = glGenLists(2);
    glNewList(track_list, GL_COMPILE);
	glColor3f(1.0f, 1.0, 1.0f);
	glBegin(GL_LINE_STRIP);
	    for ( i = 0 ; i <= n_refined ; i++ )
	    {
		refined.Evaluate_Point((float)i, p);
		glVertex3fv(p);
	    }
	glEnd();
    glEndList();

	int quadCount = 0;
	int startVertex = 0;
	int size = this->vertexList->size();
	bool leftSide = true;

	glNewList(track_list+1, GL_COMPILE);
	glBegin(GL_QUADS);
	for ( i = 0 ; i <= this->vertexList->size()-1; i++ ) {
		glColor3f(0.54f, 0.54f, 0.47f);
		glVertex3f(this->vertexList->at(i)->x,
				   this->vertexList->at(i)->y,
				   this->vertexList->at(i)->z);
		quadCount++;

		if(quadCount == 4) {
			// side 1
			Vertex *vert1 = this->vertexList->at(startVertex);
			Vertex *vert2 = this->vertexList->at((startVertex+1) % size);
			Vertex *vert3 = this->vertexList->at((startVertex+9) % size);
			Vertex *vert4 = this->vertexList->at((startVertex+8) % size);

			glVertex3f(vert1->x,vert1->y,vert1->z);
			glVertex3f(vert2->x,vert2->y,vert2->z);
			glVertex3f(vert3->x,vert3->y,vert3->z);
			glVertex3f(vert4->x,vert4->y,vert4->z);

			/////////////////////////////////
			if(leftSide) {
				float xDiff = vert4->x - vert1->x;
				float yDiff = vert4->y - vert1->y;
				float zDiff = vert4->z - vert1->z;
				float xDiffRight = this->vertexList->at((startVertex+12) % size)->x -  this->vertexList->at(startVertex+4)->x;
				float yDiffRight = this->vertexList->at((startVertex+12) % size)->y -  this->vertexList->at(startVertex+4)->y;
				float zDiffRight = this->vertexList->at((startVertex+12) % size)->z -  this->vertexList->at(startVertex+4)->z;

				glColor3f(0.54f, 0.27f, 0.07f);
				glVertex3f(vert1->x,vert1->y,vert1->z);
				glVertex3f(this->vertexList->at(startVertex+4)->x,this->vertexList->at(startVertex+4)->y,this->vertexList->at(startVertex+4)->z);
				glVertex3f(this->vertexList->at(startVertex+4)->x + (xDiffRight * 0.2f),
						   this->vertexList->at(startVertex+4)->y + (yDiffRight * 0.2f),
						   this->vertexList->at(startVertex+4)->z + (zDiffRight * 0.2f));
				glVertex3f(vert1->x + (xDiff * 0.2f),
					       vert1->y + (yDiff * 0.2f),
						   vert1->z + (zDiff * 0.2f));

				glVertex3f(vert1->x,vert1->y,vert1->z);
				glVertex3f(vert1->x + (xDiff * 0.2f),
					       vert1->y + (yDiff * 0.2f),
						   vert1->z + (zDiff * 0.2f));
				glVertex3f(this->vertexList->at(startVertex+4)->x + (xDiffRight * 0.2f),
						   this->vertexList->at(startVertex+4)->y + (yDiffRight * 0.2f),
						   this->vertexList->at(startVertex+4)->z + (zDiffRight * 0.2f));
				glVertex3f(this->vertexList->at(startVertex+4)->x,this->vertexList->at(startVertex+4)->y,this->vertexList->at(startVertex+4)->z);
				
				
			}

			/////////////////////////////////////
			glColor3f(0.54f, 0.54f, 0.47f);
		
			//side 2
			vert1 = this->vertexList->at((startVertex+1) % size);
			vert2 = this->vertexList->at((startVertex+2) % size);
			vert3 = this->vertexList->at((startVertex+10) % size);
			vert4 = this->vertexList->at((startVertex+9) % size);

			glVertex3f(vert1->x,vert1->y,vert1->z);
			glVertex3f(vert2->x,vert2->y,vert2->z);
			glVertex3f(vert3->x,vert3->y,vert3->z);
			glVertex3f(vert4->x,vert4->y,vert4->z);

			//side 3
			vert1 = this->vertexList->at((startVertex+2) % size);
			vert2 = this->vertexList->at((startVertex+3) % size);
			vert3 = this->vertexList->at((startVertex+11) % size);
			vert4 = this->vertexList->at((startVertex+10) % size);

			glVertex3f(vert1->x,vert1->y,vert1->z);
			glVertex3f(vert2->x,vert2->y,vert2->z);
			glVertex3f(vert3->x,vert3->y,vert3->z);
			glVertex3f(vert4->x,vert4->y,vert4->z);

			//side 4
			vert1 = this->vertexList->at((startVertex+3) % size);
			vert2 = this->vertexList->at((startVertex) % size);
			vert3 = this->vertexList->at((startVertex+8) % size);
			vert4 = this->vertexList->at((startVertex+11) % size);

			glVertex3f(vert1->x,vert1->y,vert1->z);
			glVertex3f(vert2->x,vert2->y,vert2->z);
			glVertex3f(vert3->x,vert3->y,vert3->z);
			glVertex3f(vert4->x,vert4->y,vert4->z);

			leftSide = !leftSide;
			quadCount = 0;
			startVertex = i+1;
		}

	}
	glEnd();
    glEndList();

    initialized = true;

    return true;
}


// Draw
void
Track::Draw(void)
{
    float   posn[3];
    float   tangent[3];
    double  angle;

    if ( ! initialized )
	return;

    glPushMatrix();

    // Draw the track
    glCallList(track_list);
    glCallList(track_list+1);

    glPushMatrix();

    // Figure out where the train is
    track->Evaluate_Point(posn_on_track, posn);

    // Translate the train to the point
    glTranslatef(posn[0], posn[1], posn[2]);
	//this->dragon->setPosition(posn[0],posn[1],posn[2]);

    // ...and what it's orientation is
    track->Evaluate_Derivative(posn_on_track, tangent);
    Normalize_3(tangent);
	
    // Rotate it to poitn along the track, but stay horizontal
    angle = atan2(tangent[1], tangent[0]) * 180.0 / M_PI;
    glRotatef((float)angle, 0.0f, 0.0f, 1.0f);

    // Another rotation to get the tilt right.
    angle = asin(-tangent[2]) * 180.0 / M_PI;
    glRotatef((float)angle, 0.0f, 1.0f, 0.0f);

	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);


    // Draw the train
    //glCallList(train_list);
	this->dragon->Draw();

    glPopMatrix();
    glPopMatrix();
}


void Track::Update(float dt)
{
    float   point[3];
    float   deriv[3];
    double  length;
    double  parametric_speed;

    if ( ! initialized )
	return;

    // First we move the train along the track with its current speed.
	this->dragon->Update(dt);

    // Get the derivative at the current location on the track.
    track->Evaluate_Derivative(posn_on_track, deriv);

    // Get its length.
    length = sqrt(deriv[0]*deriv[0] + deriv[1]*deriv[1] + deriv[2]*deriv[2]);
    if ( length == 0.0 )
	return;

    // The parametric speed is the world train speed divided by the length
    // of the tangent vector.
    parametric_speed = speed / length;

    // Now just evaluate dist = speed * time, for the parameter.
    posn_on_track += (float)(parametric_speed * dt);

    // If we've just gone around the track, reset back to the start.
    if ( posn_on_track > track->N() )
		posn_on_track -= track->N();

    // As the second step, we use conservation of energy to set the speed
    // for the next time.
    // The total energy = z * gravity + 1/2 speed * speed, assuming unit mass
    track->Evaluate_Point(posn_on_track, point);
    if ( TRAIN_ENERGY - 9.81 * point[2] < 0.0 )
	speed = 0.0;
    else
	speed = (float)sqrt(2.0 * ( TRAIN_ENERGY - 9.81 * point[2] ));
}



CameraPos Track::GetCameraPos() {
	CameraPos x;
	float   posn[3];
    float   tangent[3];
    double  angle, angle2;

	// Figure out where the train is
    this->track->Evaluate_Point(this->posn_on_track, posn);
	track->Evaluate_Derivative(posn_on_track, tangent);
    Normalize_3(tangent);

	angle = atan2(tangent[1], tangent[0]) * 180.0 / M_PI;
    angle2 = asin(-tangent[2]) * 180.0 / M_PI;//30

	x.xPos = posn[0];
	x.yPos = posn[1];
	x.zPos = posn[2]+3.5f;
	x.phi = angle2 + 20.0f;
	x.theta = angle-180.0;

	return x;
}
