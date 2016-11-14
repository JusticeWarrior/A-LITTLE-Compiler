#include "parser.hpp"

extern void yyparser(LittleParser& parser, LittleScanner& scanner);

LittleParser::LittleParser(std::istream* i, std::ostream* o):
  scanner(i,o),
  accept(true),
  error_message(0)
  {}

LittleParser::LittleParser(std::istream* i):
  scanner(i),
  accept(true)
  {}

LittleParser::~LittleParser(){
  // Cleanup str_arr_arr
  std::vector<std::vector<char*>* >::iterator str_arr_it;
  std::vector<char*>::iterator str_it;

  // Clean up sym_arr_arr
  std::vector<std::list<Symbol*>* >::iterator sym_arr_it;
  std::list<Symbol*>::iterator sym_it;

  // Iterate through all of the string vectors
  for (str_arr_it = str_arr_arr.begin(); str_arr_it != str_arr_arr.end(); str_arr_it++){
    // For each string vector, iterate through its strings and free them
    for (str_it = (**str_arr_it).begin(); str_it != (**str_arr_it).end(); str_it++){
      free(*str_it);
    }
    // now delete the array
    delete *str_arr_it;
  }

  // Iterate through all of the symbol vectors
  for (sym_arr_it = sym_arr_arr.begin(); sym_arr_it != sym_arr_arr.end(); sym_arr_it++){
    // For each symbol vector, iterate through its symbols and delete them
    for (sym_it = (**sym_arr_it).begin(); sym_it != (**sym_arr_it).end(); sym_it++){
      delete *sym_it;
    }
    // now delete the array
    delete *sym_arr_it;
  }

// clean up the iri list
  std::list<IRI*>::iterator iri_it;
  for(iri_it = iri_list.begin(); iri_it != iri_list.end(); iri_it++) {
    delete *iri_it;
  }

}

void LittleParser::error(const char* err){
  error_message = err;
  accept = false;
}

const char* LittleParser::get_error_message(){
  return error_message;
}

void LittleParser::register_str_arr(std::vector<char*>* arr){
  str_arr_arr.push_back(arr);
}

void LittleParser::register_sym_arr(std::list<Symbol*>* arr){
  sym_arr_arr.push_back(arr);
}

void LittleParser::parse(){
  yyparse(*this, scanner);
}

bool LittleParser::accepted(){
  return accept;
}

void LittleParser::iri_list_push_back(IRI* iri) {
  //iri_list.push_back(iri);
  function_list.back()->iri_list.push_back(iri);
}

void LittleParser::print_ir(std::stringstream& ss) {
  std::list<IRI*>::iterator it;
  for (it = iri_list.begin(); it != iri_list.end(); it++) {
    (**it).PrintIRI(&ss);
  }
}

void LittleParser::print_assembly(std::stringstream& ss) {
  std::list<IRI*>::iterator it;
  for (it = iri_list.begin(); it != iri_list.end(); it++) {
    (**it).PrintAssembly(&ss);
  }
  ss << "sys halt" << std::endl;
}

void LittleParser::push_label(int label) {
  label_stack.push_back(label);
}

void LittleParser::pop_label() {
  label_stack.pop_back();
}

int LittleParser::peek_label() {
  return *(--label_stack.end());
}

IRI* LittleParser::label_to_iri(int label) {
  return IRI::create(IRI::LABEL, Operand(Operand::LABEL, std::string("L")+std::to_string(static_cast<unsigned long long>(label))));
}

IRI* LittleParser::jump_to_label(int label) {
  return IRI::create(IRI::JUMP, Operand(Operand::LABEL, std::string("L")+std::to_string(static_cast<unsigned long long>(label))));
}

void LittleParser::start_function(std::string name, int argc) {
  function_list.push_back(new Function(name, argc));
}

void LittleParser::finish_function() {
  // Things
}
