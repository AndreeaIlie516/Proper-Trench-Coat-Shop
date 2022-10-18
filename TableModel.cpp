#include "TableModel.h"
#include <qcolor.h>
#include <qbrush.h>


TableModel::TableModel(Repository& repo) : repo{ repo }
{
}
int TableModel::rowCount(const QModelIndex& parent) const
{
	return repo.size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	TrenchCoat trenchCoat = repo[row];
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0:
			return QString::number(trenchCoat.getID());
		case 1:
			return QString::number(trenchCoat.getSize());
		case 2:
			return QString::fromStdString(trenchCoat.getColour());
		case 3:
			return QString::number(trenchCoat.getPrice());
		case 4:
			return QString::number(trenchCoat.getQuantity());
		case 5:
			return QString::fromStdString(trenchCoat.getPhotographyUrl());
		}
	}
	else if (role == Qt::BackgroundRole) {
		if (row & 1)
			return QBrush(QColor(224, 224, 224));
	}
	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		switch (section) {
		case 0:
			return QString("ID");
		case 1:
			return QString("Size");
		case 2:
			return QString("Colour");
		case 3:
			return QString("Price");
		case 4:
			return QString("Quantity");
		case 5:
			return QString("PhotographyUrl");
		default:
			break;
		}
	return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
	if (index.column() == 1 or index.column() == 2 or index.column() == 3 or index.column() == 4 or index.column() == 5)
		return Qt::ItemIsEditable | Qt::ItemIsEnabled;

	return Qt::ItemFlags();
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	int row = index.row();
	int column = index.column();

	TrenchCoat& trenchCoat = this->repo[row];

	if (role == Qt::EditRole || role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 1:
			trenchCoat.setSize(value.toInt());
			break;
		case 3:
			trenchCoat.setPrice(value.toDouble());
			break;
		case 4:
			trenchCoat.setQuantity(value.toInt());
			break;
		default:
			break;
		}
	}

	emit dataChanged(index, index);

	return true;
}
