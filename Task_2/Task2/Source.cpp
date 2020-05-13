#include <fstream>
#include <string>
#include <iostream>

using std::endl;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;

int counter = 1;

void split(char* buff);


void merge(char* buff)
{
	ofstream file_1("Text1.txt");
	ofstream file_2("Text2.txt");
	ifstream glavfile(buff);

	string readString;
	int counter_2 = 0;


	bool firstFileWrite = true;
	while (!glavfile.eof())
	{
		for (int i = 0; i < counter; i++)
		{
			// тут файл мог кончиться
			if(glavfile.eof())
				break;
			getline(glavfile, readString);
			if(readString.empty())
				continue;
			if (firstFileWrite)
			{
				file_1 << readString << endl;
			}
			else
			{
				file_2 << readString << endl;
				counter_2++;
			}
		}
		firstFileWrite = !firstFileWrite;
	}
	counter = counter * 2;
	file_1.close();
	file_2.close();
	glavfile.close();

	if (counter_2 != 0)
		split(buff);
	else
		cout << "all";
}

void split(char* buff)
{
	ofstream glavfile(buff);
	ifstream file_1("Text1.txt");
	ifstream file_2("Text2.txt");

	string s1, s2;

	int prevCounter = counter / 2;
	string* main = new string[counter];

	bool firstFileEnd = false;
	bool secondFileEnd = false;

	int partsInFirstFile = 0;
	int partsInSecondFile = 0;
	// читаем по prevCounter с каждого файла, пишем в итоговый
	while (true)
	{
		string* stroki_1 = new string[prevCounter];
		string* stroki_2 = new string[prevCounter];
		
		if (firstFileEnd && secondFileEnd)
			break;

		// считали первую порцию данных
		for (int i = 0; i < prevCounter; i++)
		{
			if (!file_1.eof())
			{
				getline(file_1, s1);
				if (!s1.empty())
				{
					stroki_1[i] = s1;
					partsInFirstFile++;
				}
				else
				{
					firstFileEnd = true;
				}
			}
			else
			{
				firstFileEnd = true;
			}
			// если во втором элементов меньше 
			if (!file_2.eof())
			{
				getline(file_2, s2);
				if (!s2.empty())
				{
					stroki_2[i] = s2;
					partsInSecondFile++;
				}
				else
				{
					secondFileEnd = true;
				}
			}
			else
			{
				secondFileEnd = true;
			}
		}

		if (firstFileEnd && secondFileEnd)
			break;

		// сливаем считанные preCounter элементов
		int i = 0, j = 0;

		while (true)
		{
			if (i == prevCounter && j == prevCounter) // переходим к следующему шагу
			{
				break;
			}
			else if (i == prevCounter)
			{
				if(!stroki_2[j].empty())
					glavfile << stroki_2[j] << endl;
				j++;
			}
			else if (j == prevCounter)
			{
				if(!stroki_1[i].empty())
					glavfile << stroki_1[i] << endl;
				i++;
			}
			else if (stroki_1[i] < stroki_2[j])
			{
				if(!stroki_1[i].empty())
					glavfile << stroki_1[i] << endl;
				i++;
			}
			else
			{
				if(!stroki_2[j].empty())
					glavfile << stroki_2[j] << endl;
				j++;
			}
		}

		// чистим массивы
		delete[] stroki_1;
		delete[] stroki_2;
	}

	file_1.close();
	file_2.close();
	glavfile.close();

	delete[] main;

	merge(buff);
}


int main()
{
	setlocale(0, "Russian");
	char buff[50];
	/* cout << "Введите название файла ";
	 cin.getline(buff, 50);
	ifstream proverka(buff);
	if (!proverka)
	{
		cout << "Can`t open file " << buff << std::endl;
	}
	else merge(buff);*/
	string s1 = "aa", s2 = "b";
 int key = 1;
 if (s1 < s2)
	 key = 1;
 else key = 2;
 cout<< key;

}
