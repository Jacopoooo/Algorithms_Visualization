#include "Dijkstra.hpp"

Dijkstra::Dijkstra(const size_t vertices_number, const size_t neighbors_number) :
	GraphAlgorithm<DijkstraVertex, WeightedEdge>(vertices_number, neighbors_number), _previous(_vertices.size(), -1)
{
	//_LoadFont();
}

void Dijkstra::Play()
{
	while (_window.isOpen()) {

		sf::Event event;
		bool graph_setted = false;

		while (_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				_window.close();
				return;
			}

			if (!graph_setted) {
				graph_setted = _SetGraphBounds(event);
			}

		}
		_Display();

		if (graph_setted) {
			_InitGraph();
			_Display();
			_Dijkstra();
			return;
		}
	}
}


bool Dijkstra::_LoadFont()
{
	return _font.loadFromFile("font/arial.ttf");
}

bool Dijkstra::_SetGraphBounds(const sf::Event& event)
{
	bool source_and_destination = _SetSourceAndDestinationFromUserInput(event);

	if (source_and_destination) _SetRectBounds();

	return source_and_destination;
}

bool Dijkstra::_SetSourceAndDestinationFromUserInput(const sf::Event& event)
{
	static size_t mouse_button_pressed = 0;

	if (event.type == sf::Event::MouseButtonPressed) {

		if (event.mouseButton.button == sf::Mouse::Right) {

			mouse_button_pressed++;
			const sf::Vector2i position = sf::Mouse::getPosition(_window);
			const sf::Vector2f float_pos = sf::Vector2f((float)position.x, (float)position.y);

			if (mouse_button_pressed == 1) {
				_source_id = 0;
				_vertices[_source_id] = DijkstraVertex(NODES_RADIUS, _source_id, _neighbors_number, float_pos, sf::Color(SOURCE_COLOR));
				_vertices[_source_id].InitText(_font);
				_vertices[_source_id].SetDistance(0);

			}
			else {
				_destination_id = _vertices.size() - 1;
				_vertices[_destination_id] = DijkstraVertex(NODES_RADIUS, _destination_id, _neighbors_number, float_pos, sf::Color(DESTINATION_COLOR));
				_vertices[_destination_id].InitText(_font);
				std::cout << "Right click at position: (" << position.x << ", " << position.y << ")" << std::endl;
				return true;
			}
			std::cout << "Right click at position: (" << position.x << ", " << position.y << ")" << std::endl;
		}
	}
	return false;
}



void Dijkstra::_SetRectBounds()
{
	const float PI = 3.14159265358979323846;

	const sf::Vector2f source_pos = _vertices[_source_id].getPosition();
	const sf::Vector2f destination_pos = _vertices[_destination_id].getPosition();

	Line line(source_pos, destination_pos);

	const float distance = GraphVertex::EuclideanDistance(&_vertices[_source_id], &_vertices[_destination_id]);

	_rect.setSize(sf::Vector2f(distance, GRAPH_BOUNDS_HEIGHT));
	
	const float radians = std::atan(line.GetM());
	float degrees = -radians * (180.0f / PI);

	if (source_pos.x < destination_pos.x) {
		_rect.setPosition(line.GetP1());
	}
	else {
		_rect.setPosition(line.GetP2());
	}

	_rect.setRotation(degrees);
	
	const sf::FloatRect graph_bounds = _rect.getLocalBounds();
	
	const sf::Vector2f mid_point = { graph_bounds.left , graph_bounds.top + graph_bounds.height / 2 };

	_rect.setOrigin(mid_point);

	_rect.setFillColor(sf::Color::Transparent);
	_rect.setOutlineColor(sf::Color::White);
	_rect.setOutlineThickness(2.0f);

	_SetBoundsRange();
}


// TODO: Non terrò come membro sf::RectangleShape quindi lo passerò in queste funzioni nella classe 
// "_SetRectBounds()" ed esisterà soltanto nello scope di "_SetRectBounds()"

void Dijkstra::_SetBoundsRange()
{
	sf::Transform transform = _rect.getTransform();
	const sf::Vector2f size = _rect.getSize();

	sf::Vector2f corners[4];

	corners[0] = _rect.getPosition();
	corners[1] = transform.transformPoint(size.x, 0);
	corners[2] = transform.transformPoint(size.x, size.y);
	corners[3] = transform.transformPoint(0, size.y);

	float y_min = corners[0].y;
	float y_max = corners[0].y;

	for (size_t i = 1; i < 4; ++i) {
		y_min = std::min(y_min, corners[i].y);
		y_max = std::max(y_max, corners[i].y);
	}

	_bounds_range = sf::Vector2f(y_min, y_max);
}


