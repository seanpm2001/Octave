/*

Copyright (C) 2012-2017 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#if ! defined (octave_tree_funcall_h)
#define octave_tree_funcall_h 1

#include "octave-config.h"

#include "ov.h"
#include "ovl.h"
#include "parse.h"
#include "pt-exp.h"

// Function call.  This class only represents function calls that have
// known functions (most useful for calls to built-in functions that
// are generated by the parser) and fixed argument lists, known at
// compile time.

class
tree_funcall : public tree_expression
{
public:

  tree_funcall (const octave_value& f, const octave_value_list& a,
                int l = -1, int c = -1)
    : tree_expression (l, c), fcn (f), args (a)
  {
    if (! fcn.is_function ())
      error ("tree_funcall: invalid function");
  }

  ~tree_funcall (void) { }

  bool has_magic_end (void) const { return false; }

  void print (std::ostream& os, bool pr_as_read_syntax = false,
              bool pr_orig_txt = true);

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false,
                  bool pr_orig_txt = true);

  tree_funcall *dup (symbol_table::scope_id,
                     symbol_table::context_id context) const;

  octave_value rvalue1 (int nargout)
  {
    octave_value retval;

    const octave_value_list tmp = rvalue (nargout);

    if (! tmp.empty ())
      retval = tmp(0);

    return retval;
  }

  octave_value_list rvalue (int nargout);

  octave_value function (void) const { return fcn; }

  octave_value_list arguments (void) const { return args; }

  void accept (tree_walker& tw);

private:

  // Function to call.  Error if not a valid function at time of
  // construction.
  octave_value fcn;

  // Argument list.
  octave_value_list args;

  // No copying!

  tree_funcall (const tree_funcall&);

  tree_funcall& operator = (const tree_funcall&);
};

#endif
