//
// Created by szamani on 2/6/20.
//
#ifndef    MYGUARD_H
#define    MyGUARD_H


#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"


using namespace std;
namespace pba{


    

    class ParticleState
    {
    public:
       
        Vector position;
        Vector velocity;
        Vector acceleration;
        Color color;
        float mass;
  

    };
}
#endif
