//-------------------------------------------------------
//
//  MyThing.h
//
//  PbaThing for a collection of particles
//  each doing a random walk.
//
//  Copyright (c) 2017 Jerry Tessendorf
//
//  Editing by Samaneh Zamanifard
//--------------------------------------------------------
#ifndef    MYGUARD_H
#define    MyGUARD_H


#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"
#include "Mesh.h"

using namespace std;

namespace pba{
    
    
    
    
    
    class MyThing: public PbaThingyDingy
    {
    public:
        
        // Feel free to customize the name of this thing.
        MyThing(const std::string nam = "Lecture_01_thing");
        ~MyThing();
        
        //! Initialization, including GLUT initialization.
        //! Called once at the beginning.  Could be used
        //! to set up things once.
        void Init( const std::vector<std::string>& args );
        
        ///////////////////////////////////////////////////////////////
        // CASCADING CALLBACK FUNCTIONS
        // The methods below are called as part of a bigger set
        // of similar calls.  Most of the other calls take place
        // in the viewer portion of this project.
        ///////////////////////////////////////////////////////////////
        
        //! Implements a display event
        //! This is where you code the opengl calls to display
        //! your system.
        void Display();
        
        //! Implements responses to keyboard events
        //! This is called when you hit a key
        void Keyboard( unsigned char key, int x, int y );
        
        //! Implements simulator updates during an idle period
        //! This is where the update process is coded
        //! for your dynamics problem.
        void solve();
        
        //! Implements reseting parameters and/or state
        //! This is called when you hit the 'r' key
        void Reset();
        
        //! Displays usage information on stdout
        //! If you set up actions with the Keyboard()
        //! callback, you should include a statement
        //! here as to what the keyboard option is.
        void Usage();
        void CheckCollision(float& ddt);
        void DrawLines(int x, int y, vector<pair<int,int> > Neighbor );
        void CalculateForces(int x, int y, Vector Lab );
        void ClaculateLab(int x, int y);
        
        
        
        
    private:
        
        // flag for whether to create more particles
        bool emit;
        Vector gravity;
        Vector Xa,Xb;
        int SizeOfMesh;
        float Ks,Kf,w,r;
        Mesh MyMesh;
        Vector Lab[100][100];
        Vector Xh[100][100];
        Vector Fab[100][100];
        std::vector<vector<ParticleState>> particles;
        bool circularMotion;
        ////////////////////////////////////////////////
        //
        //      PARTICLE STATE
        //
        // The state of a particle is characterized by
        // (1) particle positions
        // (2) particle velocities
        // (3) particle masses
        // (4) particle colors - useful for display
        /* class ParticleState
         {
         public:
         ParticleState() :
         position(Vector(0,0,0)),
         velocity(Vector(0,0,0)),
         color(Color(1,1,1,1)),
         mass(1.0)
         {};
         ~ParticleState(){};
         
         Vector position;
         Vector velocity;
         Vector acceleration;
         Color color;
         float mass;
         
         };
         
         // This is all of the particles in the system
         std::vector<vector<ParticleState>> particles;*/
        
        //
        //
        ////////////////////////////////////////////////
        
    };
    
    
    // This function constructs the MyThing and wraps it in a
    // smart pointer called a PbaThing.
    // You need not alter this.
    pba::PbaThing CreateMyThing();
    
    
    
    
    
    
    
    
}

#endif




