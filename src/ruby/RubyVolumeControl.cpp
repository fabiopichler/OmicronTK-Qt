/*******************************************************************************
  OmicronTK+Qt

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: MIT License

  Copyright 2018-2019, Fábio Pichler

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "OmicronTK/Qt/ruby/RubyVolumeControl.hpp"
#include "OmicronTK/Qt/ruby/base/RubyWidgetBase.hpp"
#include "OmicronTK/Qt/VolumeControl.hpp"

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

namespace OmicronTK {
namespace QT {

static const char className[] = "VolumeControl";

static mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_value pointer;
    mrb_get_args(mrb, "o", &pointer);

    DATA_PTR(self) = mrb_ptr(pointer);

    return self;
}

void RubyVolumeControl_Init(mrb_state *mrb)
{
    struct RClass *rclass = mrb_define_class(mrb, className, mrb->object_class);

    RubyWidgetBase_Init(mrb, rclass);

    mrb_define_method(mrb, rclass, "initialize", initialize, MRB_ARGS_REQ(1));
}

}
}
