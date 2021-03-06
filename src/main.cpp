
#include "pflight_config.hpp"

#include <iostream>
#include <stdlib.h>

#include "log.hpp"
#include "program.hpp"
#include "util.hpp"

Program *program;

void run(int argc, char *argv[]) {

  program = new Program(argc, argv);

  program->parseArgs();
  program->parseConfig();
  
  program->displayVersion();
  
  program->createWindow();
  program->createScene();
  
  program->dump();

  while(!program->shouldExit()) {
    program->tick();
  }

  log(LOG_LEVEL_INFO, "exiting normally");

  delete program;
}

int main(int argc, char *argv[]) {
  try {

    run(argc, argv);
    
    return(EXIT_SUCCESS);
    
  } catch(exit_exception e) {
    if(program) delete program;
    return(EXIT_SUCCESS);
    
  } catch(fatal_exception e) {
    if(program) delete program;
    return(EXIT_FAILURE);
  }
  
}
