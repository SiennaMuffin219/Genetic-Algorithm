#include "pch.h"
#include "ArgsParser.h"
#include <limits>
#include <string.h>
#include <string>


ArgsParser::ArgsParser(const unsigned nbArgs)
{
	listArgs = new Option[nbArgs];
	maxArgs = nbArgs;
	currentArgs = 0;
}

void ArgsParser::add(const char* shortArg, const char* longArg, const char* description, const int argCount, OptionArg* args, bool* present)
{
	if (currentArgs > maxArgs)
	listArgs[currentArgs].shortArg = shortArg;
		throw std::out_of_range("Too much arguments, increase nbArgs in constructor");
	listArgs[currentArgs].longArg = longArg;
	listArgs[currentArgs].description = description;
	listArgs[currentArgs].argCount = argCount;
	listArgs[currentArgs].args = args;
	listArgs[currentArgs].present = present;
	*listArgs[currentArgs].present = false;
	
	currentArgs++;
}

void ArgsParser::add(Option option)
{
	if (currentArgs > maxArgs)
		throw std::out_of_range("Too much arguments, increase nbArgs in constructor");
	listArgs[currentArgs].shortArg = option.shortArg;
	listArgs[currentArgs].longArg = option.longArg;
	listArgs[currentArgs].description = option.description;
	listArgs[currentArgs].argCount = option.argCount;
	listArgs[currentArgs].args = option.args;
	if (option.present != nullptr)
		listArgs[currentArgs].present = option.present;
	else
		listArgs[currentArgs].present = new bool;

	*listArgs[currentArgs].present = false;
	
	currentArgs++;
}

void ArgsParser::execute(const unsigned argc, char** argv)
{
	for (size_t i = 1; i < argc; i++)
	{
		for (size_t j = 0; j < currentArgs; j++)
		{
			if (strcmp(argv[i], listArgs[j].shortArg) == 0 || strcmp(argv[i], listArgs[j].longArg) == 0)
			{
				*listArgs[j].present = true;
				if (listArgs[j].argCount > 0)
				{
					if (argc < i + listArgs[j].argCount + 1)
					{
						char excep[128];
						snprintf(excep, 128, "Expected an integer value after %s", argv[i]);
						throw std::runtime_error(excep);
					}
					for (size_t k = 0; k < listArgs[j].argCount; k++)
					{
						try
						{
							switch (listArgs[j].args[k].type)
							{
							case intArg:
								*(int*)(listArgs[j].args[k].varPtr) = std::stoi(argv[i + k + 1]);
								if (*(int*)listArgs[j].args[k].varPtr < listArgs[j].args[k].min)
									throw std::out_of_range("Value less than minimum");
								break;
							case stringArg:
								memcpy((char*)listArgs[j].args[k].varPtr, argv[i + k + 1], 256);
							default:
								break;
							}
						}
						catch (std::invalid_argument)
						{
							char excep[128];
							snprintf(excep, 128, "Bad input: %s %s should be an integer.", argv[i], argv[i + k + 1]);
							throw std::runtime_error(excep);
						}
						catch (std::out_of_range)
						{
							char excep[128];
							snprintf(excep, 128, "Bad input: %s %s out of range (should be between %d and %d).", argv[i], argv[i + k + 1], listArgs[j].args[k].min, INT32_MAX);
							throw std::runtime_error(excep);
						}
					}
				}
			}
		}
	}
}

unsigned ArgsParser::help(char* text[256])
{
	text[0] = new char[32];
	strcpy(text[0], "Usage: AlgoGen [options]");
	text[1] = new char[32];
	strcpy(text[1], "");
	text[2] = new char[32];
	strcpy(text[2], "Options:");

	size_t maxChars = 0;
	char* firstPart[128];
	for (size_t i = 0; i < currentArgs; i++)
	{
		char args[64] = "";
		if (listArgs[i].argCount > 0)
			snprintf(args, 64, "<%s>", listArgs[i].args[0].name);
		firstPart[i] = new char[128];
		snprintf(firstPart[i], 128, "  %s %s %s", listArgs[i].shortArg, listArgs[i].longArg, args);
		size_t len = strlen(firstPart[i]);
		if (len > maxChars)
			maxChars = len;
	}
	for (size_t i = 0; i < currentArgs; i++)
	{
		for (size_t j = strlen(firstPart[i]); j < maxChars; j++)
			strncat(firstPart[i], " ", 128);
		text[i + 3] = new char[256];
		snprintf(text[i + 3], 256, "  %s  %s", firstPart[i], listArgs[i].description);
	}
	return currentArgs + 3;
}


ArgsParser::~ArgsParser()
{
	delete[] listArgs;
}
