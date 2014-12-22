#pragma once

namespace graph {
    
    template <class TEdge, typename TNodeID>
    class edge {
        public:
            edge(const TNodeID& n1, const TNodeID& n2) : init(n1), end(n2) {};
            edge(const TNodeID& n1, const TNodeID& n2, const TEdge& edge) : init(n1), end(n2), _data(edge) {};
            ~edge() {};

            const TNodeID init;
            const TNodeID end;
        protected:
            TEdge _data;
            
        };
    }