#include<iostream>
#include<fstream>

int** create_universe(int rows, int columns); // Прототип функции создания динамического массива для вселенной
void output_current_generation(int** current_universe_form, int rows, int columns); // Прототип функции вывода текущего поколения на экран
void finding_neighbours(int** current_universe_form, int rows, int columns); // Прототип функции для определения местоположения соседей
int alive_neighbours_counting(int** previous_universe_form, int rows, int columns); // Прототип функции для определения количества живых соседей
void next_generation_finding(int** current_universe_form, int** previous_universe_form, int rows, int columns, int next_gen); // Прототип функции для создания следующего поколения
void previous_form_preserving(int** current_universe_form, int** previous_universe_form, int rows, int columns); // Прототип функции сохранения предыдущего поколения для копирования текущего состояния программы и корректной генерации следующего поколения
void generations_comparing(int** current_universe_form, int** previous_universe_form, int rows, int columns); // Прототип функции сравнения предыдущего и текущего поколения для корректного определения расположения клеток на данных двух формах
void output_of_alive_elements_counting(int** current_universe_form, int rows, int columns); // Прототип функции для вывода на экран количества живых элементов
void delete_universe(int** current_universe_form, int universe_elements); // Прототип функции удаления динамического массива для вселенной

// Основная функция программы
int main()
{
	setlocale(LC_ALL, "Russian");
	std::ifstream file("primary_form.txt");
	if (file.is_open())
	{
		int rows_elems = 0;
		int alive_element_of_a_row = 0;
		int columns_elems = 0;
		int alive_element_of_a_column = 0;
		int generation = 1;

		file >> rows_elems >> columns_elems;
		int** universe_form;
		universe_form = create_universe(rows_elems, columns_elems);
		//int** previous_form;

		while (!file.eof())
		{
			file >> alive_element_of_a_row >> alive_element_of_a_column;
			universe_form[alive_element_of_a_row][alive_element_of_a_column] = 1;
		}
		file.close();

		output_current_generation(universe_form, rows_elems, columns_elems);
		std::cout << "Поколение: " << generation << "." << " ";
		output_of_alive_elements_counting(universe_form, rows_elems, columns_elems);
		std::cout << std::endl;

		/*do
		{
			previous_form_preserving(universe_form, previous_form, rows_elems, columns_elems);
			next_generation_finding
			
		}while*/
		delete_universe(universe_form, rows_elems);
	}
	else
	{
		std::cout << "Не получилось открыть файл!" << std::endl;
	}
	return 0;
}

// Реализация функции создания динамического массива для вселенной
int** create_universe(int rows, int columns)
{
	int** current_universe_form = new int* [rows] {};
	for (int a_row = 0; a_row < rows; a_row++)
	{
		current_universe_form[a_row] = new int[columns];
	}
	return current_universe_form;
}

// Реализация функции вывода текущего поколения на экран
void output_current_generation(int** current_universe_form, int rows, int columns)
{
	for (int a_row = 0; a_row < rows; a_row++)
	{
		for (int a_column = 0; a_column < columns; a_column++)
		{
			std::cout << (current_universe_form[a_row][a_column] == 1 ? '*' : '-') << " ";
		}
		std::cout << std::endl;
	}
}

// Реализация функции для определения местоположения соседей
void finding_neighbours(int** current_universe_form, int rows, int columns)
{
	int neighbours = 0;
	for (int a_row = rows - 1; a_row <= rows + 1; a_row++)
	{
		for (int a_column = columns - 1; a_column <= columns + 1; a_column++)
		{
			if (a_row == rows && a_column == columns)
			{
				continue;
			}
			current_universe_form[neighbours][0] = a_row;
			current_universe_form[neighbours][1] = a_column;
			neighbours++;
		}
	}
}

// Реализация функции для определения количества живых соседей
int alive_neighbours_counting(int** previous_universe_form, int rows, int columns)
{
	int alive_nb = 0;
	int row_nb = 0;
	int column_nb = 0;
	int** alive_neighbours = new int* [rows];
	for (int a_row = 0; a_row < rows; a_row++)
	{
		alive_neighbours[a_row] = new int[columns];
	}
	finding_neighbours(alive_neighbours, rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			row_nb = alive_neighbours[i][0];
			column_nb = alive_neighbours[j][0];

			if (row_nb < 0 || column_nb < 0 || row_nb >= rows || column_nb >= columns)
			{
				continue;
			}
			if (previous_universe_form[row_nb][column_nb] == 1)
			{
				alive_nb++;
			}
		}

	}
	return alive_nb;
	for (int a_row = 0; a_row < rows; a_row++)
	{
		delete[] alive_neighbours[a_row];
	}
	delete[] alive_neighbours;
}

// Реализация функции для создания следующего поколения
void next_generation_finding(int** current_universe_form, int** previous_universe_form, int rows, int columns, int next_gen)
{
	int alive_nbs = 0;
	for (int a_row = 0; a_row < rows; a_row++)
	{
		for (int a_column = 0; a_column < columns; a_column++)
		{
			alive_nbs = alive_neighbours_counting(previous_universe_form, a_row, a_column);
			if (previous_universe_form[a_row][a_column] == 1)
			{
				(alive_nbs == 2 || alive_nbs == 3) ? current_universe_form[a_row][a_column] = 1 : current_universe_form[a_row][a_column] = 0;
			}
			else
			{
				(alive_nbs == 3) ? current_universe_form[a_row][a_column] = 1 : current_universe_form[a_row][a_column] = 0;
			}
			alive_nbs = 0;
		}
	}
}

// Реализация функции сохранения предыдущего поколения для копирования текущего состояния программы и корректной генерации следующего поколения
void previous_form_preserving(int** current_universe_form, int** previous_universe_form, int rows, int columns)
{
	for (int a_row = 0; a_row < rows; a_row++)
	{
		for (int a_column = 0; a_column < columns; a_column++)
		{
			previous_universe_form[a_row][a_column] = current_universe_form[a_row][a_column];
		}
	}
}

// Реализация функции сравнения предыдущего и текущего поколения для корректного определения расположения клеток на данных двух формах
void generations_comparing(int** current_universe_form, int** previous_universe_form, int rows, int columns)
{
	int next_gen = 0;
	for (int a_row = 0; a_row < rows; a_row++)
	{
		for (int a_column = 0; a_column < columns; a_column++)
		{
			(previous_universe_form[a_row][a_column] == current_universe_form[a_row][a_column]) ? next_gen = 1 : next_gen = 0;
		}
	}
}

// Реализация функции для вывода на экран количества живых элементов
void output_of_alive_elements_counting(int** current_universe_form, int rows, int columns)
{
	int alive_elements = 0;
	for (int a_row = 0; a_row < rows; a_row++)
	{
		for (int a_column = 0; a_column < columns; a_column++)
		{
			if (current_universe_form[a_row][a_column] == 1)
			{
				alive_elements++;
			}
		}
	}
	std::cout << "Живых клеток: " << alive_elements;
}

// Реализация функции удаления динамического массива для вселенной
void delete_universe(int** current_universe_form, int universe_elements)
{
	for (int uni_element = 0; uni_element < universe_elements; uni_element++)
	{
		delete[] current_universe_form[universe_elements];
	}
	delete[] current_universe_form;
}