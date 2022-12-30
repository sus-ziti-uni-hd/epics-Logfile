/* SPDX-License-Identifier: MIT */
#include "log_event.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
std::string format_time_helper(
      const std::chrono::system_clock::time_point &_t, bool _gmt) {
   const auto ttime_t = std::chrono::system_clock::to_time_t(_t);
   const auto tp_sec = std::chrono::system_clock::from_time_t(ttime_t);
   const auto ms =
         std::chrono::duration_cast<std::chrono::milliseconds>(_t - tp_sec);
   const auto ttm = _gmt ? std::gmtime(&ttime_t) : std::localtime(&ttime_t);
   char date[11];
   std::strftime(date, sizeof date, "%Y-%m-%d", ttm);
   char time[9];
   std::strftime(time, sizeof time, "%H:%M:%S", ttm);
   std::ostringstream ss;
   ss << date << (_gmt ? "T" : " ") << time << "." << std::setw(3)
      << std::setfill('0') << ms.count();
   if (_gmt) {
      ss << "Z";
   }
   return ss.str();
}
} // namespace

std::string SuS::logfile::format_time(
      const std::chrono::system_clock::time_point &_t) {
#ifdef SuS_LOG_GMT
   return format_time_helper(_t, true);
#else
   return format_time_helper(_t, false);
#endif
} // format_time

std::string SuS::logfile::format_time_local(
      const std::chrono::system_clock::time_point &_t) {
   return format_time_helper(_t, false);
}

std::string SuS::logfile::format_time_GMT(
      const std::chrono::system_clock::time_point &_t) {
   return format_time_helper(_t, true);
}

std::string SuS::logfile::format_timestamp(
      const std::chrono::system_clock::time_point &_t) {
   const auto ttime_t = std::chrono::system_clock::to_time_t(_t);
   const auto tp_sec = std::chrono::system_clock::from_time_t(ttime_t);
   const auto ms =
         std::chrono::duration_cast<std::chrono::milliseconds>(_t - tp_sec);
   std::ostringstream ss;
   ss << ttime_t << "." << std::setw(3) << std::setfill('0') << ms.count();
   return ss.str();
} // format_timestamp
