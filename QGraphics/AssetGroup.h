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
		//build the index and vertex arrays for the AssetGroup
		//should not need calling directly, for internal use
		void build();

		//draw this AssetGroup for the next frame
		//should not need calling directly
		//called by Window::Render
		void draw();

		//create an assetGroup using existing assets
		//it is best to already set relative positions and scales before joining
		//one asset will be the parent object which will define the origin of the group
		template<typename P, typename... C>
		AssetGroup(P parent, C... children)
		{
			m_parent = parent;
			(m_children.push_back(dynamic_cast<Asset*>(children)), ...);

			m_parent->grouped = true;
			for (auto* x : m_children)
				x->grouped = true;
		}

	};
}