#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> matrix;
typedef std::vector<int> vector;

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

void show_matrix(matrix m, int lines, int columns){
  for(int i = 0; i < lines; i++){
    for(int j = 0; j < columns; j++)
      std:: cout << m[i][j];
    std:: cout << std::endl;
  }
}

int main()
{
  int lines, columns, number_of_configurations = 0, smaller_number;

  std::cin >> lines;
  std::cin >> columns;

  if(lines <= columns)
    smaller_number = lines;
  else
    smaller_number = columns;

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

  show_matrix(m_basic, lines, columns);
  std:: cout << std::endl;
  if(number_of_configurations > 0){
    for(int square_size = 2; square_size <= smaller_number; square_size++){
      if(m_basic[get_top_right_index(create_matrix(lines,columns,square_size), lines, columns)[0]]
      [get_top_right_index(create_matrix(lines,columns,square_size), lines, columns)[1]] == 1)
        number_of_configurations ++;
      else
        break;
      show_matrix(create_matrix(lines,columns,square_size),lines,columns);
      std:: cout << std::endl;
      std:: cout << get_top_right_index(create_matrix(lines,columns,square_size), lines, columns)[0]
      << ',' << get_top_right_index(create_matrix(lines,columns,square_size), lines, columns)[1] << std::endl << std::endl;
    }
  }

  std:: cout << "Number of configurations:\n>>" << number_of_configurations << std::endl;

  return 0;
}