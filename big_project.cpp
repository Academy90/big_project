#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

struct configs {
	string username;
	string language;
	int volume;
	bool fullscreen;
};
vector<configs> allConfigs;

void showConfig(vector<configs>& allConfigs) {
	if (allConfigs.empty()) {
		cout << "No configurations available." << endl;
		return;
	}
	cout << "Enter configuration number (0-" << allConfigs.size() - 1 << "): ";
	int index;
	cin >> index;
	if (index < 0 || index >= allConfigs.size()) {
		cout << "Invalid configuration number." << endl;
		return;
	}
	configs& cfg = allConfigs[index];
	cout << "Username: " << cfg.username << endl;
	cout << "Language: " << cfg.language << endl;
	cout << "Volume: " << cfg.volume << endl;
	cout << "Fullscreen: " << (cfg.fullscreen ? "Yes" : "No") << endl;
}

void findAndModifyConfig(vector<configs>& allConfigs) {
	string username;
	cout << "Enter username: ";
	cin >> username;
	int index = -1;
	for (int i = 0; i < allConfigs.size(); i++) {
		if (allConfigs[i].username == username) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "User not found" << endl;
		return;
	}
	configs* cfg = &allConfigs[index]; //покажчик на конфігурацію яку ми знайшли

	string name;
	cout << "Enter configuration name(username/language/volume/fullscreen): ";
	cin >> name;
	if (name == "username") {
		cout << "Enter new username: ";
		cin >> cfg->username;
	}
	else if (name == "language") {
		string newLanguage;
		cout << "Enter new language (uk/en/fr/ukr): ";
		cin >> newLanguage;

		if (newLanguage != "uk" && newLanguage != "en" &&
			newLanguage != "fr" && newLanguage != "ukr") {
			cout << "Invalid language." << endl;
			return;
		}
		cfg->language = newLanguage;
	}
	else if (name == "volume") {
		int newVolume;
		cout << "Enter new volume (0-100): ";
		cin >> newVolume;
		if (newVolume < 0 || newVolume > 100) {
			cout << "Invalid volume." << endl;
			return;
		}
		cfg->volume = newVolume;
	}
	else if (name == "fullscreen") {
		int fs;
		cout << "Enter fullscreen (1 - Yes, 0 - No): ";
		cin >> fs;
		if (fs != 0 && fs != 1) {
			cout << "Invalid fullscreen mode." << endl;
			return;
		}
		cfg->fullscreen = (fs == 1);
	}
	else {
		cout << "Configuration not found." << endl;
	}
}

void modifyConfig(vector<configs>& allConfigs) {
	string username;
	cout << "Enter username to modify: ";
	cin >> username;
	int index = -1;
	for (int i = 0; i < allConfigs.size(); i++) {
		if (allConfigs[i].username == username) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "User not found." << endl;
		return;
	}
	configs* cfg = &allConfigs[index];
	string newUsername, newLanguage;
	int newVolume, fs;
	cout << "Enter new username: ";
	cin >> newUsername;
	cout << "Enter new language (uk/en/fr/ukr): ";
	cin >> newLanguage;
	if (newLanguage != "uk" && newLanguage != "en" && newLanguage != "fr" && newLanguage != "ukr") {
		cout << "Invalid language." << endl;
		return;
	}
	cout << "Enter new volume (0-100): ";
	cin >> newVolume;
	if (newVolume < 0 || newVolume > 100) {
		cout << "Invalid volume." << endl;
		return;
	}
	cout << "Enter fullscreen (1 - Yes, 0 - No): ";
	cin >> fs;
	if (fs != 0 && fs != 1) {
		cout << "Invalid fullscreen mode." << endl;
		return;
	}
	cfg->username = newUsername;
	cfg->language = newLanguage;
	cfg->volume = newVolume;
	cfg->fullscreen = (fs == 1);
	cout << "Configuration modified successfully." << endl;
}

