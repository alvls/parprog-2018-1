#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>
#include "../1-test-version/vertex.h"
using namespace std;

void solve(int ** graph, Vertex * vertexes, int n) {
	const int INF = 1000000000;
	vector<int> d(n, INF);
	d[0] = 0;
	vector<edge> e;
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (graph[i][j] != -1 && i != j) {
				edge _e;
				_e.a = i;
				_e.b = j;
				_e.cost = graph[i][j];
				e.push_back(_e);
			}
		}
	}
	int m = e.size();
	vector<int> p(n, -1);
	for (;;) {
		bool any = false;
#pragma omp parallel for shared(e, d, p, any, INF)
		for (int j = 0; j < m; ++j) {
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = d[e[j].a] + e[j].cost;
					p[e[j].b] = e[j].a;
					any = true;
				}
			if (d[e[j].b] < INF)
				if (d[e[j].a] > d[e[j].b] + e[j].cost) {
					d[e[j].a] = d[e[j].b] + e[j].cost;
					p[e[j].a] = e[j].b;
					any = true;
				}
		}
		if (!any)  break;
	}
#pragma omp parallel for shared(vertexes, p, d)
	for (int i = 0; i < n; i++) {
		vector<int> path;
		for (int cur = i; cur != -1; cur = p[cur])
			path.push_back(cur);
		reverse(path.begin(), path.end());
		vertexes[i].min_path_length = d[i];
		vertexes[i].min_path_vertex_size = path.size() - 1;
		if (vertexes[i].min_path_vertex_size > 0) {
			vertexes[i].min_path = new int[vertexes[i].min_path_vertex_size];
			for (int j = 0; j < path.size() - 1; j++){
				vertexes[i].min_path[j] = path[j];
			}
		}
	}
}