#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct dfa; //forward declaration

//shorten these names and make life a little easier

using up_str = unique_ptr <string>;

using un_map_str = unordered_map <string, string>;
using trans_map = unordered_map <string, un_map_str>;
using up_trans_map = unique_ptr <trans_map>;

using un_set_str = unordered_set <string>;
using up_un_set_str = unique_ptr <un_set_str>;

using up_dfa = unique_ptr <dfa>;

struct dfa {
   up_trans_map transitions; 
   up_un_set_str states;
   up_un_set_str accepting_states;

   dfa () {
      transitions = up_trans_map (new trans_map);
      states = up_un_set_str (new un_set_str);
      accepting_states = up_un_set_str (new un_set_str);
   }

   ~dfa () {}
};

static void usage () {
   cerr << "Usage: dfa [define_file] (string_file)" << endl;
   exit (EXIT_FAILURE);
}

static void file_format () {
   cerr << "Bad file format: please refer to the README" << endl;
   exit (EXIT_FAILURE);
}

static void encode_transition (up_dfa& the_dfa, const string& line) {
   int space = 0; //index of the space in the line
   for (size_t i = 0; i < line.size (); ++i) {
      if (line.at (i) == ' ')
         space = i;
   }
   if (space == 0)
      file_format ();

   string sigma; //input to dfa
   string dest_state; //where it goes on this sigma
}

static void build_dfa (up_dfa& the_dfa,
                       const up_str& define_file_name) {
   ifstream define_file (*define_file_name);
   string line;

   if (define_file.is_open ()) {
      string current_state = "";
      while (getline (define_file, line)) {
         if (line.at (0) == '*') {
            current_state = line;
            the_dfa->states->emplace (line);
         }
         else if (line.at (0) == '_') {
            current_state = line;
            the_dfa->states->emplace (line);
            the_dfa->accepting_states->emplace (line);
         }
         else {
            if (current_state == "")
               file_format ();
            encode_transition (the_dfa, line);
         }
      }
   }
   define_file.close ();
}

int main (const int argc, const char* const* argv) {
   if (argc < 2 or argc > 3) 
      usage ();

   up_str define_file_name = up_str (new string (argv[1]));
   up_dfa the_dfa = up_dfa (new dfa);    

   build_dfa (the_dfa, define_file_name);

   return EXIT_SUCCESS;
}
