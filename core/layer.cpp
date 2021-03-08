#include "layer.h"

using namespace NN;

Layer::Layer(int size)
{
    values.resize(size, 1);
    biases.resize(size, 1);
    init_size(size);
}

void Layer::init_size(int size)
{
}

Layer::Layer()
{
}

Layer::~Layer()
{

}

void Layer::init()
{
    if(prev_layer != nullptr)
    {
        int rows = size();
        int cols = prev_layer->size();
        weights.resize(rows, cols);
        randomize_weights();
        randomize_biases();
        biases = biases*0.01;
        //(*weights)/cols;
        //(*biases)/cols;
    }
}

void Layer::init_no_random()
{
    if(prev_layer != nullptr)
    {
        int rows = size();
        int cols = prev_layer->size();
        weights.resize(rows, cols);
        //(*weights)/cols;
        //(*biases)/cols;
    }
}

void Layer::randomize_weights()
{
    weights = Matrix::Random(weights.rows(), weights.cols());
}

void Layer::randomize_biases()
{
    biases = Matrix::Random(biases.rows(), biases.cols());
    biases *= 0.1;
}

int Layer::size()
{
    return values.rows();
}

void Layer::run()
{
    values = weights * prev_layer->values + biases;
    values = activation_functions(values);
}

void Layer::print(std::stringstream &st)
{
    st << "layer_start" << std::endl;
    st << "weights_start" << std::endl;
    st << weights << std::endl;
    st << "weights_end" << std::endl;
    st << "biases_start" << std::endl;
    st << biases << std::endl;
    st << "biases_end" << std::endl;
    st << "layer_end" << std::endl;
}

void Layer::scan(std::stringstream &st)
{
    std::string read;
    std::vector<std::vector<double> > w;
    std::vector<double> b;
    while (!st.eof())
    {
        st >> read;
        if(read == "weights_start")
        {
            scan_weights(st, w);
        } else if (read == "biases_start")
        {
            scan_biases(st, b);
        } else if (read == "layer_end")
        {
            break;
        }
    }
    weights = func::vector2matrix(w);
    biases = func::vector2matrix(b);
    values.resize(biases.rows(), 1);
    init_size(biases.rows());
}

void Layer::scan_weights(std::stringstream &st, std::vector<std::vector<double>> &v)
{
    bool end = false;
    std::string read_line;
    std::string read;
    std::getline(st, read_line);
    while (!st.eof() && !end)
    {
        std::getline(st, read_line);
        std::stringstream line(read_line);
        std::vector<double> row;
        while (!line.eof())
        {
            std::string sd;
            double d;
            line >> sd;
            if(sd=="weights_end")
            {
                end = true;
                break;
            }
            if(sd != "") d = std::stod(sd);
            row.push_back(d);
        }

        if(!end) v.push_back(row);
    }
}

void Layer::Layer::scan_biases(std::stringstream &st, std::vector<double> &v)
{
    std::string read;
    while (!st.eof())  
    {
        st >> read;
        if (read == "biases_end") break;
        if(read=="") continue;
        double d;
        d = std::stod(read);
        v.push_back(d);
    }
}