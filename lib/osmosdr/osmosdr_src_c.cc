/* -*- c++ -*- */
/*
 * Copyright 2012 Dimitri Stolnikov <horiz0n@gmx.net>
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "osmosdr_src_c.h"
#include <gr_io_signature.h>
#include <gr_audio_source.h>
#include <gr_float_to_complex.h>

#include <osmosdr_arg_helpers.h>

/*
 * Create a new instance of osmosdr_src_c and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
osmosdr_src_c_sptr
osmosdr_make_src_c (const std::string &args)
{
  return gnuradio::get_initial_sptr(new osmosdr_src_c (args));
}

/*
 * The private constructor
 */
osmosdr_src_c::osmosdr_src_c (const std::string &args)
  : gr_hier_block2 ("osmosdr_src_c",
        gr_make_io_signature (0, 0, sizeof (gr_complex)),
        args_to_io_signature(args)),
    osmosdr_rx_control(args)
{
  /* Audio source; sample rate is 500kHz by default */
  audio_source::sptr src = audio_make_source(500000, audio_dev_name(), true);

  /* block to convert stereo audio to a complex stream */
  gr_float_to_complex_sptr f2c = gr_make_float_to_complex(1);

  connect(src, 0, f2c, 0); /* Left is I */
  connect(src, 1, f2c, 1); /* Right is Q */
  connect(f2c, 0, self(), 0);
}

/*
 * Our virtual destructor.
 */
osmosdr_src_c::~osmosdr_src_c ()
{
  // nothing else required in this example
}