//
// Created by Gabin on 12.05.2019.
//

#include "Node.h"

void Node::exchangePlace(int n){
    Node* other(this);
    if(n > 0){
        for(int i(0); i < n; ++i){
            other = other->next();
        }
    } else{
        for(int i(0); i < -n; ++i){
            other = other->previous();
        }
    }
    double otherPos(other->position());
    other->position_ = this->position();
    this->position_ = otherPos;
    this->particle_.swap(other->particle_);
}

void Node::insertNode(Particle_ptr particle, double position) {
    if(particle == nullptr) return;
    Node* newNode = new Node(particle, position);
    newNode->previous_ = this;
    newNode->next_ = this->next();
    this->next_->previous_ = newNode;
    this->next_ = newNode;
}
