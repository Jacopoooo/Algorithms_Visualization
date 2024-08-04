#include "UnweightedEdge.hpp"

UnweightedEdge::UnweightedEdge(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color color)
{
	_drawable[0].position = start;
	_drawable[1].position = end;

	_drawable[0].color = color;
	_drawable[1].color = color;
}

const sf::VertexArray& UnweightedEdge::GetDrawable() const
{
	return _drawable;
}

void UnweightedEdge::Explore(const sf::Color color)
{
	if (_color != color) {
		_color = color;

		_drawable[0].color = _color;
		_drawable[1].color = _color;
	}
}

void UnweightedEdge::Draw(sf::RenderWindow& window, const sf::Transform& transform) const
{
	window.draw(_drawable, transform);
}

void UnweightedEdge::Draw(sf::RenderWindow& window) const
{
	window.draw(_drawable);
}

