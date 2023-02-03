#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

// Class containing points and the connections between them.
// Also contains functions for displaying and inserting points.
class Tour {
public:

    // Creates a new tour with 4 points.
    Tour(Point p1, Point p2, Point p3, Point p4);
    // Creates a new empty tour.
    Tour();
    // Removes all points from the tour.
    ~Tour();
    // Prints all points in the tour.
    void show();
    // Draws the tour to a QGraphicsScene.
    void draw(QGraphicsScene* scene);
    // Returns the number of points in the tour.
    int size();
    // Returns the total distance of the tour.
    double distance();
    // Inserts a new point with the shortes distance to the latest node.
    void insertNearest(Point p);
    // Inserts a new point with the smallest distance increase of the tour.
    void insertSmallest(Point p);

private:
    Node* first;
};

#endif // TOUR_H
