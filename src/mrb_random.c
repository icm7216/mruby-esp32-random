/*
** mrb_random.c - ESP32 hardware RNG Module
**
** Copyright (c) icm7216 2018
**
** See Copyright Notice in LICENSE
*/

#include <mruby.h>
#include <mruby/value.h>
#include <stdio.h>

#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*
** @brief ESP32 hardware RNG
**
** Require to enable the RF subsystem if you want to use the hardware RNG.
** Otherwise, return value should be considered a pseudo-random number.
** The hardware RNG is random 32-bit word, that value between 0 and 4294967295.
** ref. "esp_random()" from "hw_random.c".
** https://github.com/espressif/esp-idf/blob/9274814268f51333bd8aed65202621161e877a6a/components/esp32/hw_random.c#L25
**
** @param  max is maximum value of the random number, that is less than (2**32).
**
** @return Random value  (0 < max) if rand(max)
**                       (0 < 1.0) if rand or rand(0)
*/
static uint32_t
esp_rand(uint32_t max)
{
  return esp_random() % max;
}

static double
esp_rand_real()
{
  double value;
  value = (double)esp_random() * (1.0 / (double)UINT32_MAX);
  /* UINT32_MAX = 4294967295UL = (2**32) - 1 */

  return value;
}

static mrb_value
mrb_esp32_random_rand(mrb_state *mrb, mrb_value self)
{  
  mrb_value value;
  mrb_int max = 0;

  mrb_get_args(mrb, "|i", &max);
  if (max == 0) {
    value = mrb_float_value(mrb, esp_rand_real());
  }
  else {
    value = mrb_fixnum_value(esp_rand((uint32_t)max));
  }

  return value;
}

void
mrb_mruby_esp32_random_gem_init(mrb_state* mrb) {
  struct RClass *esp32_module = mrb_define_module(mrb, "ESP32");
  struct RClass *esp32_random_module = mrb_define_module_under(mrb, esp32_module, "Random");

  mrb_define_module_function(mrb, esp32_random_module, "rand", mrb_esp32_random_rand, MRB_ARGS_OPT(1));
}

void
mrb_mruby_esp32_random_gem_final(mrb_state* mrb) {
}

