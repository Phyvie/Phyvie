#include "FunctionBlueprint.h"
#include <iostream>
#include <array>
#include <string>
#include <functional>

using String = std::string; 

class ModuloChar
{
public: 
	char storedChar; 

	ModuloChar(char storedChar) : storedChar(storedChar) {}; 
	static ModuloChar addModuloChars(const ModuloChar& a, const ModuloChar& b)
	{
		return ModuloChar((a.storedChar + b.storedChar)%127); 
	}
};

class ModuloString
{
public: 
	String storedString; 
	ModuloString(String storedString) : storedString(storedString) {}; 
	static ModuloString addModuloStrings(const ModuloString& a, const ModuloString& b)
	{
		std::string resultString = a.storedString.length() > b.storedString.length() ? a.storedString : b.storedString;
		for (int i = 0; i < a.storedString.length(); i++)
		{
			resultString[i] = ModuloChar::addModuloChars(a.storedString[i], b.storedString[i]).storedChar;
		}
		return resultString;
	}
};

String PrintIntWrapper(TwoIntsWrapper intWrapper)
{
	return String("(") + std::to_string(intWrapper.wrappedInt) + ", " + std::to_string(intWrapper.secondWrappedInt) + ")";
}

void functionTemplateStuff()
{
	TwoIntsWrapper firstIntWrapper(3, 6); 
	TwoIntsWrapper secondIntWrapper(5, 4); 
	double firstDouble(5);
	String firstString("s"); 
	//std::cout << maximum(3, s) << std::endl; //miezeKatze intelliSense is not stopping me from doing this, only the compiler figures out there is a problem
	/*std::cout << maximum(a, b) << std::endl;*/ 

	int intArray[3]; 
	intArray[0] = 3; 
	intArray[1] = 4; 
	intArray[2] = 5; 
	int* intArrayPointer = intArray; 
	std::cout << ArraySum(intArray, 3) << std::endl; 
	std::cout << ArraySum(intArray) << std::endl; 
	std::cout << maximum(intArray) << std::endl; 
	//std::cout << ArraySum(intArrayPointer, 3) << std::endl;

	std::array<int, 5> c11standardArray = { 3, 4, 5, 6, 7 };
	std::cout << c11standardArray[0] << std::endl;
	std::cout << printFirstEntry(c11standardArray) << std::endl;
	std::cout << ArraySum(c11standardArray, 0) << std::endl; 

	std::array<String, 3> stringArray = { "Hello ", "World! ", "\n miezeKatze" }; 
	std::cout << ArraySum(stringArray, String("")) << std::endl;
	std::cout << maximum(stringArray) << std::endl; 
	std::cout << maximum(*reinterpret_cast<String(*)[stringArray.size()]>(stringArray.data())) << std::endl;

	int five = 5; 
	int(*functionPointer)(int& firstint) = increaseByOneReturnPlus2; 
	int seven = functionPointer(five); 
	std::cout << "five: " << five << "; functionPoitnerReturn: " << functionPointer(five) << std::endl;

	TwoIntsWrapper intWrapperArray[3] = {TwoIntsWrapper(5, 2), TwoIntsWrapper(4, 4), TwoIntsWrapper(3, 3)};
	std::vector<TwoIntsWrapper> intWrapperVector = { TwoIntsWrapper(5, 2), TwoIntsWrapper(4, 4), TwoIntsWrapper(3, 3) };

	const String(TwoIntsWrapper:: * mewow)() = NULL;
	TwoIntsWrapper intWrapper = intWrapperVector[0]; 
	mewow = &TwoIntsWrapper::stringCast; 

	String(*sortFunctionPointerFromLambda)(TwoIntsWrapper intWrapper) = [](TwoIntsWrapper intWrapper) { return intWrapper.stringCast(); };
	PrintVector(intWrapperVector, sortFunctionPointerFromLambda);
	//PrintVector(intWrapperVector, [](TwoIntsWrapper intWrapper)->String { return intWrapper.stringCast(); }); //zypernKatze figure this out
	//zypernKatze figure out how to give member-function as function-pointer-parameter to function

	/*double (*maximumCastDouble)(double a, int b) = maximum<double, int>; 
	std::cout << maximum("a", "b") << std::endl; */

	Print("meow", "mewow", "meownz", "meownze", "meownzeKatze");

	ModuloChar firstModuloChar('a');
	ModuloChar secondModuloChar('b');
	std::cout << ModuloChar::addModuloChars(firstModuloChar, secondModuloChar).storedChar << std::endl;
	ModuloString firstModuloString("aa");
	ModuloString secondModuloString("bbbb"); 
	std::cout << ModuloString::addModuloStrings(firstModuloString, secondModuloString).storedString << std::endl; 

	Accumulator<int> intAccumulator(0);
	// Accumulator<int> intAccumulatorCopy(); //this declares a function 
	// std::string stringFunction(); //this declares a function
	//std::function<int(double)> dL = ; 
	String testString = String("meow"); 
	std::function<int(String)> sL = [](String s) { return s.length(); };
	std::cout << intAccumulator.addValues(testString, sL, 5.0, static_cast<std::function<int(double)>>([](double d) { return static_cast<int>(d); })) << std::endl;

	auto addUpVector = []<typename T, typename R>(std::vector<T> vector, std::function<R(T)> map) 
	{ 
		R result = map(vector[0]); 
		for (int i = 1; i < vector.size(); i++)
		{
			result += map(vector[i]); 
		}
		return result; 
	};
	

	std::function<int(std::vector<String>)> combiSL = [sL](std::vector<String> strings)
	{
		int result = sL(strings[0]); 
		for (int i = 1; i < strings.size(); i++)
		{
			result += sL(strings[i]);
		}
		return result; 
	}; 
	std::cout << intAccumulator.addValues(strings, combiSL) << std::endl; 

	auto makeForEachFunction = []<typename T, typename R>(std::function<R(T)> mappingFunction)->std::function<R(std::vector<T>)>
	{
		return [mappingFunction](std::vector<T> vector) -> R 
		{
			R result = mappingFunction(vector[0]);
			for (int i = 1; i < vector.size(); i++)
			{
				result += mappingFunction(vector[i]); 
			}
			return result;
		};
	};

	std::vector<String> strings{"meow", "wuff", "m�h"};
	std::cout << intAccumulator.addValues(strings, makeForEachFunction(sL)) << std::endl;
	std::cout << intAccumulator.addValues(strings, sL) << std::endl;
}

