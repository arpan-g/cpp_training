// Copyright 2006 Rutger E.W. van Beusekom.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __YAFFUT_H__
#define __YAFFUT_H__

#ifdef __GNUC__
#include <cxxabi.h>
#elif _MSC_VER
#pragma warning (disable: 4786)
#define NOMINMAX 
#include <windows.h> 
#endif


#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

namespace yaffut {

std::string const version = "1.0";
#ifdef _MSC_VER
static HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
#endif


void ColorOn()
{
#ifdef _MSC_VER
  SetConsoleTextAttribute(hConsoleOutput, 9 * 16 + 15);
#endif
}

void ColorOff()
{
#ifdef _MSC_VER
  SetConsoleTextAttribute(hConsoleOutput, 7);
#endif	
}

template <typename T>
std::string demangle()
{
#ifdef __GNUC__
  size_t sz;
  int status;
  char* ptr = abi::__cxa_demangle(typeid(T).name(), 0, &sz, &status);
  std::string name(ptr ? ptr : "", ptr ? strlen(ptr) : 0);
  if(ptr){ free(ptr); }
  std::string::size_type pos = name.rfind("::");
  if(pos != std::string::npos)
  {
    name = name.substr(pos + 2);
  }
#elif _MSC_VER
  std::string name(typeid(T).name());
  static const std::string struct_prefix("struct ");
  static const std::string class_prefix("class ");
  static const std::string ptr_postfix(" *");

  std::string::size_type
  at = name.find(struct_prefix);
  if(at != std::string::npos) { name.erase(at, struct_prefix.size()); }
  at = name.find(class_prefix);
  if(at != std::string::npos) { name.erase(at, class_prefix.size()); }
  at = name.find(ptr_postfix);
  if(at != std::string::npos) { name.erase(at, ptr_postfix.size()); }
#else
  std::string name(typeid(T).name());
#endif
  return name;
}

class Factory
{
public:
  typedef void (*Create_t) ();
private:
  typedef std::map<std::string, Create_t> Tests_t;
  Tests_t m_Tests;
  size_t m_fail;
  size_t m_pass;
private:
  Factory(){}
  static bool EqualsSuiteName (std::string const &name, std::string const& s)
  {
    return name.find (':') >= name.length () - 2
      && s.substr (0, name.length ()) == name;
  }
public:
  ~Factory(){}
  static Factory& Instance()
  {
    static Factory instance;
    return instance;
  }
  void Register(const std::string& name, Create_t create)
  {
    m_Tests[name] = create;
  }
  size_t Fail () { return m_fail; }
  void List(const std::string& name)
  {
    ColorOn();
    size_t i = 0;
    for(Tests_t::const_iterator it = m_Tests.begin(); it != m_Tests.end(); ++it)
    {
      if(name.empty () || it->first == name
   || EqualsSuiteName (name, it->first))
  std::cerr << i++ << ")\t";
  std::cout << it->first << std::endl;
    }
    ColorOff();
  }
  void Run(const std::string& name)
  {
    int i = -1;
    for(Tests_t::const_iterator it = m_Tests.begin(); it != m_Tests.end(); ++it)
    {
      ++i;
      if("All" == name || it->first == name
   || EqualsSuiteName (name, it->first))
      {
        try
        {
          ColorOn();
          std::cout << std::endl << i << ") " << it->first << std::flush;
          ColorOff();
          {
            it->second();
          }
          ColorOn();
          std::cout << " [OK]" << std::flush;
          ColorOff();
          ++m_pass;
        }
        catch(const std::exception& e)
        {
          ColorOn();
          std::cout << " [FAIL]\n" << e.what() << std::flush;
          ColorOff();
          ++m_fail;
        }
        catch(...)
        {
          ColorOn();
          std::cout << " [FAIL]\n  unknown exception" << std::flush;
          ColorOff();
          ++m_fail;
        }
      }
    }
  }
  void Report ()
  {
    const size_t size = m_Tests.size();
    ColorOn();
    std::cout << std::endl;
    std::cout << "[TOTAL](" << m_pass + m_fail << '/' << size << ")" << std::endl;
    std::cout << "[OK](" << m_pass << '/' << size << ")" << std::endl;
    if (m_fail)
      std::cout << "[FAIL](" << m_fail << '/' << size << ")" << std::endl;
    ColorOff();
  }
  int Main (int argc, const char* argv[])
  {
    if(argc > 1
       && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
    {
      ColorOn();
      std::cout << "Yaffut - Yet Another Framework For Unit Testing.\n\n"
  "Usage: yaffut [OPTION] [Suite:|Suite::Test]...\n\n"
  "Options:\n"
  "  -h, --help     show this help\n"
  "  -l, --list     list test cases\n"
  "  -v, --version  show version number\n"
    << std::flush;
      ColorOff();
      return 0;
    }
    if(argc > 1
       && (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--list"))
    {
      Factory::Instance().List(argc > 2 ? argv[2] : "");
      return 0;
    }
    if(argc > 1
       && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version"))
    {
      ColorOn();
      std::cout << "Yaffut " << version << std::endl;
      ColorOff();
      return 0;
    }

#ifdef __GNUC__
    std::cout << "pid(" << getpid() << ")" << std::endl;
#endif

    const char* all[] = {"All"};
    const char** test = all;
    int num = 1;
    if(1 < argc)
    {
      test = argv;
      num = argc;
    }

    for(int i = 0; i < num; ++i)
    {
      try
      {
  std::istringstream is(test[i]);
  int num;
  is >> num;
  if(is)
  {
          if(num < int(m_Tests.size()))
    {
      Tests_t::const_iterator it = m_Tests.begin();
            while(0 <= --num){++it;}
      Factory::Instance().Run(it->first);
    }
  }
        else
  {
    Factory::Instance().Run(test[i]);
  }
      }
      catch(const std::exception& e)
      {
        ColorOn();
        std::clog << e.what() << std::endl;
        ColorOff();
      }
    }

    Factory::Instance().Report ();
    return Factory::Instance().Fail ();
  }
};

class failure: public std::exception
{
  std::string failure_;
public:
  template <typename Expected, typename Actual>
  failure(const Expected& e, Actual& a, const char* at = "", const char* expr = "")
  {
    ColorOn();
    std::ostringstream os;
    os << at << expr << "\nexpected: "
       << "(" << demangle<Expected>() << ") " << e
       << " != actual: " << "(" << demangle<Actual>() << ") " << a;
    failure_ = os.str();
    ColorOff();
  }
  failure(const char* at = "", const char* expr = "")
  {
    std::ostringstream os;
    ColorOn();
    os << at << expr;
    ColorOff();
    failure_ = os.str();
  }
  virtual ~failure() throw() {}
  virtual const char* what() const throw() { return failure_.c_str(); }
};

template <typename Suite, typename Case>
struct Registrator
{
  Registrator()
  {
    Factory::Instance().Register(TestName(), Create);
  }
  const std::string& TestName()
  {
    static const std::string name(demangle<Suite>() + "::" + demangle<Case>());
    return name;
  }
  static void Create()
  {
    Case();
  }
};

template <typename Case>
struct Registrator<Case, void>
{
  Registrator()
  {
    Factory::Instance().Register(TestName(), Create);
  }
  const std::string& TestName()
  {
    static const std::string name ("::" + demangle<Case>());
    return name;
  }
  static void Create()
  {
    Case();
  }
};

template <typename Suite, typename Case = void>
struct Test: public virtual Suite
{
  static Registrator<Suite, Case> s_Registrator;
  Test(): Suite()
  {
    Registrator<Suite, Case>* forceInstance = &s_Registrator;
    forceInstance = 0;
  }
};
template <typename Suite, typename Case>
Registrator<Suite, Case> Test<Suite, Case>::s_Registrator;


template <typename Case>
struct Test<Case, void>
{
  static Registrator<Case, void> s_Registrator;
  Test()
  {
    Registrator<Case, void>* forceInstance = &s_Registrator;
    forceInstance = 0;
  }
};
template <typename Case>
Registrator<Case, void> Test<Case, void>::s_Registrator;

template <typename Expected, typename Actual>
inline void equal(const Expected& e, const Actual& a, const char* at = "", const char* expr = "")
{
  if(e != a)
  {
    throw failure(e, a, at, expr);
  }
}
inline void equal(const char* e, const char* a, const char* at = "", const char* expr = "")
{
  if(std::string(e) != std::string(a))
  {
    throw failure(e, a, at, expr);
  }
}
inline void equal(double e, double a, const char* at = "", const char* expr = "")
{
  double max = std::abs(std::max(e, a));
  max = max < 1.0 ? 1.0 : max;
  if(std::abs(e - a) > std::numeric_limits<double>::epsilon() * max)
  {
    throw failure(e, a, at, expr);
  }
}
inline void check(bool b, const char* at = "", const char* expr = "")
{
  if(!b)
  {
    throw failure(at, expr);
  }
}

template <typename Expected, typename Actual>
inline void unequal(const Expected& e, const Actual& a, const char* at = "", const char* expr = "")
{
  if(e == a)
  {
    throw failure(e, a, at, expr);
  }
}
inline void unequal(const char* e, const char* a, const char* at = "", const char* expr = "")
{
  if(std::string(e) == std::string(a))
  {
    throw failure(e, a, at, expr);
  }
}
inline void unequal(double e, double a, const char* at = "", const char* expr = "")
{
  double max = std::abs(std::max(e, a));
  max = max < 1.0 ? 1.0 : max;
  if(std::abs(e - a) <= std::numeric_limits<double>::epsilon() * max)
  {
    throw failure(e, a, at, expr);
  }
}
template <typename Actual>
inline void not_null(const Actual& a, const char* at = "", const char* expr = "")
{
  if (nullptr == a)
  {
    throw failure(at, expr);
  }
}
template <typename Actual>
inline void is_null(const Actual& a, const char* at = "", const char* expr = "")
{
  if (nullptr != a)
  {
    throw failure(at, expr);
  }
}
template <typename T>
void fail(const T& expr, const char* at = "")
{
  ColorOn();
  std::ostringstream os;
  os << expr;
  ColorOff();
  throw failure(at, os.str().c_str());
}

template <typename E, typename T>
void assert_throw(const T& functor, const char* at = "")
{
  try
  {
    functor();
    throw failure (at, " statement failed to throw");
  }
  catch(const E&){}
}

template <typename E>
void assert_throw(void(*pf)(), const char* at = "")
{
  try
  {
    (*pf)();
    throw failure (at, " statement failed to throw");
  }
  catch(const E&){}
}

template <typename E, typename T>
void assert_throw(T* pt, void(T::*mf)(), const char* at = "")
{
  try
  {
    (pt->*mf)();
    throw yaffut::failure (at, "statement failed to throw");
  }
  catch(const E&){}
}

inline int
main (int argc, const char* argv[])
{
  return Factory::Instance ().Main (argc, argv);
};

}

//and for those who prefer macro obscurity over typing
#define TEST(Suite, Case)\
  struct Case: public yaffut::Test<Suite, Case>{ Case(); }; \
  Case::Case()

#define FUNC(Case)\
  struct Case: public yaffut::Test<Case>{ Case(); }; \
  Case::Case()

#define YAFFUT_STRINGIZE(x) YAFFUT_STRINGIZE_(x)
#define YAFFUT_STRINGIZE_(x) #x

#ifdef __GNUC__
#define __YAFFUT_AT__ __FILE__ ":" YAFFUT_STRINGIZE(__LINE__)": \n"
#elif _MSC_VER
#define __YAFFUT_AT__ __FILE__ "(" YAFFUT_STRINGIZE(__LINE__)") : \n"
#endif
#ifndef __AT__
#define __AT__ __YAFFUT_AT__
#endif

#define YAFFUT_EQUAL(e,a) \
  yaffut::equal (e ,a , __YAFFUT_AT__, "EQUAL(" #e " == " #a ") failed ")
#ifndef EQUAL
#define EQUAL YAFFUT_EQUAL
#endif

#define YAFFUT_UNEQUAL(e,a) \
  yaffut::unequal (e, a, __YAFFUT_AT__, "UNEQUAL(" #e " != " #a ") failed ")
#ifndef UNEQUAL
#define UNEQUAL YAFFUT_UNEQUAL
#endif

#define YAFFUT_CHECK(e) \
  yaffut::check (e, __YAFFUT_AT__, "CHECK(" #e ") failed ")
#ifndef CHECK
#define CHECK YAFFUT_CHECK
#endif

#define YAFFUT_FAIL(s) yaffut::fail (s, __YAFFUT_AT__);
#ifndef FAIL
#define FAIL YAFFUT_FAIL
#endif

#define YAFFUT_NOT_NULL(e) \
  yaffut::not_null(e, __YAFFUT_AT__, "NOT_NULL(" #e ") failed ")
#ifndef NOT_NULL
#define NOT_NULL YAFFUT_NOT_NULL
#endif

#define YAFFUT_IS_NULL(e) \
  yaffut::is_null(e, __YAFFUT_AT__, "IS_NULL(" #e ") failed ")
#ifndef IS_NULL
#define IS_NULL YAFFUT_IS_NULL
#endif

#define YAFFUT_ASSERT_THROW(s, e) \
  try \
  { \
    s; \
    throw yaffut::failure (__YAFFUT_AT__,  #s " failed to throw"); \
  } \
  catch(const e&){}
#ifndef ASSERT_THROW
#define ASSERT_THROW YAFFUT_ASSERT_THROW
#endif

#ifdef YAFFUT_MAIN
#include <iostream>
int main(int argc, const char* argv[])
{
  int retval = yaffut::main(argc, argv);
  int tmp;
  std::cin >> tmp;
  return retval;
};
#endif /* YAFFUT_MAIN */

#endif
