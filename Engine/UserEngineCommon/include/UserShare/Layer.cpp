#include "Layer.h"

namespace yougine
{
    Layer::Layer(std::string name)
    {
        this->name = name;
    }

    std::string Layer::GetName()
    {
        return name;
    }

    LayerManager* LayerManager::m_layer_manager = nullptr;

    LayerManager::LayerManager()
    {
        AddLayer("Default");
    }

    LayerManager::~LayerManager()
    {
    }

    void LayerManager::Create()
    {
        if (!m_layer_manager)
        {
            m_layer_manager = new LayerManager();
        }
    }

    void LayerManager::Destroy()
    {
        if (m_layer_manager)
        {
            delete m_layer_manager;
            m_layer_manager = nullptr;
        }
    }

    LayerManager* LayerManager::GetInstance()
    {
        if (m_layer_manager)
            return m_layer_manager;
        return nullptr;
    }

    void LayerManager::AddLayer(std::string name)
    {
        if (GetLayerByName(name) != nullptr)
            return;

        layers.push_back(new Layer(name));
        layers_name.push_back(const_cast<char*>(layers.back()->GetName().c_str()));
    }

    void LayerManager::RemoveLayer(std::string name)
    {
        std::vector<Layer*> new_layers;
        std::vector<char*> new_layers_name;

        for (Layer* layer : layers)
        {
            if (layer->GetName() != name)
            {
                new_layers.push_back(layer);
                new_layers_name.push_back(const_cast<char*>(new_layers.back()->GetName().c_str()));
            }
        }

        layers = new_layers;
        layers_name = new_layers_name;
    }

    std::vector<Layer*> LayerManager::GetLayers()
    {
        return layers;
    }


    Layer* LayerManager::GetLayerByName(std::string name)
    {
        if (layers.empty())
            return nullptr;

        for (Layer* layer : layers)
        {
            if (layer->GetName() == name)
            {
                return layer;
            }
        }

        return nullptr;
    }

    std::vector<char*> LayerManager::GetLayersName()
    {
        return layers_name;
    }


}
