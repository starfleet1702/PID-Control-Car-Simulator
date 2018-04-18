#include "PID.h"
#include "PIDTuner.h"
#include <numeric>
#include "helper_functions.h"

using namespace std;

PIDTuner::PIDTuner() : _params {0.0,0.0,0.0}, _dparams {1,1,1}{
	// this->_params = {0.0,0.0,0.0};
	// this->d_params = {1,1,1};
	this->_best_rmse = std::numeric_limits<double>::infinity();
	// this->_ws = ws;
	this->_pid.Init(_params[0],_params[1],_params[2]);
	
	//TODO : Opt
	// PIDTuner()
}

// PIDTuner::PIDTuner(double &params,double &dparams){
	// this->_params = params;
	// this->_dparams = dparams;
	// this->_best_rmse = numeric_limits<double>::infinity();
	// this->_pid.Init(_params[0],_params[1],_params[2]);
	// // this->_ws = ws;
// }

void PIDTuner::tune(){
	double perc_change = 50;
	int size_of_params = sizeof(_params)/sizeof(_params[0]);
	unsigned int  it = 1;
	
	while((get_sum_of_dparams()>TWIDDLE_TOLERANCE)){
		if(it>=ITERATION_THRESHOLD+1){
			if(IS_DEBUG_MODE_ON){
				cout<<"Iteration Threshold reached....."<<endl;
			}
			break;
		}
		double curr_rmse;
		for(int i=0;i<size_of_params;i++){
			_params[i]+=_dparams[i];
			curr_rmse  = run();
			if(curr_rmse < _best_rmse){
				_best_rmse = curr_rmse;
				_dparams[i] += (perc_change/100.0)*_dparams[i];
			}else{
				_params[i]-=2.0*_dparams[i];
				curr_rmse  = run();
				if(curr_rmse < _best_rmse){
					_best_rmse = curr_rmse;
					_dparams[i] += (perc_change/100.0)*_dparams[i];
				}else{
					_params[i]-=_dparams[i];
					_dparams[i]-= (perc_change/100.0)*_dparams[i];
					
				}
			}
		}
		if(IS_DEBUG_MODE_ON){
			cout<<"Iteration : "<<it<<"rmse : "<<_best_rmse<<" (Kp,Ki,Kd) : "<<"( "<<_params[0]<<" , "<<_params[1]<<" , "<<_params[2]<<" )"<<endl;
		}
		it+=1;
	}
	
	
}

double PIDTuner::run(){
	//reset_simulator(this->_ws);
	int curr_steps = 0;
	double curr_rmse = 0.0;
	
	// this->curr_rmse = 0.0;
	this->_is_cte_recevied = false;
	
	while(curr_steps<_steps_per_run && _is_cte_recevied){
		
		if(IS_DEBUG_MODE_ON){
			cout<<"New CTE Received , current step : "<<curr_steps<<endl; 
		}
		
		// skipping initial few steps to allow pid to be stable
		if(curr_steps>=_steps_to_skip){
			curr_rmse = this->_cte*this->_cte;
		}
		this->_is_cte_recevied = false;
	}
	return curr_rmse;
		
}

double PIDTuner::update(double cte){
	this->setCTE(cte);
	return this->_pid.Update(cte,true);
}

void PIDTuner::setCTE(double cte){
	this->_cte = cte;
	this->_is_cte_recevied = true;
}
	

void PIDTuner::setWs(uWS::WebSocket<uWS::SERVER>& ws){
	// this->_ws = ws;
}	

double PIDTuner::get_sum_of_dparams(){
	double summ = 0.0;
	int size_of_dparams = sizeof(_dparams)/sizeof(_dparams[0]);
	for(int i=0;i<size_of_dparams;i++){
		summ+=_dparams[i];
	}
	return summ;
}