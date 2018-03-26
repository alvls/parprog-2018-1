#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char * argv[]){
	if (argc != 4 || (atoi(argv[3]) != 0 & (atoi(argv[3]) != 1))) {
		cout << "Use 'viewer <input file> <output file> <type flag: 0 - for graph data file and 1 - for answer file>'" << endl;
		return 1;
	}
	int size;
	double time;
	int file_type = atoi(argv[3]);
	freopen(argv[2], "wt", stdout);
	ifstream in(argv[1], ios::in | ios::binary);
	in.read((char *)&time, sizeof(time));
	in.read((char *)&size, sizeof(size));
	if (file_type == 0) {
		int ** graph = new int*[size];
		for (int i = 0; i < size; i++) {
			graph[i] = new int[size];
			in.read((char *)graph[i], sizeof(*graph[i])*size);
		}
		cout << size << " vertexes" << endl;
		cout << "edges:" << endl;
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++)
				if (graph[i][j] != -1)
					cout << i << " -( " << graph[i][j] << " )- " << j << endl;
		}
	}
	else {
		cout << size << " vertexes" << endl;
		cout << "paths:" << endl;
		for (int i = 0; i < size; i++) {
			int min_path_length;
			in.read((char *)&min_path_length, sizeof(min_path_length));
			int min_path_vertex_size;
			in.read((char *)&min_path_vertex_size, sizeof(min_path_vertex_size));
			cout << i << ": len " << min_path_length << ", " << min_path_vertex_size << " vertexes";
			if (min_path_vertex_size > 0) {
				cout << ": " << endl;
				int * min_path = new int[min_path_vertex_size];
				in.read((char *)min_path, sizeof(*min_path)*min_path_vertex_size);
				for (int j = 0; j < min_path_vertex_size; j++)
					cout << min_path[j] << endl;
			}
			else
				cout << endl;
		}
	}
	in.close();
	return 0;
}