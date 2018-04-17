#include "PID.h"
#include <uWS/uWS.h>

#define TWIDDLE_TOLERANCE 0.002


class PIDTuner{
	
public:
	double _best_rmse;
	double _curr_rmse;
	vector<double> _rmse;
	
	// Co-efficients
	double[] _params;
	double[] _dparams;
	
	
	PIDTuner(double params,double dparams);
	
	PIDTuner();
	
	virtual ~PIDTuner();
	
	double calcRMSE();
	
	double run();
	
	void tune();
	
	void reset_simulator(uWS::WebSocket<uWS::SERVER>& ws);
private:
	double get_sum_of_dparams();
};
