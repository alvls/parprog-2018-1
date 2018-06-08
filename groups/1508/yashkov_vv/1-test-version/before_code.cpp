#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include "vertex.h"
using namespace std;
void solve(int ** graph, Vertex * vertexes, int n);


int main(int argc, char * argv[]){
	if (argc != 3) {
		cout << "Use 'solver <input file> <output file>'" << endl;
		return 1;
	}
	int size;
	double time;
	ifstream in(argv[1], ios::in | ios::binary);
	in.read((char *)&time, sizeof(time));
	in.read((char *)&size, sizeof(size));
	int ** graph = new int*[size];
	Vertex * vertexes = new Vertex[size];
	vertexes[0].min_path_length = 0;
	vertexes[0].min_path_vertex_size = 0;
	for (int i = 0; i < size; i++) {
		graph[i] = new int[size];
		in.read((char *)graph[i], sizeof(*graph[i])*size);
	}
	in.close();
	time = omp_get_wtime();
	solve(graph, vertexes, size);
	time = omp_get_wtime() - time;
	ofstream out;
	out.open(argv[2], ios::binary | ios::out);
	out.write((char *)&time, sizeof(time));
	out.write((char *)&size, sizeof(size));
	for (int i = 0; i < size; i++) {
		out.write((char *)&(vertexes[i].min_path_length), sizeof(vertexes[i].min_path_length));
		out.write((char *)&(vertexes[i].min_path_vertex_size), sizeof(vertexes[i].min_path_vertex_size));
		if (vertexes[i].min_path_vertex_size>0)
			out.write((char *)vertexes[i].min_path, sizeof(*(vertexes[i].min_path))*vertexes[i].min_path_vertex_size);
	}
	out.close();
	return 0;
}