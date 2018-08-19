#ifndef NETWORK_H
#define NETWORK_H

#include "./Neuron.h"
#include "./Include.h"

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
  std::array<NUM, output_size> getOutput(const std::array<NUM, output_size> input)
  {
    for(std::size_t i = 0; i < layer1_size; i++)
    { layer1[i].setValueFloat(input); }

    for(std::size_t i = 0; i < layer2_size; i++)
    { layer2[i].setValue(layer1); }

    std::array<NUM, output_size> out;
    for(std::size_t i = 0; i < output_size; i++)
    { out[i] = output[i].setValue(layer2); }

    return out;
  }

  NUM calculateCost
  (
    const std::vector<std::array<NUM, input_size>> input_layer,
    const std::vector<std::array<NUM, output_size>> output_layer
  )
  {
    if(input_layer.size() > output_layer.size()){ return 0; }

    NUM cost = 0;
    for(std::size_t test = 0; test < input_layer.size(); test++)
    {
      for(std::size_t i = 0; i < layer1_size; i++)
      { layer1[i].setValueFloat(input_layer[test]); }

      for(std::size_t i = 0; i < layer2_size; i++)
      { layer2[i].setValue(layer1); }

      for(std::size_t i = 0; i < output_size; i++)
      { output[i].setValue(layer2); }

      for(std::size_t i = 0; i < output_size; i++)
      {
        NUM diff = output[i].value - output_layer[test][i];
        cost += diff*diff;
      }
    }

    return cost;
  }

  NUM train
  (
    const std::vector<std::array<NUM, input_size>> input_layer,
    const std::vector<std::array<NUM, output_size>> output_layer,
    const NUM step_size = 0.001
  )
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
  std::array<Neuron<input_size>,  layer1_size> layer1;
  std::array<Neuron<layer1_size>, layer2_size> layer2;
  std::array<Neuron<layer2_size>, output_size> output;

private: // Methods
  void optimizeWeight
  (
    const std::vector<std::array<NUM, input_size>> input_layer,
    const std::vector<std::array<NUM, output_size>> output_layer,
    NUM& weight, const NUM step_size
  )
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
};

#endif
