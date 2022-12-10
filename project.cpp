#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> matrix;
typedef std::vector<int> vector;

matrix m_basic = {};
matrix m_square = {};
vector index_column = {};
int configurations = 0;

/*
Função responsável por criar uma matrix que é dada pelos inputs.
A área a ladrilhar é inciada com o valor 1 e o resto a 0.
*/
matrix createInitialMatrix(int lines, int columns, vector index_column) {
    for(int i = 0; i < lines; i++) {
        std:: vector<int> line = {};
        for(int j = 0; j < columns; j++) {
            if(index_column[i] > j)
                line.push_back(1);
            else
                line.push_back(0);
        }
        m_basic.push_back(line);
    }

    return m_basic;
}

/*
Função responsável por criar uma matrix quadrada.
O tamanho da matriz depende de uma variável, e vai ser usada 
para descobrir o número de configurações.
*/
matrix createSquareMatrix(int lines, int columns, int square_size) {
    for(int i = 0; i < lines; i++) {
        std:: vector<int> line = {};
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
Função responsável por obter o índice da posição oblíqua à direita.
*/
vector getTopRightIndex(matrix m, int lines, int columns) {
    std:: vector<int> vec = {};

    for(int i = 0; i < lines; i++) {
        for(int j = lines - 1; j >= 0; j--) {
            if(m[i][j] != 0){
                vec.push_back(i);
                vec.push_back(j);
            }
        }
    }

    return vec;
}

/*
Função responsável por obter o número de iterações que pode realizar na vertical.
*/
int getNumberOfVerticalIterations(vector index_column, int lines, int square_size) {
    int ceiling = 0, i = 0;

    while(index_column[i] == 0) {
        i++;
    }

    ceiling = lines - (i+square_size-1);
    
    return ceiling;
}

/*

*/
int getMIndex(vector last_matrix, matrix m) {
    int size = m.size(), index = 0 , size1 = last_matrix.size();
    std:: vector<int> real_last_matrix = {};
    real_last_matrix.push_back(last_matrix[size1 - 4]);
    real_last_matrix.push_back(last_matrix[size1 - 3]);
    real_last_matrix.push_back(last_matrix[size1 - 2]);
    real_last_matrix.push_back(last_matrix[size1 - 1]);

    for(int i = 0; i < size; i++){
        if(m[i] == real_last_matrix){
            index = i;
            break;
        }
    }

    return index;
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
            total_number ++;
            if(a[0] < m[i][j +2])
                matches = true;
            if(a[2] > m[i][j])
                matches = true;
            if(a[1] > m[i][j + 3])
                matches = true;
            if(a[3] < m[i][j + 1])
                matches = true;
            if(matches)
                number_of_matches ++;
            matches = false;
        }
    }

    if(total_number == number_of_matches)
        return true;
    else
        return false;
}


/*

*/
int calculateParticularCombination(vector m_particular, int biggest_combination, matrix m) {
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
                    std:: vector<int> aux = {};
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
        }
        else
            break;
    }

    return number_of_combinations;
}

/*
Função responsável por obter o número total de combinações 
de uma certa área a ladrilhar.
*/
int calculateNumberOfCombinations(matrix m, int biggest_combinations) {
    int size = m.size(), number_of_combinations = 0;

    for(int k = 0; k < size; k++){
        number_of_combinations += calculateParticularCombination(m[k],biggest_combinations,m);
    }
    
    return number_of_combinations;
}

/*

*/
matrix getVerticesOfPossibleMatrixes(int lines, int columns, int smaller, vector index_column, matrix m) {
    matrix vertices_of_possible_matrices_aux = {};

    if(configurations > 0) {
        for(int square_size = 2; square_size <= smaller; square_size++) {
            matrix m_square_size = createSquareMatrix(lines,columns,square_size);
            if(m[getTopRightIndex(m_square_size, lines, columns)[0]][getTopRightIndex(m_square_size, lines, columns)[1]] != 1)
                break;
            for(int j = 0; j < getNumberOfVerticalIterations(index_column, lines,square_size); j++) {
                if(square_size <= index_column[lines - (square_size + j)]) {
                    std:: vector<int> vertices = {};
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

int main() {
    int number_of_combinations = 0, biggest_combination_possible = 0, 
        tobytosquares_lines = 0, tobytosquares_columns = 0;
    int lines, columns, smaller_number;

    std::cin >> lines;
    std::cin >> columns;

    if(lines <= columns)
        smaller_number = lines;
    else
        smaller_number = columns;

    if(lines > 1) {
        if(lines % 2 == 0)
            tobytosquares_lines = lines / 2;
        else
            tobytosquares_lines = (lines - 1)/2;
    }

    if(columns > 1) {
        if(columns % 2 == 0)
            tobytosquares_columns = columns / 2;
        else
            tobytosquares_columns = (columns - 1)/2;
    }

    biggest_combination_possible = tobytosquares_columns * tobytosquares_lines;

    for(int i = 0; i < lines; i++) {
        int c;
        std:: cin >> c;
        if(c > 0)
            configurations = 1;

        index_column.push_back(c);
    }

    m_basic = createInitialMatrix(lines,columns,index_column);

    matrix vertices_of_possible_matrices = getVerticesOfPossibleMatrixes(lines, columns, smaller_number, index_column, m_basic);

    if(vertices_of_possible_matrices.size() > 0) {
        number_of_combinations = calculateNumberOfCombinations(vertices_of_possible_matrices,biggest_combination_possible);
    }

    std:: cout << number_of_combinations + configurations << std::endl;

    return 0;
}
