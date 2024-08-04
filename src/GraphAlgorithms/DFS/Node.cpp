#include "Node.hpp"

Node::Node(const float radius, const size_t id, const size_t neighbours_number, const sf::Vector2f& position, sf::Color color, sf::Color outline_color, const float outline_thickness) : GraphVertex(radius, id, neighbours_number, position, color) {
	setOutlineColor(outline_color);
	setOutlineThickness(outline_thickness);
}

Node::Node() {}


const sf::Text& Node::GetText() const {
	return _render_number;
}


size_t Node::GetTextNumber() const {
	const std::string str = _render_number.getString();
	return std::stoi(str);
}


void Node::SetText(const size_t text_number, const sf::Font& font) {
	_render_number.setString(sf::String(std::to_string(text_number)));
	_render_number.setFont(font);
	_render_number.setCharacterSize(18);
	_render_number.setFillColor(sf::Color::White);

	// Centrare il testo
	const sf::FloatRect text_bounds = _render_number.getLocalBounds();

	_render_number.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
	_render_number.setPosition(GetCenter());
}


void Node::SetPosition(const sf::Vector2f& new_position) {
	setPosition(new_position);
	_render_number.setPosition(new_position);
}


void Node::SetPosition(const float x, const float y) {
	setPosition(x, y);
	_render_number.setPosition(x, y);
}

void Node::DrawWithTransform(sf::RenderWindow& window, const sf::Transform& transform) const
{
	window.draw(*this, transform);
	window.draw(_render_number, transform);
}

Node& Node::operator=(const Node& other)
{
	if (this != &other) {
		GraphVertex::operator=(other);  
		_render_number = other._render_number;
	}
	return *this;
}
