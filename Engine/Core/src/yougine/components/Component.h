#pragma once

namespace yougine::components
{
	class GameObject;

	class Component
	{
	private:
		GameObject* gameobject;

	private:
		void InitializeProperties();

	public:
		Component();
		~Component();
		void Excute();
		void InitializeOnPlayBack();
		bool operator==(const Component& rhs) const;
		GameObject* GetGameObject();
	};
}