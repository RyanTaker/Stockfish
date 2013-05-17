/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2013 Marco Costalba, Joona Kiiski, Tord Romstad

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cmath>
#include <algorithm>

#include "search.h"
#include "timeman.h"
#include "ucioption.h"

namespace {

  /// Constants

  const int MoveHorizon  = 50;    // Plan time management at most this many moves ahead
  const float MaxRatio   = 7.0f;  // When in trouble, we can step over reserved time with this ratio
  const float StealRatio = 0.33f; // However we must not steal time from remaining moves over this ratio

  int move_importance(int ply) {
      return std::max(500,
             (ply * ply * 100) / 25 + (2000 * ply) / 3 + 40000) / 100;
  }


  /// Function Prototypes

  enum TimeType { OptimumTime, MaxTime };

  template<TimeType>
  int remaining(int myTime, int movesToGo, int fullMoveNumber, int slowMover);
}


void TimeManager::pv_instability(int curChanges, int prevChanges) {

  unstablePVExtraTime =  curChanges  * (optimumSearchTime / 2)
                       + prevChanges * (optimumSearchTime / 3);
}


void TimeManager::init(const Search::LimitsType& limits, int currentPly, Color us)
{
  /* We support four different kind of time controls:

      increment == 0 && movesToGo == 0 means: x basetime  [sudden death!]
      increment == 0 && movesToGo != 0 means: x moves in y minutes
      increment >  0 && movesToGo == 0 means: x basetime + z increment
      increment >  0 && movesToGo != 0 means: x moves in y minutes + z increment

    Time management is adjusted by following UCI parameters:

      emergencyMoveHorizon: Be prepared to always play at least this many moves
      emergencyBaseTime   : Always attempt to keep at least this much time (in ms) at clock
      emergencyMoveTime   : Plus attempt to keep at least this much time for each remaining emergency move
      minThinkingTime     : No matter what, use at least this much thinking before doing the move
  */

  int hypMTG, hypMyTime, t1, t2;

  // Read uci parameters
  int emergencyMoveHorizon = Options["Emergency Move Horizon"];
  int emergencyBaseTime    = Options["Emergency Base Time"];
  int emergencyMoveTime    = Options["Emergency Move Time"];
  int minThinkingTime      = Options["Minimum Thinking Time"];
  int slowMover            = Options["Slow Mover"];

  // Initialize to maximum values but unstablePVExtraTime that is reset
  unstablePVExtraTime = 0;
  optimumSearchTime = maximumSearchTime = limits.time[us];

  // We calculate optimum time usage for different hypothetic "moves to go"-values and choose the
  // minimum of calculated search time values. Usually the greatest hypMTG gives the minimum values.
  for (hypMTG = 1; hypMTG <= (limits.movestogo ? std::min(limits.movestogo, MoveHorizon) : MoveHorizon); hypMTG++)
  {
      // Calculate thinking time for hypothetic "moves to go"-value
      hypMyTime =  limits.time[us]
                 + limits.inc[us] * (hypMTG - 1)
                 - emergencyBaseTime
                 - emergencyMoveTime * std::min(hypMTG, emergencyMoveHorizon);

      hypMyTime = std::max(hypMyTime, 0);

      t1 = minThinkingTime + remaining<OptimumTime>(hypMyTime, hypMTG, currentPly, slowMover);
      t2 = minThinkingTime + remaining<MaxTime>(hypMyTime, hypMTG, currentPly, slowMover);

      optimumSearchTime = std::min(optimumSearchTime, t1);
      maximumSearchTime = std::min(maximumSearchTime, t2);
  }

  if (Options["Ponder"])
      optimumSearchTime += optimumSearchTime / 4;

  // Make sure that maxSearchTime is not over absoluteMaxSearchTime
  optimumSearchTime = std::min(optimumSearchTime, maximumSearchTime);
}


namespace {

  template<TimeType T>
  int remaining(int myTime, int movesToGo, int currentPly, int slowMover)
  {
    const float TMaxRatio   = (T == OptimumTime ? 1 : MaxRatio);
    const float TStealRatio = (T == OptimumTime ? 0 : StealRatio);

    int thisMoveImportance = move_importance(currentPly) * slowMover / 100;
    int otherMovesImportance = 0;

    for (int i = 1; i < movesToGo; i++)
        otherMovesImportance += move_importance(currentPly + 2 * i);

    float ratio1 = (TMaxRatio * thisMoveImportance) / float(TMaxRatio * thisMoveImportance + otherMovesImportance);
    float ratio2 = (thisMoveImportance + TStealRatio * otherMovesImportance) / float(thisMoveImportance + otherMovesImportance);

    return int(floor(myTime * std::min(ratio1, ratio2)));
  }
}
