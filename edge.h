#pragma once

namespace graph {
    
    template <class TEdge>
    class edge {
        public:
            edge() {};
            edge(const TEdge& edge) : _data(edge) {};
            ~edge() {};

        protected:
            TEdge _data;
        };
    }