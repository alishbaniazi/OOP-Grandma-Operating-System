#pragma once
#include "pch.h"
#include <iostream>
using namespace std;

class RecycleBin;
//==============HELPER FUNCTIONS==============
inline int len(const char* str) {
	if (*str == '\0')
		return 0;
	else
		return 1 + len((str + 1));
}

inline double pow(double a, int b) {
	if (b == 0)
		return 1;
	else {
		return a * pow(a, b - 1);
	}
}

inline double sqrt(double a) {
	double temprt = 0.0;
	if (a == 0)
		return 0.0;
	else if (a < 0) {
		cout << "MATH ERROR(sqrt of neg value)" << endl;
		return 0.0;
	}
	else {

		// using newtons method
		temprt = a / 2;
		for (int i = 0; i < 100; i++) {
			temprt = (temprt + a / temprt) / 2;
		}
	}
	return temprt;
}

inline void copystr(const char* str1, char* str2, int size) {
	if (size == 0)	return;
	else {
		*(str2 + size - 1) = *(str1 + size - 1);
		copystr(str1, str2, size - 1);
	}
}

inline bool areEqual(const char* str1, const char* str2, int size) {       //checking if two strings are identicle or not
	if (str1 == nullptr || str2 == nullptr)return false;
	if (size == 0) {
		return true;
	}
	else {
		if (*str1 != *str2)
			return false;
		else {
			return areEqual(str1 + 1, str2 + 1, size - 1);
		}
	}
}
inline char* inttostr(long long int n) {
	if (n == 0) {
		char* arr = new char[2];
		arr[0] = '0';
		arr[1] = '\0';
		return arr;
	}
	//finding length
	bool isneg = false, ispos = false;
	long long int temp = n;

	int len = 0;
	if (temp < 0) {
		isneg = 1;
		n *= -1;
		temp = n;
		len++;
	}
	else {
		ispos = true;
	}
	while (temp != 0) {
		temp /= 10;
		len++;
	}
	char* arr = new char[len + 1];
	//storing int as char/str
	temp = n;
	int start = (int)isneg;
	if (isneg)   arr[0] = '-';
	for (int i = start; i < len; i++) {
		arr[len - i - (int)ispos] = '0' + temp % 10;
		temp = temp / 10;
	}
	arr[len] = '\0';
	return arr;
}

//===================FILE CLASS==================
class File {
	char* name;
	char* content;
	int size;

public:
	File() {
		name = nullptr;
		content = nullptr;
		size = 0;
	}
	//File(const File& other) {
	//	size = other.size;
	//	name = new char[len(other.name) + 1];
	//	copystr(other.name, name, len(other.name));
	//	name[len(other.name)] = '\0';
	//	content = new char[len(other.content) + 1];
	//	copystr(other.content, content, len(other.content));
	//	content[len(other.content)] = '\0';
	//}

	File(const File& other) {
		size = other.size;
		if (other.name) {
			name = new char[len(other.name) + 1];
			copystr(other.name, name, len(other.name));
			name[len(other.name)] = '\0';
		}
		else name = nullptr;
		if (other.content) {
			content = new char[len(other.content) + 1];
			copystr(other.content, content, len(other.content));
			content[len(other.content)] = '\0';
		}
		else content = nullptr;
	}
	File(const char* name, const char* content, int size) {
		this->name = new char[len(name) + 1];
		copystr(name, this->name, len(name));
		this->name[len(name)] = '\0';

		this->size = size;

		this->content = new char[len(content) + 1];
		copystr(content, this->content, len(content));
		this->content[len(content)] = '\0';
	}

	char* getName() const {
		if (this != NULL)
			return this->name;
		else
			return nullptr;
	}
	const char* getContent() const {
		return this->content;
	}
	int getSize()const {
		return this->size;
	}
	int getsize()const {
		return this->size;
	}
	File operator+(const File& other)const {
		File newfile;

		//copying names
		int newlen = len(this->name) + len(other.name) + 1;
		newfile.name = new char[newlen + 1];

		copystr(this->name, newfile.name, len(this->name));
		newfile.name[len(this->name)] = '_';
		copystr(other.name, &(newfile.name[len(this->name) + 1]), len(other.name));

		newfile.name[newlen] = '\0';

		//copying content
		int newClen = len(this->content) + len(other.content);
		newfile.content = new char[newClen + 1];
		copystr(this->content, newfile.content, len(this->content));
		copystr(other.content, &(newfile.content[len(this->content)]), len(other.content));
		newfile.content[newClen] = '\0';

		int s1 = this->size;
		int s2 = (other.getsize());
		newfile.size = s1 + s2;
		return newfile;
	}

	bool operator<(const File& other)const {
		if (this->size < other.size)
			return true;
		else
			return false;
	}

	void setContent(const char* cont) {
		if (content == nullptr)
			content = new char[len(cont) + 1];
		int prevsize = len(content);
		int newlen = prevsize + len(cont) + 1;
		char* tempc = new char[newlen];
		for (int i = 0; i < prevsize; i++) {
			*(tempc + i) = *(content + i);
		}

		delete[]content;
		content = tempc;
		for (int i = prevsize; i < prevsize + len(cont); i++) {
			*(content + i) = *(cont + i - prevsize);
		}
		*(content + prevsize + len(cont)) = '\0';
	}


	~File() {
		delete[] name;
		delete[] content;
	}
};



//===================STORAGE=======================
class Storage {
	File** files;
	int capacity;
	int usedSpace;
	int fileCount;
	int maxFiles;

public:
	Storage() {
		files = new File * [10];
		capacity = 0;
		usedSpace = 0;
		fileCount = 0;
		maxFiles = 10;
	}
	Storage(int capacityMB) {
		capacity = capacityMB;
		files = new File * [10];
		usedSpace = 0;
		fileCount = 0;
		maxFiles = 10;
	}
	bool saveFile(const File& file) {
		if ((capacity - usedSpace) < file.getsize()) {
			return false;
		}
		else {
			if (fileCount == maxFiles) {
				File** temp = new File * [2 * maxFiles];

				//coppying prev files
				for (int i = 0; i < fileCount; i++) {
					temp[i] = new File(*files[i]);
				}

				//deleting prev files
				for (int i = 0; i < fileCount; i++) {
					delete files[i];
				}
				delete[] files;
				files = temp;
				temp = nullptr;
				maxFiles = maxFiles * 2;

			}
			files[fileCount] = new File(file);
			fileCount++;
			usedSpace += file.getsize();
			return true;
		}
	}

	bool deleteFile(const char* name) {
		int ind = 0;
		bool found = false;
		int size = len(name);
		for (int i = 0; i < fileCount; i++) {
			if (areEqual(name, files[i]->getName(), size) && (size == len(files[i]->getName()))) {
				ind = i;
				found = true;
				break;
			}
		}
		if (found == false)
			return false;
		else {
			//deleting the file
			usedSpace -= files[ind]->getsize();
			fileCount--;
			delete files[ind];

			for (int i = ind; i < fileCount; i++) {
				files[i] = files[i + 1];
			}
			files[fileCount] = nullptr;
			return true;
		}
	}

	File* getFile(const char* name) const {
		int ind = 0;
		bool found = false;
		int size = len(name);
		for (int i = 0; i < fileCount; i++) {
			if (areEqual(name, files[i]->getName(), size) && (size == len(files[i]->getName()))) {
				ind = i;
				found = true;
				break;
			}
		}
		if (found == false)
			return nullptr;
		else {
			return files[ind];
		}
	}

	int getAvailableSpace() const {
		return capacity - usedSpace;
	}
	bool  isFull() const {
		if (this->getAvailableSpace() <= 0)
			return true;
		else
			return false;
	}
	//getters
	File** getfiles() {
		return files;
	}
	int getfileCount() {
		return fileCount;
	}
	int getusedSpace() {
		return usedSpace;
	}
	int getCapacity() {
		return capacity;
	}
	int getmaxFiles() {
		return maxFiles;
	}


	~Storage() {
		for (int i = 0; i < fileCount; i++) {
			delete files[i];
		}
		delete[] files;
		files = nullptr;
	}

};


//==================RAM=======================
class RAM {
	int capacity;
	int usedMemory;

public:
	RAM() { capacity = 0; usedMemory = 0; }
	RAM(int capacityMB) {
		capacity = capacityMB;
		usedMemory = 0;
	}
public:
	bool allocate(int sizeMB) {
		if ((capacity - usedMemory) < sizeMB)
			return false;
		else {
			usedMemory += sizeMB;
			return true;
		}
	}
	void deallocate(int sizeMB) {
		usedMemory -= sizeMB;
		if (usedMemory < 0)
			usedMemory = 0;
		return;
	}
	//getters
	int getAvailableMemory()const {
		return capacity - usedMemory;
	}
	int getcapacity() {
		return capacity;
	}
	int getusedMemory() {
		return usedMemory;
	}
	~RAM() {}

};

//==============FILE EXPLORER================
class FileExplorer {
	Storage* storage;
	char* name;
	int diskSize;
	int ramRequired;
public:
	bool isRunning;


