#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>


class Lexer {
public:
  void init(std::istream& is) {
    std::cin >> std::noskipws;
    std::istream_iterator<char> it(is);
    std::istream_iterator<char> eos;
    std::string result(it, eos);
    std::swap(buffer, result);
    swflag = false;
    input = buffer.begin();
    match = buffer.begin(); }

  void string() {
    skipws();
    std::string::iterator ip = input;
    swflag = '"' == *ip;
    if (swflag) {
      ++ip;
      while ('"' != *ip) { ++ip; }
      ++ip;
      match = input;
      input = ip; } }

  void identifier() {
    skipws();
    std::string::iterator ip = input;
    swflag = std::isalpha(*ip);
    if (swflag) {
      while (std::isalnum(*ip)) { ++ip; }
      match = input;
      input = ip; } }

  void literal(const std::string& s) {
    skipws();
    std::string::const_iterator sp = s.begin();
    std::string::iterator ip = input;
    std::string::const_iterator spe = s.end();
    std::string::iterator ipe = buffer.end();
    while (sp < spe && ip < ipe && *sp == *ip) { ++sp; ++ip; }
    swflag = sp == spe;
    if (swflag) {
      match = input;
      input = ip; } }

  void copy_match(std::ostream& os) {
    std::copy(match, input, std::ostream_iterator<char>(os)); }

  bool is_match() { return swflag; }
  void clear() { swflag = true; }
private:
  void skipws() { while (std::isspace(*input)) { ++input; } }
  bool swflag;
  std::string buffer;
  std::string::iterator match;
  std::string::iterator input;
} lex;


// Gensym counter.
int gncount = 0;


template <class T>
std::string to_string(T v) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(5) << v;
  return ss.str(); }

// From Schorre's META II paper (I added parenthesis around arguments):
#define bt(label)  if (lex.is_match()) { goto label; }
#define bf(label)  if (!lex.is_match()) { goto label; }
#define set        lex.clear();
#define be         if (!lex.is_match()) { std::exit(1); }
#define out        std::cout << "\n";
#define adr(label) int main() { lex.init(std::cin); label(); return 0; }
#define cll(fun)   fun();
#define cl(lit)    std::cout << lit;
#define tst(lit)   lex.literal(lit);
#define id         lex.identifier();
#define sr         lex.string();
#define gn1        if (sgn1 == "") { sgn1 += "a" + to_string(gncount++); } std::cout << sgn1;
#define ci         lex.copy_match(std::cout);
// Schorre called the following, "r".
#define ret        return; }
// I added these so I could use C++'s function calls.
#define lgn        std::string sgn1;
#define sub(lit)   void lit() {
#define def(lit)   void lit();

