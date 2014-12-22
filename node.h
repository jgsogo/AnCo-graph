#pragma once

namespace graph {
    
    template <class TNode, typename TNodeID>
    class node {
        public:
            node(const TNodeID& id_) : id(id_) {};
            node(const TNodeID& id_, const TNode& data) : id(id_), _data(data) {};
            ~node() {};

            const TNodeID id;
        protected:
            TNode _data;
        };
    }