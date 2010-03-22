#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

double raid6(double driveCapacity, double numberOfDrives) {
	double totalRaidSize;
	totalRaidSize = (driveCapacity * numberOfDrives) * (numberOfDrives - 2) / numberOfDrives;
	return (totalRaidSize);
}

double raid5(double driveCapacity, double numberOfDrives) {
	double totalRaidSize;
	totalRaidSize = (driveCapacity * numberOfDrives) * (numberOfDrives - 1) / numberOfDrives;
	return (totalRaidSize);
}

double raid0(double driveCapacity, double numberOfDrives) {
	double totalRaidSize;
	totalRaidSize = driveCapacity * numberOfDrives;
	return (totalRaidSize);
}

double raid1(double driveCapacity, double numberOfDrives) {
	double totalRaidSize;
	totalRaidSize = driveCapacity;
	while (numberOfDrives > 2) {
		if (numberOfDrives > 2) {
			cout << "RAID1 Requires only 2 drives. \n";
			cout << "Please revise number of drives: ";
			cin >> numberOfDrives;
		}
	}
	return (totalRaidSize);
}	


int main(int argc, char *argv[]) {
	// If arg1 = -i use interactive mode
	// commandline option loop
	bool interactiveMode = false;
	double driveCapacity, numberOfDrives;
	int raidLevel ;
	double raidCap;
	for (int optionNumber = 1; optionNumber < argc; optionNumber++) {
		string arg = argv[optionNumber];
		if (arg == "-i" || arg == "--interactive-mode") {
			interactiveMode = true;	
		}
		if (arg == "-nd") {
			numberOfDrives = argv[optionNumber++];
		}
		if (arg == "-rl") {
			raidLevel = argv[optionNumber++];
		}
		if (arg == "-ds") {
		//	driveCapacity = argv[optionNumber++];
			string driveargument = argv[optionNumber++];
			for (int stringLength = 1; length.driveargument() >= stringLength; stringLength++) {
				char ch = driveargument[stringLength];
				if (stringLength == 1) {
				// 10 pow length
				}		
			}
		}
	}			
	if (interactiveMode) {	
		cout << "Entering interactive mode...\n\n";
		cout << "RAID Level: ";
		cin >> raidLevel;
		while (raidLevel == 2 || raidLevel == 4 || raidLevel == 3 || raidLevel > 6) {
			if (! cin.fail()) {
				cout << "Invalid RAID level, supported levels are 0, 1, 5, 6.\n";
				cout << "Please choose again: ";
				cin >> raidLevel;
			}	
			while (cin.fail()) {
				cin.clear();
				cin.ignore(2000000, '\n');
				cout << "Please choose an integer value (ex: 0,1,5,6): " ;
				cin >> raidLevel;	
				//return 1;
			}
	
		}
		cout << "Individual Drive Capacity in GB (ex: 1000 = 1TB): ";
		cin >> driveCapacity;
		while (cin.fail() ) {
			cin.clear();
			cin.ignore(2000000, '\n');
			cout << "Please choose an integer value (ex: 2000): ";
			cin >> driveCapacity;
			//return 1;
		}

		cout << "Number of Drives: ";
		cin >> numberOfDrives;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(2000000, '\n');
			cout << "Please choose an integer value (1,2,3 etc.): " ;
			cin >> numberOfDrives;
			//return 1;
		}
		if (numberOfDrives <= 3 && raidLevel == 6) {
			cout << "For RAID6 you must have at least 4 drives.\n";
			if (numberOfDrives > 2) {
				cout << "You should try RAID5.\n";
			}
			return 1;	
		}
	/*	
	else {
		if (argv[1] == '-ds') {
			driveCapacity = (int) argv[2];
		}
		if (argv[3] == '-nd') {
			numberOfDrives = (int) argv[4];
		}
		if (argv[5] == '-rl') {
			raidLevel = (int) argv[6];
		}
	}
	*/
	}
	else {
		numberOfDrives = atoi(argv[1]);
		driveCapacity = atoi(argv[2]);
		raidLevel = atoi(argv[3]);
	}
	
	// End interactive mode, begin tagging mode
	if (raidLevel == 0) {
		raidCap = raid0(driveCapacity, numberOfDrives);
	}
	else if (raidLevel == 5) {
		raidCap = raid5(driveCapacity, numberOfDrives);
		if (driveCapacity >= 2000) {
			cout << "WARNING: Your chances of a URE are very high using " << driveCapacity / 1000 << "TB drives.  RAID 6 is reccomended!" << endl;
		}

	}
	else if (raidLevel == 6) {
		raidCap = raid6(driveCapacity, numberOfDrives);
	}
	else if (raidLevel == 1) {
		raidCap = raid1(driveCapacity, numberOfDrives);
	}
	
	else {
		cout << "Unsupported RAID level, only RAID 0, 1, 5 and 6 are supported at this time." << endl;
		return 1;
	}	
	cout << "Using RAID" << raidLevel << " you have " << raidCap << "GB (" << raidCap / 1000 << "TB) available space." << endl;
	return 0;
}	
