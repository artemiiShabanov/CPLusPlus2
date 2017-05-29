#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>


class  Computer
{
public:

	int code;
	std::string mark;
	std::string processor;
	int frequency;
	int ram_amount;
	int hdd_capacity;
	int vm_amount;
	int value;
	int count;

	Computer(int _code, std::string _mark, std::string _proc, int _freq, int _ram, int _hdd,
		int _vm, int _value, int _count)
	{
		code = _code;
		mark = _mark;
		processor = _proc;
		frequency = _freq;
		ram_amount = _ram;
		hdd_capacity = _hdd;
		vm_amount = _vm;
		value = _value;
		count = _count;
	}

	Computer()
	{
		code = 0;
		mark = "";
		processor = "";
		frequency = 0;
		ram_amount = 0;
		hdd_capacity = 0;
		vm_amount = 0;
		value = 0;
		count = 0;
	}

	~Computer()
	{
	}

	bool operator==(const Computer& that) const
	{
		return	this->code == that.code;
	}


};


std::ostream& operator<<(std::ostream &os, const Computer &comp) {
	/*os << "|| code: " + std::to_string(comp.code) + "  " +
	"mark: " + comp.mark + "  " +
	"proc: " + comp.processor + "  " +
	"freq: " + std::to_string(comp.frequency) + "  " +
	"ram: " + std::to_string(comp.ram_amount) + "  " +
	"hdd: " + std::to_string(comp.hdd_capacity) + "  " +
	"vm: " + std::to_string(comp.vm_amount) + "  " +
	"value: " + std::to_string(comp.value) + "  " +
	"count: " + std::to_string(comp.count) + "||\n";*/
	os << std::to_string(comp.code) + "\t" +
		comp.mark + "\t" +
		comp.processor + "\t" +
		std::to_string(comp.frequency) + "\t" +
		std::to_string(comp.ram_amount) + "\t" +
		std::to_string(comp.hdd_capacity) + "\t" +
		std::to_string(comp.vm_amount) + "\t" +
		std::to_string(comp.value) + "\t" +
		std::to_string(comp.count) + "\n";
	return os;
}

std::istream& operator >> (std::istream& is, Computer &comp)
{
	is >> comp.code;
	is >> comp.mark;
	is >> comp.processor;
	is >> comp.frequency;
	is >> comp.ram_amount;
	is >> comp.hdd_capacity;
	is >> comp.vm_amount;
	is >> comp.value;
	is >> comp.count;

	return is;
}


Computer inputComputer();

//Predicats and Comparators

class ProcPred
{
protected:
	std::string proc;

public:
	ProcPred(std::string _proc)
	{
		proc = _proc;
	}

	bool operator() (Computer comp)  
	{
		return comp.processor == proc;
	}

};

class RAMPred
{
protected:
	int ram;

public:
	RAMPred(int _ram)
	{
		ram = _ram;
	}

	bool operator() (Computer comp)
	{
		return comp.ram_amount == ram;
	}

};

class VMPred
{
protected:
	int vm;

public:
	VMPred(int _vm)
	{
		vm = _vm;
	}

	bool operator () (Computer comp)
	{
		return comp.vm_amount == vm;
	}

};

class HDDPred 
{
protected:
	int hdd;

public:
	HDDPred(int _hdd)
	{
		hdd = _hdd;
	}

	bool operator () (Computer comp)
	{
		return comp.hdd_capacity == hdd;
	}

};


class ProcComp 
{
public:
	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.processor < comp2.processor;
	}
};

class RAMComp 
{
public:
	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.ram_amount < comp2.ram_amount;
	}
};

class VMComp
{
public:
	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.vm_amount < comp2.vm_amount;
	}
};

class HDDComp 
{
public:
	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.hdd_capacity < comp2.hdd_capacity;
	}
};


class ProcAcc
{
protected:
	std::string proc;
	std::vector<Computer>* v;

public:
	ProcAcc(std::string _proc)
	{
		proc = _proc;
		v = new std::vector<Computer>();
	}

	std::vector<Computer> getSet()
	{
		return *v;
	}

	void operator () (Computer comp)
	{
		if (comp.processor == proc)
			(*v).push_back(comp);
	}
};

class RAMAcc
{
protected:
	int ram;
	std::vector<Computer>* v;

public:
	RAMAcc(int _ram)
	{
		ram = _ram;
		v = new std::vector<Computer>();
	}

	std::vector<Computer> getSet()
	{
		return *v;
	}

	void operator () (Computer comp)
	{
		if (comp.ram_amount == ram)
			(*v).push_back(comp);
	}
};

