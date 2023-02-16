#include <string>
#include <glibmm.h>
#include <giomm.h>


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