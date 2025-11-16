#include <iostream>
#include <sstream>
#include "IniDocument.h"
#include "DogArrays.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "debug.h"
#include "getdelim.h"

// character classes
bool IniDocument::is_paren_character(char c)
{
  switch(c)
    {
      case '(':
      case ')':
      case '<':
      case '>':
      case '[':
      case ']':
      case '{':
      case '}':
        return true;
    }
  return false;
}

bool IniDocument::is_punctuation_character(char c)
{
  switch(c)
    {
      case ',':
      case '.':
      case ':':
      case ';':
      case '-':
      case '_':
        return true;
    }
  return false;
}

bool IniDocument::is_whitespace_character(char c)
{
  switch(c)
    {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        return true;
    }
  return false;
}

bool IniDocument::is_comment_character(const char c)
{
  switch(c)
    {
      case ';':
      case '#':
      case '%':
        return true;
    }
  return false;
}

bool IniDocument::is_quote_character(char c)
{
  switch(c)
    {
      case '"':
      case '\'':
      case '`':
        return true;
    }
  return false;
}

bool IniDocument::is_alphabetic_character(char c)
{
  if(('A' <= c && c <= 'Z') ||
     ('a' <= c && c <= 'z') ||
     (c == '_'))
    {
      return true;
    }
  return false;
}

bool IniDocument::is_numeric_character(char c)
{
  if('0' <= c && c <= '9') return true;
    return false;
}

bool IniDocument::is_alphanumeric_character(char c)
{
  if(is_alphabetic_character(c)) return true;
  if(is_numeric_character(c)) return true;
  return false;
}

bool IniDocument::is_valid_name_character(char c)
{
  if(is_whitespace_character(c)) return false;
  if(is_quote_character(c)) return false;
  switch(c)
    {
      case '=':
      case '[':
      case ']':
         return false;
    }
  return true;
  // we could shrink this to the following
  if(is_alphanumeric_character(c)) return true;
  if(is_paren_character(c)) return true;
  if(is_punctuation_character(c)) return true;
  return false;
}

bool IniDocument::is_valid_section_name_character(char c)
{
  return is_valid_name_character(c);
}

bool IniDocument::is_valid_option_name_character(char c)
{
  return is_valid_name_character(c);
}

void IniDocument::step_over_whitespace(const char*& ptr)
{
  while(*ptr && is_whitespace_character(*ptr)) ptr++;
}

LineType IniDocument::get_lineType(const char* ptr)
{
  step_over_whitespace(ptr);
  if(!*ptr || is_comment_character(*ptr))
    return LineType::EMPTY;
  if(*ptr == '[')
    return LineType::SECTION_LABEL;
  if(is_alphabetic_character(*ptr))
    return LineType::OPTION;
  Wprintf("Could not evaluate line type: ptr=%s\n",ptr);
  return LineType::ERROR;
}

bool IniDocument::get_section_name(const char* ptr, std::string& section_name)
{
  assert(*ptr=='[');
  ptr++;
  // ptr should now point to the beginning of the string.
  if(!is_alphabetic_character(*ptr))
    {
      Wprintf("first character is not alphabetic\n")
      return false;
    }
  size_t i=0;
  while(ptr[i] && is_valid_section_name_character(ptr[i])) i++;
  if(ptr[i]!=']')
    {
      Wprintf("first nonalphanumeric character must be ']'\n");
      return false;
    }
  section_name = std::string(ptr, i);
  dprintf3("section_name=%s\n",section_name.c_str());
  return true;
}

void IniDocument::get_option_name(const char*& ptr, std::string& var_name)
{
  size_t i=0;
  while(ptr[i] && is_valid_option_name_character(ptr[i])) i++;
  var_name = std::string(ptr, i);
  ptr+=i;
}

