#include <string>
#include <glibmm.h>
#include <giomm.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <regex>
#include <locale>
#include <codecvt>

// erase the last N characthers of string
std::string eraseLastN(std::string str, int n) {
    if (str.length() < n) {
        return str;
    }

    return str.erase(str.length() - n);
};


// returns absolute path from relative path
std::string pathRel2Abs(std::string relpath) {
  // improve: add relative path after removing
  Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(relpath);

  return eraseLastN(file->get_path(), 11 + relpath.length()) + relpath;
};

std::string getHostname() {
    std::string result = "";
    FILE* pipe = popen("hostname -I", "r");
    if (!pipe) return result;

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }

    pclose(pipe);
    // Remove trailing newline character if it exists
    if (!result.empty() && result[result.length()-1] == '\n') {
        result.erase(result.length()-2);
    }
    return result;
}

bool isValidIpAddress(const std::string& ipAddress) {
    // Define the regular expression pattern for the IP address
    std::regex pattern("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");

    // Check if the input string matches the pattern
    return std::regex_match(ipAddress, pattern);
}

std::string convert2UTF8(std::string stringASCII)
{
    // Convert ASCII string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide_str = converter.from_bytes(stringASCII);
    
    // Convert wide string to UTF-8 string
    std::string stringUTF8 = converter.to_bytes(wide_str);
    return stringUTF8;
}