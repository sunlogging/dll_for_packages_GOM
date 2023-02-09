#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>

std::vector<std::string> split(std::string text, char t) {
	std::vector<char> object;
	std::vector<std::string> result;

	for (int position = 0; position <= text.length(); position++) {
		if (text[position] != t && position != text.length()) {

			object.push_back(text[position]);
		}
		else {
			std::string obj;
			for (int obj_index = 0; obj_index < object.size(); obj_index++) {
				obj += object[obj_index];
			}
			object.clear();
			result.push_back(obj);
		}
	}
	return result;
}

std::string get_type(std::string namefile) {
	return split(namefile, '.')[split(namefile, '.').size() - 1];
}
std::string set_type(std::string namefile) {
	std::string type = get_type(namefile);
	if (type == "py") return "python ";
	else if (type == "js") return "node ";
	else if (type == "exe" || "bat") return "";
}

void run(std::vector<char*> argv) {
	std::string command = set_type(argv[1]);
	for (int index = 1; index < argv.size(); index++) {
		if (index == 1) {
			command += std::string(".\\package\\") + std::string(argv[0]) + "\\" + argv[index] + " ";
			continue;
		}
		command += std::string(argv[index]) + " ";
	}
	system(command.c_str());
}

extern "C" __declspec(dllexport)
void exec(std::vector<char*> argv) {
	run(argv);
}
