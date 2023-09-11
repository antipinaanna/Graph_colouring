#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void disjunction1(std::vector<bool>& vec1, std::vector<bool>& vec2) {
    if (vec1.size() != vec2.size()) {
        // Обработка ошибки: векторы должны быть одинаковой длины
        std::cerr << "Error: std::vectors must have the same length." << std::endl;
    }

    for (unsigned i = 0; i < vec1.size(); ++i) {
        vec1[i] = (vec1[i] || vec2[i]);
    }
}

unsigned colorVertices(std::vector<std::vector<bool>>& adjacencyMatrix, std::vector<unsigned>& colours) {
    unsigned n_vertex = adjacencyMatrix.size();
    std::vector<int> V(n_vertex, 1); // Вектор V, содержащий все вершины
    std::vector<int> Sk; // Независимое множество вершин, покрашенных в цвет k
    unsigned k = 1;
    for (unsigned i = 0; i < n_vertex; i++) {
        if (V[i] == 0) {
            continue;
        }
        colours[i] = k;
        V[i] = 0;
        
        for (unsigned j = i + 1; j < n_vertex; j++){
            if (adjacencyMatrix[i][j] == 0 && V[j] == 1) {
                Sk.push_back(j);
                V[j] = 0;
                disjunction1(adjacencyMatrix[i], adjacencyMatrix[j]);
                colours[j] = k;
            }
        }
        k++;
    }
    return k - 1;
}


int main()
{

	std::string folderPath = "./data";
    std::ofstream file_out("output_dataframe.txt");
	if (file_out.is_open())
	{
		for (const auto &entry : fs::directory_iterator(folderPath)) 
		{
			if (entry.is_regular_file())
			{
				std::string filePath = entry.path().string();
				unsigned depth;
				if (filePath == "./data/ks_10000_0") depth = 10000;
				else depth = 1000;
				std::ifstream file(filePath);
				if (file.is_open())
				{
					unsigned n_vertex, n_edges, v1, v2, k; // Количество вершин в графе
                    file >> n_vertex >> n_edges;
                    std::vector<std::vector<bool>> adjacencyMatrix(n_vertex, std::vector<bool>(n_vertex, 0)); // Матрица смежности
                    std::vector<unsigned> colours(n_vertex, 0); // Вектор цветов вершин
                    for (int i = 0; i < n_edges; i++) {
                            file >> v1 >> v2;
                            adjacencyMatrix[v1][v2] = 1;
                            adjacencyMatrix[v2][v1] = 1;
                    }
                    k = colorVertices(adjacencyMatrix, colours);
                    // Вывод цветов вершин

                    file_out << filePath << ", "<< k << std::endl;
					file.close();
                    std::cout << "Цвета вершин:" << std::endl;
                    for (int i = 0; i < n_vertex; i++) {
                        std::cout << "Вершина " << i << ": " << colours[i] << " ";
                    }
                    std::cout << std::endl << k << std::endl;
				}
				else
					std::cout << "Не удалось открыть файл" << std::endl;
			}
		}
		file_out.close();
	}
}






































/*int main() {
    std::string folderPath = "./data";
    std::ofstream file_out("output_dataframe");
    if (file_out.is_open())
    {
        for (const auto &entry : fs::directory_iterator(folderPath)) 
        {
            if (entry.is_regular_file())
            {
                std::string filePath = entry.path().string();
                std::ifstream file(filePath);
                if (file.is_open()) 
                {
                    unsigned n_vertex, n_edges, v1, v2, k; // Количество вершин в графе
                    file >> n_vertex >> n_edges;
                    std::vector<std::vector<bool>> adjacencyMatrix(n_vertex, std::vector<bool>(n_vertex, 0)); // Матрица смежности
                    std::vector<unsigned> colours(n_vertex, 0); // Вектор цветов вершин
                    for (int i = 0; i < n_edges; i++) {
                            file >> v1 >> v2;
                            adjacencyMatrix[v1][v2] = 1;
                            adjacencyMatrix[v2][v1] = 1;
                    }
                    k = colorVertices(adjacencyMatrix, colours);
                    // Вывод цветов вершин

                    file_out << filePath << ", "<< k << std::endl;
					file.close();

            /*        std::cout << "Цвета вершин:" << std::endl;
                    for (int i = 0; i < n_vertex; i++) {
                        std::cout << "Вершина " << i << ": " << colours[i] << std::endl;
                    }
                    std::cout << k << std::endl;
                }
                else
                    std::cout << "Не удалось открыть файл" << std::endl;
                return 0;
            }
        }
        file_out.close();    
    }
}*/