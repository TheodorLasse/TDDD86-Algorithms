#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(Point p1, Point p2, Point p3, Point p4)
{
    Node* n1 = new Node(p1);
    Node* n2 = new Node(p2);
    Node* n3 = new Node(p3);
    Node* n4 = new Node(p4);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n1;

    first = n1;
}

Tour::Tour() {
    first = nullptr;
}

Tour::~Tour()
{
    Node *current = first;

    while (current->next != current) {
        Node *toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;

        current = current->next;
    }

    delete current;
}

void Tour::show()
{
    Node *current = first;

    do {
        cout << current->point.toString() << endl;
        current = current->next;
    } while (current != first);
}

void Tour::draw(QGraphicsScene *scene)
{
    Node *current = first;

    do {
        current->point.drawTo(current->next->point, scene);
        current = current->next;
    } while (current != first);
}

int Tour::size()
{
    int size = 0;
    Node *current = first;

    do {
        size++;
        current = current->next;
    } while (current != first);

    return size;
}

double Tour::distance()
{
    double dist = 0;
    Node *current = first;

    do {
        dist += current->point.distanceTo(current->next->point);
        current = current->next;
    } while (current != first);

    return dist;
}

void Tour::insertNearest(Point p)
{
    Node *closest = nullptr;
    double closestDist = numeric_limits<double>::infinity();

    // If no first node
    if (first == nullptr) {
        first = new Node(p, nullptr);
        first->next = first;
        return;
    }

    Node *current = first;

    do {
        double dist = current->point.distanceTo(p);
        if (dist < closestDist) {
            closest = current;
            closestDist = dist;
        }
        current = current->next;
    } while (current != first);

    Node *newNode = new Node(p, closest->next);
    closest->next = newNode;
}

void Tour::insertSmallest(Point p)
{
    // If no first node
    if (first == nullptr) {
        first = new Node(p, nullptr);
        first->next = first;
        return;
    }

    Node *minDiffNode = nullptr;
    double minDiff = numeric_limits<double>::infinity();

    Node *current = first;

    do {
        double currentDist = current->point.distanceTo(current->next->point);
        double newDist = current->point.distanceTo(p) + current->next->point.distanceTo(p);

        double diff = newDist - currentDist;

        if (diff < minDiff) {
            minDiffNode = current;
            minDiff = diff;
        }

        current = current->next;
    } while (current != first);

    Node *newNode = new Node(p, minDiffNode->next);
    minDiffNode->next = newNode;
}