void Dijkstra::_InitVertices()
{

	float source_x_pos = _vertices[_source_id].getPosition().x;
	float destination_x_pos = _vertices[_destination_id].getPosition().x;

	if (source_x_pos < destination_x_pos) {
		source_x_pos += NODES_RADIUS;
		destination_x_pos -= NODES_RADIUS;
	}
	else {
		source_x_pos -= NODES_RADIUS;
		destination_x_pos += NODES_RADIUS;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> x_pos_distribution(source_x_pos, destination_x_pos);
	std::uniform_real_distribution<float> y_pos_distribution(_bounds_range.x, _bounds_range.y);

	for (size_t i = 1; i < _vertices.size() - 1; ++i) {
		const sf::Vector2f pos = { x_pos_distribution(gen), y_pos_distribution(gen) };
		_vertices[i] = DijkstraVertex(NODES_RADIUS, i, _neighbors_number, pos, sf::Color(EDGES_COLOR));
		_vertices[i].InitText(_font);
	}
	
}	

void Dijkstra::_AddEdge(const size_t node_id, const size_t neighbour_id, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color edge_color) {
	_vertices[node_id].AddNeighbor(neighbour_id);
	_vertices[neighbour_id].AddNeighbor(node_id);

	_edges[std::make_pair(node_id, neighbour_id)] = WeightedEdge(start, end, edge_color);
}

void Dijkstra::_InitGraph()
{
	_InitVertices();
	_SetNeighboursWithKNN(sf::Color(EDGES_COLOR));
	_SetEdges();
}

void Dijkstra::_SetEdges()
{
	float total_length = 0;

	for (const auto& edge : _edges) {
		total_length += edge.second.GetLength();
	}

	const float avg_length = total_length / (float)_edges.size();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(-0.5, 0.5);

	for (auto& edge : _edges) {

		float weight;
		const float length = edge.second.GetLength();

		if (length < avg_length * 0.5) {

			weight = 1;
		}
		else if (length < avg_length * 1.5) {

			weight = 2;
		}
		else {

			weight = 3;
		}

		weight += distrib(gen);

		// multiply by 10 to get an integer then divide by 5 to get a one cipher number
		// 5 because it's the lowest weight possibile: 1 += distrib(gen), with distrib(gen) = -0.5, then 0.5*10 = 5
		edge.second.Init(_font, EDGES_CHARACTER_SIZE, (weight*10)/5); 
	}
}

void Dijkstra::_Dijkstra()
{
	// Structure: [distance, node_id]
	std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;

	_vertices[_source_id].Explore(sf::Color(SOURCE_COLOR));

	pq.push({ 0, _source_id });

	bool destination_reached = false;

	while (!pq.empty()) {

		const size_t distance = pq.top().first;
		const size_t curr_node = pq.top().second;

		pq.pop();

		if (curr_node == _destination_id) {
			destination_reached = true;
			break;
		}

		if (distance > _vertices[curr_node].GetDistance()) continue;

		if (curr_node != _source_id) _vertices[curr_node].Explore(sf::Color(EXPLORED_NODES_COLOR));

		_Display();

		for (const size_t neighbour: _vertices[curr_node].GetNeighbors()) {

			std::pair<size_t, size_t> edge_key = _GetEdgeKey(curr_node, neighbour);

			_ExploreEdge(edge_key.first, edge_key.second, sf::Color(EXPLORED_EDGES_COLOR));

			const size_t edge_weight = _edges[edge_key].GetWeight();

			if (distance + edge_weight  < _vertices[neighbour].GetDistance()) {

				const size_t new_distance = distance + edge_weight;

				pq.push({ new_distance, neighbour });

				_previous[neighbour] = curr_node;

				_vertices[neighbour].SetDistance(new_distance);
			}

			_Display();

		}
		
	}

	_DisplayBestPath(destination_reached);

	SLEEP(5000);
}

void Dijkstra::_DisplayBestPath(bool destination_reached)
{
	_window.clear(sf::Color::Black);

	if (destination_reached) {
		size_t following_node = _destination_id;

		_vertices[following_node].Draw(_window);

		WeightedEdge* edge = nullptr;

		for (size_t node = _previous[_destination_id]; node != -1; node = _previous[node]) {

			_vertices[node].setFillColor(sf::Color(BEST_PATH_NODES_COLOR));

			_vertices[node].Draw(_window);

			const std::pair<size_t, size_t> edge_key = _GetEdgeKey(following_node, node);

			edge = &_edges[edge_key];

			edge->Explore(sf::Color(BEST_PATH_EDGES_COLOR));

			edge->Draw(_window);

			following_node = node;
		}

		// TODO: Risolvere errore pointer
		//if (edge != nullptr) delete edge;

		//_InitDestinationReachedText("Best Path: ", sf::Vector2f((float)SCREEN_WIDTH/2, 150.0f));
		
	}
	else {
		//_InitDestinationReachedText("Impossible to reach\nthe destination", sf::Vector2f((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT/2));
	}


	_window.draw(_render_destination_reached);
	_window.display();
}

void Dijkstra::_InitDestinationReachedText(const std::string& text, const sf::Vector2f pos)
{
	_render_destination_reached.setString(text);
	_render_destination_reached.setFont(_font);
	_render_destination_reached.setCharacterSize(DESTINATION_REACHED_TEXT_CHARACTER_SIZE);
	_render_destination_reached.setFillColor(sf::Color(DESTINATION_REACHED_TEXT_COLOR));

	const sf::FloatRect text_bounds = _render_destination_reached.getLocalBounds();

	_render_destination_reached.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);

	_render_destination_reached.setPosition(pos);
}

void Dijkstra::_Display()
{
	_window.clear(sf::Color::Black);

	for (const auto& vertex : _vertices) {
		vertex.Draw(_window);
	}	

	for (const auto& edge: _edges) {
		edge.second.Draw(_window);
	}

	_window.draw(_rect);

	_window.display();
}
