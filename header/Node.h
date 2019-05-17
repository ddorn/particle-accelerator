//
// Created by Gabin on 12.05.2019.
//

#ifndef PARTICLEACCELERATOR_NODE_H
#define PARTICLEACCELERATOR_NODE_H

#include "Particle.h"
#include <memory>
#include <iterator>

typedef std::shared_ptr<Particle> particle_ptdr;

class Node;

class Node{
private:
    Node* next_;
    Node* previous_;
    particle_ptdr particle_;
    double position_;
    double previousPosition_;
public:
    Node() : next_(this), previous_(this), particle_(nullptr), position_(0), previousPosition_(0) {}
    Node(particle_ptdr particle, double position) : particle_(particle), position_(position), previousPosition_(position) {}
    Node(const Node &) = delete;
    void operator=(const Node &) = delete;
    ~Node();

    Node* next() const { return next_; }
    Node* previous() const { return previous_; }
    bool empty() const { return this == next_; }
    particle_ptdr particle() const { return particle_; }
    double position() const { return position_; }
    double previousPosition() const { return previousPosition_; }
    void updatePosition() { previousPosition_ = position_; position_ = particle()->longitudinalPosition(); }
    bool isHead() const { return particle_ == nullptr; }
    void exchangePlace(int n);
    void exchangePlace(Node* node);
    void exchangeNext();
    void insertNode(particle_ptdr particle);
    void removeNextNode();

    class iterator : public std::iterator<std::forward_iterator_tag, Node> {
    private:
        Node* list_ptr;
    public:
        explicit iterator(Node* n) : list_ptr(n) {}
        iterator& operator++() { list_ptr = list_ptr->next_; return *this; }
        iterator& operator--() { list_ptr = list_ptr->previous_; return *this; }
        bool operator==(iterator const& rhs) const { return this->list_ptr == rhs.list_ptr; }
        bool operator!=(iterator const& rhs) const { return !(*this == rhs); }
        Node& operator*() const { return *list_ptr; }
        Node* operator->() const { return list_ptr; }
    };

    iterator begin();
    iterator end();
};

#endif //PARTICLEACCELERATOR_NODE_H
