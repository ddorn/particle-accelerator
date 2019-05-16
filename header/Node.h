//
// Created by Gabin on 12.05.2019.
//

#ifndef PARTICLEACCELERATOR_NODE_H
#define PARTICLEACCELERATOR_NODE_H

#include "Particle.h"
#include <memory>

typedef std::shared_ptr<Particle> Particle_ptr;

class Node;

class Node{
private:
    Node* next_;
    Node* previous_;
    Particle_ptr particle_;
    double position_;
    double previousPosition_;
public:
    Node(Particle_ptr particle, double position) : particle_(particle), position_(position), previousPosition_(position) {}
    virtual ~Node();

    Node* next() const { return next_; }
    Node* previous() const { return previous_; }
    Particle_ptr particle() const { return particle_; }
    double position() const { return position_; }
    double previousPosition() const { return previousPosition_; }
    bool isHead() const { return particle_ == nullptr; }
    void exchangePlace(int n);
    void exchangePlace(Node* node);
    void exchangeNext();
    void insertNode(Particle_ptr particle);
    void removeNextNode();

};

#endif //PARTICLEACCELERATOR_NODE_H
