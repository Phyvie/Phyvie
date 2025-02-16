#include "Lambda.h"

std::string printLambda(std::string toPrint)
{
	auto funcCapture = [toPrint] () {
		std::cout << toPrint << " printed via capture List" << std::endl;
	};

    auto funcCaptureReference = [&toPrint]() {
        std::cout << toPrint << " printed via capture List as reference" << std::endl;
    };
    auto funcParameter = [](std::string toPrint) {
        std::cout << toPrint << " printed as Parameter" << std::endl;
    };

    funcCapture();
    funcCaptureReference(); 
    funcParameter(toPrint); 
    toPrint = "neuezypernKatze"; 
    funcCapture(); 
    funcCaptureReference(); 
    funcParameter(toPrint); 

	return toPrint; 
}

void lambdaArithmetic()
{
    int a = 5;
    int b = 7;

    auto additionFunc = [](int a, int b)
    {
        return a + b;
    };
    auto multiplicationFunc = [](int a, int b)
    {
        return a * b;
    };
    auto stringReturner = [](std::string aString) -> std::string
    {
        return aString;
    };

    auto currentOperation = stringReturner;

    std::cout << currentOperation("aString") << std::endl;

    //std::cout << (currentOperation("aString") + 5) << "added 5 after addition" << std::endl;
    std::cout << (additionFunc(5, 7) + 5) << "added 5 after addition" << std::endl;

    /*
    currentOperation = multiplicationFunc;
    std::cout << currentOperation(a, b) << std::endl;
    */
}

void lambdaStuff(std::string printLambdaString)
{
    
}