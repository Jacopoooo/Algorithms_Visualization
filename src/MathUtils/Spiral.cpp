#include "Spiral.hpp"

Spiral::Spiral(const float a, const float b, const size_t num_points, const float space_between_elements) : 
    _a(a), _b(b), _num_points(num_points), _dr(_a* (2 * PI)), _radius(_b), _space_between_elements(space_between_elements)
{
    _InitDrawable();
    _InitElementsNumberInLastTurn();
}

const std::vector<sf::Vector2f>& Spiral::GetDrawable() const
{
    return _drawable;
}

float Spiral::GetRadius() const
{
    return _radius;
}

size_t Spiral::GetNumPoints() const
{
    return _num_points;
}


float Spiral::GetSpaceBetweenElements() const
{
    return _space_between_elements;
}

void Spiral::_InitDrawable()
{
    _drawable.reserve(_num_points); 

    for (int i = 0; i < _num_points; ++i) {
        float x = _radius * std::cos(_theta);
        float y = _radius * std::sin(_theta);

        _drawable.emplace_back(x, y);

        // teorema di pitagora utilizzando le coordinate radiali al quadrato (dr)^2 sommate alle coordinate lineari al quadrato (2*PI*r)^2.
        // è la lunghezza dell'arco disegnato dalla spirale in un giro (misurato in radianti: 2*PI)
        float arc_length = std::sqrt(_dr * _dr + _radius * _radius * (2 * PI) * (2 * PI));

        float delta_theta = (_space_between_elements / arc_length) * (2 * PI); // variazione angolare necessaria per coprire la distanza voluta

        _theta += delta_theta;

        _radius = _a * _theta + _b;
    }

}

void Spiral::_InitElementsNumberInLastTurn() 
{
    float last_turn_radius = _radius - _dr;
    float last_turn_theta = _theta - 2*PI;
    size_t elements_in_last_turn = 0;


    while (last_turn_theta <= _theta) {
        float arc_length = std::sqrt(_dr * _dr + last_turn_radius * last_turn_radius * (2 * PI) * (2 * PI));

        float delta_theta = (_space_between_elements / arc_length) * (2 * PI);

        last_turn_theta += delta_theta;

        last_turn_radius = _a * last_turn_theta + _b;
        elements_in_last_turn++;
    }

    _elements_in_last_turn = elements_in_last_turn;
}

size_t Spiral::GetElementsNumberInLastTurn() const
{
    return _elements_in_last_turn;
}

float Spiral::GetTheta() const
{
    return _theta;
}

const sf::FloatRect Spiral::GetSize() const
{
    sf::FloatRect original_bounds;
    sf::Vector2f pos;

    for (size_t i = _drawable.size() - _elements_in_last_turn; i < _drawable.size(); ++i) {
        pos.x = _drawable[i].x;
        pos.y = _drawable[i].y;
        original_bounds.left = std::min(original_bounds.left, pos.x);
        original_bounds.top = std::min(original_bounds.top, pos.y);
        original_bounds.width = std::max(original_bounds.width, pos.x);
        original_bounds.height = std::max(original_bounds.height, pos.y);
    }

    original_bounds.width -= original_bounds.left;
    original_bounds.height -= original_bounds.top;

    return original_bounds;
}
