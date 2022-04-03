#pragma once
#include "NeuralNetworkLayer.h"

class NeuralNetwork
{
	// ===================== Public Member Function =================
public:
	NeuralNetwork(const std::vector<int>& a_neuronPerEachLayerList); // default constructor
	~NeuralNetwork(); // desturctor	

	void InitialParameters(); // initializing the parametes
	void ForwardPropagation( const std::vector<AF::ENUM_ActiFunc>& a_ActivationFuncPerLayerList ); // does forward propagation

	// ===================== Private Data Member ====================
private:
	std::vector<NeuralNetworkLayer*> m_neuronLayers;
};

