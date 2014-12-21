#pragma once

#include "graph_base.h"

namespace graph {

    template <class TNode, class TEdge, typename TNodeID>
    class graph : public graph_base<TNode, TEdge, TNodeID> {
        public:
            using node_ptr = typename graph_base<TNode, TEdge, TNodeID>::node_ptr;
            using edge_ptr = typename graph_base<TNode, TEdge, TNodeID>::edge_ptr;
            using _t_node_id = typename graph_base<TNode, TEdge, TNodeID>::_t_node_id;

        public:
            graph() {};
            ~graph() {};

            virtual node_ptr get_node(const _t_node_id& node_id) {
                return _node_map.find(node_id)->second;
                }
            virtual int get_edges(const _t_node_id& node_id, std::pair<std::vector<edge_ptr>, std::vector<edge_ptr>>& edges) {
                edges.first = _edges_outgoing.find(node_id)->second;
                edges.second = _edges_incoming.find(node_id)->second;
                return edges.first.size() + edges.second.size();
                }

        protected:
            std::map<_t_node_id, node_ptr> _node_map;
            std::map<_t_node_id, std::vector<edge_ptr>> _edges_outgoing;
            std::map<_t_node_id, std::vector<edge_ptr>> _edges_incoming;
        };

    }