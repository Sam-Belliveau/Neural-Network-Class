#ifndef NEURON_H
#define NEURON_H

#include "./Includes.h"

typedef double NUM;

#define abs(x) ((x > 0) ? x : -x)
#define RANDOMFLOAT ((NUM(rand()%0x10000)/NUM(0x8000))-NUM(1))

NUM sigmoid(const NUM input, const std::size_t iterations = 4)
{
  NUM out = input;
  for(std::size_t i = 0; i < iterations; i++)
  { out /= (abs(out) + 1); }

  if(out >= NUM(1))
  { return NUM(1); }
  else if(out <= NUM(0))
  { return NUM(0); }
  else { return out; }
}

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
  NUM setValue(const Neuron<input_input_size> inputs[])
  {
    value = 0;
    for(std::size_t i = 0; i < input_size; i++)
    { value += inputs[i].value*mult[i]; }
    value += bias;

    value = sigmoid(value);

    return value;
  }

  NUM setValueFloat(const NUM inputs[])
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
