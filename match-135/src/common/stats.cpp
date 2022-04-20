#include "stats.h"

#include <iomanip>
#include "common/state.h"

// StateStats

StateStats::StateStats(const State& state) {
  depth           = state.row;
  branching       = 0;
  closed_score    = 0;
  open_score      = 0;
  component_size  = 0;
  component_count = 0;
}

std::ostream& operator<<(std::ostream& out, const StateStats& stats) {
  out << stats.depth           << " ";
  out << stats.branching       << " ";
  out << stats.closed_score    << " ";
  out << stats.open_score      << " ";
  out << stats.component_size  << " ";
  out << stats.component_count << " ";
  return out;
}

std::istream& operator>>(std::istream& in, StateStats& stats) {
  in >> stats.depth;
  in >> stats.branching;
  in >> stats.closed_score;
  in >> stats.open_score;
  in >> stats.component_size;
  in >> stats.component_count;
  return in;
}

// VarStat

void VarStat::process(int value) {
  min = std::min(min, value);
  max = std::max(max, value);
  sum += value;
}

std::ostream& operator<<(std::ostream& out, const VarStat& stat) {
  out << stat.min << "/" << stat.max << "/" << stat.sum;
  return out;
}

// CaseStats

void CaseStats::add_state(const State& state) {
  StateStats stats = StateStats { state };

  state_count += 1;
  depth.process(stats.depth);
  branching.process(stats.branching);
  closed_score.process(stats.closed_score);
  open_score.process(stats.open_score);
  component_size.process(stats.component_size);
  component_count.process(stats.component_count);
}

std::ostream& operator<<(std::ostream& out, const CaseStats& stats) {
  out <<
    "========= Stats ========="                   << "\n" <<
    "State count     : " << stats.state_count     << "\n" <<
    "Depth           : " << stats.depth           << "\n" <<
    "Branching       : " << stats.branching       << "\n" <<
    "Closed Score    : " << stats.closed_score    << "\n" <<
    "Open Score      : " << stats.open_score      << "\n" <<
    "Component Size  : " << stats.component_size  << "\n" <<
    "Component Count : " << stats.component_count << "\n" <<
    "=========================";

  return out;
}

// Stats

Stats::Stats() {
  program_start_time = std::chrono::high_resolution_clock::now();
  last_print_time = program_start_time;
}

Stats::~Stats() {
  auto now = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - program_start_time);
  std::cerr << "Submitting ... " << duration.count() / 1000.0 << "s\n\n";
  std::cerr << case_stats << "\n\n";
}

void Stats::add_state(const State& state) {
  case_stats.add_state(state);
}

bool Stats::should_end_search() {
  auto now = std::chrono::high_resolution_clock::now();

  auto last_print_duration =
    std::chrono::duration_cast<std::chrono::milliseconds>(now - last_print_time);

  if (last_print_duration.count() > PRINT_TIME_IN_MS) {
    std::cerr <<
      "Calculating... " <<
      std::chrono::duration_cast<std::chrono::milliseconds>(now - program_start_time).count() / 1000.0 <<
      "s\n";

    last_print_time = now;
  }

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - program_start_time);
  if (duration.count() >= MAX_PROGRAM_TIME_IN_MS) {
    std::cerr << "Reached time limit!\n";
    return true;
  }

  return false;
}
