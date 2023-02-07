#include "pch.h"
#include "Log.h"

std::ofstream log_file;

void initFile(CString fileName) {
	log_file.open(fileName);
}

void closeFile() {
	log_file.close();
}

std::ofstream& get_log_file() {
	return log_file;
}