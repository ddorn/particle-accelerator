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