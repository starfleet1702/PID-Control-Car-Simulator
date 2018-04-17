#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp=Kp;
	this->Ki=Ki;
	this->Kd=Kd;
	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
	prev_cte = 0.0;
	is_first_measurement = true;
}

double PID::Update(double cte,bool reverse = false) {
	if(is_first_measurement){
		prev_cte = cte;
		is_first_measurement = false;
	}
	p_error = cte;
	d_error = (cte-prev_cte);
	i_error += cte;
	
	double output = Kp*p_error + Kd*d_error + Ki*i_error;
	
	prev_cte = cte;
	if(reverse){
		return -output;
	}
	return output;
}

double PID::TotalError() {
	// double total_error = Kp*p_error + Kd*d_error + Ki*i_error ;
	// return total_error;
	return 0.0;
}

