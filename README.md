# mruby-esp32-random

ESP32 hardware RNG Module for mruby-esp32.

This library provides a random number from the ESP32 hardware RNG.



# Installation

Add the following line below to your `esp32_build_config.rb`:

```ruby
  conf.gem :github => 'icm7216/mruby-esp32-random'
```

# Usage

generate random floating point number (0 < 1.0)
```ruby
rand or rand(0)  
```

generate random Integer number (0 < max)
*   max is maximum value of the random number, that is an Integer less than (2**32).
```ruby
rand(max)  
```
## sample

*   [Electronic Dice with mruby-esp32](https://github.com/icm7216/ElectronicDice-mruby-esp32)

## Note:

Require to enable the RF subsystem if you want to use the hardware RNG. Otherwise, return value should be considered a pseudo-random number.

The hardware RNG is random 32-bit word, that value between 0 and 4294967295.
*   ref. "esp_random()" from [ esp-idf/components/esp32/hw_random.c
](https://github.com/espressif/esp-idf/blob/9274814268f51333bd8aed65202621161e877a6a/components/esp32/hw_random.c#L25).

# example

```ruby
puts "rand     => #{ESP32::Random.rand}"
puts "rand(0)  => #{ESP32::Random.rand(0)}"
puts "rand(10) => #{ESP32::Random.rand(10)}"
```
Output the serial monitor
```
rand     => 0.7404350803095
rand(0)  => 0.65836564187388
rand(10) => 7
```

# License

under the MIT License:
- see LICENSE file
