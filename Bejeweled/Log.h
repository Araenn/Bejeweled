#ifndef LOG_H
#define LOG_H

#pragma once
#include <iostream>
#include <fstream>

void initFile(CString fileName);
void closeFile();
std::ofstream& get_log_file();


#endif