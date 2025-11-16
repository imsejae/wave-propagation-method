#ifndef _IniDocument_h_
#define _IniDocument_h_

#include <vector>
#include <string>
class IntArray;
class DblArray;

enum class LineType{ERROR,EMPTY,OPTION,SECTION_LABEL};

// The purpose of this class is to define an interface to the parameters.ini
// document which is required for each application in DoGPack.
//
// Inside the IniDocument class, each ini file is described as a list of
// "Section" objects, each of which is a list of options objects.
class IniDocument
{
  public:
    // each line in a section defines an option, e.g.
    // mynumber = 23.4e-6 ;
    // mystring = "string\" with escaped quote and newline\\n" ; this is a comment
    class Option
      {
        public:
          std::string label;
          std::string value;
          std::string line;
        public:
          Option(const std::string& label_in,
                 const std::string& value_in,
                 const std::string& line_in):
                 label(label_in),
                 value(value_in),
                 line(line_in){}
          Option(){}
          ~Option(){}
          std::string getLabel(){return label;}
          std::string getValue(){return value;}
      };

    // a collection of options preceded by a header line such as:
    // [section_name]
    class Section
      {
        public:
          std::string name;
          std::string line;
          std::vector<class Option> option_list;
        public:
          Section(const std::string& name_in,
                  const std::string& line_in):
                  name(name_in),
                  line(line_in){}
          ~Section(){}
          std::string getSectionName(){return name;}
          void pushOption(std::string label,
                          std::string value,
                          std::string line);
          void set(const std::string &label, const std::string &value);
          std::string operator[](const std::string &label);
          Section& operator=(const Section &rhs);
      };

  private:
    Section* currentSection;
    bool is_initialized_;
    std::vector<class Section> section_list;

  private:
    Section* createSection(std::string name, std::string comment);
    bool parse_line(const char* line);

  public:
    bool is_initialized(){return is_initialized_;}

    IniDocument():
                currentSection(0),
                is_initialized_(false){}
    ~IniDocument(){}
    void initFromFile(const std::string& iniFileName);
    Section & operator[](const std::string&);

  public:
    void get_defaults(IniDocument::Section& params,
                      const std::string& section_label,
                      const std::vector<std::string>& option_names_list);

    bool verify_options_set(const IniDocument::Section& params,
                            const std::string& section_name,
                            const std::vector<std::string>& option_names_list);

    void get_defaults_helper(IniDocument::Section& params,
                             const std::vector<std::string>& option_names_list,
                             const std::string& section_label,
                             const std::string& defaults_option_label,
                             const std::string& defaults_file_in);

    bool scanner(const std::string varsection,
                 const std::string varname,
                 int& var);

    bool scanner(const std::string varsection,
                 const std::string varname,
                 double& var);

    void scanner_list(const std::string varname,
                      IntArray* var);

    void scanner_list(const std::string varname,
                      DblArray* var);

    bool invalid_value(const std::string varname,
                       const std::string val);

  private:
    bool is_paren_character(char c);
    bool is_punctuation_character(char c);
    bool is_whitespace_character(char c);
    bool is_comment_character(const char c);
    bool is_quote_character(char c);
    bool is_alphabetic_character(char c);
    bool is_numeric_character(char c);
    bool is_alphanumeric_character(char c);
    bool is_valid_name_character(char c);
    bool is_valid_section_name_character(char c);
    bool is_valid_option_name_character(char c);
    void step_over_whitespace(const char*& ptr);
    LineType get_lineType(const char* ptr);
    bool get_section_name(const char* ptr, std::string& section_name);
    void get_option_name(const char*& ptr, std::string& var_name);
    bool get_value_from_quoted_string(const char* ptr, std::string& value);
    bool is_valid_unquoted_character(char c);
    bool get_value_from_unquoted_string(const char* ptr, std::string& value);
    bool get_option_name_and_value(const char* ptr, std::string& option_name, std::string& value);
    size_t my_getline(char** lineptr, size_t* n, FILE* stream);
};

#endif // _IniDocument_h_
