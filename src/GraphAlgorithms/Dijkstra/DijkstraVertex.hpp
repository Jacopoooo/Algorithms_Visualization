#pragma once

#include "GraphAlgorithms/GraphVertex.hpp"

class DijkstraVertex : public GraphVertex {
public:
	DijkstraVertex(const float radius, const size_t id, const size_t neighbours_number, const sf::Vector2f& position, sf::Color color, sf::Color outline_color = sf::Color::White, const float outline_thickness = 3.0f);
	DijkstraVertex();

	size_t GetDistance() const;
	void SetDistance(const size_t new_distance);

	const sf::Text& GetText() const;
	void SetText(const std::string& text);

	void Draw(sf::RenderWindow& window) const override;

	void InitText(const sf::Font& font);

	DijkstraVertex& operator=(const DijkstraVertex& other);

private:
	sf::Text _render_distance;
	size_t _distance = static_cast<size_t>(-1); // returns the max value for size_t

	void _CenterText();
};