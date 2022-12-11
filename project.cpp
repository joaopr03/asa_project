#include <vector>
#include <iostream>

typedef std::vector<int> vector;
typedef std::vector<vector> matrix;

matrix m_basic = {};
matrix m_square = {};

vector index_column = {};

int lines = 0;
int columns = 0;
int max_square_size = 0;
int biggest_combination = 0;
int configurations = 0;

/*
Função responsável por ler as entradas do input.
*/
void readInput() {
    std::cin >> lines;
    std::cin >> columns;

    for(int i = 0; i < lines; i++) {
        int c;
        std:: cin >> c;
        if(c > 0)
            configurations = 1;
        index_column.push_back(c);
    }
}

/*
Função responsável por criar uma matrix que é dada pelos inputs.
A área a ladrilhar é inciada com o valor 1 e o resto a 0.
*/
void createInitialMatrix() {
    for(int i = 0; i < lines; i++) {
        vector line = {};
        for(int j = 0; j < columns; j++) {
            if(index_column[i] > j)
                line.push_back(1);
            else
                line.push_back(0);
        }
        m_basic.push_back(line);
    }
}

/*
Função responsável por criar uma matrix quadrada.
O tamanho da matriz depende de uma variável, e vai ser usada 
para descobrir o número de configurações.
*/
matrix createSquareMatrix(int square_size) {
    for(int i = 0; i < lines; i++) {
        vector line = {};
        for(int j = 0; j < columns; j++) {
            if((i >= lines - square_size) && (j < square_size))
                line.push_back(square_size);
            else
                line.push_back(0);
        }
        m_square.push_back(line);
    }

    return m_square;
}

/*
Função responsável por obter o tamanho máximo do lado de um 
quadrado capaz de ladrilhar a área fornecida através dos inputs.
*/
void getMaxSquareMatrixSize() {
    if(lines <= columns)
        max_square_size = lines;
    else
        max_square_size = columns;
}

/*
Função responsável por obter o número de matrizes 2x2 (ou maiores) que é
possível ter ao mesmo tempo a ladrilhar a área fornecida.
Pode-se pensar também que é o número máximo de matrizes 2x2 que se podem
ter ao mesmo tempo a ladrilhar a área.
*/
void getMaxNumberOfCombinations() {
    int twobytwosquares_lines = 0, twobytwosquares_columns = 0;

    if(lines > 1) {
        if(lines % 2 == 0)
            twobytwosquares_lines = lines / 2;
        else
            twobytwosquares_lines = (lines - 1)/2;
    }

    if(columns > 1) {
        if(columns % 2 == 0)
            twobytwosquares_columns = columns / 2;
        else
            twobytwosquares_columns = (columns - 1)/2;
    }

    biggest_combination = twobytwosquares_columns * twobytwosquares_lines;
}

/*
Função responsável por obter o índice da posição oblíqua à direita.
*/
vector getTopRightIndex(matrix m, int square_size) {
    vector vec = {};

    vec.push_back(lines - square_size);
    vec.push_back(square_size - 1);
    
    return vec;
}


/*
Função responsável por obter o número de iterações que pode realizar na vertical.
*/
int getNumberOfVerticalIterations(int square_size) {
    int ceiling = 0, i = 0;

    while(index_column[i] <= 1) {
        i++;
    }

    ceiling = lines - (i + square_size - 1);
    
    return ceiling;
}

/*

*/
int getMIndex(vector last_matrix, matrix m) {
    int size = m.size(), size1 = last_matrix.size();
    vector real_last_matrix = {};
    real_last_matrix.push_back(last_matrix[size1 - 4]);
    real_last_matrix.push_back(last_matrix[size1 - 3]);
    real_last_matrix.push_back(last_matrix[size1 - 2]);
    real_last_matrix.push_back(last_matrix[size1 - 1]);

    for(int i = 0; i < size; i++){
        if(m[i] == real_last_matrix){
            return  i;
        }
    }

    return 0;
} 

