#ifndef NETWORK_H
#define NETWORK_H

#include "./Neuron.h"
#include "./Includes.h"

template
<
  std::size_t input_size,
  std::size_t layer1_size,
  std::size_t layer2_size,
  std::size_t output_size
>
class Network
{
public: // Methods
  NUM calculateCost(const NUM input_layer[], const NUM output_layer[])
  {
    for(std::size_t i = 0; i < layer1_size; i++)
    { layer1[i].setValueFloat(input_layer); }

    for(std::size_t i = 0; i < layer2_size; i++)
    { layer2[i].setValue(layer1); }

    for(std::size_t i = 0; i < output_size; i++)
    { output[i].setValue(layer2); }

    NUM cost = 0;
    for(std::size_t i = 0; i < output_size; i++)
    {
      NUM diff = output[i].value - output_layer[i];
      cost += diff*diff;
    }

    return cost;
  }

  NUM train(const NUM input_layer[], const NUM output_layer[], const NUM step_size)
  {
    for(std::size_t i = 0; i < layer1_size; i++)
    {
      for(std::size_t j = 0; j < input_size; j++)
      { optimizeWeight(input_layer, output_layer, layer1[i].mult[j], step_size); }
      optimizeWeight(input_layer, output_layer, layer1[i].bias, step_size);
    }

    for(std::size_t i = 0; i < layer2_size; i++)
    {
      for(std::size_t j = 0; j < layer1_size; j++)
      { optimizeWeight(input_layer, output_layer, layer2[i].mult[j], step_size); }
      optimizeWeight(input_layer, output_layer, layer2[i].bias, step_size);
    }

    for(std::size_t i = 0; i < output_size; i++)
    {
      for(std::size_t j = 0; j < layer2_size; j++)
      { optimizeWeight(input_layer, output_layer, output[i].mult[j], step_size); }
      optimizeWeight(input_layer, output_layer, output[i].bias, step_size);
    }

    return calculateCost(input_layer, output_layer);
  }

public: // Variables
  Neuron<input_size>  layer1[layer1_size];
  Neuron<layer1_size> layer2[layer2_size];
  Neuron<layer2_size> output[output_size];

private: // Methods
  void optimizeWeight(const NUM input_layer[], const NUM output_layer[], NUM& weight, NUM step_size)
  {
    const NUM startCost = calculateCost(input_layer, output_layer);
    weight += step_size;
    const NUM highCost = calculateCost(input_layer, output_layer);
    weight -= step_size*2;
    const NUM lowCost = calculateCost(input_layer, output_layer);

    if(startCost < highCost)
    {
      if(startCost < lowCost)
      { weight += step_size; }
    } else
    {
      if(highCost < lowCost)
      { weight += step_size*2; }
    }
  }

private: // Variables

};

#endif