// copy characters from ptr to values skipping escaping backslashes
// until we encounter closing double quote.
// we expect the first character to be a double quote
bool IniDocument::get_value_from_quoted_string(const char* ptr, std::string& value)
{
  value = ptr;
  assert(*ptr=='"');
  (void)*(ptr++);
  int i=0;
  int j=0;
  for(;ptr[i] && ptr[i] != '"';i++)
    {
      // can escape any character
      if(ptr[i]=='\\')
        { i++; }
      value[j++] = ptr[i];
    }
  if(!ptr[i])
    {
      Wprintf("missing closing quote\n");
      return false;
    }
  value.resize(j);
  // confirm that any trailing non-whitespace begins
  // with a comment character.
  ++ptr+=i;
  step_over_whitespace(ptr);
  if(*ptr && !is_comment_character(*ptr))
    {
      dprintf3("ptr=%s\n", ptr);
      Wprintf("invalid comment character: %c\n", *ptr);
      return false;
    }
  return true;
}

bool IniDocument::is_valid_unquoted_character(char c)
{
  // // expansive list: any
  // // nonspace noncomment character;
  // if(is_whitespace_character(c)) return false;
  // if(is_comment_character(c)) return false;
  // if(is_quote_character(c)) return false;
  // return true;
  if(is_alphanumeric_character(c)) return true;
  switch(c)
    {
      // at least should support numbers and lists thereof.
      case '.':
      case ',':
      case '-':
      case '+':
        return true;
    }
  return false;
}

bool IniDocument::get_value_from_unquoted_string(const char* ptr, std::string& value)
{
  value = ptr;
  if(!*ptr)
    {
      Wprintf("option is missing value.\n");
      return false;
    }
  int i=0;
  for(;ptr[i] && is_valid_unquoted_character(ptr[i]);i++)
    {
      value[i] = ptr[i];
    }
  value.resize(i);
  ptr+=i;
  step_over_whitespace(ptr);
  if(*ptr && !is_comment_character(*ptr))
    {
      Wprintf("invalid comment character: %c\n", *ptr);
      return false;
    }
  return true;
}

bool IniDocument::get_option_name_and_value(const char* ptr,
                                            std::string& option_name,
                                            std::string& value)
{
  get_option_name(ptr, option_name);
  dprintf3("%s\n",ptr);
  // skip over whitespace preceeding equals sign
  step_over_whitespace(ptr);
  if(*ptr++!='=')
    {
      Wprintf("missing equals sign.\n");
      return false;
    }
  // skip over whitespace trailing equals sign
  step_over_whitespace(ptr);
  if(!*ptr)
    {
      Wprintf("no value given for option.\n");
      return false;
    }
  if(*ptr=='"')
    {
      return get_value_from_quoted_string(ptr, value);
    }
  else
    {
      return get_value_from_unquoted_string(ptr, value);
    }
  return false;
}

size_t IniDocument::my_getline(char** lineptr,
                               size_t* n,
                               FILE* stream)
{
  size_t ret = getdelim (lineptr, n, '\n', stream);
  dprintf3("my_getline ret=%d\n",ret);
  return ret;
}

bool IniDocument::parse_line(const char* line)
{
  const char* ptr=line;
  step_over_whitespace(ptr);
  LineType lineType = get_lineType(ptr);
  switch(lineType)
    {
      case LineType::SECTION_LABEL:
        {
          std::string section_name;
          bool success = get_section_name(ptr, section_name);
          if(!success)
            {
              Wprintf("Could not parse section name.\n");
              return false;
            }
          // create new section
          currentSection = IniDocument::createSection(section_name, line);
          dprintf3("new section name is [%s]\n",section_name.c_str());
        }
        break;
      case LineType::OPTION:
        {
          std::string option_name;
          std::string value;
          bool success = get_option_name_and_value(ptr, option_name, value);
          dprintf3("option '%s' has value '%s'\n",
                   option_name.c_str(),value.c_str());
          if(!success) return false;
          currentSection->pushOption(option_name, value, line);
        }
        break;
      case LineType::EMPTY:
        break;
      case LineType::ERROR:
        return false;
        break;
      default:
        eprintf("Invalid line type: %d\n", lineType);
    }
  return true;
}

