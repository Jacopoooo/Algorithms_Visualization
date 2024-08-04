#pragma once

#include "GraphVertex.hpp"
#include "Edges/UnweightedEdge.hpp"
#include "PairHash.cpp"
#include <unordered_map>

template<typename VertexType, typename EdgeType>
class GraphAlgorithm {
    static_assert(std::is_base_of<GraphVertex, VertexType>::value, "VertexType must derive from GraphVertex");
    static_assert(std::is_base_of<UnweightedEdge, EdgeType>::value, "EdgeType must derive from UnweightedEdge");

public:
    GraphAlgorithm(const size_t vertices_number, const size_t neighbors_number);
    virtual ~GraphAlgorithm() = default;

    virtual void Play() = 0;

protected:
    sf::RenderWindow _window;

    std::unordered_map<std::pair<size_t, size_t>, EdgeType, PairHash> _edges;
    std::vector<VertexType> _vertices;

    const size_t _neighbors_number;

    void _SetNeighboursWithKNN(const sf::Color edge_color, const size_t starting_node_index = 0, bool start_from_end = false);
    std::pair<size_t, size_t> _GetEdgeKey(const size_t node_id, const size_t neighbour_id) const;
    virtual bool _ExploreEdge(const size_t node_id, const size_t neighbour_id, const sf::Color explore_color);
    virtual void _AddEdge(const size_t node_id, const size_t neighbour_id, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color edge_color) = 0;
    virtual void _InitGraph() = 0;
    virtual void _InitVertices() = 0;
    virtual void _Display() = 0;
};

template<typename VertexType, typename EdgeType>
GraphAlgorithm<VertexType, EdgeType>::GraphAlgorithm(size_t vertices_number, const size_t neighbors_number) : 
    _neighbors_number(neighbors_number), _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Algorithms visualization") {
    _vertices.resize(vertices_number);
}


template<typename VertexType, typename EdgeType>
inline bool GraphAlgorithm<VertexType, EdgeType>::_ExploreEdge(const size_t node_id, const size_t neighbour_id, const sf::Color explore_color)
{
    std::pair<size_t, size_t> key = _GetEdgeKey(node_id, neighbour_id);
    
    if (key.first != key.second)
    {
        auto it = _edges.find(key);
        it->second.Explore(explore_color);
        return true;
    }
    
    return false;
}


template<typename VertexType, typename EdgeType>
inline std::pair<size_t, size_t> GraphAlgorithm<VertexType, EdgeType>::_GetEdgeKey(const size_t node_id, const size_t neighbour_id) const {

    std::pair<size_t, size_t> key(node_id, neighbour_id);

    if (_edges.find(key) == _edges.end()) {
        key = { neighbour_id, node_id };
    }

    if (_edges.find(key) != _edges.end()) return key;
    else return std::pair<size_t, size_t>();
}


template<typename VertexType, typename EdgeType>
inline void GraphAlgorithm<VertexType, EdgeType>::_SetNeighboursWithKNN(const sf::Color edge_color, const size_t starting_node_index, bool start_from_end)
{
    if (start_from_end) {
        for (size_t i = starting_node_index; i > 0; i--) {

            if (_vertices[i].GetNeighbors().size() == _neighbors_number) {
                continue;
            }

            std::vector<std::pair<float, size_t>> distances;
            distances.reserve(i - 1);

            for (int j = i - 1; j >= 0; j--) {
                float distance = GraphVertex::EuclideanDistance(&_vertices[i], &_vertices[j]);
                distances.emplace_back(distance, j);
            }

            const size_t sort_size = std::min(distances.size(), _neighbors_number);

            std::partial_sort(distances.begin(), distances.begin() + sort_size, distances.end());

            for (const auto& edge : distances) {

                if (_vertices[i].GetNeighbors().size() == _neighbors_number) {
                    break;
                }

                size_t j = edge.second;

                if (_vertices[j].GetNeighbors().size() == _neighbors_number) {
                    continue;
                }

                if (!_vertices[i].CheckIfAlreadyANeighbour(j)) {
                    _AddEdge(i, j, _vertices[i].GetCenter(), _vertices[j].GetCenter(), edge_color);
                }

            }
        }
    }
    else {
        for (size_t i = starting_node_index; i  < _vertices.size() - 1; ++i) {

            if (_vertices[i].GetNeighbors().size() == _neighbors_number) {
                continue;
            }

            std::vector<std::pair<float, size_t>> distances;
            distances.reserve(_vertices.size() - i - 1);

            for (int j = i + 1; j < _vertices.size(); ++j) {
                float distance = GraphVertex::EuclideanDistance(&_vertices[i], &_vertices[j]);
                distances.emplace_back(distance, j);
            }

            const size_t sort_size = std::min(distances.size(), _neighbors_number);

            std::partial_sort(distances.begin(), distances.begin() + sort_size, distances.end());

            for (const auto& edge : distances) {

                if (_vertices[i].GetNeighbors().size() == _neighbors_number) {
                    break;
                }

                size_t j = edge.second;

                if (_vertices[j].GetNeighbors().size() == _neighbors_number) {
                    continue;
                }

                if (!_vertices[i].CheckIfAlreadyANeighbour(j)) {
                    _AddEdge(i, j, _vertices[i].GetCenter(), _vertices[j].GetCenter(), edge_color);
                }

            }
        }
    }
 
}

template class GraphAlgorithm<GraphVertex, UnweightedEdge>; // For the compiler