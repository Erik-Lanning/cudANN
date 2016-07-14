#pragma once

namespace cudANN
{
	template<typename T, typename... NextVar>
	static bool isEqual(T expectedValue, T nextVariable, NextVar... args)
	{
		if (expectedValue != nextVariable)
			return false;
		else
			return isEqual(expectedValue, args...);
	}

	template<typename T>
	static bool isEqual(T expectedValue, T finalVariable)
	{
		return (expectedValue == finalVariable);
	}
}