void addConfig(vector<configs>& allConfigs) {
	configs newCfg;
	cout << "Enter username: ";
	cin >> newCfg.username;
	cout << "Enter language (uk/en/fr/ukr): ";
	cin >> newCfg.language;
	if (newCfg.language != "uk" && newCfg.language != "en" &&
		newCfg.language != "fr" && newCfg.language != "ukr") {
		cout << "Invalid language." << endl;
		return;
	}
	cout << "Enter volume (0-100): ";
	cin >> newCfg.volume;
	if (newCfg.volume < 0 || newCfg.volume > 100) {
		cout << "Invalid volume." << endl;
		return;
	}
	int fs;
	cout << "Enter fullscreen (1 - Yes, 0 - No): ";
	cin >> fs;
	if (fs != 0 && fs != 1) {
		cout << "Invalid fullscreen mode." << endl;
		return;
	}
	newCfg.fullscreen = (fs == 1);
	allConfigs.push_back(newCfg); //push_back - додаємо новий конфіг в кінець вектора AllConfigs
	cout << "Configuration added successfully" << endl;
}

void deleteConfig(vector<configs>& allConfigs) {
	string username;
	cout << "Enter username to delete: ";
	cin >> username;
	int index = -1;
	for (int i = 0; i < allConfigs.size(); i++) {
		if (allConfigs[i].username == username) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "User not found" << endl;
		return;
	}
	allConfigs.erase(allConfigs.begin() + index);
	cout << "Configuration deleted successfully" << endl;
}

void saveConfigs(vector<configs>& allConfigs) {
	ofstream file("configs.txt");
	if (!file.is_open()) {
		cout << "Could not open file for saving" << endl;
		return;
	}
	file << allConfigs.size() << endl;
	for (int i = 0; i < allConfigs.size(); i++) {
		file << allConfigs[i].username << endl;
		file << allConfigs[i].language << endl;
		file << allConfigs[i].volume << endl;
		file << allConfigs[i].fullscreen << endl;
	}
	file.close();
	cout << "Configuration saved successfully" << endl;
}

void loadConfigs(vector<configs>& allConfigs) {
	ifstream file("configs.txt");
	if (!file.is_open()) {
		cout << "Could not open file for loading" << endl;
		return;
	}
	int size;
	file >> size;
	allConfigs.clear(); //повертаємо вектор у початок перед завантаженням нових конфігів, щоб повторно не додавати їх до старих
	for (int i = 0; i < size; i++) {
		configs cfg;
		file >> cfg.username;
		file >> cfg.language;
		file >> cfg.volume;
		file >> cfg.fullscreen;
		allConfigs.push_back(cfg); //додаємо новий конфіг до вектора
	}
	file.close();
	cout << "Configuration loaded successfully" << endl;
}

int main()
{
	cout << "\t====Config Manager====" << endl;
	cout << "=================================================" << endl;
	configs cfg = { "User1", "uk", 55, false };
	while (true) {
		cout << "\n\t1. Show Configuration" << endl;
		cout << "\t2. Find Configuration" << endl;
		cout << "\t3. Modify Configuration" << endl;
		cout << "\t4. Add Configuration" << endl;
		cout << "\t5. Delete Configuration" << endl;
		cout << "\t6. Save Configuration" << endl;
		cout << "\t7. Load Configuration" << endl;
		cout << "\t0. Exit" << endl;
		cout << "\nEnter your option: ";
		int option;
		cin >> option;
		switch (option) {
		case 1:
			showConfig(allConfigs);
			break;
		case 2:
			findAndModifyConfig(allConfigs);
			break;
		case 3:
			modifyConfig(allConfigs);
			break;
		case 4:
			addConfig(allConfigs);
			break;
		case 5:
			deleteConfig(allConfigs);
			break;
		case 6:
			saveConfigs(allConfigs);
			break;
		case 7:
			loadConfigs(allConfigs);
			break;
		case 0:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid option. Please try again" << endl;
		}
		if (option == 0) {
			break;
		}
	}
}