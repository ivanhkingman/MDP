// Reminder to myself about template classes:
// Template classes are nifty ways of creating a generic class which may be associated with different data types
// STL libriary in C++ is an example of this: Vectors have many implementations, as they are vector of a certain
// type, e.g. "Vectors of strings".

// This is often useful for storage classes, but in my case, this creates a generic State class. A State can now
// be represented as any type the user of the class wants to

template<typename T>
class State
{
public:
	State() {};
	State(T state) : m_state(state) {};
	~State() {};
	T getState() { return state; };

// TODO: Get this comparator operator working
private:
	T m_state;
	bool operator< (const State<T> &st1, const State<T> &st2) const {
		return *st1 < *st2;
	};
};