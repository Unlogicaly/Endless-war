//
// Created by tarog on 31.10.2019.
//

#ifndef UNTITLED2_NODE_H
#define UNTITLED2_NODE_H

#include <vector>
#include <string>

class Node
{
private:
    std::string name;
    double weight;
    std::vector<Node*> available_nodes;

public:
    explicit Node(std::string name, double weight = 0, std::vector<Node*> nodes = {});

    virtual std::string get_name() const {return name;}

    double get_weight() {return weight;}

    std::vector<Node> get_neighbours();

    void link(Node &node);

    void add_node(Node &node);

    bool operator < (Node n) {return this->get_weight() < n.get_weight();}
    bool operator > (Node n) {return this->get_weight() > n.get_weight();}
};

#endif //UNTITLED2_NODE_H
