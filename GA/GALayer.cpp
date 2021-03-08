#include "GA/GAlayer.h"

using namespace NN;


GALayer::GALayer(int size) : Layer(size) {}

GALayer::GALayer() : Layer() {}


GALayer * GALayer::clone()
{
    GALayer* new_layer = new GALayer(size());
    if (weights.rows() != 0 && weights.cols() != 0)
    {
        int rows = weights.rows();
        int cols = weights.cols();
        
        new_layer->weights.resize(weights.rows() , weights.cols() );
    }
    new_layer->weights = weights;
    new_layer->biases = biases;
    return new_layer;
}

void GALayer::mutate(double rate, double power)
{
    for (int i = 0 ; i < size() ; i++ )
    {
        if(func::random() < rate )
        {
            biases(i , 0) = biases(i , 0) + func::random(-1, 1)*power;
        }
    }

    for(int i = 0 ; i < weights.rows() ; i ++)
    {
        for(int j = 0; j < weights.cols() ; j++)
        {
            if( func::random() < rate )
            {
                weights(i,j) = weights(i,j) + func::random(-1, 1)*power;
            }
        }
    }
}




GALayer * GALayer::crossover(double first_section, GALayer *other)
{
    if(other->weights.rows() != weights.rows() || other->weights.cols() != weights.cols())
    {
        PRINT_ERR("Layers not match for crossover")
        exit(1);
    }

    GALayer * new_layer = other->clone();
    int half_point1 = size()/2;
    for (int i = 0 ; i < size() ; i++ )
    {
        if(first_section > 0.5)
        {
            if(i <= half_point1)
            {
                new_layer->biases(i,0) = biases(i, 0);
            } else break;
        } else
        {
            if(i >= half_point1)
            {
                new_layer->biases(i,0) = biases(i, 0);
            }
        }

    }

    int half_point = weights.rows()*weights.cols()/2;
    int counter = 0;

    for(int i = 0 ; i < weights.rows() ; i ++)
    {
        for(int j = 0; j < weights.cols() ; j++)
        {
            if(first_section > 0.5)
            {
                if( counter  <= half_point )
                {
                    new_layer->weights(i,j) = weights(i, j);
                } else break;
            } else
            {
                if( counter  >= half_point )
                {
                    new_layer->weights(i,j) = weights(i, j);
                }
            }
            counter++;
        }
    }
    return new_layer;
}




GALayer * GALayer::uniform_crossover(double win ,GALayer *other)
{
    if(other->weights.rows() != weights.rows() || other->weights.cols() != weights.cols())
    {
        PRINT_ERR("Layers not match for crossover")
        exit(1);
    }

    GALayer * new_layer = other->clone();

    for (int i = 0 ; i < size() ; i++ )
    {
        if(func::random() < win )
        {
            new_layer->biases(i,0) = biases(i, 0);
        }
    }

    for(int i = 0 ; i < weights.rows() ; i ++)
    {
        for(int j = 0; j < weights.cols() ; j++)
        {
            if( func::random() < win )
            {
                new_layer->weights(i,j) = weights(i, j);
            }
        }
    }

    return new_layer;
}

