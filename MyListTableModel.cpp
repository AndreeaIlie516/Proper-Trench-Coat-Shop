#include "MyListTableModel.h"

void MyListTableModel::addInBasket(const int& ID)
{
	service.addTrenchCoatToBasketListByID(ID);
	insertRows(service.userGetBasketList().size(), 1);

}



void MyListTableModel::changeRepositoryFileName(std::string fileName, std::string extension)
{

	int firstLength = service.userGetBasketList().size();
	service.changeRepositoryFileName(fileName, extension);
	int secondLength = service.userGetBasketList().size();
	if (firstLength - secondLength > 0)
		removeRows(secondLength, firstLength - secondLength);
	else
		insertRows(firstLength, secondLength - firstLength);
}


bool MyListTableModel::insertRows(int position, int rows, const QModelIndex& index)
{
	beginInsertRows(QModelIndex(), position, position + rows - 1);
	endInsertRows();
	return true;
}

bool MyListTableModel::removeRows(int position, int rows, const QModelIndex& index)
{
	beginRemoveRows(QModelIndex(), position, position + rows - 1);
	endRemoveRows();
	return true;
}

int MyListTableModel::rowCount(const QModelIndex& parent) const
{
	return service.userGetBasketList().size();
}

int MyListTableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant MyListTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	TrenchCoat trenchCoat = service.userGetBasketList()[row];
	
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(std::to_string(trenchCoat.getID()));
		case 1:
			return QString::fromStdString(std::to_string(trenchCoat.getSize()));
		case 2:
			return QString::fromStdString(trenchCoat.getColour());
		case 3:
			return QString::fromStdString(std::to_string(trenchCoat.getPrice()));
		case 4:
			return QString::fromStdString(std::to_string(trenchCoat.getQuantity()));
		case 5:
			return QString::fromStdString(trenchCoat.getPhotographyUrl());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section) {
			case 0:
				return QString{ "Id" };
			case 1:
				return QString{ "Size" };
			case 2:
				return QString{ "Colour" };
			case 3:
				return QString{ "Price" };
			case 4:
				return QString{ "Quantity" };
			case 5:
				return QString{ "PhotographyUrl" };
			default:
				break;
			}
		}
	}
	return QVariant();
}