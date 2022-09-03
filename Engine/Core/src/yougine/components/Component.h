#pragma once

namespace yougine
{
	class GameObject;
}

namespace yougine::components
{
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