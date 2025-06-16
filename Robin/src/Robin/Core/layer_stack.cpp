#include "rbpch.h"
#include "layer_stack.h"

namespace Robin
{
	layer_stack::layer_stack()
	{
	}

	layer_stack::~layer_stack()
	{
		for (layer* layer : m_layers)
			delete layer; 
	}

	void layer_stack::push_layer(layer* layer)
	{
		 m_layers.emplace(m_layers.begin() + m_layer_insert_index, layer);
		 m_layer_insert_index++;
	}

	void layer_stack::push_overlay(layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void layer_stack::pop_layer(layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layer_insert_index--;
		}
	}

	void layer_stack::pop_overlay(layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
			m_layers.erase(it);
	}
}