//
// Created by Gabin on 12.05.2019.
//

#ifndef PARTICLEACCELERATOR_NODE_H
#define PARTICLEACCELERATOR_NODE_H

#include "Particle.h"
#include <memory>

class Node;

class Node{
private:
    Node* next_;
    Node* previous_;
    std::shared_ptr<Particle> particle_;
    double position_;
public:
    Node* next() const { return next_; }
    Node* previous() const { return previous_; }
    std::shared_ptr<Particle> particle() const { return particle_; }
    double position() const { return position_; }
    bool isHead() const { return particle_ == nullptr; }
    void exchangePlace(int n);

};

#endif //PARTICLEACCELERATOR_NODE_H
