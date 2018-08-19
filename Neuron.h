#ifndef NEURON_H
#define NEURON_H

#include "./Includes.h"

typedef double NUM;

#define abs(x) ((x > 0) ? x : -x)
#define sigmoid(x) (x/(1.0 + abs(x)))
#define RANDOMFLOAT ((NUM(rand()%0x10000)/NUM(0x8000))-NUM(1))


template<std::size_t input_size>
struct Neuron
{
  Neuron()
  {
    srand(time(NULL));

    for(std::size_t i = 0; i < input_size; i++)
    { mult[i] = RANDOMFLOAT; }
    value = RANDOMFLOAT;
    bias = RANDOMFLOAT;
  }

  template<std::size_t input_input_size>
  NUM setValue(const std::array<Neuron<input_input_size>, input_size> inputs)
  {
    value = 0;
    for(std::size_t i = 0; i < input_size; i++)
    { value += inputs[i].value*mult[i]; }
    value += bias;

    value = sigmoid(value);

    return value;
  }

  NUM setValueFloat(const std::array<NUM, input_size> inputs)
  {
    value = 0;
    for(std::size_t i = 0; i < input_size; i++)
    { value += inputs[i]*mult[i]; }
    value += bias;

    value = sigmoid(value);
    return value;
  }

  NUM value;
  NUM bias;
  NUM mult[input_size];
};

#endif
