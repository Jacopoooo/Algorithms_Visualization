#include "BSElement.hpp"

BSElement::BSElement(const sf::Vector2f& size, const sf::Vector2f& position, size_t value, const sf::Color color, sf::Font& font, const sf::Color outline_color, float outline_thickness) :
	ArrayElement(size, position, value, color) {

	setOutlineColor(outline_color);
	setOutlineThickness(outline_thickness);

	setText(std::to_string(value), font);
};

BSElement::BSElement() {
	setFillColor(sf::Color::White);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(3.0f);
};

size_t BSElement::getValue() const {
	return value;
}

void BSElement::setValue(size_t new_value) {
	value = new_value;
	setText(std::to_string(value), *text_value.getFont());
}

const sf::Text& BSElement::getTextIndex() const {
	return text_value;
};

void BSElement::setFont(sf::Font& new_font, const std::string& path) {
	if (!new_font.loadFromFile(path)) {
		LOG("An error occured while loading the font");
	}
}


void BSElement::SetPosition(const sf::Vector2f& new_pos) {
	setPosition(new_pos);
	setText(text_value.getString(), *text_value.getFont());
}

void BSElement::SetPosition(const float x, const float y) {
	setPosition(x, y);
	setText(text_value.getString(), *text_value.getFont());
}

void BSElement::Draw(sf::RenderWindow& window) const {
	window.draw(*this);
	window.draw(this->getTextIndex());
}

void BSElement::setText(const sf::String& text, const sf::Font& font) {
	text_value.setString(text);
	text_value.setFont(font);
	text_value.setCharacterSize(32);
	text_value.setFillColor(sf::Color::Black);
	sf::FloatRect text_bounds = text_value.getLocalBounds();
	float x_text = getPosition().x + getSize().x / 2 - text_bounds.width / 2 - text_bounds.left;
	float y_text = getPosition().y + getSize().y / 2 - text_bounds.height / 2 - text_bounds.top;
	sf::Vector2f text_position(x_text, y_text);
	text_value.setPosition(text_position);

}

