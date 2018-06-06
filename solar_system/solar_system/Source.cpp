#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;

class Cosmic_body
{
	string _name;
	int _distance;
	int _size;
	int _days;
	int _temperature;
	int _radius;
	bool _abort;

	static bool checkExit(string s)
	{
		if (s == "/stop")
			return true;
		return false;
	}

	void putValByIndex(string val, int index)
	{
		void(Cosmic_body::*funcs[])(int) = {
			&Cosmic_body::SetDistanceFromSun,&Cosmic_body::SetSize,&Cosmic_body::SetRotTime,&Cosmic_body::SetTemperature,&Cosmic_body::SetRadius
		};

		if (index == 0)
		{
			SetName(val);
			return;
		}

		index--;
		(this->*funcs[index])(stoi(val));
	}

	string msgs[6] = {
		"Введите название\n",
		"Введите расстояние от солнца\n",
		"Введите размер\n",
		"Введите количество суток, за которое тело обращается вокруг солнца\n",
		"Введите температуру\n",
		"Введите радиус\n"
	};


public:
	Cosmic_body() {}
	Cosmic_body(bool fromConsole, int wtf)
	{
		if (fromConsole)
			ReadFromConsole();
	}

	virtual string GetClassName() { return "Cosmic_Body"; }
	string GetName()
	{
		return _name;
	}
	void SetName(string name)
	{
		_name = name;
	}
	int GetDistanceFormSun()
	{
		return _distance;
	}
	void SetDistanceFromSun(int distance)
	{
		_distance = distance;
	}
	int GetSize()
	{
		return  _size;
	}
	void SetSize(int size)
	{
		_size = size;
	}
	int GetRotTime()
	{
		return _days;
	}
	void SetRotTime(int days)
	{
		_days = days;
	}
	int GetTemperature()
	{
		return _temperature;
	}
	void SetTemperature(int temperature)
	{
		_temperature = temperature;
	}
	int GetRadius()
	{
		return _radius;
	}
	void SetRadius(int radius)
	{
		_radius = radius;
	}

	bool aborted()
	{
		return _abort;
	}

	void ReadFromConsole()
	{
		string inp;
		cout << "Заполните все параметры космического тела. Для отмены введите /stop\n";
		for (int i = 0; i < 6; i++)
		{
			cout << msgs[i];
			cin >> inp;
			if (checkExit(inp))
			{
				_abort = true;
				break;
			}
			putValByIndex(inp, i);
		}
		cout << "\n";
	}

	void ReadFromFile(ifstream* fin)
	{
		(*fin) >> _name
			>> _distance
			>> _size
			>> _days
			>> _temperature
			>> _radius;
	}

	int getValByIndex(int index)
	{
		int(Cosmic_body::*funcs[])() = {
			&Cosmic_body::GetDistanceFormSun,&Cosmic_body::GetSize,&Cosmic_body::GetRotTime,&Cosmic_body::GetTemperature,&Cosmic_body::GetRadius
		};
		return (this->*funcs[index])();
	}

	~Cosmic_body() {}
};

string pName[5]
{
	"Расстояние до солнца",
	"Размер",
	"Время оборота вокруг солнца",
	"Температура",
	"Радиус"
};

void PrintCosmicBody(Cosmic_body* body)
{
	cout << body->GetClassName() << " " << body->GetName() << endl;
	for (int i = 0; i < 5; i++)
		cout << pName[i] << ": " << body->getValByIndex(i) << ";" << endl;
	cout << endl;
}

void SaveToFile(string FileName, Cosmic_body* body)
{
	ofstream fout(FileName.c_str(), ios_base::app);

	fout << body->GetClassName() << " " << body->GetName() << endl
		<< body->GetDistanceFormSun() << endl
		<< body->GetSize() << endl
		<< body->GetRotTime() << endl
		<< body->GetTemperature() << endl
		<< body->GetRadius() << endl;
}

class planet : public Cosmic_body
{
public:
	planet() {}
	planet(bool fromConsole) : Cosmic_body(fromConsole, 0) {	}

	string GetClassName() override
	{
		return "planet";
	}
};

class carlic_planet : public Cosmic_body
{
public:
	carlic_planet() {}
	carlic_planet(bool fromConsole) : Cosmic_body(fromConsole, 0) {	}

	string GetClassName() override
	{
		return "carlic_planet";
	}
};

class asteroid : public Cosmic_body
{
public:
	asteroid() {}
	asteroid(bool fromConsole) : Cosmic_body(fromConsole, 0) {	}

	string GetClassName() override
	{
		return "asteroid";
	}
};

class comet : public Cosmic_body
{
public:
	comet() {}
	comet(bool fromConsole) : Cosmic_body(fromConsole, 0) {	}

	string GetClassName() override
	{
		return "comet";
	}
};

class Creator
{
public:
	virtual Cosmic_body* FactoryMethod()
	{
		return new Cosmic_body();
	}
	~Creator() {}
};

class PlanetCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod() override
	{
		return new planet(true);
	};
};

class CarlicPlanetCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod() override
	{
		return new carlic_planet(true);
	};
};

class AsteroidCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod() override
	{
		return new asteroid(true);
	};
};

class CometCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod() override
	{
		return new comet(true);
	};
};

string** split(string str, char splitSymbol = ' ')
{
	vector<string> mass = vector<string>();
	string tmp = "";
	for each(char c in str)
	{
		if (c == splitSymbol)
		{
			if (tmp.length() > 0)
			{
				mass.push_back(tmp);
				tmp = "";
			}
		}
		else
			tmp.push_back(c);
	}

	if (tmp.length() > 0)
		mass.push_back(tmp);

	string** ret = (string**)malloc(sizeof(string*)*mass.size());
	for (int i = 0; i < mass.size(); i++)
		ret[i] = new string(mass.at(i));

	return ret;
};

static Cosmic_body** ReadFromFile(string file, int * size)
{
	*size = 0;
	Cosmic_body **ff = (Cosmic_body**)malloc(sizeof(Cosmic_body*));
	ifstream fin(file);
	while (1)
	{
		if (!fin.eof())
		{
			ff = (Cosmic_body**)realloc(ff, sizeof(Cosmic_body*)*((*size) + 1));
			Cosmic_body* b;
			string type;
			fin >> type;
			if (type == "planet")
				b = new planet();

			if (type == "carlic_planet")
				b = new carlic_planet();

			if (type == "asteroid")
				b = new asteroid();

			if (type == "comet")
				b = new comet();

			if (type == "")
				break;

			b->ReadFromFile(&fin);
			ff[*size] = b;
			(*size)++;
		}
		else break;
	}
	return ff;
};

string mainfile = "system.txt";
vector<Cosmic_body*> ssystem = vector<Cosmic_body*>();

void main(void) {
	setlocale(LC_ALL, "rus");
	system("color F0");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	static const size_t count = 4;
	Creator*creators[] = {
		new PlanetCreator(),new CarlicPlanetCreator(),new AsteroidCreator(),new CometCreator() };
	string command;
	while (true) {
		cout << "Введите команду. Для справки введите help\n";
		getline(cin, command);
		if (command == "") {
			getline(cin, command);
		}

		string** comArr = split(command);
		int commandEx = 0;

		if (*comArr[0] == "input") {
			if (*comArr[1] == "planet") {
				ssystem.push_back(creators[0]->FactoryMethod());
				commandEx++;
			}
			if (*comArr[1] == "carlic")
				if (*comArr[2] == "planet") {
					ssystem.push_back(creators[1]->FactoryMethod());
					commandEx++;
				}
			if (*comArr[1] == "asteroid")
			{
				ssystem.push_back(creators[2]->FactoryMethod());
				commandEx++;
			}
			if (*comArr[1] == "comet")
			{
				ssystem.push_back(creators[3]->FactoryMethod());
				commandEx++;
			}
		}

		if (*comArr[0] == "show") {
			if (ssystem.size() == 0)
				cout << "Сначала добавьте значения" << endl;
			else
				for each (Cosmic_body *b in ssystem)
					PrintCosmicBody(b);
			commandEx++;
		}

		if (*comArr[0] == "help")
		{
			//input
			cout << "input <тип>\n"
				<< "Команда позволяет ввести обьект с клавиатуры" << endl
				<< "тип может быть одним из следующих: planet, carlic planet, asteroid, comet" << endl << endl;

			//show
			cout << "show" << endl
				<< "Команда предназначена для вывода на экран всех ссозданных космических тел" << endl << endl;

			//file
			cout << "file <команда>" << endl
				<< "open: считывает данные из файла" << endl
				<< "save: считывает данные из файла" << endl << endl;

			//delete
			cout << "delete [id]" << endl
				<< "Удаляет запись с оответствующим индексом" << endl << endl;

			//clear 
			cout << "clear" << endl
				<< "Очищает массив данных программы, все несохраненные данные будут безвозвратно утеряны" << endl << endl;

			//exit
			cout << "exit" << endl
				<< "выход из программы" << endl << endl;

			commandEx++;
		}

		if (*comArr[0] == "file") {
			if (*comArr[1] == "open") {
				int count = 0;
				Cosmic_body** bodyes = ReadFromFile(mainfile, &count);
				for (int i = 0; i < count; i++)
					ssystem.push_back(bodyes[i]);
				cout << "Успешно!" << endl;
				commandEx++;
			}
			if (*comArr[1] == "save") {
				FILE * f = fopen(mainfile.c_str(), "w");
				for each (Cosmic_body *b in ssystem)
					SaveToFile(mainfile, b);
				cout << "Успешно!" << endl;
				commandEx++;
			}
		}

		if (*comArr[0] == "delete")
		{
			int p = stoi(*comArr[1]);
			ssystem.erase(ssystem.begin()+p);
			commandEx++;
		}

		if (*comArr[0] == "clear")
		{
			ssystem = vector<Cosmic_body*>();
			commandEx++;
		}

		if (*comArr[0] == "exit")
			break;

		if (commandEx == 0)
			cout << "Команда не найдена" << endl;
	}
}