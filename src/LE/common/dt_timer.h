/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_DT_TIMER_H
#define LE_COMMON_DT_TIMER_H

namespace LE
{

class dt_stopwatch
{
public:

  void advance(float dt);

  void start();
  void reset();

  float poll() const;

private:

  float p_curr_time = 0.0f;
};

class dt_countup
{
public:
  dt_countup();
  dt_countup(float target_time);

  bool advance(float dt);

  void start();
  void reset();

  float poll() const;

  void set_target_time(float target_time);
  float get_target_time() const { return p_target_time; }
private:
  dt_stopwatch p_stopwatch;
  float p_target_time = -1.0f;
};

} // namespace LE

#endif // LE_COMMON_DT_TIMER_H