void IniDocument::initFromFile(const std::string& ini_filename)
{
  long long int bytes_read;
  size_t nbytes = 100;
  char *line;

  FILE *fp;
  fp=fopen(ini_filename.c_str(),"rb");
  if(!fp)
    { eprintf("Could not open file %s\n",ini_filename.c_str()); }

  line = (char *) malloc (nbytes + 1);
  // parse lines into ini document
  //
  // create default introductory section
  currentSection = IniDocument::createSection("defaultSection", std::string());
  rewind(fp); //fseek(fp,0,SEEK_SET); // rewind the file.
  while(bytes_read = my_getline (&line, &nbytes, fp), bytes_read!=-1)
    {
      bool success = parse_line(line);
      if(!success) eprintf("could not parse line: %s\n", line);
    }

  is_initialized_=true;
  // clean up
  fclose(fp);
  free(line);
}

// access defaults from a file that other applications
// (e.g. matlab) might also want to read
void IniDocument::get_defaults_helper(IniDocument::Section& params,
                                      const std::vector<std::string>& option_names_list,
                                      const std::string& section_label,
                                      const std::string& defaults_option_label,
                                      const std::string& defaults_file_in)
{
  std::string defaults_file = defaults_file_in;
  // search and replace $DOGPACK with value
  std::string S_DOGPACK("$DOGPACK");
  size_t found = defaults_file.find(S_DOGPACK);
  if(found!=std::string::npos)
    {
      defaults_file = defaults_file.replace(found,
                                            S_DOGPACK.length(),
                                            std::string(getenv("DOGPACK")));
    }
  IniDocument defaults_doc;
  defaults_doc.initFromFile(defaults_file);
  IniDocument::Section& defaults_params = defaults_doc[section_label];

  std::vector<std::string>::iterator io;
  // have to cast option_names_list as non-const to iterate over it
  for(io = ((std::vector<std::string>&)option_names_list).begin();
      io != ((std::vector<std::string>&)option_names_list).end(); io++)
    {
      if(params[(*io)].empty())
        {
          // if the parameter is not set use the default.
          params.set((*io),defaults_params[(*io)]);
        }
    }
  // call self recursively in case the defaults file has defaults
  std::string new_defaults_file = defaults_params[defaults_option_label];
  if(!new_defaults_file.empty())
    {
      if(new_defaults_file == defaults_file_in)
        {
          eprintf("defaults file [%s] references itself\n", defaults_file_in.c_str());
        }
      get_defaults_helper(params,
                          option_names_list,
                          section_label,
                          defaults_option_label,
                          new_defaults_file);
    }
  return;
}

void IniDocument::get_defaults(IniDocument::Section& params,
                               const std::string& section_label,
                               const std::vector<std::string>& option_names_list)
{
  std::string defaults_option_label = "defaults_file";
  std::string defaults_file = params[defaults_option_label];
  if(defaults_file.empty())
    {
      defaults_file = "$DOGPACK/config/ini_defaults/"+section_label+".ini";
    }

  get_defaults_helper(params,
                      option_names_list,
                      section_label,
                      defaults_option_label,
                      defaults_file);
}

bool IniDocument::verify_options_set(const IniDocument::Section& params,
                                     const std::string& section_name,
                                     const std::vector<std::string>& option_names_list)
{
  std::vector<std::string>::iterator io;
  for(io = ((std::vector<std::string>&)option_names_list).begin();
      io != ((std::vector<std::string>&)option_names_list).end(); io++)
    {
      const std::string& str = ((IniDocument::Section&)params)[(*io)];
      if(str.empty() || str=="must_set")
        {
          eprintf("In parameters.ini, section [%s]"
                  " you must set the parameter %s\n",
                  section_name.c_str(),
                  (*io).c_str());
          return false;
        }
    }
  return true;
}

