#pragma once

#include "SFML/Graphics.hpp"

class UnweightedEdge {
	
public:
	UnweightedEdge(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color color);

	const sf::VertexArray& GetDrawable() const;
	virtual void Explore(const sf::Color color);
	virtual void Draw(sf::RenderWindow& window, const sf::Transform& transform) const;
	virtual void Draw(sf::RenderWindow& window) const;

protected:
	sf::VertexArray _drawable = sf::VertexArray(sf::Lines, 2);
	sf::Color _color;
};