#include "precomp.h"

#include "src/IJSONParser/ijsonparser.h"

#include <fstream>

namespace Engine
{
	json IJSONParser::ReadFile(const std::string& filePath)
	{
		std::ifstream f(filePath, std::ios::in);
		if (!f.is_open())
		{
			LOG_ERROR("Could not open json file: %s", filePath);
			return {};
		}
		json data = json::parse(f, nullptr);
		f.close();
		return data;
	}

	bool IJSONParser::CheckIsBoolWithError(const json& input) const
	{
		if (!input.is_boolean())
		{
			LOG_ERROR("Parsed json object is not bool! %s", input);
			return false;
		}
		return true;
	}

	bool IJSONParser::CheckIsNumberWithError(const json& input) const
	{
		if (!input.is_number())
		{
			LOG_ERROR("Parsed json object is not number! %s", input);
			return false;
		}
		return true;
	}

	bool IJSONParser::CheckIsStringWithError(const json& input) const
	{
		if (!input.is_string())
		{
			LOG_ERROR("Parsed json object is not string! %s", input);
			return false;
		}
		return true;
	}

	bool IJSONParser::CheckIsObjectWithError(const json& input) const
	{
		if (!input.is_object())
		{
			LOG_ERROR("Parsed json object is not object! %s", input);
			return false;
		}
		return true;
	}

	bool IJSONParser::CheckIsValidWithError(const json& input) const
	{
		if (input.is_discarded())
		{
			LOG_ERROR("Parsed json object is discarded value! %s", input);
			return false;
		}
		return true;
	}
}