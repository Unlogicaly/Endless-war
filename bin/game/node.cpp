//
// Created by tarog on 31.10.2019.
//

#include "node.h"

Node::Node(std::string name, double weight, std::vector<Node *> nodes) :
        name{std::move(name)}, weight{weight}
{
    for (auto &n: nodes) link(*n);
}

std::vector<std::string> Node::get_neighbours() {
    std::vector<std::string> neighbours;
    for (auto &node: available_nodes)
    {
        neighbours.push_back(node->get_name());
    }
    return neighbours;
}

void Node::link(Node &node) {
    this->add_node(node);
    node.add_node(*this);
}

void Node::add_node(Node &node) {
    for (auto &n: available_nodes) if (node.get_name() == n->get_name()) return;
    available_nodes.push_back(&node);
}
