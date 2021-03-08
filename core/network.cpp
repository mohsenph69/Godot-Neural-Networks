#include "network.h"


using namespace NN;


unsigned Network::last_id = 1;

Network::Network()
{
    id = Network::last_id;
    Network::last_id += 1;
}

Network::~Network()
{
    for(int i =0; i < size() ; i++)
    {
        delete layers.at(i);
    }
}

void Network::set_activation_function(activation a)
{
    Func f;
    switch (a)
    {
    case activation::sigmoid:
        f = &NN::func::sigmoid;
        break;
    }

    for(unsigned i = 0 ; i < layers.size() ; i++)
    {
        layers.at(i)->activation_functions = f;
    }

}

void Network::add_layer(int size)
{
    Layer * layer = new Layer(size);
    layers.push_back(layer);
}

void Network::add_layer()
{
    Layer * layer = new Layer();
    layers.push_back(layer);
}

std::vector<Layer*> * Network::get_layers()
{
    return &layers;
}

void Network::init()
{
    set_activation_function(activation_function);
    set_prev_layers();
    for(unsigned i = 1 ; i < layers.size() ; i++)
    {
        layers.at(i)->init();
    }
}

void Network::set_prev_layers()
{
    for(unsigned i = 1 ; i < layers.size() ; i++)
    {
        layers.at(i)->prev_layer = layers.at(i -1);
    }
}

int Network::size()
{
    return layers.size();
}

void Network::randomize_weights()
{
    for(unsigned i = 0 ; i < layers.size() ; i++)
    {
        layers.at(i)->randomize_weights();
    }
}

void Network::randomize_biases()
{
    for(unsigned i = 0 ; i < layers.size() ; i++)
    {
        layers.at(i)->randomize_biases();
    }
}

Layer* Network::input_layer()
{
    return layers.at(0);
}

Layer* Network::output_layer()
{
    return layers.back();
}

Col Network::input()
{
    return input_layer()->values;
}

Col Network::output()
{
    return output_layer()->values;
}

Col Network::feedforward(Col input)
{
    if(input.rows() != layers.at(0)->values.rows() )
    {
        PRINT_ERR("input values are not in correct size")
        exit(1);
    }
    input_layer()->values = input;
    for(unsigned i = 1 ; i < layers.size() ; i++)
    {
        layers.at(i)->run();
    }
    return layers.back()->values;
}


void Network::print(std::stringstream &st)
{
    st << "network_start" << std::endl;
    for(unsigned i = 1 ; i < size() ; i++)
    {
        layers.at(i)->print(st);
    }
    st << "network_end" << std::endl;
}

bool Network::scan(std::stringstream &st)
{
    if(size() != 0)
    {
        return false;
    }
    bool network_start = false;
    std::string read;
    while (!st.eof())
    {
        st >> read;
        if(read == "network_start")
        {
            network_start = true;
            break;
        }
    }
    if(network_start && !st.eof())
    {
        int layer_index =0;
        while (!st.eof())
        {
            st >> read;
            if (read == "network_end") break;
            if(read=="layer_start")
            {
                if (layer_index == 0)
                {
                    this->add_layer();
                }
                layer_index++;
                this->add_layer();
                Layer *l = layers.at(layer_index);
                l->scan(st);
            }
        }
        // Now setting the size for the first layer
        int size = layers.at(1)->weights.cols();
        layers.at(0)->values.resize(size, 1);
        layers.at(0)->biases.resize(size, 1);
        layers.at(0)->init_size(size);

        set_activation_function(activation_function);
        set_prev_layers();
    }
    return true;

}