#include "PID.h"

class PIDTuner{
	
public:
	double best_rmse;
	double curr_rmse;
	
	// Co-efficients
	double[] _params;
	double[] _dparams;
	
	
	PIDTuner(double params,double dparams);
	
	virtual ~PIDTuner();
	
	double calcRMSE();
	
	double run();
	
	

	
};