template<typename T, int size>
T maximum(T(&refArray)[size])
{
	if (size == 0)
	{
		return NULL;
	}
	T result = refArray[0];
	for (int i = 0; i < size; i++)
	{
		if (refArray[i] > result)
		{
			result = refArray[i];
		}
	}
	return result;
}

int increaseByOneReturnPlus2(int& increaseByOne)
{
	std::cout << "pointing to this function" << std::endl; 
	increaseByOne++; 
	return increaseByOne+1; 
}

template<typename t, typename r> t maximum(t a, r b)
{
	return (a > b) ? a : b; 
}

template<> const char* maximum(const char* x, const char* y)
{
	std::cout << "maximum<const char*>()" << std::endl;
	return std::strcmp(x, y) > 0 ? x : y;
}

template<typename T, int size>
T maximum(std::array<T, size> refArray)
{
	if (size == 0)
	{
		return NULL;
	}
	T result = refArray[0];
	for (int i = 0; i < size; i++)
	{
		if (refArray[i] > result)
		{
			result = refArray[i];
		}
	}
	return result;
}

template<typename T> 
T Add(T a, T b)
{
	return a + b; 
}

template <typename T>
T ArraySum(T* pArray, int arrSize)
{
	if (arrSize == 1)
	{
		return *pArray; 
	}
	return *pArray + ArraySum(pArray + 1, arrSize-1); 
}

template <typename T, int size>
T ArraySum(T (&pArray)[size])
{
	if (size == 0)
	{
		return NULL; 
	}
	T result = pArray[0]; 
	for (int i = 1; i < size; i++)
	{
		result += pArray[i]; 
	}
	return result; 
}


template<typename T, std::size_t size>
T printFirstEntry(std::array<T, size> array)
{
	std::cout << array[0] << std::endl; 
	return array[0]; 
}

template <typename T, std::size_t size>
T ArraySum(std::array<T, size> array, T emptyResult)
{ 
	for (int i = 0; i < size; i++)
	{
		emptyResult += array[i]; 
	}
	return emptyResult; 
}

template<typename T>
std::vector<T> SortVectorByFunction(std::vector<T>& toSort, bool(*comparisonFunction)(T, T))
{
	for (int startIndex = 0; startIndex < toSort.size(); startIndex++)
	{
		int bestIndex = startIndex; 
		for (int i = startIndex; i < toSort.size(); i++)
		{
			if (comparisonFunction(toSort[i], toSort[bestIndex]))
			{
				bestIndex = i; 
			}
			std::swap(toSort[startIndex], toSort[bestIndex]);
		}
	}
}

template<typename T>
String PrintVector (const std::vector<T>& toPrint, String(*stringCastFunction)(T))
{
	String result = String("(") + stringCastFunction(toPrint[0]);
	for (int i = 1; i < toPrint.size(); i++)
	{
		result += ", "; 
		result += stringCastFunction(toPrint[i]);
	}
	result += ")"; 
	std::cout << result << std::endl; 
	return result; 
}

template<typename T>
String PrintVector(const std::vector<T>& toPrint, const String(*stringCastFunction)())
{
	String result = String("(") + stringCastFunction(toPrint[0]);
	for (int i = 1; i < toPrint.size(); i++)
	{
		result += ", ";
		result += toPrint[i].stringCastFunction(); 
	}
	result += ")";
	std::cout << result << std::endl;
	return result;
}

template<typename T, typename... Args>
String Print(T arg, Args... args)
{
	std::cout << static_cast<String>(arg) << ", ";
	return arg + Print(args...);
}

template<typename T>
String Print(T arg)
{
	std::cout << static_cast<String>(arg) << std::endl;
	return arg; 
}
