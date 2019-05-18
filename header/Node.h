//
// Created by Gabin on 12.05.2019.
//

#ifndef PARTICLEACCELERATOR_NODE_H
#define PARTICLEACCELERATOR_NODE_H

#include "Particle.h"
#include <memory>
#include <iterator>

/**
 * The node class is used to create a double linked list.
 * Each instance is a node of the list and represents
 * one particle in the accelerator. A list has one head,
 * which has no particle attached to it. The list is
 * updated each timestep to assure that it is ordered
 * relative to the longitudinal positions of the particles.
 * The head is at the beginning of the accelerator.
 */

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
    virtual ~Node();

    /**
     * Give the next node in the list
     */
    Node* next() const { return next_; }
    /**
     * Give the previous node in the list
     */
    Node* previous() const { return previous_; }
    /**
     * Say if the list is empty, ie. if there is only the head.
     */
    bool empty() const { return this == next_; }
    /**
     * Give a pointer to the particle represented by
     * this node.
     */
    particle_ptdr particle() const { return particle_; }
    /**
     * Give the longitudinal position of the particle
     * represented by this node.
     */
    double position() const { return position_; }
    /**
     * Give the previous longitudinal position of the particle
     */
    double previousPosition() const { return previousPosition_; }
    /**
     * Update the longitudinal position of the particle
     */
    void updatePosition() { previousPosition_ = position_; position_ = particle()->longitudinalPosition(); }
    /**
     * Tell whether or not this node is the head
     */
    bool isHead() const { return particle_ == nullptr; }
    void exchangePlace(int n);
    /**
     * Exchange the place of this node with the node
     * given in argument in the list.
     */
    void exchangePlace(Node* node);
    /**
     * Exchange the place of this node with the next node
     * in the list.
     */
    void exchangeNext();
    /**
     * Insert a node in the right position
     * in the list and attach the particle in
     * argument to that new node.
     */
    void insertNode(particle_ptdr particle);
    /**
     * Remove the next node of the list
     */
    void removeNextNode();

    /**
     * This iterator is used to navigate in
     * the list. The start is at the first node
     * after the head, and the end is at the head.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, Node> {
    private:
        Node* list_ptr;
    public:
        explicit iterator(Node* n) : list_ptr(n) {}
        /**
         * The iterator goes to the next node
         */
        iterator& operator++() { list_ptr = list_ptr->next_; return *this; }
        /**
         * The iterator goes the previous node
         */
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
