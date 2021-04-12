#pragma once

#include "Asset.h"


namespace QG
{
	class AssetGroup : public Asset
	{
	private:
		Asset* m_parent;
		std::vector<Asset*> m_children;
	public:
		void build();
		void draw();

		template<typename P, typename... C>
		AssetGroup(P parent, C... children)
		{
			m_parent = parent;
			(m_children.push_back(dynamic_cast<Asset*>(children)), ...);
		}

	};
}