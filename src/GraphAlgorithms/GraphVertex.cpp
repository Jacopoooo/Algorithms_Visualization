#include "GraphVertex.hpp"


GraphVertex::GraphVertex(const float radius, const size_t id, const size_t neighbours_number, const sf::Vector2f& position, sf::Color color) : CircleShape(radius), _id(id), _center(position + sf::Vector2f(radius, radius))
{
	setPosition(position);
	setFillColor(color);

	_neighbours_id.reserve(neighbours_number);
}

GraphVertex::GraphVertex() : _id(0) {}

const std::vector<size_t>& GraphVertex::GetNeighbors() const
{
	return _neighbours_id;
}

void GraphVertex::AddNeighbor(const size_t neighbour_id)
{
	_neighbours_id.emplace_back(neighbour_id);
}

bool GraphVertex::CheckIfAlreadyANeighbour(const size_t neighbour_id) const
{
	auto it = std::find(_neighbours_id.begin(), _neighbours_id.end(), neighbour_id);
	return it != _neighbours_id.end();
}

bool GraphVertex::IsExplored() const
{
	return _explored;
}

void GraphVertex::Explore(const sf::Color color)
{
	if (!_explored) {
		_explored = true;

		setFillColor(color);
	}
}

size_t GraphVertex::GetId() const
{
	return _id;
}

void GraphVertex::SetId(const size_t new_id)
{
	_id = new_id;
}

const sf::Vector2f& GraphVertex::GetCenter() const
{
	return _center;
}

void GraphVertex::DrawWithTransform(sf::RenderWindow& window, const sf::Transform& transform) const
{
	window.draw(*this, transform);
}

void GraphVertex::Draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

float GraphVertex::EuclideanDistance(const GraphVertex* v1, const GraphVertex* v2)
{
	return sqrt(std::pow((v1->_center.x - v2->_center.x), 2) + std::pow((v1->_center.y - v2->_center.y), 2));
}

GraphVertex& GraphVertex::operator=(const GraphVertex& other)
{
	if (this != &other) {
		CircleShape::operator=(other); 
		_id = other._id;
		_neighbours_id = other._neighbours_id;
		_explored = other._explored;
		_center.x = other._center.x;
		_center.y = other._center.y;
	}
	return *this;
}

