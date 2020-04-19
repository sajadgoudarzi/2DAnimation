//-------------------------------------------------------
//
//  MyThing.C
//
//  PbaThing for a collection of particles
//  each doing a random walk.
//
//  Copyright (c) 2017 Jerry Tessendorf
//  Editing by Samaneh Zamanifard
//
//--------------------------------------------------------

#include "MyThing.h"
#include <cstdlib>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>
#include "PbaViewer.h"

using namespace std;
using namespace pba;

MyThing::MyThing(const std::string nam) :
PbaThingyDingy (nam),
gravity(Vector(0,-1,0)),
emit       (false),
Ks(100),
Kf(0),
w(45),
r(1),
SizeOfMesh(20),
MyMesh (Mesh(SizeOfMesh,Vector(-5,0,-5), 0.5 ))


{
    dt = 0.001;
    Reset();
    std::cout << name << " constructed\n";
    circularMotion = false;
}
MyThing::~MyThing(){}

void MyThing::Init( const std::vector<std::string>& args ) {}

void MyThing::Display() 
{
    
    glPointSize(10);
    glBegin(GL_POINTS);
    for (int j =0 ; j<SizeOfMesh;j++)
        for (int i = 0 ; i< SizeOfMesh ; i++)
        {
            const Vector& P = particles[i][j].position;
            if (i == SizeOfMesh-1 && j ==  0) particles[i][j].color = Color(0,255,0, 0);

            const Color& ci = particles[i][j].color;
            glColor3f(ci.red()*1.8, ci.green()*1.5, ci.blue()*1.6);
            glVertex3f( P.X(), P.Y(), P.Z() );
        }
    glEnd();
    
    for (size_t j = 0 ; j< SizeOfMesh ; j++)
        for (size_t i= 0; i< SizeOfMesh; i++)
        {
            vector<pair<int,int> > Neighbor;
            Neighbor = MyMesh.ReturnNeighbor(i,j);
            const Vector& P0 = particles[i][j].position;
            for (int k= 0 ; k<Neighbor.size() ; k++)
            {
                glBegin(GL_LINES);
                int first= Neighbor[k].first ;
                int second= Neighbor[k].second ;
                const Vector& P = particles[first][second].position;
                const Color& ci = particles[i][j].color;
                glColor3f(ci.red()*1.8, ci.green()*1.5, ci.blue()*1.6);
                glVertex3f( P0.X(), P0.Y(), P0.Z() );
                glVertex3f( P.X(), P.Y(), P.Z() );
                glEnd();
            }
            
        }
    
}

void MyThing::Keyboard( unsigned char key, int x, int y )
{
    if (key == 'G'){ gravity *=1.01; cout<<"gavity is:"<<gravity.__str__()<<endl;}
    if (key =='g'){ gravity /=1.01; cout<<"gravity is:"<<gravity.__str__()<<endl;}
    if (key == 'K'){ Ks *=1.01; cout<<"spring strength:"<<Ks<<endl;}
    if (key =='k'){ Ks /=1.01; cout<<"spring strength:"<<Ks<<endl;}
    if (key == 'A'){ Kf *=1.01; cout<<"friction strength:"<<Kf<<endl;}
    if (key =='a'){ Kf /=1.01; cout<<"friction strength:"<<Kf<<endl;}
    if (key == 'S'){ w *=1.01; cout<<"the speed of the circular motion:"<<Ks<<endl;}
    if (key =='s'){ w /=1.01; cout<<"the speed of the circular motion:"<<Ks<<endl;}
    if (key == 'D'){ r *=1.01; cout<<"the size of the circle:"<<Kf<<endl;}
    if (key =='d'){ r /=1.01; cout<<"the size of the circle:"<<Kf<<endl;}
    if (key == 'c'){circularMotion = true ; Reset(); cout <<"Circular Motion: "<<circularMotion<<"\n";}
    
    
    
}


