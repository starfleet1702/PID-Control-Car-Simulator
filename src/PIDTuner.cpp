#include "PID.h"
#include "PIDTuner.h"

// Resetting the Simulator
void PIDTuner::reset_simulator(uWS::WebSocket<uWS::SERVER>& ws){
	std::string msg("42[\"reset\",{}]");
	ws.send(msg.data(),msg.length(), uWS::OpCode::TEXT);
}

PIDTuner::PIDTuner(){
	this->_params = {0.0,0.0,0.0};
	this->d_params = {1,1,1};
}

void PIDTuner::tune(){
	double perc_change = 50;
	
	while()
	
	
}

double PIDTuner::get_sum_of_dparams(){
	double summ = 0.0;
	int size_of_dparams = sizeof(dparams)/sizeof(dparams[0]);
	for(int i=0;i<size_of_dparams;i++){
		summ+=dparams[i];
	}
	return summ;
}