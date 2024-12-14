#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

struct Page {
    std::string description;
    std::map<std::string, std::string> files; // Filename -> File Content
};

std::map<std::string, Page> pages; // Page name -> Page data
const std::string pagesFolder = "pages";

// Create a new page
void createPage(const std::string& pageName, const std::string& description) {
    if (pages.find(pageName) != pages.end()) {
        std::cout << "Error: Page '" << pageName << "' already exists.\n";
        return;
    }
    pages[pageName] = {description, {}};
    std::cout << "Page '" << pageName << "' created successfully with description: " << description << "\n";
}

// Push code to a page
void pushCode(const std::string& pageName, const std::string& fileName, const std::string& fileContent) {
    auto it = pages.find(pageName);
    if (it == pages.end()) {
        std::cout << "Error: Page '" << pageName << "' does not exist. Create it first.\n";
        return;
    }

    // Ensure the pages folder exists
    if (!fs::exists(pagesFolder)) {
        fs::create_directory(pagesFolder);
    }

    std::string filePath = pagesFolder + "/" + fileName;
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << fileContent;
        outFile.close();
        it->second.files[fileName] = filePath;
        std::cout << "File '" << fileName << "' pushed to page '" << pageName << "' successfully.\n";
    } else {
        std::cout << "Error: Failed to create the file.\n";
    }
}

// List all pages
void listPages() {
    if (pages.empty()) {
        std::cout << "No pages available.\n";
        return;
    }

    std::cout << "Available Pages:\n";
    for (const auto& [pageName, pageData] : pages) {
        std::cout << "- " << pageName << " (Description: " << pageData.description << ")\n";
    }
}

// Visit a page
void visitPage(const std::string& pageName) {
    auto it = pages.find(pageName);
    if (it == pages.end()) {
        std::cout << "Error: Page '" << pageName << "' does not exist.\n";
        return;
    }

    const Page& page = it->second;
    std::cout << "**Files**:\n";
    for (const auto& [fileName, filePath] : page.files) {
        std::cout << "- " << fileName << ": type /" << pageName << " visit " << fileName << "\n";
    }

    std::cout << "\n**Description**:\n" << page.description << "\n";
}

// Access a file in a page
void visitFile(const std::string& pageName, const std::string& fileName) {
    auto it = pages.find(pageName);
    if (it == pages.end()) {
        std::cout << "Error: Page '" << pageName << "' does not exist.\n";
        return;
    }

    const auto& files = it->second.files;
    auto fileIt = files.find(fileName);
    if (fileIt == files.end()) {
        std::cout << "Error: File '" << fileName << "' does not exist in page '" << pageName << "'.\n";
        return;
    }

    std::cout << "Content of '" << fileName << "':\n";
    std::ifstream inFile(fileIt->second);
    if (inFile) {
        std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        std::cout << content << "\n";
    } else {
        std::cout << "Error: Unable to open the file.\n";
    }
}

// Delete a page
void deletePage(const std::string& pageName) {
    auto it = pages.find(pageName);
    if (it == pages.end()) {
        std::cout << "Error: Page '" << pageName << "' does not exist.\n";
        return;
    }

    for (const auto& [fileName, filePath] : it->second.files) {
        if (fs::exists(filePath)) {
            fs::remove(filePath);
        }
    }

    pages.erase(it);
    std::cout << "Page '" << pageName << "' and its files deleted successfully.\n";
}

// Parse and execute user commands
void executeCommand(const std::string& command) {
    if (command.rfind("/page name:", 0) == 0) {
        size_t descPos = command.find(" description:");
        if (descPos == std::string::npos) {
            std::cout << "Error: Missing description.\n";
            return;
        }

        std::string pageName = command.substr(12, descPos - 12);
        std::string description = command.substr(descPos + 13);
        createPage(pageName, description);
    } else if (command.rfind("/push page:", 0) == 0 && command.find(" code:") != std::string::npos) {
        size_t codePos = command.find(" code:");
        size_t contentPos = command.find(": ", codePos);
        if (contentPos == std::string::npos) {
            std::cout << "Error: Invalid push command format.\n";
            return;
        }

        std::string pageName = command.substr(11, codePos - 11);
        std::string fileName = command.substr(codePos + 6, contentPos - codePos - 6);
        std::string fileContent = command.substr(contentPos + 2);
        pushCode(pageName, fileName, fileContent);
    } else if (command == "/pages") {
        listPages();
    } else if (command.rfind("/", 0) == 0 && command.find(" visit ") == std::string::npos) {
        std::string pageName = command.substr(1);
        visitPage(pageName);
    } else if (command.rfind("/", 0) == 0 && command.find(" visit ") != std::string::npos) {
        size_t visitPos = command.find(" visit ");
        std::string pageName = command.substr(1, visitPos - 1);
        std::string fileName = command.substr(visitPos + 7);
        visitFile(pageName, fileName);
    } else if (command.rfind("/delete page:", 0) == 0) {
        std::string pageName = command.substr(14);
        deletePage(pageName);
    } else if (command == "/exit") {
        std::cout << "Exiting the platform. Goodbye!\n";
        exit(0);
    } else {
        std::cout << "Unknown command.\n";
    }
}

int main() {
    std::cout << "Welcome to the Advanced Page Platform! Type your commands below:\n";

    while (true) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        executeCommand(command);
    }

    return 0; // Ensure the main function returns an integer.
  }
