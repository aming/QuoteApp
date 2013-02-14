#include "CliDisplay.h"
#include "QuoteAppConfig.h"
#include <string.h>
#include <list>
#include <vector>

int main(int argc, char** argv)
{ 
  QuoteAppConfig config;
  Quoter quoter;

  if (!config.initialize(argc, argv)) exit(1);
  std::vector<std::string> quoteList = config.getQuoteList();
  quoter.Start();
  std::list<Quoter*> quoterList(1, &quoter);
  CliDisplay display(quoterList);
  display.Start();

  for (std::vector<std::string>::iterator it = quoteList.begin(); it != quoteList.end(); ++it) {
    quoter.AddQuote(*it);
  }

  while (true) {
    char* inputLine = new char[256];
    char* inputCmd;
    char* inputPara;
    inputLine[0] = 0;
    printf("Input>");
    fflush(stdout);
    if (fgets(inputLine, sizeof(char)*256, stdin) == NULL)
    //if (gets(inputLine) == NULL)
      break;
    printf("inputLine: %s\n", inputLine);
    inputCmd = strtok(inputLine, " \n");
    inputPara = strtok(NULL, " \n");
    printf("inputCmd: %s\n", inputCmd);

    if (!strcmp(inputCmd, "quit")) break;

    if (inputPara == NULL) {
      printf("You must give para\n");
    }
    else if (!strcmp(inputCmd, "add")) {
      std::string sym(inputPara);
      printf("Add detected::%s\n", inputPara);
      quoteList.push_back(sym);
      config.setQuoteList(quoteList);
      quoter.AddQuote(sym);
    }
    else if (!strcmp(inputCmd, "del")) {
      std::string sym(inputPara);
      printf("Del detected::%s\n", inputPara);
      for (std::vector<std::string>::iterator it = quoteList.begin(); it != quoteList.end(); ++it) {
        if (*it == sym) quoteList.erase(it);
      }
      config.setQuoteList(quoteList);
      quoter.DelQuote(sym);
    }
    else if (!strcmp(inputCmd, "time")) {
      printf("Change time detected::%s\n", inputPara);
      display.SetQuoteInterval(atoi(inputPara));
    }
    delete[] inputLine;
  }
  printf("Quit Detected\n");

  display.Stop();
  quoter.Stop();
  return 0;
}

