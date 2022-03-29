#include "Direction.hpp"
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;
namespace ariel{
    class Notebook{
        public:
        map<int, map<int, vector<char>>> the_notebook;
        void write(int page, int row, int column, Direction direction, string const& sentence);
        string read(int page, int row, int column, Direction direction, int chars_to_read);
        void erase(int page, int row, int column, Direction direction, int chars_to_erase);
        void show(int page);
        void build_page(int page, int row);
        void build_row(int page, int row);
    };
};