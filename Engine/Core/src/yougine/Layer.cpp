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
    }

    void LayerManager::RemoveLayer(std::string name)
    {
        std::vector<Layer*> new_layers;

        for (Layer* layer : layers)
        {
            if (layer->GetName() != name)
            {
                new_layers.push_back(layer);
            }
        }

        layers = new_layers;
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

}
