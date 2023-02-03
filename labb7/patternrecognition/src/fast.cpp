
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}


struct PointComperator {
    Point origin = Point(0, 0);

    bool operator() (const Point& a, const Point& b) const {
      return a.slopeTo(origin) < b.slopeTo(origin);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input6400.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Sorting Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    PointComperator comperator;
    vector<Point> sorted = points;
    int minimumDraw = 3;

    for (int p = 0 ; p < N ; p++) {
        comperator.origin = points[p];

        sort(sorted.begin(), sorted.end(), comperator);

        double currentSlope = sorted[0].slopeTo(comperator.origin);
        int sameSlopeCounter = 1;

        for (int i = 1; i < N; i++) {
            double slope = sorted[i].slopeTo(comperator.origin);

            if (slope == currentSlope) {
                sameSlopeCounter++;

            } else {
                if (sameSlopeCounter >= minimumDraw) {
                    render_line(scene, points[p], sorted[i - 1]);
                    a.processEvents(); // show rendered line
                }

                currentSlope = slope;
                sameSlopeCounter = 1;
            }
        }

        if (sameSlopeCounter >= minimumDraw) {
            render_line(scene, points[p], sorted[N - 1]);
            a.processEvents(); // show rendered line
        }

    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
