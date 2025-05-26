#ifndef MJOLNIR_FUNCTIONS_H
#define MJOLNIR_FUNCTIONS_H

#include <string>

void basic_scan(int start, int end, const std::string &ip, bool to_file, const std::string &filename);
void fast_scan(const std::string &ip, bool to_file, const std::string &filename);
#endif
