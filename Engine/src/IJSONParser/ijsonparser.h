#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Engine
{
	class IJSONParser
	{
	public:
		IJSONParser() = default;
		virtual ~IJSONParser() = default;

		virtual json ReadFile(const std::string& filePath);
		virtual void ProcessJSON(json input) = 0;

	protected:
		bool CheckIsBoolWithError(const json& input) const;
		bool CheckIsNumberWithError(const json& input) const;
		bool CheckIsStringWithError(const json& input) const;
		bool CheckIsObjectWithError(const json& input) const;
		bool CheckIsValidWithError(const json& input) const;
	};
}