#include <iostream>
#include <string>
using namespace std;

class Cosmic_body
{
	string _name;
	int _distance;
	int _size;
	int _days;
	int _temperature;
	int _radius;
public:
	Cosmic_body();
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

	void SaveToFile(string FileName)
	{
		FILE* f = fopen(FileName.c_str(), "w");
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

	void ReadFromFile(string FileName)
	{
		FILE * f = fopen(FileName.c_str(), "r");
		string s;
		fscanf(f, "%s", s);
		fscanf(f, "%s", _name);
		fscanf(f, "%i", _distance);
		fscanf(f, "%i", _size);
		fscanf(f, "%i", _days);
		fscanf(f, "%i", _temperature);
		fscanf(f, "%i", _radius);
	}

	virtual ~Cosmic_body();
};

class planet: public Cosmic_body
{
	virtual string GetClassName()
	{
		return "planet";
	}
};

class carlic_planet: public Cosmic_body
{
	virtual string GetClassName()
	{
		return "carlic_planet";
	}
};

class asteroid: public Cosmic_body
{
	virtual string GetClassName()
	{
		return "asteroid";
	}
};

class comet: public Cosmic_body
{
	virtual string GetClassName()
	{
		return "comet";
	}
};

class Creator
{
public:
	virtual Cosmic_body* FactoryMethod();
	virtual ~Creator();
};

class PlanetCreator: public Creator
{
public:
	virtual  Cosmic_body* FactoryMethod()
	{
		return new planet();
	};
};

class CarlicPlanetCreator : public Creator
{
public:
	virtual  Cosmic_body* FactoryMethod()
	{
		return new carlic_planet();
	};
};

class AsteroidCreator : public Creator
{
public:
	virtual  Cosmic_body* FactoryMethod()
	{
		return new asteroid();
	};
};

class CometCreator : public Creator
{
public:
	virtual  Cosmic_body* FactoryMethod()
	{
		return new comet();
	};
};

void main (void){

}