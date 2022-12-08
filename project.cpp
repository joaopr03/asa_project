#include <vector>
#include <iostream>

typedef std::vector<std::vector<std::vector<int>>> table;
typedef std::vector<std::vector<int>> matrix;
typedef std::vector<int> vector;

void show_matrix(matrix m, int lines, int columns){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++)
        std:: cout << m[i][j];
        std:: cout << std::endl;
    }
}

matrix create_matrix(int lines, int columns, int square_size){
    matrix m_square = {};
    for(int i = 0; i < lines; i++){
        std:: vector<int> line = {};
        for(int j = 0; j < columns; j++){
            if((i >= lines - square_size) && (j < square_size))
                line.push_back(square_size);
            else
                line.push_back(0);
        }
        m_square.push_back(line);
    }
    return m_square;
}

vector get_top_right_index(matrix m, int lines, int columns){
    std:: vector<int> vec = {};
    for(int i = 0; i < lines; i++){
        for(int j = lines - 1; j >= 0; j--){
        if(m[i][j] != 0){
            vec.push_back(i);
            vec.push_back(j);
        }
        }
    }
    return vec;
}

int get_number_of_vertical_iterations(vector index_column, int lines, int square_size){
    int ceiling = 0, i = 0;
    while(index_column[i] == 0){
        i++;
    }
    ceiling = lines - (i+square_size-1);
    return ceiling;
}

bool matches_with(matrix m, vector a){
    int size = m.size(), number_of_matches = 0;
    bool matches = false;
    for(int i = 0; i < size; i++){
        if(a[0] < m[i][2])
            matches = true;
        if(a[2] > m[i][0])
            matches = true;
        if(a[1] > m[i][3])
            matches = true;
        if(a[3] < m[i][1])
            matches = true;
        if(matches)
            number_of_matches ++;
        matches = false;
    }
    if(size == number_of_matches)
        return true;
    else
        return false;
}

int get_m_index(vector last_matrix, matrix m){
    int size = m.size(), n = 0;
    for(int i = 0; i < size; i++){
        if(m[i] == last_matrix){
            n = i;
            break;
        }
    }
    return n;
}

int calculate_number_of_combinations (matrix m, int biggest_combinations){
    int size = m.size();
    table total_combinations = {};

    for(int i = 0; i < size; i++){
        matrix m_aux = {};
        m_aux.push_back(m[i]);
        for(int j = i + 1; j < size; j++){
            matrix m_aux1  = {};
            if(matches_with(m_aux,m[j])){
                m_aux1.push_back(m[i]);
                m_aux1.push_back(m[j]);
                total_combinations.push_back(m_aux1);
            }
        }

    }

    for(int k = 2; k < biggest_combinations; k++){
        int size_of_total_combinations = total_combinations.size();
        for(int z = 0; z < size_of_total_combinations; z++){
            int size_of_matrices = total_combinations[z].size();
            if(size_of_matrices == k){
                matrix m_aux2 = {};
                for(int w = get_m_index(total_combinations[z][k-1],m); w < size; w++){
                    if(matches_with(total_combinations[z],m[w])){
                        m_aux2 = total_combinations[z];
                        m_aux2.push_back(m[w]);
                        total_combinations.push_back(m_aux2);
                    }
                    m_aux2 = {};
                }
            }
        }
    }
    
    return total_combinations.size();
}

int main()
{
    int lines, columns, number_of_configurations = 0, smaller_number, number_of_combinations = 0,
    biggest_combination_possible = 0, tobytosquares_lines = 0, tobytosquares_columns = 0;

    std::cin >> lines;
    std::cin >> columns;

    if(lines <= columns)
        smaller_number = lines;
    else
        smaller_number = columns;

    if(lines > 1){
        if(lines % 2 == 0)
            tobytosquares_lines = lines / 2;
        else
            tobytosquares_lines = (lines - 1)/2;
    }

    if(columns > 1){
        if(columns % 2 == 0)
            tobytosquares_columns = columns / 2;
        else
            tobytosquares_columns = (columns - 1)/2;
    }

    biggest_combination_possible = tobytosquares_columns * tobytosquares_lines;

    std::vector<int> index_column = {};
    for(int i = 0; i < lines; i++){
        int c;
        std:: cin >> c;
        if(c > 0)
        number_of_configurations = 1;

        index_column.push_back(c);
    }

    //criar a matriz inicial
    matrix m_basic = {};

    for(int i = 0; i < lines; i++){
        std:: vector<int> line = {};
        for(int j = 0; j < columns; j++){
        if(index_column[i] > j)
            line.push_back(1);
        else
            line.push_back(0);
        }
        m_basic.push_back(line);
    }

    matrix vertices_of_possible_matrices = {};

    if(number_of_configurations > 0){
        for(int square_size = 2; square_size <= smaller_number; square_size++){
        matrix m_square_size = create_matrix(lines,columns,square_size);
            if(m_basic[get_top_right_index(m_square_size, lines, columns)[0]]
            [get_top_right_index(m_square_size, lines, columns)[1]] != 1)
                break;
            for(int j = 0; j < get_number_of_vertical_iterations(index_column, lines,square_size); j ++){
                if(square_size <= index_column[lines - (square_size + j)]){
                    std:: vector<int> vertices = {};
                    for(int i = square_size; i <= index_column[lines - (square_size + j)]; i++){
                        number_of_configurations ++;
                        vertices.push_back(lines - j - 1);
                        vertices.push_back(i - square_size);
                        vertices.push_back(lines - j - square_size);
                        vertices.push_back(i - 1);
                        vertices_of_possible_matrices.push_back(vertices);
                        vertices  = {};
                    }
                }
            }
        }
    }

    if(vertices_of_possible_matrices.size() > 0){
        number_of_combinations = calculate_number_of_combinations(vertices_of_possible_matrices,biggest_combination_possible);
    }


    std:: cout << number_of_combinations + number_of_configurations << std::endl;

    return 0;
}
