#include "pch.h"
#include "Header.h"

#include <iostream>
using namespace std;



//==================== MAIN ====================

int main() {

	printLine();
	cout << "   Welcome to Grandma's Computer System" << endl;
	printLine();
	cout << endl;

	int choice = 0;

	while (true) {
		showMainMenu();
		cin >> choice;
		cin.ignore();
		cout << endl;

		if (choice == 1) {
			int storageMB = 0;
			int ramMB = 0;

			cout << "  Booting up your computer..." << endl;
			cout << endl;
			cout << "  Enter total storage (MB): ";
			cin >> storageMB;
			cout << "  Enter total RAM (MB): ";
			cin >> ramMB;
			cin.ignore();

			if (storageMB <= 0 || ramMB <= 0) {
				cout << endl << "  Invalid values. Storage and RAM must be positive." << endl;
				continue;
			}

			// Pre-installed apps need: 20 + 10 + 15 + 5 = 50 MB disk minimum
			if (storageMB < 50) {
				cout << endl << "  Warning: Storage too low for pre-installed apps (need at least 50 MB)." << endl;

				continue;
			}

			cout << endl << "  Initializing hardware and installing apps..." << endl;

			Computer computer(storageMB, ramMB);

			cout << "  Computer is ready!" << endl;
			cout << endl;
			cout << "  Pre-installed apps occupy:" << endl;
			cout << "    FileExplorer : 20 MB disk, needs 50 MB RAM" << endl;
			cout << "    RecycleBin   : 10 MB disk, needs 30 MB RAM" << endl;
			cout << "    Calculator   : 15 MB disk, needs 40 MB RAM" << endl;
			cout << "    Settings     :  5 MB disk, needs 20 MB RAM" << endl;
			cout << endl;
			cout << "  Available Storage : " << computer.getStorage()->getAvailableSpace() << " MB" << endl;
			cout << "  Available RAM     : " << computer.getRam()->getAvailableMemory() << " MB" << endl;


			computerMenu(computer);
		}

		else if (choice == 2) {
			cout << "  Exiting. Take care!" << endl;
			break;
		}

		else {
			cout << "  Invalid choice. Please enter 1 or 2." << endl;
		}
	}

	return 0;
}

