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
	unsigned argCount;
	OptionArg* args;
	bool* present;
};

class ArgsParser
{
private:
	Option* listArgs;
	unsigned maxArgs;
	unsigned currentArgs;
public:
	ArgsParser(const unsigned nbArgs);
	void add(const char* shortArg, const char* longArg, const char* description, const int argCount, OptionArg* args, bool* present);
	void add(Option option);
	void execute(const unsigned argc, char** argv);
	unsigned help(char** text);
	~ArgsParser();
};

