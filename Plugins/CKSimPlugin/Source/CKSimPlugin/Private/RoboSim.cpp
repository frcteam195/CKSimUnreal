// Fill out your copyright notice in the Description page of Project Settings.


#include "RoboSim.h"
#include "zmqInterface.h"

float URoboSim::Get_Motor(int motor_id)
{
	return robosim::zmq_interface::get_motor(motor_id);
}

void URoboSim::Set_Encoder(int encoder_id, float value)
{
	robosim::zmq_interface::set_encoder(encoder_id, value);
}

void URoboSim::Set_Accelerometer(int accelerometer_id, float value)
{
	robosim::zmq_interface::set_accelerometer(accelerometer_id, value);
}

void URoboSim::Set_Gyroscope(int gyroscope_id, float value)
{
	robosim::zmq_interface::set_gyroscope(gyroscope_id, value);
}

void URoboSim::Set_Advanced(int advanced_id, float value)
{
	robosim::zmq_interface::set_advanced(advanced_id, value);
}