class VMAcc
{
protected:
	int vm;
	std::vector<Computer>* v;

public:
	VMAcc(int _vm)
	{
		vm = _vm;
		v = new std::vector<Computer>();
	}

	std::vector<Computer> getSet()
	{
		return *v;
	}

	void operator () (Computer comp)
	{
		if (comp.vm_amount == vm)
			(*v).push_back(comp);
	}
};

class HDDAcc
{
protected:
	int hdd;
	std::vector<Computer>* v;

public:
	HDDAcc(int _hdd)
	{
		hdd = _hdd;
		v = new std::vector<Computer>();
	}

	std::vector<Computer> getSet()
	{
		return *v;
	}

	void operator () (Computer comp)
	{
		if (comp.hdd_capacity == hdd)
			(*v).push_back(comp);
	}
};

template <class P >
class Container
{
protected:
	std::vector<P> vect;
public:

	typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<P>>> my_iterator;
	typedef std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<P>>> my_const_iterator;

	Container(int size)
	{
		vect = std::vector<P>(size);
	}

	Container()
	{
		vect = std::vector<P>();
	}

	~Container() {}

	bool add(P p) {
		if (!find(p))
		{
			vect.push_back(p);
			return true;
		}
		else
			return false;
	}

	void remove(my_iterator &it) {
		vect.erase(it);
	}

	template<class Pred>
	bool find(Pred &p, my_iterator &it)
	{
		it = std::find_if(vect.begin(), vect.end(), p);	
		return it != vect.end();
	}

	bool find(P p)
	{
		return std::find(vect.begin(), vect.end(), p) != vect.end();
	}

	template<class Comp>
	bool find(my_iterator &it, P x, Comp &c)
	{
		std::sort(vect.begin(), vect.end(), c);
		it = std::lower_bound(vect.begin(), vect.end(), x, c);
		return it!=vect.end() && !c(x, *it);
	}

	template<class Acc>
	std::vector<P> findSubSet(Acc acc)
	{
		std::for_each(vect.begin(), vect.end(), acc);
		return acc.getSet();
	}

	void clear() { vect.clear(); }

	int vectSize() { return vect.size(); }

	my_const_iterator getBegin() { return vect.cbegin(); }

	my_const_iterator getEnd() { return vect.cend(); }
};

class MyContainer: public Container<Computer>
{
public:

	MyContainer() {}

	MyContainer(std::vector<Computer> _vect)
	{
		vect = _vect;
	}

	bool findByProc(std::string proc, my_iterator &it)
	{
		return find(ProcPred(proc), it);
	}

	bool findByRAM(int ram, my_iterator &it)
	{
		return find(RAMPred(ram), it);
	}

	bool findByVM(int vm, my_iterator &it)
	{
		return find(VMPred(vm), it);
	}

	bool findByHDD(int hdd, my_iterator &it)
	{
		return find(HDDPred(hdd), it);
	}

	bool findByProcBinary(std::string proc, my_iterator &it)
	{
		return find(it, Computer(0, "", proc, 0, 0, 0, 0, 0, 0), ProcComp());
	}

	bool findByRAMBinary(int ram, my_iterator &it)
	{
		return find(it, Computer(0, "", "", 0, ram, 0, 0, 0, 0), RAMComp());
	}

	bool findByVMBinary(int vm, my_iterator &it)
	{
		return find(it, Computer(0, "", "", 0, 0, 0, vm, 0, 0), VMComp());
	}

	bool findByHDDBinary(int hdd, my_iterator &it)
	{
		return find(it, Computer(0, "", "", 0, 0, hdd, 0, 0, 0), HDDComp());
	}

	MyContainer findSubSetByProc(std::string proc)
	{
		return MyContainer(findSubSet(ProcAcc(proc)));
	}

	MyContainer findSubSetByRAM(int ram)
	{
		return MyContainer(findSubSet(RAMAcc(ram)));
	}

	MyContainer findSubSetByVM(int vm)
	{
		return MyContainer(findSubSet(VMAcc(vm)));
	}

	MyContainer findSubSetByHDD(int hdd)
	{
		return MyContainer(findSubSet(HDDAcc(hdd)));
	}
	
	void fileInput(std::fstream fin)
	{
		if (fin.is_open())
		{
			std::istream_iterator<Computer> is(fin);
			if (fin.eof()) return;
			vect.clear();
			Computer comp = *is++;
			while (!fin.fail() && !fin.eof())
			{
				add(comp);
				comp = *is++;
			}
			add(comp);
			fin.close();
		}
		else
			std::cout << "File isn't exist!" << std::endl;
	}

