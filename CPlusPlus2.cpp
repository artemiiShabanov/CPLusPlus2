// CPlusPlus2.cpp
//#55. ������ ���������� ��������������� ����� � ��������� ����� ����������, 
//����� ����������, �������� ������ ����������, ������� ����������� ������, 
//������� �������� �����, ������� ������ ����������, ��������� ���������� �
//����������� �����������. ����� �� ���� ����������, ������ ���, ������ ���������� 
//� ������ �������� �����. 

#include "stdafx.h"
#include "Helper.h"


void printMainMenu()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Input" << std::endl;
	std::cout << " 2)Output" << std::endl;
	std::cout << " 3)Find" << std::endl;
	std::cout << " 4)Add" << std::endl;
	std::cout << " 5)Subset" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printMenuConsoleFile()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << " 1)Console" << std::endl;
	std::cout << " 2)File" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printMenuFindParam()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << " 1)By processor type" << std::endl;
	std::cout << " 2)By ram amount" << std::endl;
	std::cout << " 3)By video memory amount" << std::endl;
	std::cout << " 4)By hdd capacity" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printMenuSearch()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Simple search" << std::endl;
	std::cout << " 2)Binary search" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printAction()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Action with record:" << std::endl;
	std::cout << " 1)Print" << std::endl;
	std::cout << " 2)Change" << std::endl;
	std::cout << " 3)Delete" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
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
	MyContainer cont = MyContainer();
	MyContainer subcont = MyContainer();
	std::string str;
	int n;
	bool binarSearch;
	bool found = false;
	std::string FName;
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Computer>>> it ;

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
				consoleInput(cont);
				break;
			case 2:
				FName = input_file_name();
				cont.fileInput(std::fstream(FName, std::ios::in));
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
				consoleOutput(cont);
				break;
			case 2:
				FName = output_file_name();
				cont.fileOutput(std::fstream(FName, std::ios::out));
				break;
			case 0:
				break;
			}
			break;
		case 3://FIND
			printMenuSearch();
			n = inputInt("Enter the command: ", 0, 2);
			if (n == 0) break;
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
			n = inputInt("Enter the command: ", 0, 4);
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
					found = cont.findByVMBinary(inputInt("Enter vm amount: ", 0), it);
				else
					found = cont.findByVM(inputInt("Enter vm amount: ", 0), it);
				break;
			case 4://HDD
				if (binarSearch)
					found = cont.findByHDDBinary(inputInt("Enter hdd capacity: ", 0), it);
				else
					found = cont.findByHDD(inputInt("Enter hdd capacity: ", 0), it);
				break;
			case 0:
				break;
			}
			if (found)
			{ 
				while (true)
				{
					std::cout << "\n Record found \n";
					printAction();
					n = inputInt("Enter the command: ", 0, 3);
					if (n == 0) break;
					switch (n)
					{
					case 1:
						std::cout << *(it);
						break;
					case 2:
						try
						{
							*it = inputComputer(*it);
							break;
						}
						catch (const char* str)
						{
							break;
						}
					case 3:
						cont.remove(it);
						break;
					}
					if (n == 3) break;
				}
			}
			else
				std::cout << "Record not found \n";
			break;
		case 4://ADD
			try
			{
				cont.add(inputComputer());
			}
			catch (const char*) {}
			break;
		case 5://SUBSET
			printMenuFindParam();
			n = inputInt("Enter the command: ", 1, 4);
			switch (n)
			{
			case 1://PROC
				std::cout << "Enter processor type: ";
				std::cin >> str;
				subcont = cont.findSubSetByProc(str);
				break;
			case 2://RAM
				subcont = cont.findSubSetByRAM(inputInt("Enter ram amount: ", 0));
				break;
			case 3://VM
				subcont = cont.findSubSetByVM(inputInt("Enter vm amount: ", 0));
				break;
			case 4://HDD
				subcont = cont.findSubSetByHDD(inputInt("Enter hdd capacity: ", 0));
				break;
			}
			if (subcont.vectSize() == 0)
			{
				std::cout << "Subset is empty" << std::endl;
				break;
			}
			else
			{
				std::cout <<  std::endl << subcont.vectSize() << " records found" << std::endl;
			}
			printMenuConsoleFile();
			n = inputInt("Enter the command: ", 0, 2);
			switch (n)
			{
			case 1:
				consoleOutput(subcont);
				break;
			case 2:
				FName = output_file_name();
				subcont.fileOutput(std::fstream(FName, std::ios::out));
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