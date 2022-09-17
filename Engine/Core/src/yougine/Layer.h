#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace yougine
{
    class Layer
    {
    private:
        std::string name = "";

    public:
        Layer(std::string layer_name);
        ~Layer();
        std::string GetName();
    };

    class LayerManager
    {
    private:
        static LayerManager* m_layer_manager;
        std::vector<Layer*> layers;
        std::vector<char*> layers_name;

    private:
        LayerManager();
        ~LayerManager();

    public:
        static void Create();
        static void Destroy();
        static LayerManager* GetInstance();
        void AddLayer(std::string name);
        void RemoveLayer(std::string name);
        std::vector<Layer*> GetLayers();
        Layer* GetLayerByName(std::string);
        std::vector<char*> GetLayersName();
    };

}