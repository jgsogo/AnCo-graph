
#pragma once

#include <memory>
#include <vector>

#include "node.h"
#include "edge.h"


namespace graph {

    class not_found : public std::exception {
        public:
            //not_found(
            virtual const char* what() const throw() {
                return "graph::not_found";
                }
        };

    template <class TNode, class TEdge, typename TNodeID>
    class graph_base {
        public:
            typedef TNodeID _t_node_id;
            typedef node<TNode, _t_node_id> _t_node;
            typedef std::shared_ptr<_t_node> node_ptr;

            typedef edge<TEdge, _t_node_id> _t_edge;
            typedef std::shared_ptr<_t_edge> edge_ptr;

        public:
            graph_base() {};
            ~graph_base() {};

            virtual node_ptr get_node(const _t_node_id& node_id) const = 0;
            virtual int get_edges(const _t_node_id& node_id, std::pair<std::vector<edge_ptr>, std::vector<edge_ptr>>& edges) const = 0;
            virtual edge_ptr get_edge(const _t_node_id& node_id_1, const _t_node_id& node_id_2) const = 0;
        
        };

    }