	void fileOutput(std::fstream fout)
	{
		if (fout.is_open())
		{
			copy(vect.begin(), vect.end(), std::ostream_iterator<Computer>(fout, "\n"));
			fout.close();
		}
		else
		{
			std::cout << "Error opening file";
		}
	}

};

//-----------------helpers------------------

int inputInt(std::string message, int min = 0, int max = INT_MAX)
{
	std::string str;
	int res;

	while (true)
	{
		std::cout << message;
		try
		{
			std::cin >> str;
			if (str == "exit" || str == "EXIT") throw "exit";
			if (str == "skip" || str == "SKIP") throw 's';
			res = std::stoi(str);
			while (res < min || res > max)
			{
				std::cout << "Error(value < " << min << " or value > " << max << "). Repeat input: ";
				std::cin >> str;
				if (str == "exit" || str == "EXIT") throw "exit";
				res = std::stoi(str);
			}

			return res;
		}
		catch (std::exception&)
		{
			std::cout << "Wrong number!" << std::endl;
		}
	}
}

Computer inputComputer()
{
	int _code, _freq, _ram, _hdd, _vm, _value, _count;
	std::string _mark, _proc;

	std::cout << ">>>Computer input(enter \"exit\" for exit )<<<" << std::endl;
	_code = inputInt("Enter code: ");
	std::cout << "Enter mark: ";
	std::cin >> _mark;
	if (_mark == "exit") throw "exit";
	std::cout << "Enter processor type: ";
	std::cin >> _proc;
	if (_proc == "exit") throw "exit";
	_freq = inputInt("Enter processor frequency: ");
	_ram = inputInt("Enter ram amount: ");
	_hdd = inputInt("Enter hdd capacity: ");
	_vm = inputInt("Enter video memory amount: ");
	_value = inputInt("Enter value: ");
	_count = inputInt("Enter count of copmuters: ");

	return Computer(_code, _mark, _proc, _freq, _ram, _hdd, _vm, _value, _count);
}

Computer inputComputer(Computer comp)
{
	int _code, _freq, _ram, _hdd, _vm, _value, _count;
	std::string _mark, _proc;

	std::cout << ">>>Computer input(enter \"exit\" for exit, \"skip\" for skip )<<<" << std::endl;
	try { _code = inputInt("Enter code(current=" + std::to_string(comp.code) + "): "); }
	catch (char) { _code = comp.code; }
	std::cout << "Enter mark(current=" + comp.mark + "): ";
	std::cin >> _mark;
	if (_mark == "exit") throw "exit";
	if (_mark == "skip") { _mark = comp.mark; }
	std::cout << "Enter processor type(current=" + comp.processor + "): ";
	std::cin >> _proc;
	if (_proc == "exit") throw "exit";
	if (_proc == "skip") { _proc = comp.processor; }
	try { _freq = inputInt("Enter processor frequency(current=" + std::to_string(comp.frequency) + "): "); }
	catch (char) { _freq = comp.frequency; }
	try { _ram = inputInt("Enter ram amount(current=" + std::to_string(comp.ram_amount) + "): "); }
	catch (char) { _ram = comp.ram_amount; }
	try { _hdd = inputInt("Enter hdd capacity(current=" + std::to_string(comp.hdd_capacity) + "): "); }
	catch (char) { _hdd = comp.hdd_capacity; }
	try { _vm = inputInt("Enter video memory amount(current=" + std::to_string(comp.vm_amount) + "): "); }
	catch (char) { _vm = comp.vm_amount; }
	try { _value = inputInt("Enter value(current=" + std::to_string(comp.value) + "): "); }
	catch (char) { _value = comp.value; }
	try { _count = inputInt("Enter count of copmuters(current=" + std::to_string(comp.count) + "): "); }
	catch (char) { _count = comp.count; }

	return Computer(_code, _mark, _proc, _freq, _ram, _hdd, _vm, _value, _count);
}

void consoleOutput(MyContainer cont) 
{
	if (cont.vectSize() == 0)
		std::cout << std::endl << "Container is empty" << std::endl;
	else
	{
		std::cout << "code\tmark\tproc\tfreq\tram\thdd\tvideo\tvalue\tcount\n\n";
		copy(cont.getBegin(), cont.getEnd(), std::ostream_iterator<Computer>(std::cout, "\n"));
	}
}

void consoleInput(MyContainer &cont)
{
	cont.clear();
	Computer comp;
	while (true)
	{
		try
		{
			comp = inputComputer();
		}
		catch (const char* str)
		{
			if (str == "exit")
				return;
			else
			{
				std::cout << str;
				return;
			}
		}
		cont.add(comp);
	}
}