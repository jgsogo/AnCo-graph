#pragma once

#include <map>
#include <tuple>
#include <algorithm>
#include <assert.h>
#include "graph_base.h"

namespace graph {

    template <class TNode, class TEdge, typename TNodeID>
    class graph : public graph_base<TNode, TEdge, TNodeID> {
        public:
            //using node_ptr = typename graph_base<TNode, TEdge, TNodeID>::node_ptr;
            //using edge_ptr = typename graph_base<TNode, TEdge, TNodeID>::edge_ptr;
            //using _t_node_id = typename graph_base<TNode, TEdge, TNodeID>::_t_node_id;
            typedef typename graph_base<TNode, TEdge, TNodeID>::node_ptr node_ptr;
            typedef typename graph_base<TNode, TEdge, TNodeID>::edge_ptr edge_ptr;
            typedef typename graph_base<TNode, TEdge, TNodeID>::_t_node_id _t_node_id;
            typedef typename graph_base<TNode, TEdge, TNodeID>::_t_edge _t_edge;
            typedef typename graph_base<TNode, TEdge, TNodeID>::_t_node _t_node;

            typedef typename std::map<_t_node_id, node_ptr> _t_node_map;
            /*
            struct edge_map_key {
                edge_map_key(const TNodeID init, const TNodeID end) : _init(init), _end(end) {
                    if (_init >= _end) {
                        std::swap(_init, _end);
                        }
                    }
                bool operator<(const edge_map_key& other) {
                    return ((_init < other._init) || ((_init==other._init) && (_end < other._end)))
                    }
                TNodeID _init, _end;
                };
            */
            typedef std::map<_t_node_id, std::vector<edge_ptr>> _t_edge_map;

        public:
            graph() {};
            ~graph() {};

            virtual node_ptr get_node(const _t_node_id& node_id) const {
                try {
                    return _node_map.find(node_id)->second;
                    }
                catch(...) {
                    throw not_found();
                    }
                }
            virtual int get_edges(const _t_node_id& node_id, std::pair<std::vector<edge_ptr>, std::vector<edge_ptr>>& edges) const {
                typename _t_edge_map::const_iterator it_out = _edges_outgoing.find(node_id);
                typename _t_edge_map::const_iterator it_in = _edges_incoming.find(node_id);
                if (it_out != _edges_outgoing.end()) {
                    edges.first = it_out->second;
                    }
                if (it_in != _edges_incoming.end()) {
                    edges.second = it_in->second;
                    }
                return edges.first.size() + edges.second.size();
                }
            virtual edge_ptr get_edge(const _t_node_id& node_id_1, const _t_node_id& node_id_2) const {
                typename _t_edge_map::const_iterator it = _edges_outgoing.find(node_id_1);
                if (it != _edges_outgoing.end()) {
                    typename _t_edge_map::mapped_type::const_iterator it_ret = std::find_if(it->second.begin(), it->second.end(), [&node_id_2](const edge_ptr& ptr){
                        return node_id_2 == ptr->end;
                        });
                    if (it_ret != it->second.end()) {
                        return *it_ret;
                        }
                    }
                throw not_found();
                }

            edge_ptr add_edge(const _t_node_id& node_id_1, const _t_node_id& node_id_2, const float& cost) {
                assert(_node_map.find(node_id_1) != _node_map.end());
                assert(_node_map.find(node_id_2) != _node_map.end());
                auto edge = std::make_shared<_t_edge>(node_id_1, node_id_2);
                edge->data.length = cost;
                if (std::find_if(_edges_incoming[node_id_2].begin(), _edges_incoming[node_id_2].end(), [this, &node_id_1](edge_ptr& ptr){
                        return (ptr->init == node_id_1);
                        }) == _edges_incoming[node_id_2].end()) {
                    _edges_incoming[node_id_2].push_back(edge);
                    _edges_outgoing[node_id_1].push_back(edge);
                    }
                return edge;
                }
            void delete_edge(const _t_node_id& node_id_1, const _t_node_id& node_id_2) {
                typename _t_edge_map::iterator it = _edges_outgoing.find(node_id_1);
                std::remove_if(it->second.begin(), it->second.end(), [&node_id_1, &node_id_2](const edge_ptr& ptr) {
                    assert(node_id_1 == ptr->init);
                    return node_id_2 == ptr->end;
                    });
                it = _edges_incoming.find(node_id_2);
                std::remove_if(it->second.begin(), it->second.end(), [&node_id_1, &node_id_2](const edge_ptr& ptr) {
                    assert(node_id_2 == ptr->end);
                    return node_id_1 == ptr->init;
                    });                
                }

            std::pair<typename _t_node_map::iterator, bool> add_node(const _t_node_id& node_id) {
                return _node_map.insert(std::make_pair(node_id, std::make_shared<_t_node>(node_id)));
                }

            void delete_node(const _t_node_id& node_id) {
                _node_map.erase(node_id);
                _edges_outgoing.erase(node_id);
                _edges_incoming.erase(node_id);
                }

            const _t_node_map& get_nodes() const { return _node_map;}
            const _t_edge_map& get_edges_outgoing() const { return _edges_outgoing;}
            const _t_edge_map& get_edges_incoming() const { return _edges_incoming;}
        protected:
            _t_node_map _node_map;
            _t_edge_map _edges_outgoing;
            _t_edge_map _edges_incoming;
        };

    }