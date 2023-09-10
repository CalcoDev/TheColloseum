#include "base_types.h"

DenseTime DenseTimeFromDateTime(DateTime date_time)
{
  DenseTime dense_time = 0;

  dense_time += date_time.year;
  dense_time *= 12;
  dense_time += date_time.month;
  dense_time *= 31;
  dense_time += date_time.day;
  dense_time *= 24;
  dense_time += date_time.hour;
  dense_time *= 60;
  dense_time += date_time.minute;
  dense_time *= 61;
  dense_time += date_time.second;
  dense_time *= 1000;
  dense_time += date_time.milisecond;

  return dense_time;
}

DateTime DateTimeFromDenseTime(DenseTime dense_time)
{
  DateTime date_time = {0};

  date_time.milisecond = dense_time % 1000;
  dense_time /= 1000;
  date_time.second = dense_time % 61;
  dense_time /= 61;
  date_time.minute = dense_time % 60;
  dense_time /= 60;
  date_time.hour = dense_time % 24;
  dense_time /= 24;
  date_time.day = dense_time % 31;
  dense_time /= 31;
  date_time.month = dense_time % 12;
  dense_time /= 12;
  date_time.year = dense_time;

  return date_time;
}