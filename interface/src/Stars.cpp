//
// Stars.cpp
// interface
//
// Created by Tobias Schwinger on 3/22/13.
// Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//

#include "InterfaceConfig.h"
#include "Stars.h"

#define __interface__Starfield_impl__
#include "starfield/Controller.h"
#undef __interface__Starfield_impl__

Stars::Stars() : 
    _controller(0l), _fileLoaded(false) { 
    _controller = new starfield::Controller; 
}

Stars::~Stars() { 
    delete _controller; 
}

bool Stars::readInput(const char* url, const char* cacheFile, unsigned limit) {
    _fileLoaded = _controller->readInput(url, cacheFile, limit); 
    return _fileLoaded;
}

bool Stars::setResolution(unsigned k) { 
    return _controller->setResolution(k); 
}

float Stars::changeLOD(float fraction, float overalloc, float realloc) { 
    return float(_controller->changeLOD(fraction, overalloc, realloc));
} 

void Stars::render(float fovY, float aspect, float nearZ, float alpha) {

    // determine length of screen diagonal from quadrant height and aspect ratio
    float quadrantHeight = nearZ * tan(angleConvert<Degrees,Radians>(fovY) * 0.5f);
    float halfDiagonal = sqrt(quadrantHeight * quadrantHeight * (1.0f + aspect * aspect));

    // determine fov angle in respect to the diagonal
    float fovDiagonal = atan(halfDiagonal / nearZ) * 2.0f;

    // pull the modelview matrix off the GL stack
    glm::mat4 view; glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(view)); 

    _controller->render(fovDiagonal, aspect, glm::affineInverse(view), alpha); 
}


