// Copyright 2019 Rica Radu Leonard
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string convert_camel_to_snake(std::string line) {
    for (auto it = line.begin() + 1; it < line.end(); ++it) {
        if (isupper(*it)) {
            *it = tolower(*it);
            if (islower(*(it - 1))) {
                it = line.insert(it, '_');
            }
        } else if (!isalpha(*(it - 1))) {
            if ((*it) == '_') {
                it = line.erase(it);
            }
        }
    }
    return line;
}

void help_message() {
    std::cout << "Usage: camel2snake [options] files..\n";
    std::cout << "General Options:\n";
    std::cout << "\t-o\tOverwrite the file. Default is filename_snaked.\n";
}

std::string get_new_filename(char *name, bool overwrite) {
    if (overwrite) {
        return name;
    }
    std::string new_name = std::string(name);
    new_name.insert(new_name.find_last_of("."), "_snaked");
    return new_name;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        help_message();
        return -1;
    }
    bool overwrite = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0) {
            overwrite = 1;
        } else {
            std::ifstream in_file(argv[i]);
            std::ostringstream output_buffer;
            std::string line;
            while (std::getline(in_file, line)) {
                output_buffer << convert_camel_to_snake(line) << '\n';
            }
            in_file.close();
            std::ofstream out_file(get_new_filename(argv[i], overwrite));
            out_file << output_buffer.str();
        }
    }
}