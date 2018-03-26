class Vertex {
public:
	int min_path_length = -1;
	int min_path_vertex_size = 0;
	int * min_path;
};
struct edge {
	int a, b, cost;
};