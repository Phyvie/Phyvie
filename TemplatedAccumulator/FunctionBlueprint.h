#pragma once
#include <array>
#include <vector>
#include <string>
#include <functional>

using String = std::string; 

class TwoIntsWrapper; 
class ModuloChar; 
class ModuloString; 

template<typename T>
class Accumulator
{
private:
	T value;

public:
	Accumulator() = delete;
	Accumulator(T initialValue) : value(initialValue) {}

	template<typename R, typename S, typename... Rest>
	T addValues(R r, std::function<T(R)> rmap, S s, std::function<T(S)> smap, Rest... rest)
	{
		value += rmap(r);
		return addValues<S, Rest...>(s, smap, rest...);
	}
	template<typename R>
	T addValues(R r, std::function<T(R)> rmap)
	{
		value += rmap(r);
		return value; 
	}
	template<typename R, typename S, typename... Rest>
	T addValues(std::vector<R> rVector, std::function<T(R)> rmap, S s, std::function<T(S)> smap, Rest... rest)
	{
		for (R r : rVector)
		{
			value += rmap(r); 
		}
		return addValues<S, Rest...>(s, smap, rest...); 
	}
	template<typename R>
	T addValues(std::vector<R> rVector, std::function<T(R)> rmap)
	{
		for (R r : rVector)
		{
			value += rmap(r);
		}
		return value;
	}
};

void functionTemplateStuff();
int increaseByOneReturnPlus2(int& increaseByOne); 

template<typename T, int size>
T maximum(T (&refArray)[size]);
template<typename T, int size>
T maximum(std::array<T, size>); 
template<typename T, typename R>
T maximum(T a, R b);
template<> const char* maximum(const char* x, const char* y); 
template<typename T> 
T Add(T a, T b); 
template<typename T> 
T ArraySum(T* pArray, int arraySize);
template<typename T, int size>
T ArraySum(T (&pArray)[size]);
template<typename T, std::size_t size>
T printFirstEntry(std::array<T, size> array); 
template <typename T, std::size_t size>
T ArraySum(std::array<T, size> array, T emptyResult); 

template<typename T>
std::vector<T> SortVectorByFunction(std::vector<T>& toSort, bool(*comparisonFunction)(T, T)); 
template<typename T>
String PrintVector(const std::vector<T>& toPrint, String(*stringCastFunction)(T)); 

//zypernKatze this should be avoidable
String PrintIntWrapper(TwoIntsWrapper intWrapper); 
template<typename T, typename... Args>
String Print(T arg, Args... args); 
template<typename T>
String Print(T arg); 