	FileExplorer() {
		storage = NULL;
		isRunning = false;
		diskSize = 20;
		ramRequired = 50;
		const char* temp = "FileExplorer";
		this->name = new char[len(temp) + 1];
		copystr(temp, this->name, len(temp));
		this->name[len(temp)] = '\0';
	}
	FileExplorer(Storage* storage) {
		this->storage = storage;
		isRunning = false;
		diskSize = 20;
		ramRequired = 50;
		const char* temp = "FileExplorer";
		this->name = new char[len(temp) + 1];
		copystr(temp, this->name, len(temp));
		this->name[len(temp)] = '\0';
	}
	//copy constructor

	FileExplorer(const FileExplorer& other) {
		storage = other.storage;
		isRunning = other.isRunning;
		diskSize = other.diskSize;
		ramRequired = other.ramRequired;
		name = new char[len(other.name) + 1];
		copystr(other.name, name, len(other.name));
		name[len(other.name)] = '\0';
	}
	//methods
	bool createFile(const char* name, const char* content, int size) {
		if (!this->getisRunning())
			return false;

		else {
			File f(name, content, size);
			if (storage->saveFile(f))
				return true;
			else return false;
		}
	}

	bool deleteFile(const char* name, RecycleBin* bin);


	// {
	// 
	// if (bin!=nullptr && bin->getisRunning()) {
	   //  bin->addFile(*(storage->getFile(name)));
	   //  return storage->deleteFile(name);
	// }
	// if (!isRunning)
	   //  return false;
	// return storage->deleteFile(name);
	// 
 //}

	void listFiles() const {
		if (!isRunning)
			return;
		cout << "-----FILE NAMES------" << endl << endl;
		File** f = storage->getfiles();
		for (int i = 0; i < storage->getfileCount(); i++) {
			cout << i + 1 << ". " << f[i]->getName() << endl;
		}
		return;
	}

	File* viewFile(const char* name) const {
		return storage->getFile(name);
	}

	//getters
	char* getname() {
		if (this != NULL)
			return this->name;
		else
			return nullptr;
	}
	int getdiskSize() {
		return this->diskSize;
	}
	int getramRequired() {
		return this->ramRequired;
	}
	bool getisRunning() {
		return isRunning;
	}
	Storage* getstorage() {
		return storage;
	}

	//setter
	void setisRunning(bool state) {
		isRunning = state;
	}
};


//===============RECYCLE BIN=================
class RecycleBin {
	File** deletedFiles;  // dynamic array, starts at capacity 5 
	int fileCount;
	int maxFiles;
	Storage* storage;
	char* name;
	int diskSize;
	int ramRequired;
public:
	bool isRunning;

	RecycleBin() {
		ramRequired = 30;
		name = "RecycleBin";
		diskSize = 10;
		fileCount = 0;
		maxFiles = 5;
		storage = NULL;
		const char* temp = "RecycleBin";
		this->name = new char[len(temp) + 1];
		copystr(temp, this->name, len(temp));
		this->name[len(temp)] = '\0';
		isRunning = false;
		deletedFiles = new File * [5];
	}
	RecycleBin(Storage* s) {
		storage = s;
		ramRequired = 30;
		const char* temp = "RecycleBin";
		this->name = new char[len(temp) + 1];
		copystr(temp, this->name, len(temp));
		this->name[len(temp)] = '\0';
		diskSize = 10;
		fileCount = 0;
		maxFiles = 5;
		isRunning = false;
		deletedFiles = new File * [5];
	}
	//copy constructor
	RecycleBin(const RecycleBin& other) {
		diskSize = other.diskSize;
		ramRequired = other.ramRequired;
		fileCount = other.fileCount;
		maxFiles = other.maxFiles;
		storage = other.storage;
		isRunning = other.isRunning;
		name = new char[len(other.name) + 1];
		copystr(other.name, name, len(other.name));
		name[len(other.name)] = '\0';
		deletedFiles = new File * [maxFiles];
		for (int i = 0; i < fileCount; i++)
			deletedFiles[i] = new File(*other.deletedFiles[i]);
	}

	//methods

	void addFile(const File& file) {
		if (!isRunning) {
			cout << "Recycle Bin is not responding" << endl;
			return;
		}
		else {
			if (fileCount >= maxFiles) {
				File** temp = new File * [maxFiles * 2];
				for (int i = 0; i < fileCount; i++) {
					*(temp + i) = *(deletedFiles + i);
				}
				deletedFiles = temp;
			}
			deletedFiles[fileCount] = new File(file);
			fileCount++;
			maxFiles *= 2;
			return;
		}
	}
	int  getFileCount() const {
		return fileCount;
	}

	void listBin() const {
		if (this->isRunning) {
			cout << "----FILES IN BIN--------" << endl << endl;
			for (int i = 0; i < this->fileCount; i++) {
				cout << i + 1 << ". " << deletedFiles[i]->getName() << endl;
			}
		}
	}

	void emptyBin() {
		if (!isRunning) {
			return;
		}
		else {
			for (int i = 0; i < fileCount; i++) {
				delete deletedFiles[i];
			}
			delete[] deletedFiles;
			fileCount = 0;
		}
	}

	bool restoreFile(const char* filename) {
		File* f = NULL;

		bool found = false;
		for (int i = 0; i < fileCount; i++) {
			if (areEqual(deletedFiles[i]->getName(), filename, len(filename))) {
				f = deletedFiles[i];
				found = true;
				for (int j = i; j < fileCount - 1; j++) {
					deletedFiles[j] = deletedFiles[j + 1];
				}
				//delete deletedFiles[fileCount - 1];
			//	break;
			}
		}
		if (found == false)
			return false;

		fileCount--;
		bool res = storage->saveFile(*f);
		return res;
	}

	void operator-(const char* filename) {
		if (!isRunning)
			return;
		storage->deleteFile(filename);
		this->emptyBin();
	}

	//getters
	const char* getname() {
		if (this != NULL)
			return this->name;
		else
			return nullptr;
	}
	int getdiskSize() {
		return this->diskSize;
	}
	int getramRequired() {
		return this->ramRequired;
	}
	bool getisRunning() {
		return isRunning;
	}
	Storage* getstorage() {
		return storage;
	}


	//setter
	void setisRunning(bool state) {
		isRunning = state;
	}



	//destructor
	~RecycleBin() {
		for (int i = 0; i < fileCount; i++) {
			delete deletedFiles[i];
		}
		delete[] deletedFiles;
		deletedFiles = NULL;
	}
};


inline bool FileExplorer::deleteFile(const char* name, RecycleBin* bin) {

	if (bin != nullptr && bin->getisRunning()) {
		bin->addFile(*(storage->getFile(name)));
		return storage->deleteFile(name);
	}
	if (!isRunning)
		return false;
	return storage->deleteFile(name);

}


//================CALCULATOR==================
class Calculator {
	char** history;       // dynamic array of calculation strings 
	int historyCount, maxHistory;
	double variables[26]; // A maps to index 0, Z to index 25 
	double* memory;       // dynamic array of stored results 
	int memoryCount, maxMemory;
	char* name;
	int diskSize;      // = 15 
	int ramRequired;   // = 40 
public:
	bool isRunning;

	Calculator() {
		isRunning = false;
		history = nullptr;
		maxHistory = 0;
		maxMemory = 0;
		for (int i = 0; i < 26; i++)
			variables[i] = 0.0;
		historyCount = 0;
		memory = nullptr;
		memoryCount = 0;
		diskSize = 15;
		ramRequired = 40;
		const char* temp = "Calculator";
		this->name = new char[len(temp) + 1];
		copystr(temp, this->name, len(temp));
		this->name[len(temp)] = '\0';

	}
	//copy const
	Calculator(const Calculator& other) {
		maxHistory = other.maxHistory;
		memoryCount = other.memoryCount;
		for (int i = 0; i < 26; i++)
			variables[i] = other.variables[i];
		isRunning = other.isRunning;
		diskSize = other.diskSize;
		ramRequired = other.ramRequired;
		historyCount = other.historyCount;
		maxMemory = other.maxMemory;
		name = new char[len(other.name) + 1];
		copystr(other.name, name, len(other.name));
		name[len(other.name)] = '\0';
		if (other.history == nullptr)
			history = nullptr;
		else {
			history = new char* [maxHistory];
			for (int i = 0; i < historyCount; i++) {
				history[i] = new char[len(other.history[i]) + 1];
				copystr(other.history[i], history[i], len(other.history[i]));
				history[i][len(other.history[i])] = '\0';
			}
		}
		if (other.memory == nullptr)
			memory = nullptr;
		else {
			memory = new double[maxMemory];
			for (int i = 0; i < memoryCount; i++)
				memory[i] = other.memory[i];
		}
	}

	//getters
	char* getname() {
		if (this != NULL)
			return this->name;
		else
			return nullptr;
	}
	int getdiskSize() {
		return this->diskSize;
	}
	int getramRequired() {
		return this->ramRequired;
	}
	bool getisRunning() {
		return isRunning;
	}
	//setter
	void setisRunning(bool state) {
		isRunning = state;
	}

