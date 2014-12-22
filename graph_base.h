
#pragma once

#include <memory>
#include <map>
#include <vector>

#include "node.h"
#include "edge.h"


namespace graph {

    template <class TNode, class TEdge, typename TNodeID>
    class graph_base {
        public:
            typedef node<TNode, TNodeID> _t_node;
            typedef edge<TEdge> _t_edge;
            typedef TNodeID _t_node_id;

            typedef std::shared_ptr<_t_node> node_ptr;
            typedef std::shared_ptr<_t_edge> edge_ptr;

        public:
            graph_base() {};
            ~graph_base() {};

            virtual node_ptr get_node(const _t_node_id& node_id) const = 0;
            virtual int get_edges(const _t_node_id& node_id, std::pair<std::vector<edge_ptr>, std::vector<edge_ptr>>& edges) const = 0;
        
        };

    }