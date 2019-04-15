#pragma once

enum typeArg
{
	intArg,
	stringArg
};

struct OptionArg
{
	const char* name;
	typeArg type;
	void* varPtr;
	int min;
};

struct Option
{
	const char* shortArg;
	const char* longArg;
	const char* description;
	int argCount;
	OptionArg* args;
	bool* present;
};

class ArgsParser
{
private:
	Option* listArgs;
	int maxArgs;
	int currentArgs;
public:
	ArgsParser(const int nbArgs);
	void add(const char* shortArg, const char* longArg, const char* description, const int argCount, OptionArg* args, bool* present);
	void add(Option option);
	void execute(const int argc, char** argv);
	int help(char** text);
	~ArgsParser();
};

