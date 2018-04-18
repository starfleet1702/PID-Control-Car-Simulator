#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H


#include <iostream>
#include <uWS/uWS.h>


std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

// Resetting the Simulator
void reset_simulator(uWS::WebSocket<uWS::SERVER>& ws){
	std::string msg("42[\"reset\",{}]");
	ws.send(msg.data(),msg.length(), uWS::OpCode::TEXT);
}

#endif //HELPER_FUNCTIONS_H