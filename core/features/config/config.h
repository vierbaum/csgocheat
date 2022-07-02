#pragma once
#include "includes.h"

template <typename T>
struct ConfigVar {
	ConfigVar() = default;
	ConfigVar(std::string _category, std::string _name, T _val, int _size = 0) {
		category = _category;
		name = _name;
		val = _val;
		size = _size;
	}

	std::string category, name;
	T val;
	int size;
};

class Config {
	// CHEAT VARS GO HERE
private:
	int bunnyhop;
	int lagcomp;

	int chamtype;
	int enemychamsvis;
	float enemyviscol[4];
	int enemychamsinvis;
	float enemyinviscol[4];
	int lagcompchams;

	int nameesp;
	int boxesp;
	int healthesp;

	int legitbot;
	float legitsmoothing[3];
	float legitfov[3];
	float legitrcs[3];

	// GRAPHS
	double legitgraph[8];

	// access variables using these maps
public:
	std::unordered_map<std::string, ConfigVar<int>> ints;
	std::unordered_map<std::string, ConfigVar<float>> floats;

	std::unordered_map<std::string, ConfigVar<int*>> arrints;
	std::unordered_map<std::string, ConfigVar<float*>> arrfloats;

	std::unordered_map<std::string, ConfigVar<double*>> graphs;

public:
	int iSelConfig = 0;
	void Save(std::string name);
	void Load(std::string name);
	Config() { Init(); }

private:
	void Init();

	// normal vars
	void SetupVal(int& i, int def, std::string category, std::string name);
	void SetupVal(float& f, float def, std::string category, std::string name);

	// arrays
	void SetupVal(int* i, std::vector<int> defs, int size, std::string category, std::string name);
	void SetupVal(float* f, std::vector<float> defs, int size, std::string category, std::string name);

	// graphs
	void SetupVal(double* d, std::vector<double> defs, std::string category, std::string name);
};

extern Config g_Config;