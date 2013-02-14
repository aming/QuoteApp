#ifndef QUOTEAPPCONFIG_H
#define QUOTEAPPCONFIG_H

#include <boost/program_options.hpp>
#include <vector>
#include <string>

#define CONFIG_FILENAME "quoteapp.cfg"

class QuoteAppConfig {
 public:
  QuoteAppConfig();
  bool initialize(int argc, char** argv);
  std::vector<std::string> getQuoteList();
  bool setQuoteList(std::vector<std::string> newQuoteList);

 protected:
  boost::program_options::options_description m_cmdline_options;
  boost::program_options::options_description m_config_file_options;

  boost::program_options::variables_map m_varMap;
  boost::program_options::positional_options_description m_posOptDesc;
  
  std::vector<std::string> m_quoteList;
};

#endif //QUOTEAPPCONFIG_H