	//methodsssss
	double add(double a, double b) {
		if (!isRunning)
			return 0.0;
		else {
			//incrementing history and memory
			if (maxHistory == historyCount) {
				if (maxHistory == 0) {
					maxHistory = 5;
					history = new char* [maxHistory];
				}
				else {
					maxHistory *= 2;
					char** temphistory = new char* [maxHistory];
					for (int i = 0; i < historyCount; i++) {
						temphistory[i] = history[i];
					}
					delete[] history;
					history = temphistory;
				}
			}
			//memory
			if (maxMemory == memoryCount) {
				if (maxMemory == 0) {
					maxMemory = 5;
					memory = new double[maxMemory];
				}
				else {
					maxMemory *= 2;
					double* tempmemory = new double[maxMemory];
					for (int i = 0; i < memoryCount; i++) {
						tempmemory[i] = memory[i];
					}
					delete[] memory;
					memory = tempmemory;
				}
			}


			double res = a + b;
			//finding length of expression for history
			int length = 0;
			char* stra = inttostr((long long int)a);
			char* strb = inttostr((long long int)b);
			char* strres = inttostr((long long int)res);


			length += len(stra) + 3 + len(strb) + 3 + len(strres) + 1;  //for spaces operators and null char
			//storing in history
			history[historyCount] = new char[length];
			int ind = 0;

			//storing a

			int lena = len(stra);
			for (int i = 0; i < lena; i++) {
				history[historyCount][ind] = *(stra + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '+';
			history[historyCount][ind++] = ' ';

			//storing b

			int lenb = len(strb);
			for (int i = 0; i < lenb; i++) {
				history[historyCount][ind] = *(strb + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '=';
			history[historyCount][ind++] = ' ';

			//storing res

			int lenres = len(strres);
			for (int i = 0; i < lenres; i++) {
				history[historyCount][ind] = *(strres + i);
				ind++;
			}


			history[historyCount][ind] = '\0';
			delete[] stra;
			delete[] strb;
			delete[] strres;

			historyCount++;
			memory[memoryCount++] = res;
			return res;
		}
	}

	double subtract(double a, double b) {
		if (!isRunning)
			return 0.0;
		else {
			//incrementing history and memory
			if (maxHistory == historyCount) {
				if (maxHistory == 0) {
					maxHistory = 5;
					history = new char* [maxHistory];
				}
				else {
					maxHistory *= 2;
					char** temphistory = new char* [maxHistory];
					for (int i = 0; i < historyCount; i++) {
						temphistory[i] = history[i];
					}
					delete[] history;
					history = temphistory;
				}
			}
			//memory
			if (maxMemory == memoryCount) {
				if (maxMemory == 0) {
					maxMemory = 5;
					memory = new double[maxMemory];
				}
				else {
					maxMemory *= 2;
					double* tempmemory = new double[maxMemory];
					for (int i = 0; i < memoryCount; i++) {
						tempmemory[i] = memory[i];
					}
					delete[] memory;
					memory = tempmemory;
				}
			}


			double res = a - b;
			//finding length of expression for history
			int length = 0;
			char* stra = inttostr((long long int)a);
			char* strb = inttostr((long long int)b);
			char* strres = inttostr((long long int)res);


			length += len(stra) + 3 + len(strb) + 3 + len(strres) + 1;  //for spaces operators and null char
			//storing in history
			history[historyCount] = new char[length];
			int ind = 0;

			//storing a

			int lena = len(stra);
			for (int i = 0; i < lena; i++) {
				history[historyCount][ind] = *(stra + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '-';
			history[historyCount][ind++] = ' ';

			//storing b

			int lenb = len(strb);
			for (int i = 0; i < lenb; i++) {
				history[historyCount][ind] = *(strb + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '=';
			history[historyCount][ind++] = ' ';

			//storing res

			int lenres = len(strres);
			for (int i = 0; i < lenres; i++) {
				history[historyCount][ind] = *(strres + i);
				ind++;
			}


			history[historyCount][ind] = '\0';
			delete[] stra;
			delete[] strb;
			delete[] strres;

			historyCount++;
			memory[memoryCount++] = res;
			return res;
		}
	}

	double multiply(double a, double b) {
		if (!isRunning)
			return 0.0;
		else {
			//incrementing history and memory
			if (maxHistory == historyCount) {
				if (maxHistory == 0) {
					maxHistory = 5;
					history = new char* [maxHistory];
				}
				else {
					maxHistory *= 2;
					char** temphistory = new char* [maxHistory];
					for (int i = 0; i < historyCount; i++) {
						temphistory[i] = history[i];
					}
					delete[] history;
					history = temphistory;
				}
			}
			//memory
			if (maxMemory == memoryCount) {
				if (maxMemory == 0) {
					maxMemory = 5;
					memory = new double[maxMemory];
				}
				else {
					maxMemory *= 2;
					double* tempmemory = new double[maxMemory];
					for (int i = 0; i < memoryCount; i++) {
						tempmemory[i] = memory[i];
					}
					delete[] memory;
					memory = tempmemory;
				}
			}

			double res = a * b;
			//finding length of expression for history
			int length = 0;
			char* stra = inttostr((long long int)a);
			char* strb = inttostr((long long int)b);
			char* strres = inttostr((long long int)res);


			length += len(stra) + 3 + len(strb) + 3 + len(strres) + 1;  //for spaces operators and null char
			//storing in history
			history[historyCount] = new char[length];
			int ind = 0;

			//storing a

			int lena = len(stra);
			for (int i = 0; i < lena; i++) {
				history[historyCount][ind] = *(stra + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '*';
			history[historyCount][ind++] = ' ';

			//storing b

			int lenb = len(strb);
			for (int i = 0; i < lenb; i++) {
				history[historyCount][ind] = *(strb + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '=';
			history[historyCount][ind++] = ' ';

			//storing res

			int lenres = len(strres);
			for (int i = 0; i < lenres; i++) {
				history[historyCount][ind] = *(strres + i);
				ind++;
			}


			history[historyCount][ind] = '\0';
			delete[] stra;
			delete[] strb;
			delete[] strres;

			historyCount++;
			memory[memoryCount++] = res;
			return res;
		}
	}

	double divide(double a, double b) {
		if (!isRunning)
			return 0.0;
		else if (b == 0) {
			cout << "MATH ERROR(division by zero)" << endl;
			return 0.0;
		}
		else {
			//incrementing history and memory
			if (maxHistory == historyCount) {
				if (maxHistory == 0) {
					maxHistory = 5;
					history = new char* [maxHistory];
				}
				else {
					maxHistory *= 2;
					char** temphistory = new char* [maxHistory];
					for (int i = 0; i < historyCount; i++) {
						temphistory[i] = history[i];
					}
					delete[] history;
					history = temphistory;
				}
			}
			//memory
			if (maxMemory == memoryCount) {
				if (maxMemory == 0) {
					maxMemory = 5;
					memory = new double[maxMemory];
				}
				else {
					maxMemory *= 2;
					double* tempmemory = new double[maxMemory];
					for (int i = 0; i < memoryCount; i++) {
						tempmemory[i] = memory[i];
					}
					delete[] memory;
					memory = tempmemory;
				}
			}

			double res = a / b;
			//finding length of expression for history
			int length = 0;
			char* stra = inttostr((long long int)a);
			char* strb = inttostr((long long int)b);
			char* strres = inttostr((long long int)res);


			length += len(stra) + 3 + len(strb) + 3 + len(strres) + 1;  //for spaces operators and null char
			//storing in history
			history[historyCount] = new char[length];
			int ind = 0;

			//storing a

			int lena = len(stra);
			for (int i = 0; i < lena; i++) {
				history[historyCount][ind] = *(stra + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '/';
			history[historyCount][ind++] = ' ';

			//storing b

			int lenb = len(strb);
			for (int i = 0; i < lenb; i++) {
				history[historyCount][ind] = *(strb + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '=';
			history[historyCount][ind++] = ' ';

			//storing res

			int lenres = len(strres);
			for (int i = 0; i < lenres; i++) {
				history[historyCount][ind] = *(strres + i);
				ind++;
			}


			history[historyCount][ind] = '\0';
			delete[] stra;
			delete[] strb;
			delete[] strres;

			historyCount++;
			memory[memoryCount++] = res;
			return res;
		}
	}

	double power(double base, double exp) {

		if (!isRunning)
			return 0.0;

		else {
			//incrementing history and memory
			if (maxHistory == historyCount) {
				if (maxHistory == 0) {
					maxHistory = 5;
					history = new char* [maxHistory];
				}
				else {
					maxHistory *= 2;
					char** temphistory = new char* [maxHistory];
					for (int i = 0; i < historyCount; i++) {
						temphistory[i] = history[i];
					}
					delete[] history;
					history = temphistory;
				}
			}
			//memory
			if (maxMemory == memoryCount) {
				if (maxMemory == 0) {
					maxMemory = 5;
					memory = new double[maxMemory];
				}
				else {
					maxMemory *= 2;
					double* tempmemory = new double[maxMemory];
					for (int i = 0; i < memoryCount; i++) {
						tempmemory[i] = memory[i];
					}
					delete[] memory;
					memory = tempmemory;
				}
			}

			double res = pow(base, exp);
			if (res == 0.0)    return 0.0;
			//finding length of expression for history
			int length = 0;
			char* stra = inttostr((long long int)base);
			char* strb = inttostr((long long int)exp);
			char* strres = inttostr((long long int)res);


			length += len(stra) + 3 + len(strb) + 3 + len(strres) + 1;  //for spaces operators and null char
			//storing in history
			history[historyCount] = new char[length];
			int ind = 0;

			//storing a

			int lena = len(stra);
			for (int i = 0; i < lena; i++) {
				history[historyCount][ind] = *(stra + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '^';
			history[historyCount][ind++] = ' ';

			//storing b

			int lenb = len(strb);
			for (int i = 0; i < lenb; i++) {
				history[historyCount][ind] = *(strb + i);
				ind++;
			}

			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '=';
			history[historyCount][ind++] = ' ';

			//storing res

			int lenres = len(strres);
			for (int i = 0; i < lenres; i++) {
				history[historyCount][ind] = *(strres + i);
				ind++;
			}


			history[historyCount][ind] = '\0';
			delete[] stra;
			delete[] strb;
			delete[] strres;

			historyCount++;
			memory[memoryCount++] = res;
			return res;
		}
	}

	double squareRoot(double value) {
		if (!isRunning)
			return 0.0;

		else {
			//incrementing history and memory
			if (maxHistory == historyCount) {
				if (maxHistory == 0) {
					maxHistory = 5;
					history = new char* [maxHistory];
				}
				else {
					maxHistory *= 2;
					char** temphistory = new char* [maxHistory];
					for (int i = 0; i < historyCount; i++) {
						temphistory[i] = history[i];
					}
					delete[] history;
					history = temphistory;
				}
			}
			//memory
			if (maxMemory == memoryCount) {
				if (maxMemory == 0) {
					maxMemory = 5;
					memory = new double[maxMemory];
				}
				else {
					maxMemory *= 2;
					double* tempmemory = new double[maxMemory];
					for (int i = 0; i < memoryCount; i++) {
						tempmemory[i] = memory[i];
					}
					delete[] memory;
					memory = tempmemory;
				}
			}

			double res = sqrt(value);
			if (res == 0.0) return 0.0;
			//finding length of expression for history
			int length = 0;

			char* strb = inttostr((long long int)value);
			char* strres = inttostr((long long int)res);

			length += len("root(") + len(strb) + len(") = ") + len(strres) + 1;  //for spaces operators and null char
			//storing in history
			history[historyCount] = new char[length];
			int ind = 0;

			//storing root(
			history[historyCount][ind++] = 'r';
			history[historyCount][ind++] = 'o';
			history[historyCount][ind++] = 'o';

			history[historyCount][ind++] = 't';
			history[historyCount][ind++] = '(';


			//storing b

			int lenb = len(strb);
			for (int i = 0; i < lenb; i++) {
				history[historyCount][ind] = *(strb + i);
				ind++;
			}

			history[historyCount][ind++] = ')';
			history[historyCount][ind++] = ' ';
			history[historyCount][ind++] = '=';
			history[historyCount][ind++] = ' ';

			//storing res

			int lenres = len(strres);
			for (int i = 0; i < lenres; i++) {
				history[historyCount][ind] = *(strres + i);
				ind++;
			}

			history[historyCount][ind] = '\0';
			delete[] strb;
			delete[] strres;

			historyCount++;
			memory[memoryCount++] = res;
			return res;
		}
	}

	void storeVariable(char name, double value) {
		if (!isRunning)
			return;
		else {
			if (name >= 'a' && name <= 'z')
				name = name - 32;
			variables[name - 'A'] = value;
		}
	}

	double recallVariable(char name) const {
		if (!isRunning)
			return 0.0;
		else {
			if (name >= 'a' && name <= 'z')
				name = name - 32;
			return variables[name - 'A'];
		}
	}

	double getMean() const {
		if (!isRunning)
			return 0.0;
		if (memoryCount == 0)
			return 0.0;
		else {
			double sum = 0;
			for (int i = 0; i < memoryCount; i++) {
				sum += memory[i];
			}
			return sum / memoryCount;
		}
	}
	double getSum() const {
		if (!isRunning)
			return 0.0;
		if (memoryCount == 0)
			return 0.0;
		else {
			double sum = 0;
			for (int i = 0; i < memoryCount; i++) {
				sum += memory[i];
			}
			return sum;
		}
	}

	double getMin() const {
		if (!isRunning)
			return 0.0;
		if (memoryCount == 0)
			return 0.0;
		double min = memory[0];

		for (int i = 0; i < memoryCount; i++) {
			if (memory[i] < min) {
				min = memory[i];
			}
		}
		return min;
	}
	double getMax() const {
		if (!isRunning)
			return 0.0;
		if (memoryCount == 0)
			return 0.0;
		double max = memory[0];

		for (int i = 0; i < memoryCount; i++) {
			if (memory[i] > max) {
				max = memory[i];
			}
		}
		return max;
	}

	bool exportHistory(const char* filename, Storage* storage) {
		if (!isRunning)
			return false;
		File f(filename, "", 1);
		for (int i = 0; i < historyCount; i++) {
			f.setContent(history[i]);
		}
		return storage->saveFile(f);
	}
	void printHistory() const {
		if (!isRunning)
			return;
		cout << "-----------CALCULATOR HISTORY------------" << endl << endl;
		for (int i = 0; i < historyCount; i++) {
			cout << history[i] << endl;
		}
	}

	int  getMemoryCount() const {
		return memoryCount;
	}

	double operator()(double a, char op, double b) {
		if (op == '+') {
			return add(a, b);
		}
		else if (op == '-') {
			return subtract(a, b);
		}
		else if (op == '/')
			return divide(a, b);
		else if (op == '*')
			return multiply(a, b);
		else if (op == '^')
			return power(a, b);
		else {
			return 0.0;
		}
	}

	double operator[](char varName) const {
		if (!isRunning)
			return 0.0;
		else {
			if (varName >= 'a' && varName <= 'z')
				varName = varName - 32;
			return variables[varName - 'A'];
		}
	}

	//destructor
	~Calculator() {
		for (int i = 0; i < historyCount; i++) {
			delete history[i];
		}
		delete[] history;
		history = nullptr;
		delete[] memory;
		memory = nullptr;
	}
};


//=================SETTINGS========================
class Settings {
	char** keys;
	char** values;
	// dynamic array of setting keys 
	// parallel array of setting values 
	int     count, maxPairs;
	char* name;
	// = "Settings" 
	int     diskSize;      // = 5
	int     ramRequired;  // = 20

public:
	bool    isRunning;
	Settings() {
		keys = new char* [5];
		const char* temp = "font_size";
		keys[0] = new char[len(temp) + 1];
		copystr(temp, keys[0], len(temp));
		keys[0][len(temp)] = '\0';

		temp = "font_family";
		keys[1] = new char[len(temp) + 1];
		copystr(temp, keys[1], len(temp));
		keys[1][len(temp)] = '\0';

		temp = "theme";
		keys[2] = new char[len(temp) + 1];
		copystr(temp, keys[2], len(temp));
		keys[2][len(temp)] = '\0';

		temp = "language";
		keys[3] = new char[len(temp) + 1];
		copystr(temp, keys[3], len(temp));
		keys[3][len(temp)] = '\0';

		temp = "date_format";
		keys[4] = new char[len(temp) + 1];
		copystr(temp, keys[4], len(temp));
		keys[4][len(temp)] = '\0';

		values = new char* [5];
		temp = "12";
		values[0] = new char[len(temp) + 1];
		copystr(temp, values[0], len(temp));
		values[0][len(temp)] = '\0';

		temp = "Arial";
		values[1] = new char[len(temp) + 1];
		copystr(temp, values[1], len(temp));
		values[1][len(temp)] = '\0';

		temp = "light";
		values[2] = new char[len(temp) + 1];
		copystr(temp, values[2], len(temp));
		values[2][len(temp)] = '\0';

		temp = "English";
		values[3] = new char[len(temp) + 1];
		copystr(temp, values[3], len(temp));
		values[3][len(temp)] = '\0';

		temp = "DD/MM/YYYY";
		values[4] = new char[len(temp) + 1];
		copystr(temp, values[4], len(temp));
		values[4][len(temp)] = '\0';

		count = 5;
		maxPairs = 5;
		isRunning = false;
		diskSize = 5;
		ramRequired = 20;
		temp = "Settings";
		this->name = new char[len(temp) + 1];
		copystr(temp, this->name, len(temp));
		this->name[len(temp)] = '\0';
	}
	//getters
	char* getname() {
		if (this != NULL)
			return this->name;
		else
			return nullptr;
	}
	int getdiskSize() {
		return this->diskSize;
	}
	int getramRequired() {
		return this->ramRequired;
	}
	bool getisRunning() {
		return isRunning;
	}
	//copy constructor
	Settings(const Settings& other) {
		isRunning = other.isRunning;
		diskSize = other.diskSize;
		ramRequired = other.ramRequired;
		count = other.count;
		maxPairs = other.maxPairs;
		name = new char[len(other.name) + 1];
		copystr(other.name, name, len(other.name));
		name[len(other.name)] = '\0';
		if (other.keys == nullptr)
			keys = nullptr;
		else
			keys = new char* [maxPairs];
		if (other.values == nullptr)
			values = nullptr;
		else
			values = new char* [maxPairs];
		if (keys != nullptr && values != nullptr)
			for (int i = 0; i < count; i++) {
				keys[i] = new char[len(other.keys[i]) + 1];
				copystr(other.keys[i], keys[i], len(other.keys[i]));
				keys[i][len(other.keys[i])] = '\0';
				values[i] = new char[len(other.values[i]) + 1];
				copystr(other.values[i], values[i], len(other.values[i]));
				values[i][len(other.values[i])] = '\0';
			}
	}
	//setter
	void setisRunning(bool state) {
		isRunning = state;
	}

	bool setSetting(const char* key, const char* value) {
		if (!isRunning)
			return false;
		else {
			for (int i = 0; i < 5; i++) {
				if (areEqual(keys[i], key, len(key))) {
					delete[] values[i];
					values[i] = new char[len(value) + 1];
					copystr(value, values[i], len(value));
					values[i][len(value)] = '\0';
					return true;
				}
			}
		}
		return false;
	}

	const char* getSetting(const char* key) const {
		if (!isRunning)
			return nullptr;
		else {
			for (int i = 0; i < 5; i++) {
				if (areEqual(keys[i], key, len(key))) {
					return  values[i];
				}
			}
		}
		return nullptr;
	}

	void displaySettings() const {
		if (!isRunning)
			return;
		else {
			cout << "-----------SETTINGS--------------" << endl << endl;
			for (int i = 0; i < 5; i++) {
				cout << keys[i] << ":  " << values[i] << endl;
			}
		}
	}

	bool resetToDefault() {
		if (!isRunning)
			return false;
		else {
			for (int i = 0; i < 5; i++)
				delete[] values[i];
			delete[] values;
			const char* temp;
			values = new char* [5];
			temp = "12";
			values[0] = new char[len(temp) + 1];
			copystr(temp, values[0], len(temp));
			values[0][len(temp)] = '\0';

			temp = "Arial";
			values[1] = new char[len(temp) + 1];
			copystr(temp, values[1], len(temp));
			values[1][len(temp)] = '\0';

			temp = "light";
			values[2] = new char[len(temp) + 1];
			copystr(temp, values[2], len(temp));
			values[2][len(temp)] = '\0';

			temp = "English";
			values[3] = new char[len(temp) + 1];
			copystr(temp, values[3], len(temp));
			values[3][len(temp)] = '\0';

			temp = "DD/MM/YYYY";
			values[4] = new char[len(temp) + 1];
			copystr(temp, values[4], len(temp));
			values[4][len(temp)] = '\0';
			return true;
		}
	}

	~Settings() {
		for (int i = 0; i < count; i++) {
			delete[] keys[i];
			delete[] values[i];
		}
		delete[]keys;
		delete[]values;
		keys = nullptr;
		values = nullptr;
	}
};


//================APPLICATION MANAGER==================
class ApplicationManager {
	FileExplorer* fileExplorer;
	RecycleBin* recycleBin;
	Calculator* calculator;
	Settings* settings;
	Storage* storage;
	RAM* ram;
public:
	ApplicationManager() {}
	ApplicationManager(Storage* storage, RAM* ram) {
		this->storage = storage;
		this->ram = ram;

		this->fileExplorer = new FileExplorer(storage);
		this->recycleBin = new RecycleBin(storage);
		this->calculator = new Calculator();
		this->settings = new Settings();


		//creating files
		File FEfile(fileExplorer->getname(), "", fileExplorer->getdiskSize());
		File RBfile(recycleBin->getname(), "", recycleBin->getdiskSize());
		File calculatorfile(calculator->getname(), "", calculator->getdiskSize());
		File settingsfile(settings->getname(), "", settings->getdiskSize());

		//saving files to storage
		storage->saveFile(FEfile);
		storage->saveFile(RBfile);
		storage->saveFile(calculatorfile);
		storage->saveFile(settingsfile);

	}

	bool launchApp(const char* appName) {
		File* file = storage->getFile(appName);
		if (file == nullptr)	return false;


		if (areEqual(appName, "FileExplorer", len(appName)) && len(appName) == len("FileExplorer"))
			if (ram->allocate(fileExplorer->getramRequired()) == true) {
				fileExplorer->setisRunning(true);
			}
			else
				return false;

		else if (areEqual(appName, "RecycleBin", len(appName)) && len(appName) == len("RecycleBin"))
			if (ram->allocate(recycleBin->getramRequired()) == true) {
				recycleBin->setisRunning(true);
			}
			else
				return false;


		else if (areEqual(appName, "Calculator", len(appName)) && len(appName) == len("Calculator"))
			if (ram->allocate(calculator->getramRequired()) == true) {
				calculator->setisRunning(true);
			}
			else
				return false;

		else if (areEqual(appName, "Settings", len(appName)) && len(appName) == len("Settings"))
			if (ram->allocate(settings->getramRequired()) == true) {
				settings->setisRunning(true);
			}
			else
				return false;

		else return false;
		return true;
	}

	bool closeApp(const char* appName) {
		File* file = storage->getFile(appName);

		if (file == nullptr)	return false;

		if (areEqual(appName, "FileExplorer", len(appName)) && len(appName) == len("FileExplorer")) {
			if (fileExplorer->getisRunning() == false)	return false;
			ram->deallocate(fileExplorer->getramRequired());
			fileExplorer->setisRunning(false);
		}

		else if (areEqual(appName, "RecycleBin", len(appName)) && len(appName) == len("RecycleBin")) {
			if (recycleBin->getisRunning() == false)	return false;
			ram->deallocate(recycleBin->getramRequired());
			recycleBin->setisRunning(false);
		}



		else if (areEqual(appName, "Calculator", len(appName)) && len(appName) == len("Calculator")) {
			if (calculator->getisRunning() == false)	return false;
			ram->deallocate(calculator->getramRequired());
			calculator->setisRunning(false);
		}


		else if (areEqual(appName, "Settings", len(appName)) && len(appName) == len("Settings")) {
			if (settings->getisRunning() == false)	return false;
			ram->deallocate(settings->getramRequired());
			settings->setisRunning(false);
		}

		else return false;
		return true;

	}

	bool isRunning(const char* appName) const {
		File* file = storage->getFile(appName);
		if (file == nullptr)	return false;

		if (areEqual(appName, "FileExplorer", len(appName)) && len(appName) == len("FileExplorer")) {
			return fileExplorer->getisRunning();
		}

		else if (areEqual(appName, "RecycleBin", len(appName)) && len(appName) == len("RecycleBin")) {
			return recycleBin->getisRunning();
		}

		else if (areEqual(appName, "Calculator", len(appName)) && len(appName) == len("Calculator")) {
			return calculator->getisRunning();
		}


		else if (areEqual(appName, "Settings", len(appName)) && len(appName) == len("Settings")) {
			return settings->getisRunning();
		}

		else return false;

	}

	void* getApp(const char* appName) const {
		File* file = storage->getFile(appName);
		if (file == nullptr)	return false;

		if (areEqual(appName, "FileExplorer", len(appName)) && len(appName) == len("FileExplorer")) {
			return (void*)fileExplorer;
		}

		else if (areEqual(appName, "RecycleBin", len(appName)) && len(appName) == len("RecycleBin")) {
			return (void*)recycleBin;
		}

		else if (areEqual(appName, "Calculator", len(appName)) && len(appName) == len("Calculator")) {
			return (void*)calculator;
		}

		else if (areEqual(appName, "Settings", len(appName)) && len(appName) == len("Settings")) {
			return (void*)settings;
		}
		else return nullptr;
	}

	void dispalyAll()const {
		cout << "---------Application Details-------------" << endl << endl;
		//file explorer
		cout << "---------Application Name: " << fileExplorer->getname() << "-----------" << endl;
		cout << "Running State: ";
		if (fileExplorer->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "Disk Size: " << fileExplorer->getdiskSize() << "MB" << endl;
		cout << "RAM Requirement: " << fileExplorer->getramRequired() << endl << endl;

		//recyclebin
		cout << "---------Application Name: " << recycleBin->getname() << "-----------" << endl;
		cout << "Running State: ";
		if (recycleBin->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "Disk Size: " << recycleBin->getdiskSize() << "MB" << endl;
		cout << "RAM Requirement: " << recycleBin->getramRequired() << endl << endl;

		//calculator
		cout << "---------Application Name: " << calculator->getname() << "-----------" << endl;
		cout << "Running State: ";
		if (calculator->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "Disk Size: " << calculator->getdiskSize() << "MB" << endl;
		cout << "RAM Requirement: " << calculator->getramRequired() << endl << endl;

		//settings
		cout << "---------Application Name: " << settings->getname() << "-----------" << endl;
		cout << "Running State: ";
		if (settings->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "Disk Size: " << settings->getdiskSize() << "MB" << endl;
		cout << "RAM Requirement: " << settings->getramRequired() << endl << endl;
	}

	~ApplicationManager() {
		delete fileExplorer;
		delete recycleBin;
		delete calculator;
		delete settings;
	}
};

//=============================COMPUTER===============================
class Computer {
	Storage* storage;
	RAM* ram;
	ApplicationManager* apps;


public:
	Computer() {}
	Computer(int storageMB, int ramMB) {
		storage = new Storage(storageMB);
		ram = new RAM(ramMB);
		apps = new ApplicationManager(storage, ram);
	}

	bool launchApp(const char* appName) {
		return apps->launchApp(appName);
	}

	bool closeApp(const char* appName) {
		return apps->closeApp(appName);
	}


	inline void displaySystemStatus() const {
		cout << "-----------SYSTEM STATUS--------------" << endl << endl;
		cout << "Storage Usage: " << storage->getusedSpace() << "MB" << endl << endl;
		cout << "RAM Usage: " << ram->getAvailableMemory() << "MB available" << endl << endl;


		cout << "---FILE EXPLORER---" << endl;
		FileExplorer* fe = (FileExplorer*)apps->getApp("FileExplorer");

		cout << "Running State: ";
		if (fe->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "RAM Usage: ";
		if (fe->getisRunning())
			cout << fe->getramRequired() << endl;
		else
			cout << 0 << "MB" << endl;


		cout << "---Recycle BIN---" << endl;
		RecycleBin* rb = (RecycleBin*)apps->getApp("RecycleBin");

		cout << "Running State: ";
		if (rb->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "RAM Usage: ";
		if (rb->getisRunning())
			cout << rb->getramRequired() << endl;
		else
			cout << 0 << "MB" << endl;

		cout << "---Calculator---" << endl;
		Calculator* cal = (Calculator*)apps->getApp("Calculator");

		cout << "Running State: ";
		if (cal->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "RAM Usage: ";
		if (cal->getisRunning())
			cout << cal->getramRequired() << endl;
		else
			cout << 0 << "MB" << endl;

		cout << "---SETTINGS---" << endl;
		Settings* s = (Settings*)apps->getApp("Settings");

		cout << "Running State: ";
		if (s->getisRunning())
			cout << "Running(true)" << endl;
		else
			cout << "Not Running(false)" << endl;
		cout << "RAM Usage: ";
		if (s->getisRunning())
			cout << s->getramRequired() << endl;
		else
			cout << 0 << "MB" << endl;
	}
	//getters
	RAM* getRam()const {
		return ram;
	}
	Storage* getStorage() {
		return storage;
	}
	ApplicationManager* getApplicationManager() {
		return apps;
	}


	//accessors
	FileExplorer* getFileExplorer() {
		return (FileExplorer*)apps->getApp("FileExplorer");
	}
	RecycleBin* getRecycleBin() {
		return (RecycleBin*)apps->getApp("RecycleBin");
	}
	Calculator* getCalculator() {
		return (Calculator*)apps->getApp("Calculator");
	}
	Settings* getSettings() {
		return (Settings*)apps->getApp("Settings");
	}


	bool createFile(const char* name, const char* content, int size) {

		FileExplorer* fe = (FileExplorer*)apps->getApp("FileExplorer");
		if (!fe->getisRunning()) {
			return false;
		}
		else {
			fe->createFile(name, content, size);
		}
	}
	bool deleteFile(const char* name) {
		FileExplorer* f = (FileExplorer*)apps->getApp("FileExplorer");
		RecycleBin* r = (RecycleBin*)apps->getApp("RecycleBin");
		return f->deleteFile(name, r);  // FileExplorer handles everything
	}
	bool restoreFile(const char* name) {
		RecycleBin* r = (RecycleBin*)apps->getApp("RecycleBin");
		return r->restoreFile(name);
	}

	void emptyRecycleBin() {
		RecycleBin* r = (RecycleBin*)apps->getApp("RecycleBin");
		r->emptyBin();
	}
	void listFiles() const {
		FileExplorer* f = (FileExplorer*)apps->getApp("FileExplorer");
		f->listFiles();
	}
	void listRecycleBin() const {
		RecycleBin* r = (RecycleBin*)apps->getApp("RecycleBin");
		r->listBin();
	}
	Computer& operator+=(const char* appName) {
		this->launchApp(appName);
		return *this;
	}
	Computer& operator-=(const char* appName) {
		this->closeApp(appName);
		return *this;
	}
	bool operator>(const Computer& other) const {
		return((this->getRam()->getAvailableMemory()) > (other.getRam()->getAvailableMemory()));
	}
	friend ostream& operator<<(ostream&, const Computer& c);

	double calculate(double a, char op, double b) {
		Calculator* cal = (Calculator*)apps->getApp("Calculator");
		return (*cal)(a, op, b);
	}
	bool exportCalculations(const char* filename) {
		Calculator* cal = (Calculator*)apps->getApp("Calculator");
		return cal->exportHistory(filename, storage);
	}

	bool setSetting(const char* key, const char* value) {
		Settings* s = (Settings*)apps->getApp("Settings");
		if (s->getisRunning())
			return s->setSetting(key, value);
		else return false;
	}

	const char* getSetting(const char* key) const {
		Settings* s = (Settings*)apps->getApp("Settings");
		if (s->getisRunning())
			return s->getSetting(key);
		else return nullptr;
	}

	~Computer() {}
};

inline ostream& operator<<(ostream& out, const Computer& c) {
	out << "-----------SYSTEM STATUS--------------\n\n";
	out << "Storage Usage: " << c.storage->getusedSpace() << "MB\n\n";
	out << "RAM Usage: " << c.ram->getAvailableMemory() << "MB available\n\n";

	out << "---FILE EXPLORER---\n";
	FileExplorer* fe = (FileExplorer*)c.apps->getApp("FileExplorer");
	out << "Running State: ";
	if (fe->getisRunning())
		out << "Running(true)" << endl;
	else
		out << "Not Running(false)" << endl;
	out << "RAM Usage: ";
	if (fe->getisRunning())
		out << fe->getramRequired() << "MB" << endl;
	else
		out << "0MB\n";

	out << "---Recycle BIN---" << endl;
	RecycleBin* rb = (RecycleBin*)c.apps->getApp("RecycleBin");
	out << "Running State: ";
	if (rb->getisRunning())
		out << "Running(true)\n";
	else
		out << "Not Running(false)\n";

	out << "RAM Usage: ";
	if (rb->getisRunning())
		out << rb->getramRequired() << "MB" << endl;
	else
		out << "0MB" << endl;

	out << "---Calculator---" << endl;


	Calculator* cal = (Calculator*)c.apps->getApp("Calculator");
	out << "Running State: ";
	if (cal->getisRunning())
		out << "Running(true)" << endl;
	else
		out << "Not Running(false)\n";

	out << "RAM Usage: ";

	if (cal->getisRunning())
		out << cal->getramRequired() << "MB\n";
	else
		out << "0MB\n";

	out << "---SETTINGS---\n";

	Settings* s = (Settings*)c.apps->getApp("Settings");
	out << "Running State: ";
	if (s->getisRunning())
		out << "Running(true)\n";
	else
		out << "Not Running(false)\n";

	out << "RAM Usage: ";

	if (s->getisRunning())
		out << s->getramRequired() << "MB" << endl;
	else
		out << "0MB" << endl;

	return out;
}




//===========================MAIN KA MAAL====================================


inline void printLine() {
	cout << "============================================" << endl;
}

inline void printDash() {
	cout << "--------------------------------------------" << endl;
}



//================= MAIN MENU ====================

inline void showMainMenu() {
	printLine();
	cout << "       GRANDMA'S COMPUTER SYSTEM" << endl;
	printLine();
	cout << "  1.  Boot Up Computer" << endl;
	cout << "  2.  Exit" << endl;
	printLine();
	cout << "  Enter choice: ";
}

// ==================== COMPUTER MENU ====================

inline void showComputerMenu() {
	printLine();
	cout << "         COMPUTER MAIN MENU" << endl;
	printLine();
	cout << "  [1]  Application Manager" << endl;
	cout << "  [2]  File Manager" << endl;
	cout << "  [3]  Calculator" << endl;
	cout << "  [4]  Settings" << endl;
	cout << "  [5]  Display System Status" << endl;
	cout << "  [6]  Shut Down Computer" << endl;
	printLine();
	cout << "  Enter choice: ";
}

// ==================== APP MANAGER MENU ====================

inline void showAppManagerMenu() {
	printDash();
	cout << "       APPLICATION MANAGER" << endl;
	printDash();
	cout << "  [1]  Launch an Application" << endl;
	cout << "  [2]  Close an Application" << endl;
	cout << "  [3]  Check if App is Running" << endl;
	cout << "  [4]  Display All Applications" << endl;
	cout << "  [5]  Back" << endl;
	printDash();
	cout << "  Enter choice: ";
}

inline void appManagerMenu(Computer& computer) {
	int choice = 0;

	while (true) {
		showAppManagerMenu();
		cin >> choice;
		cin.ignore();
		cout << endl;

		if (choice == 1) {
			cout << "  Available Apps: FileExplorer | RecycleBin | Calculator | Settings" << endl;
			cout << "  Enter app name: ";
			char appName[50];
			cin.getline(appName, 50);

			bool result = computer.launchApp(appName);
			if (result == true) {
				cout << endl << "  [SUCCESS] " << appName << " launched successfully." << endl;
			}
			else {
				cout << endl << "  [FAILED] Could not launch " << appName << ". Check RAM or app name." << endl;
			}

		}

		else if (choice == 2) {
			cout << "  Enter app name to close: ";
			char appName[50];
			cin.getline(appName, 50);

			bool result = computer.closeApp(appName);
			if (result == true) {
				cout << endl << "  [SUCCESS] " << appName << " closed." << endl;
			}
			else {
				cout << endl << "  [FAILED] Could not close " << appName << ". It may not be running." << endl;
			}
		}

		else if (choice == 3) {
			cout << "  Enter app name: ";
			char appName[50];
			cin.getline(appName, 50);

			ApplicationManager* am = computer.getApplicationManager();
			bool running = am->isRunning(appName);
			cout << endl;
			if (running == true) {
				cout << "  " << appName << " is currently RUNNING." << endl;
			}
			else {
				cout << "  " << appName << " is currently NOT running." << endl;
			}
		}

		else if (choice == 4) {
			cout << endl;
			computer.getApplicationManager()->dispalyAll();

		}

		else if (choice == 5) {
			break;
		}

		else {
			cout << "  Invalid choice. Try again." << endl;

		}
	}
}

//=================== FILE MANAGER MENU ====================

inline void showFileManagerMenu() {
	printDash();
	cout << "         FILE MANAGER" << endl;
	printDash();
	cout << "  Note: FileExplorer and RecycleBin must be running." << endl;
	printDash();
	cout << "  [1]  Create a File" << endl;
	cout << "  [2]  Delete a File" << endl;
	cout << "  [3]  Restore a File from Recycle Bin" << endl;
	cout << "  [4]  List All Files" << endl;
	cout << "  [5]  View File Content" << endl;
	cout << "  [6]  Empty Recycle Bin" << endl;
	cout << "  [7]  List Recycle Bin" << endl;
	cout << "  [8]  Merge Two Files (File + Operator)" << endl;
	cout << "  [9]  Compare Two Files (Size)" << endl;
	cout << "  [10] Back" << endl;
	printDash();
	cout << "  Enter choice: ";
}

inline void fileManagerMenu(Computer& computer) {
	int choice = 0;

	while (true) {
		showFileManagerMenu();
		cin >> choice;
		cin.ignore();
		cout << endl;

		if (choice == 1) {
			char name[100];
			char content[500];
			int size = 0;

			cout << "  Enter file name: ";
			cin.getline(name, 100);
			cout << "  Enter file content: ";
			cin.getline(content, 500);
			cout << "  Enter file size (MB): ";
			cin >> size;
			cin.ignore();

			bool result = computer.createFile(name, content, size);
			cout << endl;
			if (result == true) {
				cout << "  [SUCCESS] File '" << name << "' created." << endl;
			}
			else {
				cout << "  [FAILED] Could not create file. FileExplorer may not be running or storage is full." << endl;
			}

		}

		else if (choice == 2) {
			char name[100];
			cout << "  Enter file name to delete: ";
			cin.getline(name, 100);

			bool result = computer.deleteFile(name);
			cout << endl;
			if (result == true) {
				cout << "  [SUCCESS] File '" << name << "' deleted." << endl;
			}
			else {
				cout << "  [FAILED] Could not delete file. It may not exist." << endl;
			}

		}

		else if (choice == 3) {
			char name[100];
			cout << "  Enter file name to restore: ";
			cin.getline(name, 100);

			bool result = computer.restoreFile(name);
			cout << endl;
			if (result == true) {
				cout << "  [SUCCESS] File '" << name << "' restored from Recycle Bin." << endl;
			}
			else {
				cout << "  [FAILED] Could not restore. File may not be in bin or storage is full." << endl;
			}

		}

		else if (choice == 4) {
			cout << endl;
			computer.listFiles();

		}

		else if (choice == 5) {
			char name[100];
			cout << "  Enter file name to view: ";
			cin.getline(name, 100);
			cout << endl;

			FileExplorer* fe = computer.getFileExplorer();
			File* f = fe->viewFile(name);
			if (f == nullptr) {
				cout << "  [FAILED] File not found or FileExplorer not running." << endl;
			}
			else {
				printDash();
				cout << "  File Name    : " << f->getName() << endl;
				cout << "  File Size    : " << f->getSize() << " MB" << endl;
				cout << "  File Content : " << f->getContent() << endl;
				printDash();
			}
		}

		else if (choice == 6) {
			computer.emptyRecycleBin();
			cout << "  Recycle Bin emptied (if it was running)." << endl;

		}

		else if (choice == 7) {
			cout << endl;
			computer.listRecycleBin();

		}

		else if (choice == 8) {
			char name1[100];
			char name2[100];
			cout << "  Enter first file name: ";
			cin.getline(name1, 100);
			cout << "  Enter second file name: ";
			cin.getline(name2, 100);
			cout << endl;

			Storage* st = computer.getStorage();
			File* f1 = st->getFile(name1);
			File* f2 = st->getFile(name2);

			if (f1 == nullptr || f2 == nullptr) {
				cout << "  [FAILED] One or both files not found in storage." << endl;
			}
			else {
				File merged = *f1 + *f2;
				printDash();
				cout << "  Merged File Name    : " << merged.getName() << endl;
				cout << "  Merged File Size    : " << merged.getSize() << " MB" << endl;
				cout << "  Merged File Content : " << merged.getContent() << endl;
				printDash();
				cout << endl;
				cout << "  Do you want to save the merged file? (y/n): ";
				char ans;
				cin >> ans;
				cin.ignore();
				if (ans == 'y' || ans == 'Y') {
					bool saved = st->saveFile(merged);
					if (saved == true) {
						cout << "  [SUCCESS] Merged file saved to storage." << endl;
					}
					else {
						cout << "  [FAILED] Not enough storage space." << endl;
					}
				}
			}
		}

		else if (choice == 9) {
			char name1[100];
			char name2[100];
			cout << "  Enter first file name: ";
			cin.getline(name1, 100);
			cout << "  Enter second file name: ";
			cin.getline(name2, 100);
			cout << endl;

			Storage* st = computer.getStorage();
			File* f1 = st->getFile(name1);
			File* f2 = st->getFile(name2);

			if (f1 == nullptr || f2 == nullptr) {
				cout << "  [FAILED] One or both files not found." << endl;
			}
			else {
				printDash();
				cout << "  " << f1->getName() << " size: " << f1->getSize() << " MB" << endl;
				cout << "  " << f2->getName() << " size: " << f2->getSize() << " MB" << endl;
				printDash();
				if (*f1 < *f2) {
					cout << "  Result: " << f1->getName() << " is SMALLER than " << f2->getName() << endl;
				}
				else if (*f2 < *f1) {
					cout << "  Result: " << f2->getName() << " is SMALLER than " << f1->getName() << endl;
				}
				else {
					cout << "  Result: Both files are of EQUAL size." << endl;
				}
			}
		}

		else if (choice == 10) {
			break;
		}

		else {
			cout << "  Invalid choice. Try again." << endl;

		}
	}
}

//=================== CALCULATOR MENU ====================

inline void showCalculatorMenu() {
	printDash();
	cout << "            CALCULATOR" << endl;
	printDash();
	cout << "  Note: Calculator must be running." << endl;
	printDash();
	cout << "  [1]  Add" << endl;
	cout << "  [2]  Subtract" << endl;
	cout << "  [3]  Multiply" << endl;
	cout << "  [4]  Divide" << endl;
	cout << "  [5]  Power" << endl;
	cout << "  [6]  Square Root" << endl;
	cout << "  [7]  Use Operator (a op b)" << endl;
	cout << "  [8]  Store Variable (A-Z)" << endl;
	cout << "  [9]  Recall Variable (A-Z)" << endl;
	cout << "  [10] Get Statistics (Mean/Sum/Min/Max)" << endl;
	cout << "  [11] Print History" << endl;
	cout << "  [12] Export History to File" << endl;
	cout << "  [13] Back" << endl;
	printDash();
	cout << "  Enter choice: ";
}

inline void calculatorMenu(Computer& computer) {
	int choice = 0;

	while (true) {
		showCalculatorMenu();
		cin >> choice;
		cin.ignore();
		cout << endl;

		Calculator* cal = computer.getCalculator();

		if (choice == 1) {
			double a = 0, b = 0;
			cout << "  Enter first number: ";
			cin >> a;
			cout << "  Enter second number: ";
			cin >> b;
			cin.ignore();
			double result = cal->add(a, b);
			cout << endl << "  Result: " << a << " + " << b << " = " << result << endl;

		}

		else if (choice == 2) {
			double a = 0, b = 0;
			cout << "  Enter first number: ";
			cin >> a;
			cout << "  Enter second number: ";
			cin >> b;
			cin.ignore();
			double result = cal->subtract(a, b);
			cout << endl << "  Result: " << a << " - " << b << " = " << result << endl;

		}

		else if (choice == 3) {
			double a = 0, b = 0;
			cout << "  Enter first number: ";
			cin >> a;
			cout << "  Enter second number: ";
			cin >> b;
			cin.ignore();
			double result = cal->multiply(a, b);
			cout << endl << "  Result: " << a << " * " << b << " = " << result << endl;

		}

		else if (choice == 4) {
			double a = 0, b = 0;
			cout << "  Enter first number: ";
			cin >> a;
			cout << "  Enter divisor: ";
			cin >> b;
			cin.ignore();
			double result = cal->divide(a, b);
			cout << endl << "  Result: " << a << " / " << b << " = " << result << endl;

		}

		else if (choice == 5) {
			double base = 0, exp = 0;
			cout << "  Enter base: ";
			cin >> base;
			cout << "  Enter exponent: ";
			cin >> exp;
			cin.ignore();
			double result = cal->power(base, exp);
			cout << endl << "  Result: " << base << " ^ " << exp << " = " << result << endl;

		}

		else if (choice == 6) {
			double val = 0;
			cout << "  Enter value: ";
			cin >> val;
			cin.ignore();
			double result = cal->squareRoot(val);
			cout << endl << "  Result: sqrt(" << val << ") = " << result << endl;

		}

		else if (choice == 7) {
			double a = 0, b = 0;
			char op;
			cout << "  Enter first number: ";
			cin >> a;
			cout << "  Enter operator (+, -, *, /, ^): ";
			cin >> op;
			cout << "  Enter second number: ";
			cin >> b;
			cin.ignore();
			double result = computer.calculate(a, op, b);
			cout << endl << "  Result: " << a << " " << op << " " << b << " = " << result << endl;

		}

		else if (choice == 8) {
			char varName;
			double value = 0;
			cout << "  Enter variable name (A-Z): ";
			cin >> varName;
			cout << "  Enter value: ";
			cin >> value;
			cin.ignore();
			cal->storeVariable(varName, value);
			cout << endl << "  Variable '" << varName << "' set to " << value << endl;
		}

		else if (choice == 9) {
			char varName;
			cout << "  Enter variable name (A-Z): ";
			cin >> varName;
			cin.ignore();
			double val = cal->recallVariable(varName);
			cout << endl << "  Variable '" << varName << "' = " << val << endl;

			cout << "  (Also accessible via [] operator: cal['" << varName << "'] = " << (*cal)[varName] << ")" << endl;

		}

		else if (choice == 10) {
			cout << endl;
			printDash();
			cout << "  Memory Count : " << cal->getMemoryCount() << " result(s) stored" << endl;
			cout << "  Mean         : " << cal->getMean() << endl;
			cout << "  Sum          : " << cal->getSum() << endl;
			cout << "  Min          : " << cal->getMin() << endl;
			cout << "  Max          : " << cal->getMax() << endl;
			printDash();

		}

		else if (choice == 11) {
			cout << endl;
			cal->printHistory();
		}

		else if (choice == 12) {
			char filename[100];
			cout << "  Enter filename to export history to: ";
			cin.getline(filename, 100);
			bool result = computer.exportCalculations(filename);
			cout << endl;
			if (result == true) {
				cout << "  [SUCCESS] History exported to '" << filename << "' in storage." << endl;
			}
			else {
				cout << "  [FAILED] Export failed. Calculator may not be running or storage is full." << endl;
			}
		}

		else if (choice == 13) {
			break;
		}

		else {
			cout << "  Invalid choice. Try again." << endl;
		}
	}
}

// ==================== SETTINGS MENU ====================

inline void showSettingsMenu() {
	printDash();
	cout << "             SETTINGS" << endl;
	printDash();
	cout << "  Note: Settings must be running." << endl;
	cout << "  Keys: font_size | font_family | theme | language | date_format" << endl;
	printDash();
	cout << "  [1]  Set a Setting" << endl;
	cout << "  [2]  Get a Setting" << endl;
	cout << "  [3]  Display All Settings" << endl;
	cout << "  [4]  Reset to Default" << endl;
	cout << "  [5]  Back" << endl;
	printDash();
	cout << "  Enter choice: ";
}

inline void settingsMenu(Computer& computer) {
	int choice = 0;

	while (true) {
		showSettingsMenu();
		cin >> choice;
		cin.ignore();
		cout << endl;

		Settings* s = computer.getSettings();

		if (choice == 1) {
			char key[50];
			char value[50];
			cout << "  Enter key   : ";
			cin.getline(key, 50);
			cout << "  Enter value : ";
			cin.getline(value, 50);
			bool result = computer.setSetting(key, value);
			cout << endl;
			if (result == true) {
				cout << "  [SUCCESS] Setting updated: " << key << " = " << value << endl;
			}
			else {
				cout << "  [FAILED] Could not update setting. Key may be invalid or Settings not running." << endl;
			}
		}

		else if (choice == 2) {
			char key[50];
			cout << "  Enter key: ";
			cin.getline(key, 50);
			const char* val = computer.getSetting(key);
			cout << endl;
			if (val == nullptr) {
				cout << "  [FAILED] Key not found or Settings not running." << endl;
			}
			else {
				cout << "  " << key << " = " << val << endl;
			}
		}

		else if (choice == 3) {
			cout << endl;
			s->displaySettings();

		}

		else if (choice == 4) {
			bool result = s->resetToDefault();
			cout << endl;
			if (result == true) {
				cout << "  [SUCCESS] Settings reset to defaults." << endl;
			}
			else {
				cout << "  [FAILED] Settings not running." << endl;
			}

		}

		else if (choice == 5) {
			break;
		}

		else {
			cout << "  Invalid choice. Try again." << endl;

		}
	}
}

//==================== OPERATOR DEMO MENU ====================

inline void operatorDemoMenu(Computer& computer) {
	printDash();
	cout << "     OPERATOR DEMOS" << endl;
	printDash();
	cout << "  [1]  += (Launch App)" << endl;
	cout << "  [2]  -= (Close App)" << endl;
	cout << "  [3]  >> (Compare RAM with another computer)" << endl;
	cout << "  [4]  << (Print system status)" << endl;
	cout << "  [5]  Back" << endl;
	printDash();
	cout << "  Enter choice: ";

	int choice = 0;
	cin >> choice;
	cin.ignore();
	cout << endl;

	if (choice == 1) {
		char appName[50];
		cout << "  Enter app name to launch via += : ";
		cin.getline(appName, 50);
		computer += appName;
		cout << "  Done. Check app status to confirm." << endl;
	}

	else if (choice == 2) {
		char appName[50];
		cout << "  Enter app name to close via -= : ";
		cin.getline(appName, 50);
		computer -= appName;
		cout << "  Done. Check app status to confirm." << endl;

	}

	else if (choice == 3) {
		int otherStorage = 0, otherRam = 0;
		cout << "  Creating a second computer for comparison." << endl;
		cout << "  Enter storage MB for second computer: ";
		cin >> otherStorage;
		cout << "  Enter RAM MB for second computer: ";
		cin >> otherRam;
		cin.ignore();

		Computer other(otherStorage, otherRam);

		cout << endl;
		printDash();
		cout << "  Your Computer Available RAM : " << computer.getRam()->getAvailableMemory() << " MB" << endl;
		cout << "  Other Computer Available RAM: " << other.getRam()->getAvailableMemory() << " MB" << endl;
		printDash();
		if (computer > other) {
			cout << "  Result: Your computer has MORE available RAM." << endl;
		}
		else {
			cout << "  Result: Other computer has MORE or EQUAL available RAM." << endl;
		}
	}

	else if (choice == 4) {
		cout << endl;
		cout << computer;

	}

	else if (choice == 5) {
		return;
	}

	else {
		cout << "  Invalid choice." << endl;

	}
}

//=================== COMPUTER MENU HANDLER ====================

inline void computerMenu(Computer& computer) {
	int choice = 0;

	while (true) {
		showComputerMenu();
		cin >> choice;
		cin.ignore();
		cout << endl;

		if (choice == 1) {
			appManagerMenu(computer);
		}

		else if (choice == 2) {
			fileManagerMenu(computer);
		}

		else if (choice == 3) {
			calculatorMenu(computer);
		}

		else if (choice == 4) {
			settingsMenu(computer);
		}

		else if (choice == 5) {
			cout << endl;
			computer.displaySystemStatus();
			cout << endl;

			cout << "  -- Operator Demo --" << endl;
			cout << "  (Testing << operator)" << endl;
			cout << endl;
			cout << computer;

			cout << endl;
			cout << "  Would you like to access Operator Demos? (y/n): ";
			char ans;
			cin >> ans;
			cin.ignore();
			if (ans == 'y' || ans == 'Y') {
				operatorDemoMenu(computer);
			}

		}

		else if (choice == 6) {
			cout << "  Shutting down computer..." << endl;
			cout << "  Goodbye, Grandma!" << endl;

			break;
		}

		else {
			cout << "  Invalid choice. Try again." << endl;


		}
	}
}