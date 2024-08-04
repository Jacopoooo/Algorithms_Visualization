#include "WeightedEdge.hpp"

WeightedEdge::WeightedEdge(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color color) :
	UnweightedEdge(start, end, color) {}

WeightedEdge::WeightedEdge() : UnweightedEdge(sf::Vector2f(0, 0), sf::Vector2f(1000, 1000), sf::Color::Magenta)
{
	
}

void WeightedEdge::Draw(sf::RenderWindow& window) const 
{ 
	window.draw(_drawable);
	window.draw(_render_weight);
}

void WeightedEdge::Init(const sf::Font& font, const size_t character_size, const size_t weight)
{
	_weight = weight;
	_InitText(font, character_size);
}

size_t WeightedEdge::GetWeight() const
{
	return _weight;
}

float WeightedEdge::GetLength() const
{
	const float x1 = _drawable[0].position.x;
	const float x2 = _drawable[1].position.x;

	const float y1 = _drawable[0].position.y;
	const float y2 = _drawable[1].position.y;

	return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}



void WeightedEdge::_InitText(const sf::Font& font, const size_t character_size)
{
	_render_weight.setString(sf::String(std::to_string(_weight)));
	_render_weight.setFont(font);
	_render_weight.setCharacterSize(character_size);
	_render_weight.setFillColor(sf::Color::White);

	const sf::FloatRect text_bounds = _render_weight.getLocalBounds();

	_render_weight.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);

	const float mid_x = (_drawable[0].position.x + _drawable[1].position.x) / 2;
	const float mid_y = (_drawable[0].position.y + _drawable[1].position.y) / 2;

	_render_weight.setPosition(sf::Vector2f(mid_x, mid_y));
}

