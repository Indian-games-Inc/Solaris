#include "Actor/Item/Item.h"
#include "Data/ItemData.h"


AItem::AItem()
{
	ItemData.Name = GetName();
	ItemData.ID = GetName();

	if (const auto Body = GetBody(); IsValid(Body))
	{
		ItemData.Model = DuplicateObject<UMeshComponent>(Body, nullptr);
	}
}

FItemData AItem::Pick()
{
	Destroy();
	return this->ItemData;
}

FString AItem::HintMessage() const
{
	return ItemData.Name;
}
