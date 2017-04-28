// CPlusPlus2.cpp
//#55. Модель компьютера характеризуется кодом и названием марки компьютера, 
//типом процессора, частотой работы процессора, объемом оперативной памяти, 
//объемом жесткого диска, объемом памяти видеокарты, ценностью компьютера и
//количеством экземпляров. Поиск по типу процессора, объему ОЗУ, памяти видеокарты 
//и объему жесткого диска. 

#include "stdafx.h"
#include "Helper.h"


void printMainMenu()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Input" << std::endl;
	std::cout << " 2)Output" << std::endl;
	std::cout << " 3)Find" << std::endl;
	std::cout << " 4)Add" << std::endl;
	std::cout << " 5)Subset" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "------------------------------" << std::endl;
}

void printMenuConsoleFile()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Console" << std::endl;
	std::cout << " 2)File" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "------------------------------" << std::endl;
}

void printMenuFindParam()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)By processor type" << std::endl;
	std::cout << " 2)By ram amount" << std::endl;
	std::cout << " 3)By video memory amount" << std::endl;
	std::cout << " 4)By hdd capacity" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "------------------------------" << std::endl;
}

void printMenuSearch()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Simple search" << std::endl;
	std::cout << " 2)Binary search" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "------------------------------" << std::endl;
}

void printAction()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Action with record:" << std::endl;
	std::cout << " 1)Print" << std::endl;
	std::cout << " 2)Change" << std::endl;
	std::cout << " 3)Delete" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "------------------------------" << std::endl;
}

std::string output_file_name()
{
	std::string name;
	std::cout << "Enter file name(empty string = 'defaulname'): " << std::endl;
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "defaultname";
	return name + ".txt";
}

std::string input_file_name()
{
	std::fstream f;
	std::string res;
	std::cout << "Enter text file name(empty string = 'defaultname'): ";
	std::getline(std::cin, res);
	std::getline(std::cin, res);
	f.open(res + ".txt");
	while (!f.is_open() && res != "")
	{
		std::cout << "There are no such file, repeat input(empty string = 'defaultname'): ";
		std::getline(std::cin, res);
		f.open(res + ".txt");
	};
	f.close();
	return (res == "") ? "defaultname.txt" : res + ".txt";
}


int main()
{
	MyContainer<> cont = MyContainer<>();
	std::string str;
	int n;
	bool binarSearch;
	bool found;
	std::string FName;
	std::vector<Computer>::iterator it;

	while (true)
	{
		printMainMenu();
		n = inputInt("Enter the command: ", 0, 5);
		switch (n)
		{
		case 1://INPUT
			printMenuConsoleFile();
			n = inputInt("Enter the command: ", 0, 2);
			switch (n)
			{
			case 1:
				cont.consoleInput();
				break;
			case 2:
				FName = input_file_name();
				cont.fileInput(FName);
				break;
			case 0:
				break;
			}
			break;
		case 2://OUTPUT
			printMenuConsoleFile();
			n = inputInt("Enter the command:", 0, 2);
			switch (n)
			{
			case 1:
				cont.consoleOutput();
				break;
			case 2:
				cont.fileOutput(output_file_name());
				break;
			case 0:
				break;
			}
			break;
		case 3://FIND
			printMenuSearch();
			n = inputInt("Enter the command: ", 1, 2);
			switch (n)
			{
			case 1://SIMPLE
				binarSearch = false;
				break;
			case 2://BINARY
				binarSearch = true;
				break;
			}

			printMenuFindParam();
			n = inputInt("Enter the command: ", 1, 4);
			switch (n)
			{
			case 1://PROC
				std::cout << "Enter processor type: ";
				std::cin >> str;
				if (binarSearch)
					found = cont.findByProcBinary(str, it);
				else
					found = cont.findByProc(str, it);
				break;
			case 2://RAM
				if (binarSearch)
					found = cont.findByRAMBinary(inputInt("Enter ram amount: ", 0), it);
				else
					found = cont.findByRAM(inputInt("Enter ram amount: ", 0), it);
				break;
			case 3://VM
				if (binarSearch)
					found = cont.findByRAMBinary(inputInt("Enter vm amount: ", 0), it);
				else
					found = cont.findByRAM(inputInt("Enter vm amount: ", 0), it);
				break;
			case 4://HDD
				if (binarSearch)
					found = cont.findByRAMBinary(inputInt("Enter hdd capacity: ", 0), it);
				else
					found = cont.findByRAM(inputInt("Enter hdd capacity: ", 0), it);
				break;
			}
			if (found)
			{
				std::cout << "Record found \n";
				printAction();
				n = inputInt("Enter the command: ", 0, 3);
				switch (n)
				{
				case 1:
					std::cout << *it;
					break;
				case 2:
					cont.change(it);
					break;
				case 3:
					cont.remove(it);
					break;
				case 0:
					break;
				}
			}
			else
				std::cout << "Record not found \n";
			break;
		case 4://ADD
			cont.add(inputComputer());
			break;
		case 5://SUBSET
			printMenuFindParam();
			n = inputInt("Enter the command: ", 1, 4);
			switch (n)
			{
			case 1://PROC
				std::cout << "Enter processor type: ";
				std::cin >> str;
				cont.findSubSetByProc(str);
				break;
			case 2://RAM
				cont.findSubSetByRAM(inputInt("Enter ram amount: ", 0));
				break;
			case 3://VM
				cont.findSubSetByVM(inputInt("Enter vm amount: ", 0));
				break;
			case 4://HDD
				cont.findSubSetByHDD(inputInt("Enter hdd capacity: ", 0));
				break;
			}
			if (cont.subv.size() == 0)
			{
				std::cout << "Subset is empty" << std::endl;
				break;
			}
			printMenuConsoleFile();
			n = inputInt("Enter the command: ", 0, 2);
			switch (n)
			{
			case 1:
				cont.consoleOutputSub();
				break;
			case 2:
				FName = output_file_name();
				cont.fileOutputSub(FName);
				break;
			case 3:
				break;
			}
			break;
		case 0://EXIT
			return 0;
		}
	}
}