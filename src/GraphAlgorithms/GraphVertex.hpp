#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "Constants.hpp"

class GraphVertex : public sf::CircleShape {
public:

	GraphVertex(const float radius, const size_t id, const size_t neighbours_number, const sf::Vector2f& position, sf::Color color);
	GraphVertex();

	const std::vector<size_t>& GetNeighbors() const;
	void AddNeighbor(const size_t neighbour_id);
	bool CheckIfAlreadyANeighbour(const size_t neighbour_id) const;

	bool IsExplored() const;
	virtual void Explore(const sf::Color color);

	size_t GetId() const;
	void SetId(const size_t new_id);

	const sf::Vector2f& GetCenter() const;

	virtual void DrawWithTransform(sf::RenderWindow& window, const sf::Transform& transform) const;
	virtual void Draw(sf::RenderWindow& window) const;

	static float EuclideanDistance(const GraphVertex* v1, const GraphVertex* v2);

	GraphVertex& operator=(const GraphVertex& other);

protected:
	bool _explored = false;
	std::vector<size_t> _neighbours_id;
	size_t _id;
	sf::Vector2f _center;
};

