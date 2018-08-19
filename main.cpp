#include "./Includes.h"
#include "./Network.h"

void printDoubleArray(const double input[])
{ std::cout << input[0] << ", " << input[1]; }

template<std::size_t size>
void printNeuronArray(const Neuron<size> input[])
{ std::cout << input[0].value << ", " << input[1].value; }

int main()
{
  Network<2, 2, 2, 2> network;
  double input[2] = {4.0,0.0};
  double output[2] = {1.0,0.0};
  for(std::size_t i = 0; i < 256; i++)
  {
    std::cout << "(" << i << "/256) Loss: " << network.train(input, output, 0.1) << "\n";
    std::cout << "Input: ";
    printDoubleArray(input);
    std::cout << "\nExpected Output: ";
    printDoubleArray(output);
    std::cout << "\nOutput: ";
    printNeuronArray(network.output);
    std::cout << "\n\n";

    for(std::size_t i = 0; i < 0xffff; i++)
    {
      network.train(input, output, 0.1);
    };
  };
}
