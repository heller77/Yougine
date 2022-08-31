#pragma once
namespace yougine
{
	struct Vector3
	{
	public:
		float x, y, z;

		Vector3(float x, float y, float z)
			: x(x),
			y(y),
			z(z)
		{
		}

		/**
		 * \brief ‘ã“ü‰‰ŽZŽq
		 * \param v ‘ã“ü‚·‚é’l‚ 
		 * \return ‘ã“ü‚³‚ê‚½ŽQÆ
		 */
		Vector3& operator=(const Vector3& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}
	};

}