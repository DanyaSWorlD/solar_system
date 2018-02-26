#include <iostream>
#include <string>
#include <vector>
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
	Cosmic_body(){}
	Cosmic_body(bool fromConsole)
	{
		if (fromConsole)
			ReadFromConsole();
	}

	virtual string GetClassName();
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
	void SaveToFile(string FileName)
	{
		FILE* f = fopen(FileName.c_str(), "a");
		string s;
		s.append(GetClassName()).append(" ").append(GetName()).append("\n");
		s.append(std::to_string(GetDistanceFormSun())).append("\n");
		s.append(std::to_string(GetSize())).append("\n");
		s.append(std::to_string(GetRotTime())).append("\n");
		s.append(std::to_string(GetTemperature())).append("\n");
		s.append(std::to_string(GetRadius())).append("\n");
		fprintf(f, s.c_str());
	}

	void print()
	{
		string s;
		s.append(GetClassName()).append(" ").append(GetName()).append("\n");
		s.append(std::to_string(GetDistanceFormSun())).append("\n");
		s.append(std::to_string(GetSize())).append("\n");
		s.append(std::to_string(GetRotTime())).append("\n");
		s.append(std::to_string(GetTemperature())).append("\n");
		s.append(std::to_string(GetRadius())).append("\n");
		cout << s;
	}

	void ReadFromConsole()
	{
		string inp;
		cout << "Заполните все параметры космического тела. Для отмены введите /stop";
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

	void ReadFromFile(FILE* f)
	{
		fscanf(f, "%s", _name);
		fscanf(f, "%i", _distance);
		fscanf(f, "%i", _size);
		fscanf(f, "%i", _days);
		fscanf(f, "%i", _temperature);
		fscanf(f, "%i", _radius);
	}


	virtual ~Cosmic_body() {}
};

class planet : public Cosmic_body
{
public:
	planet() {}
	planet(bool fromConsole) : Cosmic_body(fromConsole) {	}

	string GetClassName()
	{
		return "planet";
	}
};

class carlic_planet : public Cosmic_body
{
public:
	carlic_planet() {}
	carlic_planet(bool fromConsole) : Cosmic_body(fromConsole) {	}

	string GetClassName()
	{
		return "carlic_planet";
	}
};

class asteroid : public Cosmic_body
{
public:
	asteroid() {}
	asteroid(bool fromConsole) : Cosmic_body(fromConsole) {	}

	string GetClassName()
	{
		return "asteroid";
	}
};

class comet : public Cosmic_body
{
public:
	comet() {}
	comet(bool fromConsole) : Cosmic_body(fromConsole) {	}

	string GetClassName()
	{
		return "comet";
	}
};

class Creator
{
public:
	virtual Cosmic_body* FactoryMethod();
	virtual ~Creator() {}
};

class PlanetCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod()
	{
		return new planet(true);
	};
};

class CarlicPlanetCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod()
	{
		return new carlic_planet(true);
	};
};

class AsteroidCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod()
	{
		return new asteroid(true);
	};
};

class CometCreator : public Creator
{
public:
	Cosmic_body* FactoryMethod()
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

static Cosmic_body* ReadFromFile(string file, int * size)
{
	*size = 0;
	Cosmic_body *ff = (Cosmic_body*)malloc(sizeof(Cosmic_body));
	FILE* f = fopen(file.c_str(), "r");
	while (1)
	{
		if (!feof(f))
		{
			ff = (Cosmic_body*)realloc(ff, sizeof(Cosmic_body)*((*size) + 1));
			Cosmic_body* b;
			string type;
			cin >> type;
			if (type == "planet")
				b = new planet();

			if (type == "carlic_planet")
				b = new carlic_planet();

			if (type == "asteroid")
				b = new asteroid();

			if (type == "comet")
				b = new comet();

			b->ReadFromFile(f);
			ff[*size] = (*b);
		}
		else break;
	}
	return ff;
};

string mainfile = "system.txt";
vector<Cosmic_body> ssystem = vector<Cosmic_body>();

void main(void) {
	setlocale(LC_ALL, "rus");
	static const size_t count = 4;
	Creator*creators[] = {
		&PlanetCreator(),&CarlicPlanetCreator(),&AsteroidCreator(),&CometCreator() };
	string command;
	while (1) {
		cout << "Введите команду. Для справки введите help\n";
		getline(cin, command);
		string** comArr = split(command);
		if (*comArr[0] == "save") {
			FILE * f = fopen(mainfile.c_str(), "w");
			for each (Cosmic_body b in ssystem)
				b.SaveToFile(mainfile);
		}

		if (*comArr[0] == "input") {
			if (*comArr[1] == "planet")
				ssystem.push_back(creators[0]->FactoryMethod());
			if (*comArr[1] == "carlic")
				if (*comArr[2] == "planet")
					ssystem.push_back(creators[1]->FactoryMethod());
			if (*comArr[1] == "asteroid")
				ssystem.push_back(creators[2]->FactoryMethod());
			if (*comArr[1] == "comet")
				ssystem.push_back(creators[3]->FactoryMethod());
		}

		if (*comArr[0] == "help")
		{

		}

		if (*comArr[0] == "file")
			if (*comArr[1] == "open") {
				int count = 0;
				Cosmic_body* bodyes = ReadFromFile(mainfile, &count);
				for (int i = 0; i < count; i++)
					ssystem.push_back(bodyes[i]);
			}

		if (*comArr[0] == "exit")
			break;
	}

}