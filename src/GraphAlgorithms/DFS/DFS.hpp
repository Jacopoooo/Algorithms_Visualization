#pragma once

#include "GraphAlgorithms/GraphAlgorithm.hpp"
#include "Node.hpp"
#include "Spiral.hpp"
#include <stack>

class DFS : public GraphAlgorithm<Node, UnweightedEdge> {
public:
	DFS(const size_t vertices_number, const size_t neighbors_number);
	~DFS();
	
	void Play() override;

	static const size_t NODES_RADIUS = 15;
	
	static const uint32_t EXPLORE_NODE_COLOR = 0xFF0000FF;
	static const uint32_t EXPLORE_EDGE_COLOR = 0xFF0000FF;

	static const uint32_t NODE_COLOR = 0x0000FFFF;
	static const uint32_t EDGE_COLOR = 0x0000FFFF;

private:
	sf::Font _font;
	sf::Transform _transform;

	sf::Text _render_vertices_number;
	sf::Text _render_iterations_number;
	sf::Text _render_used_edges_number;

	size_t _iterations = 0;
	size_t _explored_edges = 0;

	void _InitVertices() override;
	void _InitGraph() override;
	void _AddEdge(const size_t node_id, const size_t neighbour_id, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color edge_color) override;
	void _KNN(const size_t starting_node_index);
	bool _LoadFont();
	void _SetScalingFactors(const Spiral& spiral, const float margin); 
	void _InitText(const sf::Vector2f& pos, sf::Text& render_text, const size_t character_size, const std::string& text) const;
	void _UpdateIterationsText();
	void _UpdateExploredEdgesText();
	void _Display() override;
	void _DFS(const size_t node_id);
};