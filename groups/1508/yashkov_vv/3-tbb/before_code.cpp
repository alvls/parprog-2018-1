#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <omp.h>
#include "tbb\tick_count.h"
#include "tbb\tbb.h"
#include <fstream>
#include "../1-test-version/vertex.h"
using namespace std;
void solve(int ** graph, Vertex * vertexes, int n);


int main(int argc, char * argv[]){
	if (argc != 4) {
		cout << "Use 'solver <input file> <output file> <num_threads>'" << endl;
		return 1;
	}
	tbb::task_scheduler_init init(atoi(argv[3]));
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
	tbb::tick_count start = tbb::tick_count::now();
	solve(graph, vertexes, size);
	tbb::tick_count finish = tbb::tick_count::now();
	time = (double)(finish - start).seconds();
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