// -------------------------------------------------------------------------- //
// Scanning function for "int" variables
bool IniDocument::scanner(const std::string varsection,
                          const std::string varname,
                          int& var)
{
  return (sscanf(varname.c_str(),"%d" ,&var) || invalid_value(varsection, varname));
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Scanning function for "int" list variables
// The list must be comma separated with no white spaces
//    e.g.,  varname = 3,8,-1,6
// NOTE: right now we are limited to lists with at most 10 comma-separated integers
void IniDocument::scanner_list(const std::string varname,
                               IntArray* var)
{
  assert_eq(var->get_num_ind(),1);
  const int m = var->get_ind_length(1);
  assert_ge(m,1);
  int* itmp = new int[m];

  std::istringstream iss(varname);
  std::stringstream ss;
  std::string token;

  int iti = -1;
  while(std::getline(iss, token, ','))
    {
      iti = iti + 1;
      ss << token << '\n';
      ss >> itmp[iti];

      if ((iti+1)>m)
        {
          printf(" ERROR in IniDocument.cpp, function IniDocument::scanner_list.\n");
          printf("    max allowed index = %i, index from user = %i\n\n",m,iti+1);
          exit(1);
        }
    }

  for (int i=1; i<=m; i++)
    {
      var->fetch(i) = itmp[i-1];
    }

  delete[] itmp;
}
// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //
// Scanning function for "double" variables
bool IniDocument::scanner(const std::string varsection,
                          const std::string varname,
                          double& var)
{
  return (sscanf(varname.c_str(),"%lf" ,&var) || invalid_value(varsection, varname));
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Scanning function for "double" list variables
// The list must be comma separated with no white spaces
//    e.g.,  varname = 3.09,8,-1.11,0.6
// NOTE: right now we are limited to lists with at most 10 comma-separated doubles
void IniDocument::scanner_list(const std::string varname,
                               DblArray* var)
{
  assert_eq(var->get_num_ind(),1);
  const int m = var->get_ind_length(1);
  assert_ge(m,1);
  double* dtmp = new double[m];

  std::istringstream iss(varname);
  std::stringstream ss;
  std::string token;

  int dti = -1;
  while(std::getline(iss, token, ','))
    {
      dti = dti + 1;
      ss << token << '\n';
      ss >> dtmp[dti];

      if ((dti+1)>m)
        {
          printf(" ERROR in IniDocument.cpp, function IniDocument::scanner_list.\n");
          printf("    max allowed index = %i, index from user = %i\n\n",m,dti+1);
          exit(1);
        }
    }

  for (int i=1; i<=m; i++)
    {
      var->fetch(i) = dtmp[i-1];
    }

  delete[] dtmp;
}
// -------------------------------------------------------------------------- /

// -------------------------------------------------------------------------- //
// Error message to give the user feedback about what the offending parameters
// did wrong.
bool IniDocument::invalid_value(const std::string varname,
                                const std::string val)
{
  eprintf("invalid value: %s = [%s]", varname.c_str(), val.c_str());
  return false;
}
// -------------------------------------------------------------------------- //

void IniDocument::Section::pushOption(std::string label,
                                      std::string value,
                                      std::string line)
{
  this->option_list.push_back(Option(label, value, line));
}

void IniDocument::Section::set(const std::string &label, const std::string &value)
{
  std::vector<class IniDocument::Option>::iterator i;
  for(i = this->option_list.begin(); i != this->option_list.end(); i++)
    {
      if( (*i).label == label)
        {
          (*i).value = value;
          return;
        }
    }
  /* the label does not exist, so add it */
  pushOption(label, value, std::string());
  return;
}

IniDocument::Section & IniDocument::Section::operator=(const IniDocument::Section &rhs)
{
  this->name = rhs.name;
  this->line = rhs.line;
  this->option_list = rhs.option_list;
  return *this;
}

std::string IniDocument::Section::operator[](const std::string& str)
{
  std::vector<class IniDocument::Option>::iterator i;
  for(i = this->option_list.begin(); i != this->option_list.end(); i++)
    {
      if( (*i).label == str)
        {
          return (*i).value;
        }
    }
  // if it doesn't exist then return an empty string
  return std::string();
}

// return the section with a given name
class IniDocument::Section & IniDocument::operator[] (const std::string& name_in)
{
  std::vector<IniDocument::Section>::iterator i;
  for(i = this->section_list.begin(); i != this->section_list.end(); i++)
    {
      if( (*i).name == name_in)
        {
          return *i;
        }
    }
  // if it doesn't exist then return the first (the default)
  i = this->section_list.begin();
  return *i;
}

IniDocument::Section* IniDocument::createSection(std::string name, std::string line)
{
  this->section_list.push_back(Section(name, line));
  return &(this->section_list.back());
}
