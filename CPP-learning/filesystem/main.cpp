#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

#ifdef _WIN32
    #include <conio.h>
    #define CLEAR_SCREEN() clrscr()
    #define WAIT_KEY() _getch()
#else
    #define CLEAR_SCREEN() std::cout << "\033[2J\033[H"
    #define WAIT_KEY() std::cin.get()
#endif

namespace fs = std::filesystem;

void createDirectoryStructure() {
    std::vector<fs::path> dirs = {
        "project",
        "project/src",
        "project/include",
        "project/bin",
        "project/logs"
    };

    for (const auto& dir : dirs) {
        if (!fs::exists(dir)) {
            fs::create_directory(dir);
            std::cout << "Created: " << dir << '\n';
        }
    }
}

void createConfigFile() {
    std::ofstream file{"project/config.txt"};
    file << "APP_NAME=FileSystemDemo\n";
    file << "VERSION=1.0\n";
    file << "LOG_LEVEL=DEBUG\n";
    file.close();
    std::cout << "Config file created.\n";
}

void createDataFileWithPadding() {
    std::ofstream file{"project/data.bin", std::ios::binary};
    int numbers[] = {10, 20, 30, 40, 50};
    file.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    file.close();
    std::cout << "Binary data written.\n";
}

void readFileAsText() {
    std::ifstream file{"project/config.txt"};
    std::string line;
    int lineCount = 0;
    std::cout << "\n--- config.txt ---\n";
    while (std::getline(file, line)) {
        std::cout << std::setw(2) << ++lineCount << ": " << line << '\n';
    }
    file.close();
}

void readBinaryFile() {
    std::ifstream file{"project/data.bin", std::ios::binary};
    int numbers[5];
    file.read(reinterpret_cast<char*>(numbers), sizeof(numbers));
    file.close();

    std::cout << "\n--- Binary Data ---\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "  data[" << i << "] = " << numbers[i] << '\n';
    }
}

void listFilesWithExtension() {
    std::cout << "\n--- .txt files in project/ ---\n";
    for (const auto& entry : fs::directory_iterator("project")) {
        if (entry.path().extension() == ".txt") {
            std::cout << "  " << entry.path().filename() << '\n';
        }
    }
}

void recursiveDirectoryList() {
    std::cout << "\n--- All files (recursive) ---\n";
    for (const auto& entry : fs::recursive_directory_iterator("project")) {
        std::string indent(fs::depth(entry), '  ');
        std::cout << indent << "📄 " << entry.path().filename();
        if (entry.is_directory()) {
            std::cout << " [DIR]";
        }
        std::cout << '\n';
    }
}

void demonstratePathOperations() {
    fs::path p = "project/src/main.cpp";

    std::cout << "\n--- Path Info ---\n";
    std::cout << "Full path: " << p << '\n';
    std::cout << "Root: " << p.root_name() << '\n';
    std::cout << "Parent: " << p.parent_path() << '\n';
    std::cout << "Filename: " << p.filename() << '\n';
    std::cout << "Stem: " << p.stem() << '\n';
    std::cout << "Extension: " << p.extension() << '\n';
}

void copyDirectoryTree() {
    try {
        fs::copy("project", "project_backup", fs::copy_options::recursive);
        std::cout << "\nProject copied to 'project_backup'\n";
    } catch (...) {
        std::cout << "\nCopy failed (already exists or in use)\n";
    }
}

void renameDirectory() {
    if (fs::exists("project_backup") && !fs::exists("archive_project")) {
        fs::rename("project_backup", "archive_project");
        std::cout << "Renamed backup to 'archive_project'\n";
    }
}

void createSymbolicLink() {
#ifdef _WIN32
    try {
        fs::create_symlink("archive_project/logs", "project/logs_link");
        std::cout << "Symbolic link created (Windows)\n";
    } catch (...) {
        std::cout << "Failed to create symlink (need admin rights?)\n";
    }
#else
    try {
        fs::create_symlink("archive_project/logs", "project/logs_link");
        std::cout << "Symbolic link created (Linux/macOS)\n";
    } catch (...) {
        std::cout << "Failed to create symlink\n";
    }
#endif
}

void getFilePermissions() {
#ifdef __unix__
    auto status = fs::status("project/config.txt");
    auto perms = status.permissions();
    std::cout << "\n--- File Permissions (Unix-like) ---\n";
    std::cout << ((perms & fs::perms::owner_read) != fs::perms::none ? "r" : "-");
    std::cout << ((perms & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
    std::cout << ((perms & fs::perms::owner_exec) != fs::perms::none ? "x" : "-");
    std::cout << " " << fs::file_size("project/config.txt") << " bytes\n";
#endif
}

void demonstrateSeekOperations() {
    std::fstream file{"project/data.bin", std::ios::in | std::ios::binary};
    int value;

    file.seekg(2 * sizeof(int), std::ios::beg);
    file.read(reinterpret_cast<char*>(&value), sizeof(int));
    std::cout << "\n--- Seek Demo ---\n";
    std::cout << "Read from position 2: " << value << '\n';
    file.close();
}

void createTemporaryFile() {
    std::string tempName = "temp_XXXXXX.txt";
    std::replace(tempName.begin(), tempName.end(), 'X', 'a');
    std::ofstream temp{"project/" + tempName};
    temp << "This is a temporary file.\n";
    temp.close();
    std::cout << "Created temp file: " << tempName << '\n';
}

void removeBackupTree() {
    if (fs::exists("archive_project")) {
        fs::remove_all("archive_project");
        std::cout << "\nBackup directory removed.\n";
    }
}

void showDiskSpace() {
    if (fs::exists("project")) {
        auto space = fs::space("project");
        std::cout << "\n--- Disk Space (project) ---\n";
        std::cout << "Capacity: " << space.capacity / 1024 << " KB\n";
        std::cout << "Free:     " << space.free / 1024 << " KB\n";
        std::cout << "Available:" << space.available / 1024 << " KB\n";
    }
}

void demonstrateStringStreamForFiles() {
    std::stringstream buffer;
    buffer << "Cached output\nLine 2\nLine 3";
    
    std::ofstream file{"project/buffered.txt"};
    file << buffer.str();
    file.close();
    std::cout << "Data from stringstream saved.\n";
}

int main() {
    CLEAR_SCREEN();

    createDirectoryStructure();
    createConfigFile();
    createDataFileWithPadding();
    demonstratePathOperations();
    readFileAsText();
    readBinaryFile();
    demonstrateSeekOperations();
    listFilesWithExtension();
    recursiveDirectoryList();
    showDiskSpace();
    demonstrateStringStreamForFiles();
    copyDirectoryTree();
    renameDirectory();
    createSymbolicLink();
    getFilePermissions();
    createTemporaryFile();
    removeBackupTree();

    std::cout << "\n✅ All operations completed.\n";
    std::cout << "Press any key to exit...";
    WAIT_KEY();

    return 0;
}
