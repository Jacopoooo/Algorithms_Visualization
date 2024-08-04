#pragma once

#include "GraphAlgorithms/GraphVertex.hpp"


class Node : public GraphVertex {

public:
	Node(const float radius, const size_t id, const size_t neighbours_number, const sf::Vector2f& position, sf::Color color, sf::Color outline_color = sf::Color::White, const float outline_thickness = 3.0f);
	Node();

	const sf::Text& GetText() const;
	void SetText(size_t text_number, const sf::Font& font);
	size_t GetTextNumber() const;

	void SetPosition(const sf::Vector2f& new_position);
	void SetPosition(const float x, const float y);

	void DrawWithTransform(sf::RenderWindow& window, const sf::Transform& transform) const override;

	Node& operator=(const Node& other);

private:
	sf::Text _render_number;
};