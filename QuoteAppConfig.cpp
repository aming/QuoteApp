#include "QuoteAppConfig.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
namespace po = boost::program_options;

QuoteAppConfig::QuoteAppConfig()
{
  // group of options allowed only on command line
  po::options_description generic;
  generic.add_options()
      ("version,v", "print version string")
      ("help", "produce help message")
      ("quote", po::value< vector<string> >(&m_quoteList), "Quote Symbol")
      ;
  // group of options allowed both on command line and in config file  
  po::options_description config;
  config.add_options()
      ("optimization", po::value<int>()->default_value(10), 
       "optimization level")
      ("quote", 
       po::value< vector<string> >(&m_quoteList)->composing(), 
       "Quote Symbol")
      ;
  // group of options will be allowed both on command line and
  // in config file, but will not be shown to the user.
  po::options_description hidden;
  hidden.add_options()
      ("input-file", po::value< vector<string> >(), "input file")
      ;
  m_posOptDesc.add("quote", -1);

  m_cmdline_options.add(generic).add(config);
  m_config_file_options.add(config).add(hidden);
}

bool QuoteAppConfig::initialize(int argc, char** argv)
{
  po::store(po::command_line_parser(argc, argv).
            options(m_cmdline_options).
            positional(m_posOptDesc)
            .run(),
            m_varMap);
  ifstream in;
  in.open( CONFIG_FILENAME );
  po::store(po::parse_config_file(in, m_config_file_options), m_varMap);
  po::notify(m_varMap);
  if (m_varMap.count("help"))
  {
    if (m_varMap.count("quote"))
    {
      cout << "quote are: " ;
      for (vector<string>::iterator it=m_quoteList.begin(); it != m_quoteList.end(); ++it)
      {
        cout << *it << " ";
      }
      cout << endl;
    }

    cout << m_cmdline_options << endl;
    return false;
  }
  return true;
}

vector<string> QuoteAppConfig::getQuoteList() {
  return m_quoteList;
}

bool QuoteAppConfig::setQuoteList(vector<string> newQuoteList) {
  m_quoteList = newQuoteList;
  ofstream outfile;
  outfile.open( CONFIG_FILENAME );
  for (vector<string>::iterator it = newQuoteList.begin(); it != newQuoteList.end(); ++it) {
    outfile << "quote=" << *it << endl;
  }
  outfile.close();
  return true;
}

