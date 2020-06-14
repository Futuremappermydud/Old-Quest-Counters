#include "include/Main.hpp"
using std::string;

namespace CustomCounters
{
	class Counter
	{
		public:
		string Data = "0";
		string Name = "Test Counter: ";
		enum CounterType { Decrease, Increase, } Type = Increase;
		void* IncrementFunction;
		Counter(string name, string data, CounterType type, void* incrementFunction) {
			Name = name;
			Data = data;
			Type = type;
			IncrementFunction = incrementFunction;
		}
	};
}