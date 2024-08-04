#include "DijkstraVertex.hpp"

DijkstraVertex::DijkstraVertex(const float radius, const size_t id, const size_t neighbours_number, const sf::Vector2f& position, sf::Color color, sf::Color outline_color, const float outline_thickness) :
    GraphVertex(radius, id, neighbours_number, position, color){

    setOutlineColor(outline_color);
    setOutlineThickness(outline_thickness);
}

DijkstraVertex::DijkstraVertex() {}


size_t DijkstraVertex::GetDistance() const
{
    return _distance;
}

void DijkstraVertex::SetDistance(const size_t new_distance)
{
    _distance = new_distance;
    SetText(std::to_string(new_distance));

    _CenterText();
}

const sf::Text& DijkstraVertex::GetText() const
{
    return _render_distance;
}

void DijkstraVertex::SetText(const std::string& text)
{
    _render_distance.setString(text);
}


void DijkstraVertex::Draw(sf::RenderWindow& window) const
{
    window.draw(*this);
    window.draw(_render_distance);
}

void DijkstraVertex::InitText(const sf::Font& font)
{
    const size_t character_size = 30;
    const std::string infinity = "INF";

	_render_distance.setString(infinity);
	_render_distance.setFont(font);
	_render_distance.setCharacterSize(character_size);
	_render_distance.setFillColor(sf::Color::White);

    _CenterText();
}

DijkstraVertex& DijkstraVertex::operator=(const DijkstraVertex& other)
{
    if (this != &other) {
        GraphVertex::operator=(other);
        _distance = other._distance;
        _render_distance = other._render_distance;
        _CenterText();
    }
    return *this;
}

void DijkstraVertex::_CenterText()
{
    const sf::FloatRect text_bounds = _render_distance.getLocalBounds();

    _render_distance.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
    _render_distance.setPosition(GetCenter());
}
