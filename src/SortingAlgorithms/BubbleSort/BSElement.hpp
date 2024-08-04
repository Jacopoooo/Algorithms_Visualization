#pragma once

#include "SortingAlgorithms/ArrayElement.hpp"

class BSElement : public ArrayElement{
public:
	BSElement(const sf::Vector2f& size, const sf::Vector2f& position, size_t value, const sf::Color color, sf::Font& font, const sf::Color outline_color = sf::Color::Black, float outline_thickness = 3.0f);
	BSElement();

	size_t getValue() const override;
	void setValue(size_t new_value) override;

	const sf::Text& getTextIndex() const;

	void setFont(sf::Font& new_font, const std::string& path);

	void SetPosition(const sf::Vector2f& new_pos) override;
	void SetPosition(const float x, const float y) override;

	void Draw(sf::RenderWindow& window) const override;

private:
	sf::Text text_value;

	void setText(const sf::String& text, const sf::Font& font);
};

