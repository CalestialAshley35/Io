# Io: Advanced Page Management Platform

Io is an advanced page management platform built in C++ that allows users to create, manage, and interact with virtual pages and their associated files. It supports page creation, code pushing, file viewing, and page deletion through a command-based interface.

## Features

- **Create Pages**: Add new pages with descriptions.
- **Push Code**: Attach files with content to specific pages.
- **List Pages**: View all available pages along with their descriptions.
- **Visit Pages**: Inspect the files and descriptions of a page.
- **Access Files**: View the content of individual files within a page.
- **Delete Pages**: Remove a page and its associated files.
- **Command-Based Interface**: Interact with the platform using commands.

## How to Use

Start the program, and you'll be greeted with a command prompt. Use the commands below to interact with Io.

### Commands

1. **Create a Page**

/page name:<page_name> description:<description>

Example:

/page name:MyPage description:This is my first page.

2. **Push Code to a Page**

/push page:<page_name> code:<file_name>: <file_content>

Example:

/push page:MyPage code:index.html: <html><body>Hello, World!</body></html>

3. **List All Pages**

/pages

4. **Visit a Page**

/<page_name>

Example:

/MyPage

5. **Access a File in a Page**

/<page_name> visit <file_name>

Example:

/MyPage visit index.html

6. **Delete a Page**

/delete page:<page_name>

Example:

/delete page:MyPage

7. **Exit the Platform**

/exit

## Directory Structure

- All files pushed to pages are stored in the `pages` directory.
- Each file is created and saved dynamically when you push code.

## Example Usage

1. Create a new page:

/page name:HomePage description:Welcome to the homepage.

2. Push a file to the page:

/push page:HomePage code:index.html: <html><h1>Welcome!</h1></html>

3. List available pages:

/pages

4. Visit the page:

/HomePage

5. Access a specific file in the page:

/HomePage visit index.html

6. Delete the page:

/delete page:HomePage

## Dependencies

- **C++17 or higher** for `std::filesystem` support.
- A compiler supporting C++17 features (e.g., GCC, Clang, or MSVC).

## How to Compile

Copy Io code from: https://github.com/CalestialAshley35/Io/blob/d4f112e4cc12f06ab23fe00d3166c861c8c461d9/Io/iopages.cpp
And paste it to IDE or Code Editor and run it.

## Notes

- Ensure the program has permission to create and modify files in the `pages` directory.
- If the `pages` directory doesn't exist, it will be created automatically.

## License

Io is open-source software licensed under the MIT License.
