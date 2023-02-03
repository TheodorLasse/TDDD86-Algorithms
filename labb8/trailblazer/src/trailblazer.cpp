#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include <algorithm>
using namespace std;

// Builds a path from the nodes' previous values.
void buildPath(vector<Vertex*>& path, Vertex* end) {
    Vertex* current = end;
    do {
        path.push_back(current);
        current = current->previous;
    } while (current != nullptr);

    reverse(path.begin(), path.end());
}

// Recursive helper function for depthFirstSearch.
bool depthFirstSearchRecursive(vector<Vertex*>& path, BasicGraph& graph, Vertex* current, Vertex* end) {
    path.push_back(current);
    current->setColor(Color(GREEN));
    current->visited = true;

    if (current == end) {
        return true;
    }

    for (Vertex* vertex : graph.getNeighbors(current)) {
        if (vertex->visited) {
            continue;
        }
        if (depthFirstSearchRecursive(path, graph, vertex, end)) {
            return true;
        }
    }

    current->setColor(Color(GRAY));
    path.pop_back();
    return false;
}

// DFS.
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;

    depthFirstSearchRecursive(path, graph, start, end);
    return path;
}

// BFS.
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    Queue<Vertex*> queue;
    queue.enqueue(start);
    start->visited = true;

    while (!queue.isEmpty()) {
        Vertex* current = queue.dequeue();
        current->setColor(Color(GREEN));

        if (current == end) {
            break;
        }

        // Loop through neighbors and add them to the queue (if not visited).
        for (Vertex* neighbor : graph.getNeighbors(current)) {
            if (!neighbor->visited) {
                neighbor->previous = current;
                neighbor->visited = true;
                neighbor->setColor(Color(YELLOW));
                queue.enqueue(neighbor);
            }
        }
    }

    buildPath(path, end);
    return path;
}

// Dijkstras.
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> queue;
    queue.enqueue(start, 0);

    // Set all nodes costs to infinity.
    for (Vertex* v : graph.getNodeSet()) {
        v->cost = INFINITY;
    }
    // Seed value for start node.
    start->cost = 0;

    while (!queue.isEmpty()) {
        Vertex* current = queue.dequeue();
        current->visited = true;
        current->setColor(Color(GREEN));

        if (current == end) {
            break;
        }

        // Enqueue all neighbors with lower cost.
        for (Vertex* neighbor : graph.getNeighbors(current)) {
            double cost = graph.getEdge(current, neighbor)->cost + current->cost;

            if (cost < neighbor->cost) {
                neighbor->cost = cost;
                neighbor->previous = current;

                if (neighbor->visited) {
                    queue.changePriority(neighbor, cost);
                } else {
                    queue.enqueue(neighbor, cost);
                    neighbor->setColor(Color(YELLOW));
                }
            }
        }
    }

    buildPath(path, end);
    return path;
}

// A*
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> queue;
    queue.enqueue(start, 0);

    // Set all nodes costs to infinity.
    for (Vertex* v : graph.getNodeSet()) {
        v->cost = INFINITY;
    }
    // Set seed value for start node.
    start->cost = 0;

    while (!queue.isEmpty()) {
        Vertex* current = queue.dequeue();
        current->visited = true;
        current->setColor(Color(GREEN));

        if (current == end) {
            break;
        }

        // Add neighbors with lower cost.
        for (Vertex* neighbor : graph.getNeighbors(current)) {
            double cost = graph.getEdge(current, neighbor)->cost + current->cost;
            double h = neighbor->heuristic(end);

            if (cost < neighbor->cost) {
                neighbor->cost = cost;
                neighbor->previous = current;

                // Change priority if the neighbor is enqueued, or enqueue the neighbor.
                if (neighbor->visited) {
                    queue.changePriority(neighbor, cost + h);
                } else {
                    queue.enqueue(neighbor, cost + h);
                    neighbor->setColor(Color(YELLOW));
                }
            }
        }
    }

    buildPath(path, end);
    return path;
}
