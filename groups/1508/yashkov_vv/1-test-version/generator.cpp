#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <time.h>
#include <iostream>
#include <fstream>
#include "vertex.h"

using namespace std;

int n_tests[] = { 2, 3, 4, 5, 7, 8, 10, 50, 100, 200, 300, 400, 500, 600, 800, 1000, 1200, 1500, 2000, 3000 };

int main(int argc, char * argv[]) {
	if (argc != 4 || atoi(argv[1]) < 1 || atoi(argv[1]) > 20) {
		cout << "Use 'generator <test number (1 - 20)> <output binary file> <answer binary file>'" << endl;
		return 1;
	}
	int N = n_tests[atoi(argv[1]) - 1]; // vertex count
	int **graph = new int*[N];
	for (int i = 0; i < N; i++) {
		graph[i] = new int[N];
		for (int j = 0; j < N; j++) {
			graph[i][j] = -1;
		}
	}
	Vertex * vertexes = new Vertex[N];
	vertexes[0].min_path_length = 0;
	vertexes[0].min_path_vertex_size = 0;
	// generate min pathes
	srand(time(0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(i!=j){
				int edge_size = -10 + rand() % 31; // from -10 to 20, if size <= 10 that edge isn't exist
				if (graph[i][j] == -1 && edge_size>10) {
					if (vertexes[i].min_path_length != -1 && vertexes[j].min_path_length == -1) {
						graph[i][j] = edge_size;
						graph[j][i] = edge_size;
						vertexes[j].min_path_length = vertexes[i].min_path_length + edge_size;
						vertexes[j].min_path_vertex_size = vertexes[i].min_path_vertex_size + 1;
						vertexes[j].min_path = new int[vertexes[j].min_path_vertex_size];
						for (int l = 0; l < vertexes[i].min_path_vertex_size; l++)
							vertexes[j].min_path[l] = vertexes[i].min_path[l];
						vertexes[j].min_path[vertexes[j].min_path_vertex_size - 1] = i;
						continue;
					}
					if (vertexes[i].min_path_length == -1 && vertexes[j].min_path_length != -1) {
						graph[i][j] = edge_size;
						graph[j][i] = edge_size;
						vertexes[i].min_path_length = vertexes[j].min_path_length + edge_size;
						vertexes[i].min_path_vertex_size = vertexes[j].min_path_vertex_size + 1;
						vertexes[i].min_path = new int[vertexes[i].min_path_vertex_size];
						for (int l = 0; l < vertexes[j].min_path_vertex_size; l++)
							vertexes[i].min_path[l] = vertexes[j].min_path[l];
						vertexes[i].min_path[vertexes[i].min_path_vertex_size - 1] = j;
						continue;
					}
					if (vertexes[i].min_path_length != -1 && vertexes[j].min_path_length != -1) {
						int min_edge_size = vertexes[i].min_path_length - vertexes[j].min_path_length;
						if (min_edge_size < 0)
							min_edge_size = -min_edge_size;
						edge_size += min_edge_size;
						graph[i][j] = edge_size;
						graph[j][i] = edge_size;
					}
				}
			}
		}
	}
	//graph binding
	for(int i = 1; i < N; i++)
		if (vertexes[i].min_path_length == -1) {
			int edge_size = 11 + (rand() % 10); // from 11 to 20
			graph[i][0] = edge_size;
			graph[0][i] = edge_size;
			vertexes[i].min_path_length = edge_size;
			vertexes[i].min_path_vertex_size = 1;
			vertexes[i].min_path = new int[1];
			vertexes[i].min_path[0] = 0;
		}
	double tmp = -1;
	ofstream out;
	out.open(argv[2], ios::binary | ios::out);
	out.write((char *)&tmp, sizeof(tmp));
	out.write((char *)&N, sizeof(N));
	int *arr = new int[N*N];
	int iter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[iter] = graph[i][j];
			iter++;
		}
	}
	out.write((char *)arr, sizeof(*arr)*N*N);
	out.close();
	out.open(argv[3], ios::binary | ios::out);
	out.write((char *)&tmp, sizeof(tmp));
	out.write((char *)&N, sizeof(N));
	for (int i = 0; i < N; i++) {
		out.write((char *)&(vertexes[i].min_path_length), sizeof(vertexes[i].min_path_length));
		out.write((char *)&(vertexes[i].min_path_vertex_size), sizeof(vertexes[i].min_path_vertex_size));
		if (vertexes[i].min_path_vertex_size>0)
			out.write((char *)vertexes[i].min_path, sizeof(*(vertexes[i].min_path))*vertexes[i].min_path_vertex_size);
	}
	out.close();
	return 0;
}