/*

*/
matrix getVerticesOfPossibleMatrixes() {
    matrix vertices_of_possible_matrices_aux = {};

    if(configurations > 0) {
        for(int square_size = 2; square_size <= max_square_size; square_size++) {
            matrix m_square_size = createSquareMatrix(square_size);
            vector topRightIndex = getTopRightIndex(m_square_size, square_size);
            if(m_basic[topRightIndex[0]][topRightIndex[1]] != 1)
                break;
            int verticalIterations = getNumberOfVerticalIterations(square_size);
            std::cout << "verticalIterations: " << verticalIterations << std::endl;
            for(int j = 0; j < verticalIterations; j++) {
                if(square_size <= index_column[lines - (square_size + j)]) {
                    vector vertices = {};
                    for(int i = square_size; i <= index_column[lines - (square_size + j)]; i++) {
                        configurations++;
                        vertices.push_back(lines - j - 1);
                        vertices.push_back(i - square_size);
                        vertices.push_back(lines - j - square_size);
                        vertices.push_back(i - 1);
                        vertices_of_possible_matrices_aux.push_back(vertices);
                        vertices  = {};
                    }
                }
            }
        }
    }

    return vertices_of_possible_matrices_aux;
}

/*

*/
bool matchesWith(matrix m, vector a) {
    int size = m.size();
    int number_of_matches = 0, total_number = 0;
    bool matches = false;

    for(int i = 0; i < size; i++) {
        int size1 = m[i].size();
        for(int j = 0; j < size1; j += 4) {
            total_number++;
            if(a[0] < m[i][j +2])
                matches = true;
            if(a[2] > m[i][j])
                matches = true;
            if(a[1] > m[i][j + 3])
                matches = true;
            if(a[3] < m[i][j + 1])
                matches = true;
            if(matches)
                number_of_matches++;
            matches = false;
        }
    }

    return total_number == number_of_matches;
}

/*

*/
int calculateParticularCombination(vector m_particular, matrix m) {
    int size = m.size(), number_of_combinations = 0;
    matrix m_aux = {};
    m_aux.push_back(m_particular);

    for(int k = 1; k < biggest_combination; k++) {
        int size_of_new_matrix = m_aux.size();
        matrix m_aux2 = {};
        for(int z = 0; z < size_of_new_matrix; z++) {
            matrix m_aux3 = {};
            m_aux3.push_back(m_aux[z]);
            for(int w = getMIndex(m_aux[z], m) + 1; w < size; w++) {
                if(matchesWith(m_aux3, m[w])) {
                    vector aux = {};
                    int size2 = m_aux[z].size();
                    for(int j = 0; j < size2; j++) {
                        aux.push_back(m_aux[z][j]);
                    }
                    aux.push_back(m[w][0]);
                    aux.push_back(m[w][1]);
                    aux.push_back(m[w][2]);
                    aux.push_back(m[w][3]);
                    m_aux2.push_back(aux);
                }
            }
        }

        if(m_aux2.size() > 0) {
            m_aux = m_aux2;
            number_of_combinations += m_aux2.size();
        } else {
            break;
        }
    }

    return number_of_combinations;
}

/*
Função responsável por obter o número total de combinações 
de uma certa área a ladrilhar.
*/
int calculateNumberOfCombinations(matrix m) {
    int size = m.size(), number_of_combinations = 0;

    for(int k = 0; k < size; k++){
        number_of_combinations += calculateParticularCombination(m[k], m);
    }
    
    return number_of_combinations;
}

int main() {
    int number_of_combinations = 0;

    readInput();

    getMaxSquareMatrixSize();

    getMaxNumberOfCombinations();

    createInitialMatrix();

    matrix vertices_of_possible_matrices = getVerticesOfPossibleMatrixes();

    if(vertices_of_possible_matrices.size() > 0) {
        number_of_combinations = calculateNumberOfCombinations(vertices_of_possible_matrices);
    }
    /* for(int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << vertices_of_possible_matrices[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std:: cout << number_of_combinations + configurations << std::endl;
    for(int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << vertices_of_possible_matrices[i][j] << " ";
        }
        std::cout << std::endl;
    } */
    std:: cout << number_of_combinations + configurations << std::endl;
    

    return 0;
}
