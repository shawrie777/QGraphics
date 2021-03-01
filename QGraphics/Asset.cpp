#include "Asset.h"

namespace QG
{

	void QG::Asset::build()
	{
		if (built)
			return;

		vertices.Build();
		indices.Build();
		built = true;
	}

	void Asset::draw()
	{
		if (!built)
			build();

		vertices.Bind();
		indices.Bind();
		shader->use();
		
		glDrawElements(drawType, indices.count(), GL_UNSIGNED_INT, nullptr);
	}

	QM::matrix<4, 4, float> Asset::modelMatrix()
	{
		QM::matrix<4, 4> Mscale;
		Mscale.set(1, 1, scale.get(1));
		Mscale.set(2, 2, scale.get(2));
		Mscale.set(3, 3, scale.get(3));
		Mscale.set(4, 4, 1);
		
		QM::matrix<4, 4> Mrotation;

		float angle = 2.0f * (float)acos(rotation.r);
		
		if (angle != 0)
		{
			QM::vector<3> axis = QM::vector<3>((float)rotation.x, (float)rotation.y, (float)rotation.z).normalise();
			float C = cos(angle);
			float S = sin(angle);


			Mrotation.set(1, 1, C + axis.get(1) * axis.get(1) * (1 - C));
			Mrotation.set(1, 2, axis.get(1) * axis.get(2) * (1 - C) - axis.get(3) * S);
			Mrotation.set(1, 3, axis.get(1) * axis.get(3) * (1 - C) + axis.get(2) * S);
			Mrotation.set(2, 1, axis.get(2) * axis.get(1) * (1 - C) + axis.get(3) * S);
			Mrotation.set(2, 2, C + axis.get(2) * axis.get(2) * (1 - C));
			Mrotation.set(2, 3, axis.get(2) * axis.get(3) * (1 - C) - axis.get(1) * S);
			Mrotation.set(3, 1, axis.get(3) * axis.get(1) * (1 - C) - axis.get(2) * S);
			Mrotation.set(3, 2, axis.get(3) * axis.get(2) * (1 - C) + axis.get(1) * S);
			Mrotation.set(3, 3, C + axis.get(3) * axis.get(3) * (1 - C));
			Mrotation.set(4, 4, 1);
		}
		else
			Mrotation = QM::identity<4>();

		QM::matrix<4, 4> Mtranslation = QM::identity<4>();
		Mtranslation.set(1, 4, position.get(1));
		Mtranslation.set(2, 4, position.get(2));
		Mtranslation.set(3, 4, position.get(3));

		return Mtranslation * Mrotation * Mscale;
	}

	void Asset::setScale(float SF)
	{
		setScale(SF, SF, SF);
	}

	void Asset::setScale(float x, float y, float z)
	{
		scale = QM::vector<3>(x, y, z);
	}

	void Asset::setScale(QM::vector<3> SF)
	{
		scale = SF;
	}

	QM::vector<3> Asset::getScale()
	{
		return scale;
	}

	void Asset::changeScale(float SF)
	{
		scale = SF * scale;
	}

	void Asset::changeScale(float x, float y, float z)
	{
		scale.set(1, scale.get(1) * x);
		scale.set(2, scale.get(2) * y);
		scale.set(3, scale.get(3) * z);
	}

	void Asset::changeScale(QM::vector<3> SF)
	{
		scale.set(1, scale.get(1) * SF.get(1));
		scale.set(2, scale.get(2) * SF.get(2));
		scale.set(3, scale.get(3) * SF.get(3));
	}

	void Asset::setRotation(double xAngle, double yAngle, double zAngle)
	{
		rotation = QM::rotation(xAngle, yAngle, zAngle);
	}

	void Asset::setRotation(float angle, QM::vector<3> axis)
	{
		rotation = QM::rotation(angle, axis);
	}

	void Asset::setRotation(QM::Quaternion Q)
	{//may need more checks
		if (abs(Q.magnitude()-1) < 0.01)
			rotation = Q;
	}

	QM::Quaternion Asset::getRotation()
	{
		return rotation;
	}

	void Asset::changeRotation(double xAngle, double yAngle, double zAngle)
	{
		auto rot2 = QM::rotation(xAngle, yAngle, zAngle);
		rotation = rot2 * rotation;
	}

	void Asset::changeRotation(float angle, QM::vector<3> axis)
	{
		auto rot2 = QM::rotation(angle, axis);
		rotation = rot2 * rotation;
	}

	void Asset::changeRotation(QM::Quaternion Q)
	{
		if (abs(Q.magnitude() - 1) < 0.01)
			rotation = Q * rotation;
	}

	void Asset::setPosition(float x, float y, float z)
	{
		position = QM::vector<3>(x, y, z);
	}

	void Asset::setPosition(QM::vector<3> R)
	{
		position = R;
	}

	QM::vector<3> Asset::getPosition()
	{
		return position;
	}

	void Asset::move(float x, float y, float z)
	{
		position += QM::vector<3>(x, y, z);
	}

	void Asset::move(QM::vector<3> R)
	{
		position += R;
	}

}