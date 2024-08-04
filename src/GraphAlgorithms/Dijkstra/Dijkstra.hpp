#pragma once 

#include "GraphAlgorithms/GraphAlgorithm.hpp"
#include "DijkstraVertex.hpp"
#include "GraphAlgorithms/Edges/WeightedEdge.hpp"
#include <queue>
#include <random>
#include <set>
#include "Line.hpp"


class Dijkstra : public GraphAlgorithm<DijkstraVertex, WeightedEdge> {
public:
	Dijkstra(const size_t vertices_number, const size_t neighbors_number);
	void Play() override;

	static const size_t GRAPH_BOUNDS_HEIGHT = 500;
	static const size_t EDGES_CHARACTER_SIZE = 30;	
	static const size_t NODES_RADIUS = 30;
	static const size_t DESTINATION_REACHED_TEXT_CHARACTER_SIZE = 150;
	
	static const uint32_t SOURCE_COLOR = 0x8000FFFF;
	static const uint32_t DESTINATION_COLOR = 0x8000FFFF;

	static const uint32_t EDGES_COLOR = 0x0000FFFF;
	static const uint32_t NODES_COLOR = 0x0000FFFF;

	static const uint32_t EXPLORED_EDGES_COLOR = 0xFF0000FF;
	static const uint32_t EXPLORED_NODES_COLOR = 0xFF0000FF;

	static const uint32_t BEST_PATH_EDGES_COLOR = 0x8000FFFF;
	static const uint32_t BEST_PATH_NODES_COLOR = 0x8000FFFF;

	static const uint32_t DESTINATION_REACHED_TEXT_COLOR = 0xFFFFFFFF;

private:
	std::vector<size_t> _previous;
	sf::RectangleShape _rect;
	sf::Font _font;
	sf::Text _render_destination_reached;
	sf::Transform _transform;
	sf::Vector2f _bounds_range;
	size_t _source_id;
	size_t _destination_id;

	void _InitVertices() override;
	bool _LoadFont();
	bool _SetSourceAndDestinationFromUserInput(const sf::Event& event);
	bool _SetGraphBounds(const sf::Event& event);
	void _SetRectBounds();
	void _SetBoundsRange();
	void _InitGraph() override;
	void _SetEdges();
	void _AddEdge(const size_t node_id, const size_t neighbour_id, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color edge_color) override;
	void _Display() override;
	void _Dijkstra();
	void _DisplayBestPath(bool destination_reached);
	void _InitDestinationReachedText(const std::string& text, const sf::Vector2f pos);
};