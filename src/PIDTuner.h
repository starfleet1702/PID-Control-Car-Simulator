#ifndef PID_TUNER_H
#define PID_TUNER_H

#include "PID.h"
#include <uWS/uWS.h>

#define TWIDDLE_TOLERANCE 0.002
#define IS_DEBUG_MODE_ON true
#define ITERATION_THRESHOLD 3


class PIDTuner{
	
public:
	double _best_rmse;
	// double _curr_rmse;
	// vector<double> _rmse;
	uWS::WebSocket<uWS::SERVER> *_ws;
	
	// Co-efficients
	double _params[3];
	double _dparams[3];
	
	unsigned int _steps_per_run = 200;
	unsigned int _steps_to_skip = 100;
	
	double _cte ;
	double _output;
	bool _is_cte_recevied;
	
	PID _pid;
	
	// PIDTuner(double &params,double &dparams);
	
	PIDTuner();
	
	virtual ~PIDTuner();
	
	void tune();
	
	double run();
	
	double update(double cte);
	
	void setCTE(double cte);
	
	void setWs(uWS::WebSocket<uWS::SERVER>& ws);
	
	double get_sum_of_dparams();

	// void reset_simulator(uWS::WebSocket<uWS::SERVER>& ws);
private:

};

#endif // PID_TUNER_H 
