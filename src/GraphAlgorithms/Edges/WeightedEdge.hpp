#pragma once

#include "UnweightedEdge.hpp"
#include "Constants.hpp"

class WeightedEdge : public UnweightedEdge {
public:
	WeightedEdge(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color color);
	WeightedEdge();

	void Init(const sf::Font& font, const size_t character_size, const size_t weight);
	size_t GetWeight() const;
	float GetLength() const;

	void Draw(sf::RenderWindow& window) const override;

private:
	sf::Text _render_weight;
	size_t _weight = static_cast<size_t>(-1); // returns max size of size_t

	void _InitText(const sf::Font& font, const size_t character_size);
};