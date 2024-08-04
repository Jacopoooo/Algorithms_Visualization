#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class ArrayElement : public sf::RectangleShape {
public:
	ArrayElement(const sf::Vector2f& size, const sf::Vector2f& position, size_t value, sf::Color color);
	ArrayElement();

	virtual size_t getValue() const;
	virtual void setValue(size_t new_value);

	virtual void SetPosition(const sf::Vector2f& new_pos);
	virtual void SetPosition(const float x, const float y);

	virtual void Draw(sf::RenderWindow& window) const;

protected:
	size_t value;
	sf::Vector2f position;
};

