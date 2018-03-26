#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 4 || (atoi(argv[3]) != 0 & (atoi(argv[3]) != 1))) {
		cout << "Use 'typer <input file> <output file> <type flag: 0 - for graph data file and 1 - for answer file>'" << endl;
		return 1;
	}
	FILE *in, *out;
	char* line = new char[255];
	int file_type = atoi(argv[3]);
	in = fopen(argv[1], "rt");
	out = fopen(argv[2], "wb");
	if (in != nullptr) {
		fgets(line, 255, in);
		int N = atoi(line);
		if (file_type == 0) {
			int **graph = new int*[N];
			for (int i = 0; i < N; i++) {
				graph[i] = new int[N];
				for (int j = 0; j < N; j++) {
					graph[i][j] = -1;
				}
			}
			fgets(line, 255, in); // "edges:"
			while (fgets(line, 255, in) != nullptr) {
				int vertex1 = atoi(strtok(line, " "));
				strtok(NULL, " "); // " -( "
				int len = atoi(strtok(NULL, " "));
				strtok(NULL, " "); // " )- "
				int vertex2 = atoi(strtok(NULL, " "));
				graph[vertex1][vertex2] = len;
				graph[vertex2][vertex1] = len;
			}
			fwrite(&N, sizeof(double), 1, out);
			fwrite(&N, sizeof(N), 1, out);

			int *arr = new int[N*N];
			int iter = 0;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					arr[iter] = graph[i][j];
					iter++;
				}
			}
			fwrite(arr, sizeof(*arr), N*N, out);
		}
		else {
			fgets(line, 255, in); // "paths:"
			fwrite(&N, sizeof(double), 1, out);
			fwrite(&N, sizeof(N), 1, out);
			while (fgets(line, 255, in) != nullptr) {
				strtok(line, " "); // "<vertex num>: "
				strtok(NULL, " "); // "len "
				int min_path_length = atoi(strtok(NULL, " "));
				int min_path_vertex_size = atoi(strtok(NULL, " "));
				fwrite(&min_path_length, sizeof(min_path_length), 1, out);
				fwrite(&min_path_vertex_size, sizeof(min_path_vertex_size), 1, out);
				if (min_path_vertex_size > 0) {
					int * min_path = new int[min_path_vertex_size];
					for (int i = 0; i < min_path_vertex_size; i++) {
						fgets(line, 255, in);
						min_path[i] = atoi(line);
					}
					fwrite(min_path, sizeof(*min_path), min_path_vertex_size, out);
				}
			}
		}
	}
	fclose(in);
	fclose(out);
	delete[] line;
	return 0;
}