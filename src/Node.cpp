//
// Created by Gabin on 12.05.2019.
//

#include <Node.h>

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
    exchangePlace(other);
}
void Node::exchangePlace(Node* other){
    other->previous()->next_ = this;
    other->next()->previous_ = this;
    this->previous()->next_ = other;
    this->next()->previous_ = other;

    Node* otherNext(other->next());
    Node* otherPrevious(other->previous());
    other->next_ = this->next();
    other->previous_ = this->previous();
    this->next_ = otherNext;
    this->previous_ = otherPrevious;
}

void Node::insertNode(Particle_ptr particle, double position) {
    if(particle == nullptr) return;

    if(position < next()->position() or next()->isHead()) {
        Node *newNode = new Node(particle, position);
        newNode->previous_ = this;
        newNode->next_ = this->next();
        this->next_->previous_ = newNode;
        this->next_ = newNode;
    } else{
        next()->insertNode(particle, position);
    }
}

Node::~Node() {
    if(isHead()){
        while(!next()->isHead()){
            next()->~Node();
        }
    } else {
        previous()->next_ = next();
        next()->previous_ = previous();
        particle_.~shared_ptr();
    }
}