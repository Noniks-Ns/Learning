#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <string>
#include <vector>

#ifdef _WIN32
    #include <conio.h>
    #define CLEAR_SCREEN() clrscr()
    #define WAIT_KEY() _getch()
#else
    #define CLEAR_SCREEN() std::cout << "\033[2J\033[H"
    #define WAIT_KEY() std::cin.get()
#endif

namespace fs = std::filesystem;

void createDirectory() {
    fs::path dir{"my_files"};
    if (!fs::exists(dir)) {
        fs::create_directory(dir);
        std::cout << "Directory 'my_files' created.\n";
    } else {
        std::cout << "Directory 'my_files' already exists.\n";
    }
}

void createFileWithFormattedData() {
    std::ofstream file{"my_files/report.txt"};
    file << std::setw(15) << std::left << "Product" 
         << std::setw(10) << std::right << "Price" << '\n';
    file << std::setfill('-') << std::setw(25) << "" << std::setfill(' ') << '\n';
    file << std::setw(15) << std::left << "Laptop" 
         << std::setw(10) << std::right << "999" << '\n';
    file << std::setw(15) << std::left << "Mouse" 
         << std::setw(10) << std::right << "25" << '\n';
    file.close();
    std::cout << "Formatted data saved to report.txt\n";
}

void checkFileStatus() {
    fs::path p{"my_files/report.txt"};
    if (fs::exists(p)) {
        std::cout << "File: " << p.filename() << " exists.\n";
        std::cout << "Size: " << fs::file_size(p) << " bytes\n";
        std::cout << "Last write: " << static_cast<uint64_t>(fs::last_write_time(p).time_since_epoch().count()) << " (timestamp)\n";
    }
}

void listDirectoryContents() {
    std::cout << "\nDirectory contents:\n";
    for (const auto& entry : fs::directory_iterator("my_files")) {
        std::cout << "  " << entry.path().filename();
        if (entry.is_directory()) {
            std::cout << " [DIR]";
        } else {
            std::cout << " [FILE]";
        }
        std::cout << '\n';
    }
}

void readFileAndDisplay() {
    std::ifstream file{"my_files/report.txt"};
    std::string line;
    std::cout << "\n--- File Content ---\n";
    while (std::getline(file, line)) {
        std::cout << "  " << line << '\n';
    }
    file.close();
}

void copyFile() {
    fs::path src{"my_files/report.txt"};
    fs::path dst{"my_files/report_backup.txt"};
    try {
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        std::cout << "File copied to report_backup.txt\n";
    } catch (...) {
        std::cout << "Copy failed (possibly already exists or error)\n";
    }
}

void renameFile() {
    fs::path old_name{"my_files/report_backup.txt"};
    fs::path new_name{"my_files/archive_report.txt"};
    if (fs::exists(old_name) && !fs::exists(new_name)) {
        fs::rename(old_name, new_name);
        std::cout << "File renamed to archive_report.txt\n";
    }
}

void removeFiles() {
    fs::remove("my_files/archive_report.txt");
    std::cout << "Temporary backup removed.\n";
}

void demonstrateStreamManipulators() {
    std::cout << "\n--- Formatting Demo ---\n";
    std::cout << std::setw(12) << std::setfill('.') << std::right << "Done" << '\n';
    std::cout << std::setw(12) << std::setfill('0') << 42 << '\n';
    std::cout << std::setfill(' ');
}

int main() {
    CLEAR_SCREEN();

    createDirectory();
    createFileWithFormattedData();
    checkFileStatus();
    demonstrateStreamManipulators();
    listDirectoryContents();
    readFileAndDisplay();
    copyFile();
    renameFile();
    removeFiles();

    std::cout << "\nPress any key to exit...";
    WAIT_KEY();

    return 0;
}

