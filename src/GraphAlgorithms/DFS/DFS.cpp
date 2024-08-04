#include "DFS.hpp"


DFS::DFS(const size_t vertices_number, const size_t neighbors_number) :
	GraphAlgorithm<Node, UnweightedEdge>(vertices_number, neighbors_number) {

    //_LoadFont();
    
    const sf::Vector2f text_pos(100.0f, 100.0f);
    const size_t font_size = 48;
    const size_t text_spacing = 80.0f;

    _InitText(text_pos, _render_vertices_number, font_size, "Vertices: " + std::to_string(_vertices.size()));
    _InitText(sf::Vector2f(text_pos.x, text_pos.y + text_spacing), _render_iterations_number, font_size, "Iterations: " + std::to_string(_iterations));
    _InitText(sf::Vector2f(text_pos.x, text_pos.y + 2*text_spacing), _render_used_edges_number, font_size, "Explored Edges: " + std::to_string(_explored_edges));

    _InitGraph();
}


DFS::~DFS() {}


void DFS::_InitVertices() {
    const float a = 19.0f;
    const float b = 0.0f;
    const float space_between_elements = 100.0f;
    const float margin = 50.0f;

    const Spiral spiral = Spiral(a, b, _vertices.size(), space_between_elements);
    const std::vector<sf::Vector2f>& points = spiral.GetDrawable();

    for (size_t i = 0; i < _vertices.size(); i++) {
        _vertices[i] = Node(NODES_RADIUS, i, _neighbors_number, points[i], sf::Color(NODE_COLOR));
        _vertices[i].SetText(i + 1, _font);
    }

    _SetScalingFactors(spiral, margin);
}


void DFS::_SetScalingFactors(const Spiral& spiral, const float margin) {

    const float max_width = SCREEN_WIDTH - 2 * margin;
    const float max_height = SCREEN_HEIGHT - 2 * margin;
    const float diameter = NODES_RADIUS * 2;

    const sf::FloatRect spiral_bounds = spiral.GetSize();

    // Calcola il fattore di scala
    const float scale_x = max_width / spiral_bounds.width;
    const float scale_y = max_height / spiral_bounds.height;
    const float scale_factor = std::min(scale_x, scale_y);

    // Calcola la traslazione per centrare
    const float translate_x = (SCREEN_WIDTH - spiral_bounds.width * scale_factor) / 2 - spiral_bounds.left * scale_factor;
    const float translate_y = (SCREEN_HEIGHT - spiral_bounds.height * scale_factor) / 2 - spiral_bounds.top * scale_factor;

    _transform.translate(translate_x, translate_y).scale(scale_factor, scale_factor);
}


void DFS::_InitGraph() {

    _InitVertices();

    size_t starting_node_index;
    if (_neighbors_number == 2) {
        const size_t first_node_index = _vertices.size() - 1;
        starting_node_index = _vertices.size() - 2;

        _AddEdge(first_node_index, first_node_index - 1, _vertices[first_node_index].GetCenter(), _vertices[first_node_index - 1].GetCenter(), sf::Color(EDGE_COLOR));

    }
    else {
        starting_node_index = _vertices.size() - 1;
    }

    _KNN(starting_node_index);
}

void DFS::_AddEdge(const size_t node_id, const size_t neighbour_id, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color edge_color)
{
    _vertices[node_id].AddNeighbor(neighbour_id);
    _vertices[neighbour_id].AddNeighbor(node_id);

    _edges.emplace(std::make_pair(node_id, neighbour_id), UnweightedEdge(start, end, edge_color));
}


void DFS::_KNN(const size_t starting_node_index)
{
    for (size_t i = starting_node_index; i > 0; i--) {

        if (_vertices[i].GetNeighbors().size() == _neighbors_number) {
            continue;
        }

        std::vector<std::pair<float, size_t>> distances;
        distances.reserve(i - 1);

        for (int j = i - 1; j >= 0; j--) {
            float distance = GraphVertex::EuclideanDistance(&_vertices[i], &_vertices[j]);
            distances.emplace_back(distance, j);
        }

        const size_t sort_size = std::min(distances.size(), _neighbors_number);

        std::partial_sort(distances.begin(), distances.begin() + sort_size, distances.end());

        std::sort(distances.begin(), distances.begin() + sort_size,
            [](const std::pair<float, size_t>& p1, const std::pair<float, size_t>& p2) {
                return p1.second > p2.second;
            });

        for (const auto& edge : distances) {

            if (_vertices[i].GetNeighbors().size() == _neighbors_number) {
                break;
            }

            size_t j = edge.second;

            if (_vertices[j].GetNeighbors().size() == _neighbors_number) {
                continue;
            }

            if (!_vertices[i].CheckIfAlreadyANeighbour(j)) {
                _AddEdge(i, j, _vertices[i].GetCenter(), _vertices[j].GetCenter(), sf::Color(EDGE_COLOR));
            }

        }
    }
}


bool DFS::_LoadFont()
{
    return _font.loadFromFile(".../font/arial.ttf");
}


void DFS::Play() {

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }

            _DFS(_vertices.size() - 1);

            SLEEP(3000);

            _window.clear();
        }

        return;
    }

}


void DFS::_DFS(const size_t node_id) {

    std::stack<std::pair<size_t, size_t>> stack;
    stack.push({node_id, node_id});

    while (!stack.empty()) {

        _UpdateIterationsText();
        _Display();

        size_t curr_node = stack.top().first;
        size_t parent_node = stack.top().second;
        
        stack.pop();
        
        if (!_vertices[curr_node].IsExplored()) {

            _vertices[curr_node].Explore(sf::Color(EXPLORE_NODE_COLOR));

            if(_ExploreEdge(curr_node, parent_node, sf::Color(EXPLORE_EDGE_COLOR))) _UpdateExploredEdgesText();

            const auto& node_neighbours = _vertices[curr_node].GetNeighbors();

            for (const size_t neighbour_id : node_neighbours) {
                if (!_vertices[neighbour_id].IsExplored()) {
                    stack.push(std::make_pair(neighbour_id, curr_node));
                }
            }
        }
    }

    _Display();

}


void DFS::_UpdateIterationsText() {
    _iterations++;
    _render_iterations_number.setString("Iterations: " + std::to_string(_iterations));
}

void DFS::_UpdateExploredEdgesText() {
    _explored_edges++;
    _render_used_edges_number.setString("Used Edges: " + std::to_string(_explored_edges));
}


void DFS::_InitText(const sf::Vector2f& pos, sf::Text& render_text, const size_t character_size, const std::string& text) const {
    render_text.setCharacterSize(character_size);
    render_text.setFont(_font);
    render_text.setFillColor(sf::Color::White);
    render_text.setPosition(pos);
    render_text.setString(text);
}


void DFS::_Display() {

    _window.clear(sf::Color::Black);


    for (const auto& pair : _edges) {
        pair.second.Draw(_window, _transform);
        
    }

    for (const auto& node : _vertices) {
        node.DrawWithTransform(_window, _transform);
    }

    _window.draw(_render_vertices_number);
    _window.draw(_render_iterations_number);
    _window.draw(_render_used_edges_number);

    _window.display();
}
        