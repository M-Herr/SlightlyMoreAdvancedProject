#pragma once
#ifndef __SIGNAL_HANDLING_HH__
#define __SIGNAL_HANDLING_HH__

#include <csignal>

class Application;

namespace Core {
     void signalHandler(int signum);
}


#endif //__SIGNAL_HANDLING_HH__