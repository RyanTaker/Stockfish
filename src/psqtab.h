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

#ifndef PSQTAB_H_INCLUDED
#define PSQTAB_H_INCLUDED

#include "types.h"

#define S(mg, eg) make_score(mg, eg)


/// PSQT[PieceType][Square] contains Piece-Square scores. For each piece type on
/// a given square a (midgame, endgame) score pair is assigned. PSQT is defined
/// for white side, for black side the tables are symmetric.

static const Score PSQT[][SQUARE_NB] = {
  { },
  { // Pawn
   S( 0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S( 0, 0),
   S(-20,0), S(-6,0), S( 4,0), S(14,0), S(14,0), S( 4,0), S(-6,0), S(-20,0),
   S(-20,0), S(-6,0), S( 9,0), S(34,0), S(34,0), S( 9,0), S(-6,0), S(-20,0),
   S(-20,0), S(-6,0), S(17,0), S(54,0), S(54,0), S(17,0), S(-6,0), S(-20,0),
   S(-20,0), S(-6,0), S(17,0), S(34,0), S(34,0), S(17,0), S(-6,0), S(-20,0),
   S(-20,0), S(-6,0), S( 9,0), S(14,0), S(14,0), S( 9,0), S(-6,0), S(-20,0),
   S(-20,0), S(-6,0), S( 4,0), S(14,0), S(14,0), S( 4,0), S(-6,0), S(-20,0),
   S( 0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S( 0,0), S( 0,0), S(  0,0)
  },
  { // Knight
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0)
  },
  { // Bishop
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0)
  },
  { // Rook
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0),
   S(-12, 0), S(-7, 0), S(-2, 0), S(2, 0), S(2, 0), S(-2, 0), S(-7, 0), S(-12, 0)
  },
  { // Queen
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), 
   S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0)
  },
  { // King
   S(287, 18), S(311, 77), S(262,105), S(214,135), S(214,135), S(262,105), S(311, 77), S(287, 18),
   S(262, 77), S(287,135), S(238,165), S(190,193), S(190,193), S(238,165), S(287,135), S(262, 77),
   S(214,105), S(238,165), S(190,193), S(142,222), S(142,222), S(190,193), S(238,165), S(214,105),
   S(190,135), S(214,193), S(167,222), S(119,251), S(119,251), S(167,222), S(214,193), S(190,135),
   S(167,135), S(190,193), S(142,222), S( 94,251), S( 94,251), S(142,222), S(190,193), S(167,135),
   S(142,105), S(167,165), S(119,193), S( 69,222), S( 69,222), S(119,193), S(167,165), S(142,105),
   S(119, 77), S(142,135), S( 94,165), S( 46,193), S( 46,193), S( 94,165), S(142,135), S(119, 77),
   S(94,  18), S(119, 77), S( 69,105), S( 21,135), S( 21,135), S( 69,105), S(119, 77), S( 94, 18)
  }
};

#undef S

#endif // #ifndef PSQTAB_H_INCLUDED
