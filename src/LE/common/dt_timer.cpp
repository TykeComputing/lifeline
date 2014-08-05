/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "dt_timer.h"

namespace LE
{

void dt_stopwatch::advance(float dt)
{
  p_curr_time += dt;
}

void dt_stopwatch::start()
{
  p_curr_time = 0.0f;
}

void dt_stopwatch::reset()
{
  p_curr_time = 0.0f;
}

float dt_stopwatch::poll() const
{
  return p_curr_time;
}

dt_countup::dt_countup()
{
}

dt_countup::dt_countup(float target_time) :
  p_target_time(target_time)
{
}

bool dt_countup::advance(float dt)
{
  p_stopwatch.advance(dt);
  return p_stopwatch.poll() >= p_target_time;
}

void dt_countup::start()
{
  p_stopwatch.start();
}

void dt_countup::reset()
{
  p_stopwatch.reset();
}

float dt_countup::poll() const
{
  return p_stopwatch.poll();
}

void dt_countup::set_target_time(float target_time)
{
  p_target_time = target_time;
}

} // namespace LE
