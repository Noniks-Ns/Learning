#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <conio.h> // only for Windows

int main() {
    std::string filename = "data.txt";
    std::string dirname = "test_folder";
    std::filesystem::path dir{dirname};
    std::filesystem::path file = dir / filename;

    clrscr();

    if (std::filesystem::exists(dir)) {
        std::cout << "Directory '" << dirname << "' already exists.\n";
    } else {
        std::filesystem::create_directory(dir);
        std::cout << "Directory '" << dirname << "' created.\n";
    }

    std::ofstream fout(file);
    if (fout.is_open()) {
        fout << std::setw(10) << std::left << "obj1" << "Age\n";
        fout << std::setw(10) << std::left << "obj2" << "7\n";
        fout << std::setw(10) << std::left << "obj3" << "25\n";
        fout.close();
        std::cout << "Data written to " << file << "\n";
    }

    if (std::filesystem::exists(file)) {
        std::cout << "\nFile size: " << std::filesystem::file_size(file) << " bytes\n";
        std::cout << "Contents:\n\n";

        std::ifstream fin(file);
        std::string line;

        while (std::getline(fin, line)) {
            std::cout << "  " << line << '\n';
        }
        fin.close();
    }

    std::cout << "\nPress any key to exit...";
    _getch();

    return 0;
}
