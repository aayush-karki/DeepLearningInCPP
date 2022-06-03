#include "stdafx.h"
#include "NeuralNetworkLayer.h"

///
/// @brief constructor
/// 
/// dynamicaly allocates the neuron
/// 
/// @param a_numData number of input train/test data 
/// @param a_layerType type of neural layer
/// @param a_TotalNeuralNum number of neuron in the layer
/// 
NeuralNetworkLayer::NeuralNetworkLayer( unsigned a_numData, ENUM_NeuronLayerType a_layerType, unsigned a_TotalNeuralNum ):
	m_layerType(a_layerType), m_layerWidth(a_TotalNeuralNum)
{
	// dynamically allocating neurons
	for( unsigned i = 0; i < a_TotalNeuralNum; ++i )
	{
		m_layerNeuronList.push_back( new Neuron( a_numData ) );
	}
}

/// 
/// @brief default destructor
///
NeuralNetworkLayer::~NeuralNetworkLayer()
{
	// deallocating the vectors
	for(unsigned i = 0; i < m_layerNeuronList.size(); ++i)
	{
		delete m_layerNeuronList[ i ];
	}

	m_layerNeuronList.clear(); // clearling the vector list itself
}

///
/// @brief calls the initialize random parameter funciton of each neuron
///
void NeuralNetworkLayer::InitializeRandomParameters(unsigned a_previousLayerWidth)
{
	for(unsigned i = 0; i < m_layerNeuronList.size(); ++i)
	{
		m_layerNeuronList[ i ]->InitializeRandomParameters(a_previousLayerWidth);
	}
}


///
/// @brief Calls forward Propagation on each of its neuron 
///
/// @param a_prevNNLayerNeurons memory address to vector containing
///		 the pointer to neurons in previous layer
/// @param a_activationFunc  activatoin function to call
/// 
void NeuralNetworkLayer::ForwardPropagation(const std::vector<Neuron*>& a_prevNNLayerNeurons)
{
	// calling the linear-activation function for each neuron
	for(unsigned i = 0; i < m_layerNeuronList.size(); ++i)
	{
		m_layerNeuronList[ i ]->LinerActivation(a_prevNNLayerNeurons);
	}
}


/// 
/// @brief Sets the activation value of the input neuron.
/// 
/// @warning all the data provided in the dataset is inserted. So, if only a
///		part of the data set were to be inserted then create a new vector and 
///		pass that in
/// @warning assumes that all the images in the dataset are of same resolution
/// 
/// @param a_dataSet dataset that contains the images to insert to the NN
/// 
void NeuralNetworkLayer::PopulateInputLayer( std::vector<std::vector<uint8_t>*>* a_dataSet )
{
	// only input layer will be populated manually
	assert( m_layerType == ENUM_NeuronLayerType::m_inputLayer );
	// checking if the number of input neuron in the layer is same the number of 
	// input in one test/train case
	assert( a_dataSet->at( 0 )->size() == m_layerWidth );

	// as the number of input neuron and number of pixels in one image is the same,
	// we loop through the pixle then save the pixel of each images in the activation 
	// vector to populate the input neuron that corresponds to that pixel
	// 
	// assumes that all the image are of same resolution
	// 
	// looping through the pixels 
	for( unsigned pixelIdx = 0; pixelIdx < a_dataSet->at(0)->size(); ++pixelIdx )
	{
		// populating the activation vector for the curr Neuron
		std::vector<long double>* currNeuronActiVec = m_layerNeuronList.at( pixelIdx )->GetActivationVector();

		// checking that the size of the activation value vector is same as the number of images
		// the dataset
		assert( a_dataSet->at( 0 )->size() == currNeuronActiVec->size() );
		
		// looping through the images and inserting the pixel of each image at pixelIdx 
		// in the input neuron
		for( unsigned imgIdx = 0; imgIdx < a_dataSet->size(); ++imgIdx )
		{
			currNeuronActiVec->at( imgIdx ) = a_dataSet->at( imgIdx )->at( pixelIdx );
		}
	}
}

/// 
/// @brief sets the activaiton fucition that each neuron uses
/// @param a_ActivationFunc 
/// 
void NeuralNetworkLayer::SetActivaitonFunciton( const AF::ENUM_ActiFunc a_ActivationFunc )
{
	// setitng  the activaiton function for each neuron 
	for( unsigned currNeuronLayerIdx = 0; currNeuronLayerIdx < m_layerNeuronList.size(); ++currNeuronLayerIdx )
	{
		m_layerNeuronList.at( currNeuronLayerIdx )->SetActivationFunction( a_ActivationFunc );
	}
}
