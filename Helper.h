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

	bool operator < (const Computer &comp)
	{
		return this->code < comp.code; //было ==
	}
};


std::ostream& operator <<(std::ostream &os, const Computer &comp) {
	os << "|| code: " + std::to_string(comp.code) + "  " +
		"mark: " + comp.mark + "  " +
		"proc: " + comp.processor + "  " +
		"freq: " + std::to_string(comp.frequency) + "  " +
		"ram: " + std::to_string(comp.ram_amount) + "  " +
		"hdd: " + std::to_string(comp.hdd_capacity) + "  " +
		"vm: " + std::to_string(comp.vm_amount) + "  " +
		"value: " + std::to_string(comp.value) + "  " +
		"count: " + std::to_string(comp.count) + "||\n";
	return os;
}

std::istream& operator>> (std::istream& is, Computer &comp)
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

	bool operator () (Computer comp)
	{
		return comp.processor == proc;
	}

	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.processor == comp2.processor;
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

	bool operator () (Computer comp)
	{
		return comp.ram_amount == ram;
	}

	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.ram_amount == comp2.ram_amount;
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

	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.vm_amount == comp2.vm_amount;
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

	bool operator () (Computer comp1, Computer comp2)
	{
		return comp1.hdd_capacity == comp2.hdd_capacity;
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

//Что это?!?!?!?
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

/*class Counter //мне не нужно вроде
{
protected:
	int count;

public:
	Counter() :count(0) {}

	void operator () (Computer comp)
	{
		count = count + comp.sumOfHDD;
	}
	int getCount()
	{
		return count;
	}
};*/

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




template <class P = Computer>
class MyContainer
{
public:

	MyContainer(int size)
	{
		vect = std::vector<P>(size);
	}

	MyContainer()
	{
		vect = std::vector<P>();
	}

	~MyContainer() {}

	bool add(P comp) {
		if (!find(comp))
		{
			vect.push_back(comp);
			return true;
		}
		else
			return false;
	}


	bool find(P comp, std::random_access_iterator_tag &it)
	{
		it = std::find(vect.begin(), vect.end(), comp);
		return it != vect.end()
	}

	bool find(P comp)
	{
		std::vector<P>::iterator it =
			std::find(vect.begin(), vect.end(), comp);
		return it != vect.end();
	}

	void remove(std::vector<Computer>::iterator it) {
		vect.erase(it);
	}

	void change(std::vector<Computer>::iterator &it) {
		*it = inputComputer();
	}


	bool findByProc(std::string proc, std::vector<Computer>::iterator &it)
	{
		ProcPred pred = ProcPred(proc);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByRAM(int ram, std::vector<Computer>::iterator &it)
	{
		RAMPred pred = RAMPred(ram);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByVM(int vm, std::vector<Computer>::iterator &it)
	{
		VMPred pred = VMPred(vm);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByHDD(int hdd, std::vector<Computer>::iterator &it)
	{
	    HDDPred pred = HDDPred(HDD);
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	bool findByProcBinary(std::string proc, std::vector<Computer>::iterator &it)
	{
		ProcPred pred = ProcPred(proc);
		ProcComp comp = ProcComp();
		std::sort(vect.begin(), vect.end(), comp);
		P c = Computer(0, "", proc, 0, 0, 0, 0, 0, 0);//???????????????
		if (std::binary_search(vect.begin(), vect.end(), c, pred))
		{
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool findByRAMBinary(int ram, std::vector<Computer>::iterator &it)
	{
		RAMPred pred = RAMPred(ram);
		RAMComp comp = RAMComp();
		P c = Computer(0, "", "", 0, ram, 0, 0, 0, 0);
		std::sort(vect.begin(), vect.end(), comp);
		if (std::binary_search(vect.begin(), vect.end(), c, pred))
		{
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool findByVMBinary(int vm, std::vector<Computer>::iterator &it)
	{
		VMPred pred = VMPred(vm);
		VMComp comp = VMComp();
		std::sort(vect.begin(), vect.end(), comp);
		P c = Computer(0, "", "", 0, 0, 0, vm, 0, 0);
		if (std::binary_search(vect.begin(), vect.end(), c, pred))
		{
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool findByHDDBinary(int hdd, std::vector<Computer>::iterator &it)
	{
		HDDPred pred = HDDPred(hdd);
		HDDComp comp = HDDComp();
		std::sort(vect.begin(), vect.end(), comp);
		P c = Computer(0, "", "", 0, 0, hdd, 0, 0, 0);
		if (std::binary_search(vect.begin(), vect.end(), c, pred))
		{
			it = std::find_if(vect.begin(), vect.end(), pred);
			return true;
		}
		else
		{
			return false;
		}
	}

	void findSubSetByProc(std::string proc)
	{
		ProcAcc acc = ProcAcc(proc);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void findSubSetByRAM(int ram)
	{
		RAMAcc acc = RAMAcc(ram);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void findSubSetByVM(int vm)
	{
		VMAcc acc = VMAcc(vm);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}

	void findSubSetByHDD(int hdd)
	{
		HDDAcc acc = HDDAcc(hdd);
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}
	void consoleInput()//??????????????????
	{
		std::istream_iterator<P> is(std::cin);
		vect.clear();
		P comp = *is;
		while (comp.code != -99)
		{
			add(comp);
			is++;
			comp = *is;
		}
	}

	void consoleOutput()
	{
		copy(vect.begin(), vect.end(), std::ostream_iterator<P>(std::cout, "\n"));
	}

	void consoleOutputSub()
	{
		copy(subv.begin(), subv.end(), std::ostream_iterator<P>(std::cout, "\n"));
	}

	void fileInput(std::string fn)
	{
		std::fstream fin(fn, std::ios::in);
		if (fin.is_open())
		{
			std::istream_iterator<P> is(fin);
			vect.clear();
			P comp = *is++;
			while (comp.code != -99)
			{
				add(comp);
				comp = *is++;
			}
			fin.close();
		}
		else
			std::cout << "File isn't exist!" << std::endl;
	}

	void fileOutput(std::string fn)
	{
		std::fstream fout(fn, std::ios::out);
		if (fout.is_open())
		{
			copy(vect.begin(), vect.end(), std::ostream_iterator<P>(fout, "\n"));
			fout << "-99";
			fout.close();
		}
		else
		{
			std::cout << "Error opening file";
		}
	}


	void fileOutputSub(std::string fn)
	{
		std::fstream fout(fn, std::ios::out);
		if (fout.is_open())
		{
			copy(subv.begin(), subv.end(), std::ostream_iterator<P>(fout, "\n"));
			fout << "-99";
			fout.close();
		}
		else
		{
			std::cout << "Error opening file";
		}
	}



private:
	std::vector<P> vect;
	std::vector<P> subv;
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
			res = std::stoi(str);
			while (res < min || res > max)
			{
				std::cout << "Error(value < " << min << " or value > " << max << "). Repeat input: ";
				std::cin >> res;
			}
			std::cout << std::endl;
			return res;
		}
		catch (std::exception& e)
		{
			std::cout << "Wrong number!" << std::endl;
		}
	}
}

Computer inputComputer()
{
	int _code, _freq, _ram, _hdd, _vm, _value, _count;
	std::string _mark, _proc;

	std::cout << ">>>Computer input<<<" << std::endl;
	_code = inputInt("Enter code: ");
	std::cout << "Enter mark: ";
	std::cin >> _mark;
	std::cout << std::endl;
	std::cout << "Enter processor type: ";
	std::cin >> _proc;
	std::cout << std::endl;
	_freq = inputInt("Enter processor frequency: ");
	_ram = inputInt("Enter ram amount: ");
	_hdd = inputInt("Enter hdd capacity: ");
	_vm = inputInt("Enter video memory amount: ");
	_value = inputInt("Enter value: ");
	_count = inputInt("Enter count of copmuters: ");

	return Computer(_code, _mark, _proc, _freq, _ram, _hdd, _vm, _value, _count);
}