void MyThing::solve()
{
    double ddt = dt * 0.5;
    for (int j = 0 ; j<SizeOfMesh; j++)
        for (int i = 0 ; i<SizeOfMesh; i++)
        {
            // cout << "base particle ( i " << i << ", j " << j <<") = ( " << particles[i][j].position.X() <<", " << particles[i][j].position.Y() <<", " << particles[i][j].position.Z() << ")\n";
            
            vector<pair<int,int> > Neighbor;
            Neighbor = MyMesh.ReturnNeighbor(i,j);
            Fab[i][j] = particles[i][j].mass * gravity ;
            for (int k= 0 ; k<Neighbor.size() ; k++)
            {
                int first= Neighbor[k].first ;
                int second= Neighbor[k].second ;
                // cout << "neighbor ( i " << first << ", j " << second <<") = ( " << particles[first][second].position.X() <<", " << particles[first][second].position.Y() <<", " << particles[first][second].position.Z() << ")\n";
                Vector Xab = particles[first][second].position - particles[i][j].position;
                
                float Lab = (Xh[first][second] - Xh[i][j]).magnitude();
                if ((Xab.magnitude()!=0))
                {
                    Fab[i][j] +=  Ks * (Xab.magnitude()-Lab) * (Xab/ Xab.magnitude()) + Kf * (Xab/ Xab.magnitude()) *((particles[first][second].velocity - particles[i][j].velocity)* (Xab/ Xab.magnitude()));
                }
                
            }
            
            
        }
    
    
    // Update Velocity
    if (circularMotion == false)
    {
        for (int j = 0 ; j<SizeOfMesh; j++)
            for (int i = 0 ; i<SizeOfMesh; i++)
            {
                if (( i == 0 || i == SizeOfMesh -1) && (j == 0 || j == SizeOfMesh - 1))
                {
                    particles[i][j].velocity = Vector(0,0,0);
                }
                else
                {
                    particles[i][j].velocity = particles[i][j].velocity + (Fab[i][j]/particles[i][j].mass) * ddt ;
                    
                }
            }
    }
    else if (circularMotion == true)
    {
        for (int j = 0 ; j<SizeOfMesh; j++)
            for (int i = 0 ; i<SizeOfMesh; i++)
            {
                if ( (i == 0 && j == SizeOfMesh - 1) || (i = SizeOfMesh -1) &&(j == 0 || j == SizeOfMesh - 1 ))
                {
                    particles[i][j].velocity = Vector(0,0,0);
                }
                else
                {
                    particles[i][j].velocity = particles[i][j].velocity + (Fab[i][j]/particles[i][j].mass) * ddt ;
                    
                }
            }
    }
    // Update Position
    if (circularMotion == false)
    {
        for (int j = 0 ; j<SizeOfMesh; j++)
            for (int i = 0 ; i<SizeOfMesh; i++)
            {
                if ((i == 0 || i == SizeOfMesh -1  ) && (j== 0 || j==SizeOfMesh -1  )  )
                {
                           particles[i][j].position =  Xh[i][j];
                            
                }
                else
                {
                    particles[i][j].position =  particles[i][j].position + particles[i][j].velocity * ddt;
                }
            }
        
    }
    else if (circularMotion  == true)
    {
        for (int j = 0 ; j<SizeOfMesh; j++)
            for (int i = 0 ; i<SizeOfMesh; i++)
            {
                if (i == 0 & j == 0 )
                {
                    particles[i][j].position = Xh[i][j] + Vector( r * cos(w*ddt), 0, r * sin(w*ddt) );
                }
                else if ( (i == 0 && j == SizeOfMesh - 1) || (i = SizeOfMesh -1) &&(j == 0 || j == SizeOfMesh - 1 ))

                {
                    particles[i][j].position =  Xh[i][j];
                    
                }
                else
                {
                    particles[i][j].position =  particles[i][j].position + particles[i][j].velocity * ddt;
                }
            }
    }
    
    
    
    
    
}

/* else
 {
 particles[i][j].position = Xh[i][j] + Vector(r * cos (w * ddt) , 0 , r * sin(w * ddt));
 particles[i][j].color = Color(255,255,255,0);
 }*/


/* if ((particles[i][j].position.magnitude() - Xh[i][j].magnitude())< 0)
 {
 particles[i][j].color = Color(255,0,0, 0);
 }
 else
 {   particles[i][j].color = Color(0,255,0, 0);}*/



//}

//}



void MyThing::Reset()
{
    particles =  vector<vector<ParticleState>> (SizeOfMesh, vector<ParticleState>(SizeOfMesh));
    for (int j = 0 ; j<SizeOfMesh; j++)
        for (int i = 0 ; i<SizeOfMesh; i++)
        {
            particles[i][j] = MyMesh.MakesMeshPoints()[i][j];
            cout << "Particles ( i " << i << ", j " << j <<") = ( " << particles[i][j].position.X() <<", " << particles[i][j].position.Y() <<", " << particles[i][j].position.Z() << ")\n";
            Xh[i][j] = particles[i][j].position;
        }
    
}



void MyThing::Usage()
{}

pba::PbaThing pba::CreateMyThing(){ return PbaThing( new MyThing() ); }


